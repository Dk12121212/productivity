<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */
define('PRODUCTIVITY_GITHUB_ISSUE_OPEN_STATUS', 'WIP');
define('PRODUCTIVITY_GITHUB_ISSUE_CLOSED_STATUS', 'Done');

/**
 * Menu callback; display tracking table for issues.
 */
function productivity_time_tracking_issue_table_callback($node = FALSE, $year = FALSE, $month = FALSE, $estimated_based = FALSE) {
  $estimated_based = $estimated_based == 'false' ? FALSE : TRUE;
  return productivity_time_tracking_issue_table($node, $year, $month, $estimated_based);
}

/**
 * Render callback;  Bidder page.
 */
function productivity_time_tracking_issue_table($node = FALSE, $year = FALSE, $month = FALSE, $estimated_based = FALSE) {
  global $base_url;
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_tracking') . '/monthly_report/monthly_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_tracking') . '/monthly_report/monthly_report.css');
  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
  drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

  // Add datepicker lib.
  drupal_add_js("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/js/bootstrap-datepicker.min.js", array('type' => 'external'));
  drupal_add_css("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/css/bootstrap-datepicker.min.css", array('type' => 'external'));

  $variables = array();
  $variables['year'] = !empty($year) ? $year : date('Y');
  $variables['month']= !empty($month) ? $month : date('m', strtotime("-1 month"));



  if ($year == 'all'){
    $variables['date'] = t('All time');
  }
  elseif ($month == 'all'){
    $variables['date'] = t('Year @year', array('@year' => $year));
  }
  else {
    $variables['date'] = date("F Y", strtotime("$year-$month-01"));
  }


  $variables['projects'] = productivity_project_get_all_projects();
  $variables['current_project_id'] = 0;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';

  drupal_add_js(array('monthly_report' => array(
    'base_url' => $base_url,
    'year' => $variables['year'],
    'month' => $variables['month'],
    'estimate' => $estimated_based,
    )
  ), 'setting');


  // No project given.
  if (!$node) {
    return theme('productivity_time_tracking_monthly_report', $variables);
  }
  $nid = $node->nid;
  drupal_add_js(array('monthly_report' => array(
    'project_id' => $nid,
    )
  ), 'setting');

  $wrapper = entity_metadata_wrapper('node', $node);

  $variables['project_title'] = $wrapper->label();
  $variables['account'] = $wrapper->field_account->label();

//  $nodes_old = productivity_github_get_project_github_issues_query($node->nid, $variables['year'], $variables['month']);
  $tracking = productivity_tracking_get_tracking($node->nid, FALSE, $variables['year'], $variables['month']);

  $issues_table = array();

  // Get all issues for the project.
  if (!empty($count = $tracking->rowCount())) {
    $issues_table = productivity_time_tracking_create_issues_table($tracking, $node->nid);
  }
  else {
    $variables['no_result'] = TRUE;
    $variables['message'] = t('No work done this month.');
  }

  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');

  // Create tables for the template.
  $variables['tables'] = array();
  $variables['total_types'] = array();
  $variables['grand_total'] = 0;
  $header = array(
    'Issue',
    'Label',
    'Date',
    'Time',
    'Amount'
  );
  // Build table.
  foreach ($issues_table as $table_name => $table) {
    $variables['table_titles'][$table_name] = _productivity_time_tracking_get_table_title($table_name, $node, $table['label']);
    $variables['total_per_types'][$table_name] = 0;
    $variables['total_per_hours_types'][$table_name] = 0;

    foreach ($table['issues'] as $index => $issue) {
      $rows[$index]['label'] = $issue['issue_num'] == '#' ? 'N/A' : l($issue['issue_num'], $issue['gh_url'], array(
        'absolute' => TRUE,
        'attributes' => array('target' => '_blank'),
      ));

      $rows[$index]['gitHub_issue_num'] = l($issue['label'], 'node/' . $issue['nid'] . '/edit', array('attributes' => array('target' => '_blank')));

      // Fix date according to variable.
      // This is to normalize report to a single year.
      if ($year = variable_get("productivity_fix_date_project_$nid")) {
        $date = strtotime($issue['date']);
        if (date('Y', $date) != $year) {
          // Add one year.
          $new_date = $date + (24*60*60*365);
          while ($new_date > time()) {
            $new_date -= 60*60*24*10;
          }
          $issue['date'] = date("Y/m/d", $new_date);
        }
      }

      $rows[$index]['date'] = $issue['date'];
      $rows[$index]['time'] = $issue['time'];
      $rows[$index]['amount'] = $issue['issue_amount'] . ' ' . $issue['issue_currency'];
      $variables['total_per_types'][$table_name] += $issue['issue_amount'];
      $variables['total_per_hours_types'][$table_name] += $issue['time'];
      $variables['total_currency_per_types'][$table_name] = $issue['issue_currency'];
      $variables['grand_total'] += $issue['issue_amount'];
    }
    $variables['tables'][$table_name] = theme('table', array(
      'header' => $header,
      'rows' => $rows
    ));
    $rows = array();
  }

  // Get all the projects for project input
  $variables['current_project_id'] = $node->nid;

  $variables['table'] = theme('productivity_time_tracking_monthly_report_table', $variables);

  return theme('productivity_time_tracking_monthly_report', $variables);
}

