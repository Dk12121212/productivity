<?php
/**
 * @file
 * Triggering the process of updating the time tracking entities to update the
 * spent time in the issues in case the total hours does not match.
 */
// Get the last node id.
$repo_id = drush_get_option('repo_id', 'Gizra/unio');
$project_nid = drush_get_option('project', '33709');


$query = db_select('field_data_field_issues_logs', 'il');
$query
  ->leftJoin('field_data_field_project', 'p', 'il.entity_id = p.entity_id');

$result = $query
  ->fields('il', array('field_issues_logs_field_issue_label_value', 'entity_id', 'field_issues_logs_id'))
  ->condition('il.entity_type', 'node')
  ->condition('il.bundle', 'time_tracking')
  ->condition('p.field_project_target_id', $project_nid)
  ->condition('il.field_issues_logs_field_github_issue_target_id', '');

$result = $query->execute();

while ($record = $result->fetchAssoc()) {
  $re = '/#([0-9]*).*/';
  $str = $record['field_issues_logs_field_issue_label_value'];
  preg_match_all($re, $str, $matches);
  if (!isset($matches[1][0])) {
    print("no match for : {$record['field_issues_logs_field_issue_label_value']} \n");
    continue;
  }

  $issue_id = $matches[1][0];
  print("Processing : {$record['field_issues_logs_field_issue_label_value']} match:{$matches[1][0]} \n");

  // List of issues for a project nid.
  $query_issue = db_select('node', 'n');
  $query_issue
    ->join('field_data_field_github_project_id', 'gpi', 'n.nid = gpi.entity_id');
  $query_issue
    ->leftJoin('field_data_field_project', 'p', 'n.nid = p.entity_id');
  $query_issue
    ->leftJoin('field_data_field_issue_id', 'i', 'n.nid = i.entity_id');
  $query_issue
    ->leftJoin('field_data_field_employee', 'e', 'n.nid = e.entity_id');


  $query_issue
    ->fields('n', array('nid', 'title'))
    ->fields('i', array('field_issue_id_value'))
    ->fields('gpi', array('field_github_project_id_value'))
    ->fields('p', array('field_project_target_id'))
    ->fields('e', array('field_employee_target_id'))
    ->condition('status', NODE_PUBLISHED)
    ->condition('type', 'github_issue')
    ->condition('gpi.field_github_project_id_value', $repo_id)
    ->condition('p.field_project_target_id', $project_nid)
    ->condition('i.field_issue_id_value', $issue_id)
    ->range(0, 1);


  $result_issue = $query_issue->execute();

  if ($record_issue = $result_issue->fetchAssoc()) {
    print("found : nid:{$record_issue['nid']} #{$record_issue['field_issue_id_value']} : {$record_issue['title']} uid:{$record_issue['field_employee_target_id']} \n");
    $node = node_load($record['entity_id']);
    print("loading track  : nid: {$record['entity_id']} looking for mfid {$record['field_issues_logs_id']} \n");

    // Look for MF to update.
    foreach ($node->field_issues_logs['und'] as $key => $mf) {
      if ($mf['id'] == $record['field_issues_logs_id']) {
        print("saving track : nid:{$record['entity_id']}  \n");
        $node->field_issues_logs['und'][$key]['field_github_issue']['und'][0]['target_id'] = $record_issue['nid'];
        node_save($node);
        break;
      }
    }
  }
  else {
    print("cant find issue #{$issue_id} \n");
  }
}