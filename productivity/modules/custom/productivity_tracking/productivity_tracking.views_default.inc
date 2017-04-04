<?php
/**
 * @file
 * productivity_tracking.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function productivity_tracking_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'new_tracking';
  $view->description = 'Find and manage content.';
  $view->tag = 'admin';
  $view->base_table = 'node';
  $view->human_name = 'New Tracking';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Content';
  $handler->display->display_options['css_class'] = 'admin-views-view';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'timestamp' => 'title',
    'changed' => 'changed',
    'field_project' => 'field_project',
    'field_date' => 'field_date',
    'edit_node' => 'edit_node',
    'delete_node' => 'edit_node',
    'field_day_type' => 'field_day_type',
    'field_employee' => 'field_employee',
    'field_track_hours' => 'field_track_hours',
    'field_work_length' => 'field_work_length',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_project' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '&emsp;',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_day_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_employee' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_track_hours' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_work_length' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/time-tracking">Add time tracking</a>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change author',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change value',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
      'postpone_processing' => 0,
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Stick',
      'postpone_processing' => 0,
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unstick',
      'postpone_processing' => 0,
    ),
    'action::node_promote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Promote to front page',
      'postpone_processing' => 0,
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Publish',
      'postpone_processing' => 0,
    ),
    'action::node_unpromote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Demote from front page',
      'postpone_processing' => 0,
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unpublish',
      'postpone_processing' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Has new content */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'history';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Field: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Track log */
  $handler->display->display_options['fields']['field_track_log']['id'] = 'field_track_log';
  $handler->display->display_options['fields']['field_track_log']['table'] = 'field_data_field_track_log';
  $handler->display->display_options['fields']['field_track_log']['field'] = 'field_track_log';
  $handler->display->display_options['fields']['field_track_log']['click_sort_column'] = 'field_date_value';
  $handler->display->display_options['fields']['field_track_log']['settings'] = array(
    'view_mode' => 'default',
  );
  $handler->display->display_options['fields']['field_track_log']['delta_offset'] = '0';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  /* Field: Content: Time Estimate */
  $handler->display->display_options['fields']['field_time_estimate']['id'] = 'field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['table'] = 'field_data_field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['field'] = 'field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Field: Issue ID */
  $handler->display->display_options['fields']['field_issue_id']['id'] = 'field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['table'] = 'field_data_field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['field'] = 'field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Field: Issue Status */
  $handler->display->display_options['fields']['field_issue_status']['id'] = 'field_issue_status';
  $handler->display->display_options['fields']['field_issue_status']['table'] = 'field_data_field_issue_status';
  $handler->display->display_options['fields']['field_issue_status']['field'] = 'field_issue_status';
  $handler->display->display_options['fields']['field_issue_status']['settings'] = array(
    'link' => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'time_tracking' => 'time_tracking',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  /* Filter criterion: Field: Project (field_project) */
  $handler->display->display_options['filters']['field_project_target_id']['id'] = 'field_project_target_id';
  $handler->display->display_options['filters']['field_project_target_id']['table'] = 'field_data_field_project';
  $handler->display->display_options['filters']['field_project_target_id']['field'] = 'field_project_target_id';
  $handler->display->display_options['filters']['field_project_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id']['expose']['operator_id'] = 'field_project_target_id_op';
  $handler->display->display_options['filters']['field_project_target_id']['expose']['label'] = 'Project (field_project)';
  $handler->display->display_options['filters']['field_project_target_id']['expose']['operator'] = 'field_project_target_id_op';
  $handler->display->display_options['filters']['field_project_target_id']['expose']['identifier'] = 'field_project_target_id';
  $handler->display->display_options['filters']['field_project_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Day type (field_day_type) */
  $handler->display->display_options['filters']['field_day_type_value']['id'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['table'] = 'field_data_field_day_type';
  $handler->display->display_options['filters']['field_day_type_value']['field'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_day_type_value']['expose']['operator_id'] = 'field_day_type_value_op';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['label'] = 'Day type (field_day_type)';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['operator'] = 'field_day_type_value_op';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['identifier'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Field: Project (field_project) (reference filter) */
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['id'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['table'] = 'field_data_field_project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['field'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator_id'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['label'] = 'Project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['identifier'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_display'] = 'entity_ref_list:entityreference_1';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_arguments'] = 'project';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'tracking' => 'tracking',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Track log (field_track_log:field_date_value) */
  $handler->display->display_options['filters']['field_track_log_field_date_value']['id'] = 'field_track_log_field_date_value';
  $handler->display->display_options['filters']['field_track_log_field_date_value']['table'] = 'field_data_field_track_log';
  $handler->display->display_options['filters']['field_track_log_field_date_value']['field'] = 'field_track_log_field_date_value';
  $handler->display->display_options['filters']['field_track_log_field_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_track_log_field_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_track_log_field_date_value']['expose']['operator_id'] = 'field_track_log_field_date_value_op';
  $handler->display->display_options['filters']['field_track_log_field_date_value']['expose']['label'] = 'date';
  $handler->display->display_options['filters']['field_track_log_field_date_value']['expose']['operator'] = 'field_track_log_field_date_value_op';
  $handler->display->display_options['filters']['field_track_log_field_date_value']['expose']['identifier'] = 'field_track_log_field_date_value';
  $handler->display->display_options['filters']['field_track_log_field_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Content: Github Project ID (field_github_project_id) */
  $handler->display->display_options['filters']['field_github_project_id_value']['id'] = 'field_github_project_id_value';
  $handler->display->display_options['filters']['field_github_project_id_value']['table'] = 'field_data_field_github_project_id';
  $handler->display->display_options['filters']['field_github_project_id_value']['field'] = 'field_github_project_id_value';
  $handler->display->display_options['filters']['field_github_project_id_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['operator_id'] = 'field_github_project_id_value_op';
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['label'] = 'Repo';
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['operator'] = 'field_github_project_id_value_op';
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['identifier'] = 'field_github_project_id_value';
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Field: Project (field_project) (reference filter) */
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['id'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['table'] = 'field_data_field_project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['field'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator_id'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['label'] = 'Project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['identifier'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_display'] = 'entity_ref_list:entityreference_1';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_arguments'] = 'project';
  /* Filter criterion: Field: Employee (field_employee) (reference filter) */
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['id'] = 'field_employee_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['table'] = 'field_data_field_employee';
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['field'] = 'field_employee_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['expose']['operator_id'] = 'field_employee_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['expose']['label'] = 'Employee';
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['expose']['operator'] = 'field_employee_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['expose']['identifier'] = 'field_employee_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_employee_target_id_entityreference_filter']['reference_display'] = 'user_list:entityreference_1';
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['path'] = 'admin/content/new-tracking';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'New Tracking';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Page 2 */
  $handler = $view->new_display('page', 'Page 2', 'page_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change author',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change value',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
      'postpone_processing' => 0,
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Stick',
      'postpone_processing' => 0,
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unstick',
      'postpone_processing' => 0,
    ),
    'action::node_promote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Promote to front page',
      'postpone_processing' => 0,
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Publish',
      'postpone_processing' => 0,
    ),
    'action::node_unpromote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Demote from front page',
      'postpone_processing' => 0,
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unpublish',
      'postpone_processing' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Has new content */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'history';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Field: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  /* Field: Content: Time Estimate */
  $handler->display->display_options['fields']['field_time_estimate']['id'] = 'field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['table'] = 'field_data_field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['field'] = 'field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Field: Issue ID */
  $handler->display->display_options['fields']['field_issue_id']['id'] = 'field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['table'] = 'field_data_field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['field'] = 'field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Field: Issue Status */
  $handler->display->display_options['fields']['field_issue_status']['id'] = 'field_issue_status';
  $handler->display->display_options['fields']['field_issue_status']['table'] = 'field_data_field_issue_status';
  $handler->display->display_options['fields']['field_issue_status']['field'] = 'field_issue_status';
  $handler->display->display_options['fields']['field_issue_status']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'tracking' => 'tracking',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Day type (field_day_type) */
  $handler->display->display_options['filters']['field_day_type_value']['id'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['table'] = 'field_data_field_day_type';
  $handler->display->display_options['filters']['field_day_type_value']['field'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['group'] = 1;
  $handler->display->display_options['filters']['field_day_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_day_type_value']['expose']['operator_id'] = 'field_day_type_value_op';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['label'] = 'Day type (field_day_type)';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['operator'] = 'field_day_type_value_op';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['identifier'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Field: Project (field_project) (reference filter) */
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['id'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['table'] = 'field_data_field_project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['field'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['group'] = 1;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator_id'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['label'] = 'Project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['identifier'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_display'] = 'entity_ref_list:entityreference_1';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_arguments'] = 'project';
  /* Filter criterion: Content: Github Project ID (field_github_project_id) */
  $handler->display->display_options['filters']['field_github_project_id_value']['id'] = 'field_github_project_id_value';
  $handler->display->display_options['filters']['field_github_project_id_value']['table'] = 'field_data_field_github_project_id';
  $handler->display->display_options['filters']['field_github_project_id_value']['field'] = 'field_github_project_id_value';
  $handler->display->display_options['filters']['field_github_project_id_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['operator_id'] = 'field_github_project_id_value_op';
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['label'] = 'Github Repo';
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['operator'] = 'field_github_project_id_value_op';
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['identifier'] = 'field_github_project_id_value';
  $handler->display->display_options['filters']['field_github_project_id_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['path'] = 'admin/content/new-tracking-simple';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Tracking simple';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['new_tracking'] = $view;

  return $export;
}
