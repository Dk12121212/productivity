<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; display tracking table for issues.
 * Render callback;  Bidder page.
 */
function productivity_project_finance_report_table($year, $month) {
  global $base_url;
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_project') . '/project_finance_report/project_finance_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_project') . '/project_finance_report/project_finance_report.css');
  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
  drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

  $variables = array();

//  $variables['projects'] = productivity_project_get_project_by_date($month, $year);
  $variables['no_result'] = FALSE;
  $variables['message'] = '';
  $variables['month'] = $month;
  $variables['year'] = $year;

  drupal_add_js(array(
    'monthly_report' => array(
      'base_url' => $base_url,
    )
  ), 'setting');


  $result = productivity_project_finance_get_tracking(FALSE, FALSE, $year, $month);
  // Read result and sum total.
  while ($record = $result->fetchAssoc()) {
    $nid = $record['field_project_target_id'];
    $time = $record['field_track_log_field_time_spent_value'];
    $type = $record['field_track_log_field_issue_type_value'];

    if (!$time || !$type) {
      continue;
    }

    // Create skeleton
    if (!isset($summary_project[$nid]['types'][$type])) {
      $summary_project[$nid]['types'][$type] = [];
    }
    $summary_project[$nid]['types'][$type]['rate'] = $record['rate'];
    $summary_project[$nid]['types'][$type]['currency'] = $record['currency'];
    $summary_project[$nid]['types'][$type]['typename'] = $record['typename'];

    // Summarize hours by dev type.
    productivity_finance_reset_value($summary_project[$nid]['types'][$type]['amount'], $time);

  }


  // Build display table.
  // Build table.
  $header = [
    'Name',
    'Type',
    'Rate (AVG)',
    'Currency',
    'Project type',
    'Scope/Done',
    'Total this month',
    'Earn this month'
  ];
  // Currency normalize.
  $currency = [];
  $currency['USD']['rate'] = CurrencyExchangerFixedRates::load('USD', 'ILS');
  $currency['USD']['obj'] = currency_load('USD');
  $currency['EUR']['rate'] = CurrencyExchangerFixedRates::load('EUR', 'ILS');
  $currency['EUR']['obj'] = currency_load('EUR');
  $currency['ILS']['rate'] = 1;
  $currency['ILS']['obj'] = currency_load('ILS');

  $variables['rate_str'] = "(\${$currency['USD']['rate']} €{$currency['EUR']['rate']})";

  $total_row_ils = 0;
  $total_hours_billed = 0;
  $total_hours_billed_partial = 0;
  $total_projects = 0;

  // Iterates over projects.
  foreach ($summary_project as $nid => $project_data) {
    $total_projects++;
    $wrapper = entity_metadata_wrapper('node', $nid);
    $project_type = $wrapper->field_type->value();
    $link = l($wrapper->label(), 'node/' . $nid);
    $scope = productivity_project_get_total_scope($wrapper, FALSE, TRUE);

    // If no rates.
    if (isset($project_data['types'])) {
      // Iterates over dev types.
      foreach ($project_data['types'] as $type_name => $type_total) {
        // Get total of hours done since begining of project ins same dev type.
        $all_time_totals = productivity_tracking_get_tracking_total($nid, $type_name);
        $all_time_totals = $all_time_totals[0]->total_done;

        // Estimate the gain.
        // For fix look at the total budget, and divide
        // by actual.
        $total_earn_ils = 0;

        $total_earn = 0;
        $avg_per_hour = 0;
        if ($type_total['rate']) {
          // Type is fix, mean the budget is closed.
          if ($project_type == 'fix') {
            $budget = $scope[$type_name] * $type_total['rate'];
            // Take the bigger number. This can be improved by adding waited
            // data, taken from estimate vs done.
            $divider = $scope[$type_name] > $all_time_totals ? $scope[$type_name] : $all_time_totals;
            $avg_per_hour = $budget / $divider;
            $total_earn = $type_total['amount'] * $avg_per_hour;

            if ($avg_per_hour < $type_total['rate']) {
              $total_hours_billed_partial += $type_total['amount'];
            }
          }

          // For T&M we simply multiply the hours (except non-billable)
          if ($project_type == 'T&M') {
            $total_earn = $type_total['amount'] * $type_total['rate'];
          }

          // Check we have USD or ILS or EUR.
          if (!is_object($currency[$type_total['currency']]['obj'])) {
            drupal_set_message("Project $link:($nid) has an undefined currency {$type_total['currency']} ");
          }
          else {
            // Formatting currency.
            $total_earn_ils = $total_earn * $currency[$type_total['currency']]['rate'];
            $total_earn = $currency[$type_total['currency']]['obj']->format(number_format($total_earn, 0, '.', ''));
            $total_row_ils += $total_earn_ils;
            $total_earn_ils = $currency['ILS']['obj']->format(number_format($total_earn_ils, 0, '.', ''));
          }

          // Summarize hours payed.
          if ($type_total['rate'] != 0.00) {
            $total_hours_billed += $type_total['amount'];
          }
        }


        $avg_per_hour = number_format($avg_per_hour);
        $all_time_totals = number_format($all_time_totals);
        $rows[] =
          [$link] +
          [1 => $type_name] +
          [3 => "{$type_total['rate']} ($avg_per_hour)"] +
          [4 => $type_total['currency']] +
          [6 => $project_type] +
          [7 => isset($scope[$type_name]) ? "{$scope[$type_name]}/{$all_time_totals}" : 0] +
          [2 => $type_total['amount']] +
          [8 => "$total_earn  ($total_earn_ils)"];
      }
    }
  }

  $total_hours = productivity_tracking_get_tracking_totals($month, $year, FALSE);
  $not_billed = $total_hours['sum']['month'] - $total_hours_billed;
  $not_billed_percent = number_format(100 / $total_hours['sum']['month']  * $not_billed);

  $variables['total_ils'] = $currency['ILS']['obj']->format(number_format($total_row_ils, 0, '.', ''));
  $variables['total_hours'] = number_format($total_hours_billed) . ' (' . number_format($total_hours_billed_partial) . ')';
  $variables['total_hours_not_billed'] = "$not_billed ($not_billed_percent%)" ;
  $variables['total_projects'] = $total_projects;
  $variables['table'] = theme('table', array(
    'header' => $header,
    'rows' => $rows
  ));

  return theme('productivity_project_finance_report', $variables);
}

