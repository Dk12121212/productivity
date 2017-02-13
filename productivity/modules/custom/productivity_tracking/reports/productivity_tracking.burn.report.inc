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

  // Add a link to go to the project selection.
  $go_back_link = '<div class="back-link">' . l(t('Back to project'), "node/{$project_node->nid}") . '</div>';

  return $go_back_link . theme('table', $table);
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
  $main_track_id = FALSE;
  $last_nid = FALSE;
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

    // Issue data.
    $repo_id = $track_record['field_github_project_id_value'];
    $estimate = $track_record['field_time_estimate_value'];
    $issue_id = $track_record['field_issue_id_value'];
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
      // Set total to previous row.
      if ($main_track_id) {
        $table['rows']["nid_" . $last_nid]['data']['overtime'] = $totals[$last_nid] - $table['rows']["nid_" . $last_nid]['data']['estimate'];
        $table['rows']["nid_" . $last_nid]['data']['actual'] = $totals[$last_nid];

        // Total row.
        $total_row['data']['estimate'] += $table['rows']["nid_" . $last_nid]['data']['estimate'];
        $total_row['data']['actual'] += $totals[$last_nid];
        $total_row['data']['overtime'] = $total_row['data']['actual'] - $total_row['data']['estimate'];
      }
      // Create a new issue row.
      $main_track_id = $track_id;
      $issue_row = array(
        'class' => '',
        'data' => array(
          'issue_id' => $issue_link,
          'estimate' => $estimate,
          'actual' => 0,
          'developer' => l('Link to node', "node/$nid/edit", array('attributes' => array('target' => '_blank'))),
          'type' => '',
          'overtime' => 0,
          // TODO: Followup - closing/opening issue should change this.
          'status' => 'WIP',
        ),
      );
      $table['rows']["nid_" . $nid] = $issue_row;
      $totals[$nid] = floatval($pr_time);
      $last_nid = $nid;
    }
    else {
      // Get total actual.
      $totals[$nid] += floatval($pr_time);
    }
    // Add sub rows for each PR.
    $pr_row = array(
      'class' => '',
      'data' => array(
        'issue_id' => "pr-$pr_link",
        'estimate' => '',
        'actual' => $pr_time,
        'developer' => $pr_developer,
        'type' => $pr_work_type,
        'overtime' => '-',
        // TODO: Followup - closing/opening issue should change this.
        'status' => 'PR',
      ),
    );

    // Add to the table
    $table['rows'][$track_id] = $pr_row;
  }

  // Add total row.
  array_unshift($table['rows'], $total_row);

  // Final calculations.
  $side = 'odd';
  foreach($table['rows'] as &$row) {
    $data = &$row['data'];


    // Invert on each issue.
    if ($data['status'] == 'WIP') {
      $row['class'] = 'info';
    }
    else {
      $row['class'] = 'warning';
    }

    // Add class only to overtime cells.
    if ($data['overtime'] != '-') {
      $data['overtime'] = array(
        'class' => ($data['actual'] > $data['estimate'] ? 'cell-bad-' : 'cell-ok-') . $side,
        'data' => $data['overtime'],
      );
    }
  }

  return $table;
}