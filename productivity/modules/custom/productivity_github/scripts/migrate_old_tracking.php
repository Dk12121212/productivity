<?php
/**
 * @file
 * Triggering the process of updating the time tracking entities to update the
 * spent time in the issues in case the total hours does not match.
 */

// 33709 => unio 6.5
$project_nid = '33709';



$issues = productivity_issue_get_all($project_nid, 'issue');

foreach ($issues as $old_issue) {
  // Get or create tracking node.
  $wrapper = get_new_tracking($old_issue);


}


$tracking = productivity_issue_diagram_tracking($project_nid);
$prs_and_issues = productivity_issue_diagram_graph_connections($project_nid);


/**
 * Get the issue by ID
 */
function get_new_tracking($issues) {
//
//      'uid' => $record['uid'],
//      'title' => $record['title'],
//      'estimate' => $record['field_time_estimate_value'],
//      'issue_id' => $record['field_issue_id_value'],
//      'type' => $record['field_github_content_type_value'],
//      'related_issue' => $record['field_issue_reference_target_id'],
//      'related_issue_gh_id' => $record['ri_field_issue_id_value'],
//      'actual' => $record['field_actual_hours_value'],
//      'github_repo' => $record['field_github_project_id_value'],
//      'employee' => $record['field_employee_value'],
  // List of issues for a project nid.
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'tracking')
    ->fieldCondition('field_issue_id', 'value', $issues['issue_id'])
    ->fieldCondition('field_github_project_id', 'value', $issues['github_repo'])
    ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
    ->range(0, 1)
    ->execute();

  if (!empty($result['node'])) {
    $nid = reset($result['node']);
    $node =  node_load($nid->nid);
    print("Found existing new tracking {$node->title} \n");
    $wrapper = entity_metadata_wrapper('node', $node);
  }
  else {
    $title = "Tracking for issue {$issues['github_repo']}/{$issues['issue_id']}";
    $values = array(
      'title' => $title,
      'type' => 'tracking',
      'uid' => $issues['uid'],
      'status' => 1,
    );
    print("Creating new $title \n");
    $node = entity_create('node', $values);
    $wrapper = entity_metadata_wrapper('node', $node);
    $wrapper->field_project->set($issues['field_project_target_id']);
    $wrapper->field_time_estimate->set($issues['field_time_estimate_value']);
    $wrapper->field_issue_id->set($issues['issue_id']);
    $wrapper->field_github_project_id->set($issues['github_repo']);

    $wrapper->save();

  }
  return $wrapper;
}

/**
 * Get entity reference connections.
 */
function productivity_issue_get_all($project_nid = FALSE, $issue_type = FALSE) {

  // List of issues for a project nid.
  $query = db_select('node', 'n');


  $query
    ->join('field_data_field_project', 'p', 'n.nid = p.entity_id');
  $query
    ->leftJoin('field_data_field_time_estimate', 'e', 'n.nid = e.entity_id');
  $query
    ->leftJoin('field_data_field_issue_id', 'i', 'n.nid = i.entity_id');
  $query
    ->leftJoin('field_data_field_github_content_type', 'ct', 'n.nid = ct.entity_id');
  $query
    ->leftJoin('field_data_field_issue_reference', 'ir', 'n.nid = ir.entity_id');
  // Field on GH issue.
  $query
    ->leftJoin('field_data_field_actual_hours', 'ah', 'n.nid = ah.entity_id');
  $query
    ->leftJoin('field_data_field_github_project_id', 'gpi', 'n.nid = gpi.entity_id');
  $query
    ->leftJoin('field_data_field_issue_id', 'ri', 'ir.field_issue_reference_target_id = ri.entity_id');
  $query
    ->leftJoin('field_data_field_employee', 'fe', 'n.nid = fe.entity_id');

  $query
    ->fields('n', array('title', 'nid', 'uid'))
    ->fields('e', array('field_time_estimate_value'))
    ->fields('i', array('field_issue_id_value'))
    ->fields('ct', array('field_github_content_type_value'))
    ->fields('ir', array('field_issue_reference_target_id'))
    ->fields('ri', array('ri' => 'field_issue_id_value'))
    ->fields('ah', array('field_actual_hours_value'))
    ->fields('gpi', array('field_github_project_id_value'))
    ->fields('fe', array('field_employee_value'));
    ->fields('p', array('field_project_target_id'));

    if ($project_nid) {
      $query
        ->condition('p.field_project_target_id', $project_nid);
    }

    $query
      ->condition('type', 'github_issue')
    ->condition('status', NODE_PUBLISHED);

  if ($issue_type) {
    $query->condition('field_github_content_type_value', $issue_type);
  }
  $result = $query->execute();

  // Create an associative array:
  $issues = array();
  while($record = $result->fetchAssoc()) {
    $issues[$record['nid']] = array(
      'link' =>  l($record['nid'], 'node/' . $record['nid']),
      'nid' =>  $record['nid'],
      'uid' => $record['uid'],
      'title' => $record['title'],
      'estimate' => $record['field_time_estimate_value'],
      'issue_id' => $record['field_issue_id_value'],
      'type' => $record['field_github_content_type_value'],
      'related_issue' => $record['field_issue_reference_target_id'],
      'related_issue_gh_id' => $record['ri_field_issue_id_value'],
      'actual' => $record['field_actual_hours_value'],
      'github_repo' => $record['field_github_project_id_value'],
      'employee' => $record['field_employee_value'],
      'project' => $record['field_project_target_id'],
    );
  }

  return $issues;
}