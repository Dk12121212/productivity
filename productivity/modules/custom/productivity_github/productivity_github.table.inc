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
function productivity_github_time_tracking_issue_table($project_node) {
  $project_wrapper = entity_metadata_wrapper('node', $project_node);
  $graph = productivity_issue_diagram_graph_normalized($project_node->nid);

  if (empty($graph)) {
    return t('No issues found for project @project.', array('@project' => $project_wrapper->label()));
  }

  // Header.
  $table = array(
    'header' => array(
      t('Issue ID'),
      t('Issue name'),
      t('Time estimate'),
      t('Actual time'),
      t('Overtime'),
      t('Status'),
    ),
    'attributes' => array('class' => array('per-issue-table')),
  );

  $total_row = array(
    'data' => array(
      'placeholder' => '',
      'name' => array('data' => t('Total')),
      'estimate' => 0,
      'actual' => 0,
      'overtime' => 0,
      'status' => '',
    ),
  );

  // Prepare table for tracking data.
  foreach($graph as $repo_id => $repo) {
    foreach ($repo as $github_issue_id => $issue) {

      $estimate = $issue['estimated'];
      $actual = 0;
      $nid = $issue['nid'];

      // Get total actual.
      foreach ($issue['prs'] as $pr) {
        foreach ($pr['tracks'] as $track) {
          $actual += floatval($track['time']);
        }
      }

      $issue_link = "https://github.com/$repo_id/issues/$github_issue_id";


      $issue_row = array(
        'class' => '',
        'data' => array(
          'issue_id' => l("$repo_id/$github_issue_id", $issue_link, array('attributes' => array('target' => '_blank'))),
          'issue_name' =>  l($issue['title'], "node/$nid/edit"),
          'estimate' => $estimate,
          'actual' => $actual,
          'overtime' => $actual - $estimate,
          // TODO: Followup - closing/opening issue should change this.
          'status' => 'WIP',
        ),
      );

      // Total row.
      $total_row['data']['estimate'] += $issue_row['data']['estimate'];
      $total_row['data']['actual'] += $issue_row['data']['actual'];
      $total_row['data']['overtime'] += $issue_row['data']['overtime'];

      // Add to the table
      $table['rows'][$nid] = $issue_row;
    }
  }

  // Add total row.
  array_unshift($table['rows'], $total_row);

  // Final calculations.
  $side = 'odd';
  foreach($table['rows'] as &$row) {
    $data = &$row['data'];
    $side = ($side == 'odd') ? 'even' : 'odd';

    // Add class only to overtime cells.
    $data['overtime'] = array(
      'class' => ($data['actual'] > $data['estimate'] ? 'cell-bad-' : 'cell-ok-') . $side,
      'data' => $data['overtime'],
    );
  }

  return $table;
}

/**
 * Render the time tracking per issue table.
 *
 * @param int $project_node_id
 *   Project to process.
 * @param bool $show_link
 *  Whether to show or hide the link to the tracking list.
 * @return string Rendered HTML.
 * Rendered HTML.
 */
function productivity_github_time_display_tracking_issue_table($project_node = FALSE) {

  drupal_set_title(t('@project issue tracking table', array('@project' => $project_node->title)));

  $table = productivity_github_time_tracking_issue_table($project_node);
  if (!is_array($table)) {
    // Table returned an error message.
    return $table;
  }

  // Add a link to go to the project selection.
  $go_back_link = '<div class="back-link">' . l(t('Back to project'), 'tracking/per-issue') . '</div>';

  return  $go_back_link . theme('table', $table);
}