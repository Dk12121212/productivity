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
    'gh_labels' => array(
      'name' => 'GH Labels',
      'machine_name' => 'gh_labels',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'gh_milstones' => array(
      'name' => 'GH Milstones',
      'machine_name' => 'gh_milstones',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
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
