<?php
/**
 * @file
 * productivity_user.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function productivity_user_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'user_by_profile';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'User by profile';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'stakeholder' => 'stakeholder',
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['user_by_profile'] = $view;

  $view = new view();
  $view->name = 'user_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'User list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: User: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'users';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['user_list'] = $view;

  $view = new view();
  $view->name = 'work_sessions';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Work sessions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Work sessions';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_employee' => 'field_employee',
    'field_session_date_2' => 'field_session_date_2',
    'field_session_date' => 'field_session_date',
    'field_session_date_1' => 'field_session_date_1',
    'field_session_date_3' => 'field_session_date_3',
    'field_session_date_4' => 'field_session_date_4',
    'expression' => 'expression',
    'field_project' => 'field_project',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_employee' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_session_date_2' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_session_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_session_date_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_session_date_3' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_session_date_4' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'expression' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_project' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/work-session">Add work session</a>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_employee_target_id']['id'] = 'field_employee_target_id';
  $handler->display->display_options['relationships']['field_employee_target_id']['table'] = 'field_data_field_employee';
  $handler->display->display_options['relationships']['field_employee_target_id']['field'] = 'field_employee_target_id';
  $handler->display->display_options['relationships']['field_employee_target_id']['required'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          'work_session::field_employee' => 'work_session::field_employee',
          'work_session::field_project' => 'work_session::field_project',
          'work_session::field_session_date' => 'work_session::field_session_date',
        ),
      ),
    ),
  );
  /* Field: Field: Employee */
  $handler->display->display_options['fields']['field_employee']['id'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['table'] = 'field_data_field_employee';
  $handler->display->display_options['fields']['field_employee']['field'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date_2']['id'] = 'field_session_date_2';
  $handler->display->display_options['fields']['field_session_date_2']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date_2']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date_2']['label'] = 'Date';
  $handler->display->display_options['fields']['field_session_date_2']['settings'] = array(
    'format_type' => 'date',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date']['id'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date']['label'] = 'From raw';
  $handler->display->display_options['fields']['field_session_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_session_date']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_session_date']['alter']['text'] = '[field_session_date-value]';
  $handler->display->display_options['fields']['field_session_date']['type'] = 'date_plain';
  $handler->display->display_options['fields']['field_session_date']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date_1']['id'] = 'field_session_date_1';
  $handler->display->display_options['fields']['field_session_date_1']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date_1']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date_1']['label'] = 'Until raw';
  $handler->display->display_options['fields']['field_session_date_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_session_date_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_session_date_1']['alter']['text'] = '[field_session_date_1-value2]';
  $handler->display->display_options['fields']['field_session_date_1']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date_3']['id'] = 'field_session_date_3';
  $handler->display->display_options['fields']['field_session_date_3']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date_3']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date_3']['label'] = 'Start';
  $handler->display->display_options['fields']['field_session_date_3']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date_4']['id'] = 'field_session_date_4';
  $handler->display->display_options['fields']['field_session_date_4']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date_4']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date_4']['label'] = 'End';
  $handler->display->display_options['fields']['field_session_date_4']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Length';
  $handler->display->display_options['fields']['expression']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['expression']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['expression']['precision'] = '2';
  $handler->display->display_options['fields']['expression']['separator'] = '';
  $handler->display->display_options['fields']['expression']['expression'] = '([field_session_date_1] - [field_session_date]) / 3600';
  /* Field: Field: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 0,
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Field: Content: Session type */
  $handler->display->display_options['fields']['field_session_type']['id'] = 'field_session_type';
  $handler->display->display_options['fields']['field_session_type']['table'] = 'field_data_field_session_type';
  $handler->display->display_options['fields']['field_session_type']['field'] = 'field_session_type';
  /* Sort criterion: Content: Session date -  start date (field_session_date) */
  $handler->display->display_options['sorts']['field_session_date_value']['id'] = 'field_session_date_value';
  $handler->display->display_options['sorts']['field_session_date_value']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['sorts']['field_session_date_value']['field'] = 'field_session_date_value';
  $handler->display->display_options['sorts']['field_session_date_value']['order'] = 'DESC';
  /* Sort criterion: Field: Employee (field_employee) */
  $handler->display->display_options['sorts']['field_employee_target_id']['id'] = 'field_employee_target_id';
  $handler->display->display_options['sorts']['field_employee_target_id']['table'] = 'field_data_field_employee';
  $handler->display->display_options['sorts']['field_employee_target_id']['field'] = 'field_employee_target_id';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'work_session' => 'work_session',
  );
  /* Filter criterion: Content: Session date -  start date (field_session_date) */
  $handler->display->display_options['filters']['field_session_date_value']['id'] = 'field_session_date_value';
  $handler->display->display_options['filters']['field_session_date_value']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['filters']['field_session_date_value']['field'] = 'field_session_date_value';
  $handler->display->display_options['filters']['field_session_date_value']['operator'] = 'between';
  $handler->display->display_options['filters']['field_session_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_session_date_value']['expose']['operator_id'] = 'field_session_date_value_op';
  $handler->display->display_options['filters']['field_session_date_value']['expose']['label'] = 'Date';
  $handler->display->display_options['filters']['field_session_date_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_session_date_value']['expose']['operator'] = 'field_session_date_value_op';
  $handler->display->display_options['filters']['field_session_date_value']['expose']['identifier'] = 'field_session_date_value';
  $handler->display->display_options['filters']['field_session_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_session_date_value']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_session_date_value']['year_range'] = '-1:+1';
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'field_employee_target_id';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Employee';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Content: Session type (field_session_type) */
  $handler->display->display_options['filters']['field_session_type_tid']['id'] = 'field_session_type_tid';
  $handler->display->display_options['filters']['field_session_type_tid']['table'] = 'field_data_field_session_type';
  $handler->display->display_options['filters']['field_session_type_tid']['field'] = 'field_session_type_tid';
  $handler->display->display_options['filters']['field_session_type_tid']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_session_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_session_type_tid']['expose']['operator_id'] = 'field_session_type_tid_op';
  $handler->display->display_options['filters']['field_session_type_tid']['expose']['label'] = 'Session type';
  $handler->display->display_options['filters']['field_session_type_tid']['expose']['operator'] = 'field_session_type_tid_op';
  $handler->display->display_options['filters']['field_session_type_tid']['expose']['identifier'] = 'field_session_type_tid';
  $handler->display->display_options['filters']['field_session_type_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_session_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_session_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_session_type_tid']['vocabulary'] = 'session_types';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/work-sessions';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Work sessions';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field: Employee */
  $handler->display->display_options['fields']['field_employee']['id'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['table'] = 'field_data_field_employee';
  $handler->display->display_options['fields']['field_employee']['field'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date_2']['id'] = 'field_session_date_2';
  $handler->display->display_options['fields']['field_session_date_2']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date_2']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date_2']['label'] = 'Date';
  $handler->display->display_options['fields']['field_session_date_2']['settings'] = array(
    'format_type' => 'date',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date']['id'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date']['label'] = 'From raw';
  $handler->display->display_options['fields']['field_session_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_session_date']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_session_date']['alter']['text'] = '[field_session_date-value]';
  $handler->display->display_options['fields']['field_session_date']['type'] = 'date_plain';
  $handler->display->display_options['fields']['field_session_date']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date_1']['id'] = 'field_session_date_1';
  $handler->display->display_options['fields']['field_session_date_1']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date_1']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date_1']['label'] = 'Until raw';
  $handler->display->display_options['fields']['field_session_date_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_session_date_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_session_date_1']['alter']['text'] = '[field_session_date_1-value2]';
  $handler->display->display_options['fields']['field_session_date_1']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date_3']['id'] = 'field_session_date_3';
  $handler->display->display_options['fields']['field_session_date_3']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date_3']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date_3']['label'] = 'Start';
  $handler->display->display_options['fields']['field_session_date_3']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Session date */
  $handler->display->display_options['fields']['field_session_date_4']['id'] = 'field_session_date_4';
  $handler->display->display_options['fields']['field_session_date_4']['table'] = 'field_data_field_session_date';
  $handler->display->display_options['fields']['field_session_date_4']['field'] = 'field_session_date';
  $handler->display->display_options['fields']['field_session_date_4']['label'] = 'End';
  $handler->display->display_options['fields']['field_session_date_4']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Length';
  $handler->display->display_options['fields']['expression']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['expression']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['expression']['precision'] = '2';
  $handler->display->display_options['fields']['expression']['separator'] = '';
  $handler->display->display_options['fields']['expression']['expression'] = '([field_session_date_1] - [field_session_date]) / 3600';
  /* Field: Field: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 0,
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author';
  $handler->display->display_options['path'] = 'admin/content/work-sessions/export';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $export['work_sessions'] = $view;

  return $export;
}
