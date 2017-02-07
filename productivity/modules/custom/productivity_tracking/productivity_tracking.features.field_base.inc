<?php
/**
 * @file
 * productivity_tracking.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function productivity_tracking_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_last_push'.
  $field_bases['field_last_push'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_last_push',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'date',
    'settings' => array(
      'cache_count' => 4,
      'cache_enabled' => 0,
      'granularity' => array(
        'day' => 'day',
        'hour' => 'hour',
        'minute' => 'minute',
        'month' => 'month',
        'second' => 0,
        'year' => 'year',
      ),
      'profile2_private' => FALSE,
      'timezone_db' => '',
      'todate' => '',
      'tz_handling' => 'none',
    ),
    'translatable' => 0,
    'type' => 'datetime',
  );

  // Exported field_base: 'field_track_log'.
  $field_bases['field_track_log'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_track_log',
    'indexes' => array(
      'field_employee_target_id' => array(
        0 => 'field_employee_target_id',
      ),
      'field_github_username_format' => array(
        0 => 'field_github_username_format',
      ),
      'field_issue_label_format' => array(
        0 => 'field_issue_label_format',
      ),
      'field_issue_type_value' => array(
        0 => 'field_issue_type_value',
      ),
      'id' => array(
        0 => 'id',
      ),
    ),
    'locked' => 0,
    'module' => 'multifield',
    'settings' => array(
      'entity_translation_sync' => array(
        0 => 'id',
      ),
      'hide_blank_items' => 1,
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'multifield',
  );

  return $field_bases;
}
