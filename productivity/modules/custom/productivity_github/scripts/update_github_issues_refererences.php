<?php
/**
 * @file
 * Triggering the process of updating the time tracking entities to update the
 * isseu refrences.
 */
// Get the last node id.
$nid = drush_get_option('nid', 0);
$gh_id = drush_get_option('gh_id', 0);
// Get the number of nodes to be processed.
$batch = drush_get_option('batch', 50);
// Get allowed memory limit.
$memory_limit = drush_get_option('memory_limit', 500);


$i = 0;

$base_query = new EntityFieldQuery();
$base_query
  ->entityCondition('entity_type', 'node')
  ->propertyCondition('type', 'github_issue')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->propertyOrderBy('nid', 'ASC');


if ($gh_id) {
  $base_query->fieldCondition('field_github_project_id', 'value', $gh_id);
}


if ($nid) {
  $base_query->propertyCondition('nid', $nid, '>');
}

$query_count = clone $base_query;
$count = $query_count->count()->execute();

while ($i < $count) {
  $query = clone $base_query;
  $result = $query
    ->range($i, $batch)
    ->execute();

  if (empty($result['node'])) {
    return;
  }
  $ids = array_keys($result['node']);
  $nodes = node_load_multiple($ids);

  foreach ($nodes as $node) {
    $wrapper = entity_metadata_wrapper('node', $node);
    print "processing Node: {$wrapper->getIdentifier()}\n";
    if ($wrapper->field_project->value() && $wrapper->body->value()) {
      productivity_github_save_references_issue(
        $wrapper,
        $wrapper->body->value->value(),
        $wrapper->field_github_project_id->value(),
        $wrapper->field_project->getIdentifier());

      $wrapper->save();
      print "Saving Node: {$wrapper->getIdentifier()}\n";
    }
    else {
      print "Bypass Node: {$wrapper->getIdentifier()} no project ref or body.\n";
    }
  }

  $i += count($nodes);
  $nid = end($ids);
  $params = array(
    '@start' => reset($ids),
    '@end' => end($ids),
    '@iterator' => $i,
    '@max' => $count,
  );
  drush_print(dt('Process entities from id @start to id @end. Batch state: @iterator/@max', $params));
}
