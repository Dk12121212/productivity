<?php
/**
 * @file
 * Code for the Productivity burn report.
 */


/**
 * Menu callback;  Render the time tracking per issue table.
 *
 * @param int $project_node
 *   Project to process.
 *
 * @return string
 *  Rendered table.
 */
function productivity_tracking_burn_report_callback($project_node) {

  drupal_set_title(t('@project issue tracking table', array('@project' => $project_node->title)));

  $table = productivity_tracking_burn_report($project_node);
  if (!is_array($table)) {
    // Table returned an error message.
    return $table;
  }

  $variables = [];
  $variables['backlink'] = l(t('Back to project'), "node/{$project_node->nid}");
  $variables['table'] = theme('table', $table);

  return theme('tracking_burn_table', $variables);
}

/**
 * Display tracking table for issues.
 */
function productivity_tracking_burn_report($project_node) {
  $project_wrapper = entity_metadata_wrapper('node', $project_node);

  // TODO: for QA and management create separate tables.
  $tracking = productivity_tracking_get_tracking($project_node->nid);

  if (empty($count = $tracking->rowCount())) {
    return t('No issues found for project @project.', array('@project' => $project_wrapper->label()));
  }
  else {
    print "Rendering $count tracking.";
  }

  // Header.
  $table = array(
    'header' => array(
      t('Issue ID'),
      t('Time estimate'),
      t('Actual time'),
      t('Developer'),
      t('type'),
      t('Overtime'),
      t('Status'),
    ),
    'attributes' => array('class' => array('per-issue-table')),
  );

  $total_row = array(
    'data' => array(
      'issue_id' => 'TOTALs',
      'estimate' => '',
      'actual' => '',
      'developer' => '',
      'type' => '',
      'overtime' => '',
      'status' => 'TOTAL',
    )
  );

  $totals = [];

  // Prepare table for tracking data.
  while($track_record = $tracking->fetchAssoc()) {
    // Pr data.
    $pr_time = $track_record['field_track_log_field_time_spent_value'];
    $pr_gh_id = $track_record['field_track_log_field_issue_id_value'];
    $pr_title = $track_record['field_track_log_field_issue_label_value'];
    $pr_work_type = $track_record['field_track_log_field_issue_type_value'];
    $pr_developer = $track_record['field_track_log_field_github_username_value'];
    $pr_developer_uid = $track_record['field_track_log_field_employee_target_id'];
    $pr_date = $track_record['field_track_log_field_date_value'];
    $track_id = $track_record['field_track_log_id'];
    $pr_status = $track_record['pr_status_name'];

    // Issue data.
    $repo_id = $track_record['field_github_project_id_value'];
    $estimate = $track_record['field_time_estimate_value'];
    $issue_id = $track_record['field_issue_id_value'];
    $issue_status = $track_record['name'];
    $nid = $track_record['nid'];


    $pr_url = "https://github.com/$repo_id/issues/$pr_gh_id";
    $pr_link = l("$repo_id/$pr_gh_id", $pr_url, array(
      'attributes' => array(
        'title' => $pr_title,
        'target' => '_blank',
      ),
    ));

    $issue_url = "https://github.com/$repo_id/issues/$issue_id";
    $issue_link = l("$repo_id/$issue_id", $issue_url, array('attributes' => array('target' => '_blank')));

    // First row of issue.
    if (!isset($totals[$nid])) {
      // Create a new issue row.
      $issue_row = array(
        'class' => 'info',
        'data' => array(
          'issue_id' => $issue_link,
          'estimate' => $estimate,
          'actual' => $pr_time,
          'developer' => l('Link to node', "node/$nid/edit", array('attributes' => array('target' => '_blank'))),
          'type' => '',
          'overtime' =>  array(
            'class' => ($pr_time - $estimate > 0 ? 'cell-bad-odd' : 'cell-ok-even'),
            'data' => $pr_time - $estimate,
          ),
          'status' =>  array(
            'class' => ($issue_status == 'closed' ? 'cell-bad-even' : 'cell-ok-even'),
            'data' => $issue_status,
          ),
        ),
      );
      // SAve row to table.
      $table['rows']["nid_" . $nid] = $issue_row;

      // Init first total value.
      $totals[$nid] = floatval($pr_time);
      // Sum estimate.
      $total_row['data']['estimate'] += $estimate;
    }
    else {
      // Add up total work time.
      $totals[$nid] += floatval($pr_time);

      // Update actual.
      $table['rows']["nid_" . $nid]['data']['actual'] = $totals[$nid];

      // Update overtime.
      $overtime = $totals[$nid] - $table['rows']["nid_" . $nid]['data']['estimate'];

      $table['rows']["nid_" . $nid]['data']['overtime'] =  array(
        'class' => ($overtime > 0 ? 'cell-bad-odd' : 'cell-ok-even'),
        'data' => $overtime,
      );

    }
    // Update sum row.
    $total_row['data']['actual'] += $pr_time;
    $total_row['data']['overtime'] = $total_row['data']['actual'] - $total_row['data']['estimate'];

    // Add sub rows for each PR.
    $pr_row = array(
      'class' => 'warning',
      'data' => array(
        'issue_id' => "pr-$pr_link",
        'estimate' => '',
        'actual' => $pr_time,
        'developer' => $pr_developer,
        'type' => $pr_work_type,
        'overtime' => '-',
        'status' =>  array(
          'class' => ($pr_status == 'closed' ? 'cell-bad-odd' : 'cell-ok-even'),
          'data' => $pr_status,
        ),
      ),
    );

    // Add to the table
    $table['rows'][$track_id] = $pr_row;
  }

  // Add total row to top of the table.
  array_unshift($table['rows'], $total_row);

  return $table;
}