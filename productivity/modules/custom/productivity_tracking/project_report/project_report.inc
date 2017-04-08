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
  drupal_add_js(drupal_get_path('module', 'productivity_time_tracking') . '/project_report/project_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_time_tracking') . '/project_report/project_report.css');
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
  $result = productivity_tracking_get_tracking($node->nid);
  $summary_user = [];
  $summary_year = [];
  $sum_month = [];
  $user_names = [];
  $types = [];
  // Read result a sum total.
  while ($record = $result->fetchAssoc()) {
    $track_year = date("Y", strtotime($record['field_track_log_field_date_value']));
    $track_month = date("m", strtotime($record['field_track_log_field_date_value']));
    $uid = $record['field_track_log_field_employee_target_id'];
    $time = $record['field_track_log_field_time_spent_value'];
    $type = $record['field_track_log_field_issue_type_value'];

    if(!$time || !$uid) {
      continue;
    }

    if (!isset($user_names[$uid])) {
      $user = user_load($uid);
      $user_names[$uid] = $user->name;
    }
    // Save all types in use.
    if (!isset($types[$type])) {
      $types[$type] = $type;
    }

    // Create skeleton
    if (!isset($summary_user[$track_year][$user_names[$uid]])) {
      $summary_user[$track_year][$user_names[$uid]] = [];
      for ($i=1; $i <= 12; $i++) {
        $key = str_pad($i, 2, '0', STR_PAD_LEFT);
        $summary_user[$track_year][$user_names[$uid]][$key] = 0;
      }
    }

    // Create skeleton
    if (!isset($sum_month[$track_year])) {
      $summary_year[$track_year] = 0;
      for ($i=1; $i <= 12; $i++) {
        $key = str_pad($i, 2, '0', STR_PAD_LEFT);
        $sum_month[$track_year][$key] = 0;
      }
    }

    // Summarize hours by user.
    productivity_time_tracking_reset_value($summary_user[$track_year][$user_names[$uid]][$track_month], $time);
    // Total per month.
    productivity_time_tracking_reset_value($sum_month[$track_year][$track_month], $time);
    // Total per year.
    productivity_time_tracking_reset_value($summary_year[$track_year], $time);
  }
  // Build display table.
  // Build table.
   $header = ['Type', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 'Sum'];
   foreach ($summary_user as $year => $user_data) {
     $rows = [];
     foreach ($user_data as $username => $month_data) {
       $rows[] = [$username] + $month_data;
     }
     $rows[] = ['Sum'] + $sum_month[$year] + ['sum' => $summary_year[$year]];
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