/**
 * Reset and add up total to array key.
 */
function productivity_finance_reset_value(&$element, $value){
  if (!isset($element)) {
    $element = 0;
  }
  $element += $value;
}

/**
 * Get entity reference connections.
 *
 * @param $project_nid
 *  The project nid.
 *
 * @param $work_type
 *  qa, dev, management or other type.
 *
 * @return
 *   SelectQuery::execute();
 */
function productivity_project_finance_get_tracking($project_nid = FALSE, $work_type = FALSE, $year = FALSE, $month = FALSE) {
  $dates = [];
  $dates['start']['month'] = $month;
  $dates['start']['year'] = $year;
  // List of issues for a project nid.
  $query = productivity_tracking_get_tracking_base_query($project_nid, $work_type, $dates);
  //field_data_field_table_rate

  // Get project rate for this type.
  $query
    ->leftjoin("field_data_field_table_rate",
      'rate',
      'p.field_project_target_id = rate.entity_id AND rate.field_table_rate_field_issue_type_value = type.field_issue_type_value');

  $query->addField('rate', 'field_table_rate_field_rate_amount', 'rate');
  $query->addField('rate', 'field_table_rate_field_rate_currency', 'currency');
  $query->addField('rate', 'field_table_rate_field_issue_type_value', 'typename');
  $query
    ->orderBy('gpi.field_github_project_id_value')
    ->orderBy('i.field_issue_id_value');

  $result = $query->execute();
  return $result;
}