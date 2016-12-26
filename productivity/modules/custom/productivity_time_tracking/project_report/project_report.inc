<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; display tracking table for issues.
 * Render callback;  Bidder page.
 */
function productivity_time_tracking_project_table($node = FALSE, $year = 2016) {
  global $base_url;
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_time_tracking') . '/project_report/project_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_time_tracking') . '/project_report/project_report.css');
  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
  drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

  // Add datepicker lib.
  drupal_add_js("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/js/bootstrap-datepicker.min.js", array('type' => 'external'));
  drupal_add_css("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/css/bootstrap-datepicker.min.css", array('type' => 'external'));

  $variables = array();
  $variables['year'] = !empty($year) ? $year : date('Y');
  $variables['date'] = date("F Y", strtotime("$year-01-01"));


  $variables['projects'] = productivity_project_get_all_projects();
  $variables['current_project_id'] = $node->nid;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';

  drupal_add_js(array('monthly_report' => array(
    'base_url' => $base_url,
    'year' => $variables['year'],
    'month' => $variables['month'],
    )
  ), 'setting');


  $result = productivity_project_get_tracking($node->nid);
  $summary = [];
  $user_names = [];
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
    // Summarize hours.
    productivity_time_tracking_reset_value($summary[$track_year][$track_month][$type][$user_names[$uid]], $time);
    productivity_time_tracking_reset_value($summary[$track_year][$track_month][$type]['sum'], $time);
    productivity_time_tracking_reset_value($summary[$track_year][$track_month]['sum'], $time);
    productivity_time_tracking_reset_value($summary[$track_year]['sum'][$type], $time);
    productivity_time_tracking_reset_value($summary[$track_year]['sum']['total'], $time);
    productivity_time_tracking_reset_value($summary['sum'], $time);

  }
  dpm($summary);
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