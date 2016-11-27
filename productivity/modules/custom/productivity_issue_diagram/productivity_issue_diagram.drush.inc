<?php

/**
 * Implements hook_drush_command().
 */
function productivity_issue_diagram_drush_command() {
  $items['productivity_issue_diagram'] = array(
    'description' => 'Generate a graph of the entities and fields.',
    'aliases' => array('pid'),
    'options' => array(
      'project' => 'Project nid ',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'core' => array('7+'),
    'drupal dependencies' => array('field'),
    'examples' => array(
      'drush pid | dot -Gratio=0.7 -Eminlen=2 -T png -o ./test.png' => 'Generate the Entity-Relationship graph for the current site and export it has a PNG image.',
      'drush pid --project=14525 | dot -Gratio=0.7 -Eminlen=2 -T png -o ./test.png' => 'Generate the Entity-Relationship graph for a entity type site including fields and export it has a PNG image.',
    ),
  );
  return $items;
}

function drush_productivity_issue_diagram() {
  $project = drush_get_option('project', FALSE);
  $graph =  productivity_issue_diagram_graph($project);
  echo productivity_issue_diagram_graph_generate($graph);
}
