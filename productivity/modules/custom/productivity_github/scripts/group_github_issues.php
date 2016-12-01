<?php
/**
 * @file
 * Triggering the process of updating the time tracking entities to update the
 * spent time in the issues in case the total hours does not match.
 */
// Get the last node id.
$repo_id = drush_get_option('repo', 'Gizra/unio');


// List of issues for a project nid.
$query = db_select('node', 'n');
$query
  ->join('field_data_field_project', 'p', 'n.nid = p.entity_id');
$query
  ->leftJoin('field_data_field_issue_id', 'i', 'n.nid = i.entity_id');
$query
  ->leftJoin('field_data_field_github_content_type', 'ct', 'n.nid = ct.entity_id');
$query
  ->leftJoin('field_data_field_issue_reference', 'ir', 'n.nid = ir.entity_id');
$query
  ->leftJoin('field_data_field_github_project_id', 'gpi', 'n.nid = gpi.entity_id');
$query
  ->leftJoin('field_data_field_employee', 'eid', 'n.nid = eid.entity_id');

//$query->groupBy('gpi.field_github_project_id_value');
//$query->groupBy('i.field_issue_id_value');


$query
  ->fields('n', array('title', 'nid'))
  ->fields('i', array('field_issue_id_value'))
  ->fields('ct', array('field_github_content_type_value'))
  ->fields('ir', array('field_issue_reference_target_id'))
  ->fields('gpi', array('field_github_project_id_value'))
  ->fields('p', array('field_project_target_id'))
  ->fields('eid', array('field_employee_target_id'))
  ->condition('ct.field_github_content_type_value', 'pull_request')
  ->condition('gpi.field_github_project_id_value', $repo_id)
  ->condition('type', 'github_issue')
  ->orderBy('field_github_project_id_value', 'DESC')
  ->orderBy('field_issue_id_value');

$result = $query->execute();

$base_record = $result->fetchAssoc();
$node_base = node_load($base_record['nid']);
print("{$base_record['field_github_project_id_value']}/{$base_record['field_issue_id_value']}\n");

while($record = $result->fetchAssoc()) {
  if (($base_record['field_github_project_id_value'] == $record['field_github_project_id_value']) &&
    ($base_record['field_issue_id_value'] == $record['field_issue_id_value']) &&
    ($base_record['field_employee_target_id'] == $record['field_employee_target_id'])) {
    print('match->');
    // Merge and delete.
    $node_to_merge = node_load($record['nid']);
    $fields_to_merge = array(
      'value' => 'field_push_date',
      'target_id ' => 'field_issue_reference',
    );

    foreach($fields_to_merge as $key => $field) {
      if (!isset($node_to_merge->{$field}['und'])) {
        continue;
      }
      foreach($node_to_merge->{$field}['und'] as $field_to_merge) {
        // Check value if not already set.
        $value_to_save = TRUE;
        foreach ($node_base->{$field}['und'] as $field_combined) {
          // Compare values.
          if ($field_combined[$key] == $field_to_merge[$key]) {
            $value_to_save = FALSE;
            print("Value {$field_combined[$key]} already exist. \n");
            break;
          }
        }
        // Save only new values.
        if ($value_to_save) {
          $node_base->{$field}['und'][] = $field_to_merge;
        }
      }
    }
    node_save($node_base);
    $node_to_merge->status = 0;
    node_save($node_to_merge);
    print("Node {$node_to_merge->nid} merged into  {$node_base->nid} \n");
  }
  else {
    $base_record = $record;
    $node_base = node_load($base_record['nid']);
    print('newBaseNode->');
  }
  print("{$record['field_github_project_id_value']}/{$record['field_issue_id_value']}\n");

}