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

  dpm( $variables['projects']);
  $summary_project_combined = [];
  $summary_project_combined[$year] = [];
  $summary_project_combined[$year][$month] = [];
  $summary_project = [];
  foreach ($variables['projects'] as $nid => $project_name) {
    // Get all project tracking.
    $work_type = FALSE;
    $result = productivity_tracking_get_tracking($nid, $work_type, $year, $month);
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
      if (!isset($summary_project['types'])) {
        $summary_project['types'] = [];
      }

      // Summarize hours by user.
      productivity_finance_reset_value($summary_project['types'][$type], $time);
      // Total per month.
//      productivity_time_tracking_reset_value($sum_month[$track_year][$track_month], $time);
      // Total per year.
//      productivity_time_tracking_reset_value($summary_year[$track_year], $time);
    }
    // Set project name.
    $summary_project['name'] = $project_name;
    $summary_project_combined[$year][$month][$nid] = $summary_project;
  }


  // Build display table.
  // Build table.
   $header = ['Type', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 'Sum'];
  dpm($summary_project_combined);
   foreach ($summary_project_combined as $year => $month_data) {
     $rows = [];
     foreach ($month_data as $project_nid => $project_data) {
       foreach ($project_data['types'] as $type_name => $type_total) {
         $rows[] = [$project_data['name']] + ':' + $type_name + ':' + $type_total;
       }
     }
//     $rows[] = ['Sum'] + $sum_month[$year] + ['sum' => $summary_year[$year]];
//     // Save one table per year.
     $variables['tables'][$year] = theme('table', array(
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