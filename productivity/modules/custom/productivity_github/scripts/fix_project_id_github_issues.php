<?php
/**
 * @file
 * Updating issues with no project reference, but with gh project id.
 */


// List of issues for a project nid.
$query = db_select('node', 'n');
$query
  ->join('field_data_field_github_project_id', 'gpi', 'n.nid = gpi.entity_id');
$query
  ->leftJoin('field_data_field_project', 'p', 'n.nid = p.entity_id');


$query
  ->fields('n', array('nid'))
  ->fields('gpi', array('field_github_project_id_value'))
  ->fields('p', array('field_project_target_id'))
  ->condition('type', 'github_issue')
  ->condition('p.field_project_target_id', NULL);

$result = $query->execute();

$no_project_found = array();
while($record = $result->fetchAssoc()) {
  print("Processing : {$record['nid']} \n");

  $repository_info = new stdClass();
  $repository_info->owner = new stdClass();
  // Break Gizra/Unio into both.
  $names = explode('/',  $record['field_github_project_id_value']);
  $repository_info->name = $names[1];
  $repository_info->owner->login = $names[0];
  $repository_info->full_name = $record['field_github_project_id_value'];
  // Get project nid.
  $pnid = productivity_github_get_project_by_repository($repository_info);

  if ($pnid) {
    $wrapper = entity_metadata_wrapper('node', $record['nid']);
    $wrapper->field_project->set($pnid);
    print("Found project $pnid  for {$repository_info->name}\n");
    $wrapper->save();
  }
  else {
    if (!isset($no_project_found[$repository_info->name])) {
      $no_project_found[$repository_info->name] = 0;
    }
    $no_project_found[$repository_info->name] += 1;
    print("no project found for {$repository_info->name}\n");
  }
}
print "Missing projects:\n";
print_r($no_project_found);

exit;