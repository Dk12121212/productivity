<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; display tracking table for issues.
 * Render callback;  Bidder page.
 */
function productivity_time_tracking_project_table($node = FALSE) {
  global $base_url;
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_tracking') . '/project_report/project_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_tracking') . '/project_report/project_report.css');
  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
  drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

  $variables = array();

  $variables['projects'] = productivity_project_get_all_projects();
  $variables['current_project_id'] = $node->nid;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';

  drupal_add_js(array(
    'monthly_report' => array(
      'base_url' => $base_url,
    )
  ), 'setting');

  // Get all project tracking.
  $result = productivity_project_get_tracking($node->nid);
  $summary = [];
  $user_names = [];
  $types = [];
  // Read result a sum total.
  while ($record = $result->fetchAssoc()) {
    $track_year = date("Y", strtotime($record['field_work_date_value']));
    $track_month = date("m", strtotime($record['field_work_date_value']));
    $type = $record['field_issues_logs_field_issue_type_value'];
    $time = $record['field_issues_logs_field_time_spent_value'];
    $uid = $record['field_employee_target_id'];

    if (!isset($user_names[$uid])) {
      $user = user_load($uid);
      $user_names[$uid] = $user->name;
    }
    // Save all types in use.
    if (!isset($types[$type])) {
      $types[$type] = $type;
    }
    // Summarize hours.
    productivity_time_tracking_reset_value($summary[$track_year][$track_month][$type][$user_names[$uid]], $time);
    productivity_time_tracking_reset_value($summary[$track_year][$track_month][$type]['sum'], $time);
    productivity_time_tracking_reset_value($summary[$track_year][$track_month]['sum'], $time);
    productivity_time_tracking_reset_value($summary[$track_year]['sum'][$type], $time);
    productivity_time_tracking_reset_value($summary[$track_year]['sum']['total'], $time);
    productivity_time_tracking_reset_value($summary['sum'], $time);
  }
  // Build display table.
  $header = ['Type'];
  $rows = [];
  // Build table.
  foreach ($summary as $year => $year_data) {
    if ($year == 'sum') {
      continue;
    }
    foreach ($year_data as $month => $month_data) {
      if ($month == 'sum') {
        continue;
      }
      $header[] = $month;
      // Save type columns, month by month.
      foreach ($types as $type) {
        if (!isset($rows[$type])) {
          $rows[$type]['title'] = $type;
        }
        $rows[$type][$month] = isset($month_data[$type]['sum']) ? $month_data[$type]['sum'] : 0;
      }
      $rows['sum']['title'] = 'Sum';
      $rows['sum'][$month] = $year_data[$month]['sum'];
    }

    // Save row sums
    $header[] = 'Sum';
    foreach ($types as $type) {
      $rows[$type]['sum'] = isset($year_data['sum'][$type]) ? $year_data['sum'][$type] : 0;
    }
    // Full year sum.
    $rows['sum']['sum'] = $year_data['sum']['total'];

    // Save one table per year.
    $variables['tables'][$year] = theme('table', array(
      'header' => $header,
      'rows' => $rows
    ));
  }

  return theme('productivity_time_tracking_project_report', $variables);
}

/**
 * Reset and add up total to array key.
 */
function productivity_time_tracking_reset_value(&$element, $value){
  if (!isset($element)) {
    $element = 0;
  }
  $element += $value;
}