/**
 * Create a matrix of all the issues from GitHub nodes,
 * And the url project.
 *
 * @param $nodes
 *  All the nodes return from the query.
 *
 * @return array
 *  Matrix of all the issues, and the URL project
 */
function productivity_time_tracking_create_issues_table($tracking, $project_nid) {
  $issues_table = [];
  while($track_record = $tracking->fetchAssoc()) {

    // Bypass stubs.
    if ($track_record['field_track_log_field_time_spent_value'] == 0) {
      continue;
    }

    $date = date('Y/m/d', strtotime($track_record['field_track_log_field_date_value']));

    // Check if there is already a table with that type.
    $type = $track_record['field_track_log_field_issue_type_value'];
    if (empty($issues_table[$type])) {
      $issues_table[$type] = [];
    }
    // Push the issue details to the type table.
    if (!isset($rate[$type])) {
      $rate[$type] = productivity_project_get_rate($project_nid, $type);
    }
    /// The table length of every type.
    $issue_id = '#' . $track_record['field_issue_id_value'];
    $gh_id = $track_record['field_github_project_id_value'];

    // Replace this with human readable type.
    $issues_table[$type]['label'] = $rate[$type]['label'];
    $issues_table[$type]['issues'][] = array(
      'nid' => $track_record['nid'],
      'issue_num' => $issue_id,
      'gh_url' => 'https://github.com/' . $gh_id . '/issues/' . $issue_id,
      'label' => $track_record['field_track_log_field_issue_label_value'],
      'date' => $date,
      'time' => $track_record['field_track_log_field_time_spent_value'],
      'issue_amount' => $track_record['field_track_log_field_time_spent_value'] *  $rate[$type]['amount'],
      'issue_currency' =>  $rate[$type]['currency']
    );
  }

  return $issues_table;
}

/**
 * Check for a project override to the table title.
 * These are set in the project's node field_work_type.
 * Function designed to run once per page load (can be optimized
 * if all the overrides are needed).
 *
 * @param $table_machine_name
 * @param $node
 * @param string $default_name
 * @return string
 */
function _productivity_time_tracking_get_table_title($table_machine_name, $node, $default_name = '') {
  // Find all of the overrides.
  $overrides = array();
  $wrapper = entity_metadata_wrapper('node', $node);
  foreach($wrapper->field_table_rate as $multifield) {
    $machine_name = $multifield->field_issue_type->value();
    $override = $multifield->field_issue_type_label->value();

    $overrides[$machine_name] = $override;
  }

  return empty($overrides[$table_machine_name]) ?  $default_name : $overrides[$table_machine_name];
}
