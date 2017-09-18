<?php
/**
 * @file
 * productivity_project.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function productivity_project_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_triage|node|project|form';
  $field_group->group_name = 'group_triage';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Project triage filters',
    'weight' => '8',
    'children' => array(
      0 => 'field_github_repository_name',
      1 => 'field_gh_milestone',
      2 => 'field_close_tracking',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-triage field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_triage|node|project|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Project triage filters');

  return $field_groups;
}
