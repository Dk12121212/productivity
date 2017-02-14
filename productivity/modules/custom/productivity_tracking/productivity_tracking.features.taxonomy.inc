<?php
/**
 * @file
 * productivity_tracking.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function productivity_tracking_taxonomy_default_vocabularies() {
  return array(
    'issue_status' => array(
      'name' => 'Issue Status',
      'machine_name' => 'issue_status',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
