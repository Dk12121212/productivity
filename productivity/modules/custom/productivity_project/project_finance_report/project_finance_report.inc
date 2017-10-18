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
  drupal_add_js(drupal_get_path('module', 'productivity_project_finance') . '/project_finance_report/project_finance_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_project_finance') . '/project_finance_report/project_finance_report.css');
  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
  drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

  $variables = array();

  $variables['projects'] = productivity_project_get_project_by_date($month, $year);
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';

  drupal_add_js(array(
    'monthly_report' => array(
      'base_url' => $base_url,
    )
  ), 'setting');

  $summary_project_combined = [];
  $summary_project_combined[$year] = [];
  $summary_project_combined[$year][$month] = [];
  $summary_project = [];
  foreach ($variables['projects'] as $nid => $project_name) {
    // Get all project tracking.
    $work_type = FALSE;
    $result = productivity_project_finance_get_tracking($nid, $work_type, $year, $month);
    $types = [];
    // Read result a sum total.
    while ($record = $result->fetchAssoc()) {
      $time = $record['field_track_log_field_time_spent_value'];
      $type = $record['field_track_log_field_issue_type_value'];

      if (!$time) {
        continue;
      }
      // Save all types in use.
      if (!isset($types['types'][$type])) {
        $types['types'][$type] = $type;
      }

      // Create skeleton
      if (!isset($summary_project['types'][$type])) {
        $summary_project['types'][$type] = [];
      }
      $summary_project['types'][$type]['rate'] = $record['rate'];
      $summary_project['types'][$type]['currency'] = $record['currency'];
      $summary_project['types'][$type]['typename'] = $record['typename'];

      // Summarize hours by user.
      productivity_finance_reset_value($summary_project['types'][$type]['amount'], $time);
    }
    // Set project name.
    $summary_project['name'] = $project_name;
    $summary_project_combined[$year][$month][$nid] = $summary_project;
  }


  // Build display table.
  // Build table.
   $header = ['Name', 'Type', 'Total', 'Rate', 'currency', 'type'];
   foreach ($summary_project_combined as $year_name => $month_data) {
     $rows = [];
     foreach ($month_data as $project_nid => $projects) {
       foreach ($projects as $nid => $project_data) {
         foreach ($project_data['types'] as $type_name => $type_total) {
           $rows[] =
             [$project_data['name']] +
             [1 => $type_name] +
             [2 => $type_total['amount']] +
             [3 => $type_total['rate']] +
             [4 => $type_total['currency']]   +
             [5 => $type_total['typename']];
         }
       }
     }
     $variables['tables'][$year_name] = theme('table', array(
       'header' => $header,
       'rows' => $rows
     ));

   }
dpm($variables);
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