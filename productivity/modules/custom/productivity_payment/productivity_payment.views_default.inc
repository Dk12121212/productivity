<?php
/**
 * @file
 * productivity_payment.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function productivity_payment_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'payments';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Payments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Payed';
  $handler->display->display_options['css_class'] = 'main-box';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_project' => 'field_project',
    'field_amount' => 'field_amount',
    'field_date_expected' => 'field_date_expected',
    'field_payment_status' => 'field_payment_status',
    'field_transaction' => 'field_transaction',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'field_date_expected';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
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
    'field_amount' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date_expected' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_payment_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_transaction' => array(
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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Field: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 1,
  );
  /* Field: Field: Amount */
  $handler->display->display_options['fields']['field_amount']['id'] = 'field_amount';
  $handler->display->display_options['fields']['field_amount']['table'] = 'field_data_field_amount';
  $handler->display->display_options['fields']['field_amount']['field'] = 'field_amount';
  $handler->display->display_options['fields']['field_amount']['click_sort_column'] = 'amount';
  /* Field: Content: Date expected */
  $handler->display->display_options['fields']['field_date_expected']['id'] = 'field_date_expected';
  $handler->display->display_options['fields']['field_date_expected']['table'] = 'field_data_field_date_expected';
  $handler->display->display_options['fields']['field_date_expected']['field'] = 'field_date_expected';
  $handler->display->display_options['fields']['field_date_expected']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_payment_status']['id'] = 'field_payment_status';
  $handler->display->display_options['fields']['field_payment_status']['table'] = 'field_data_field_payment_status';
  $handler->display->display_options['fields']['field_payment_status']['field'] = 'field_payment_status';
  $handler->display->display_options['fields']['field_payment_status']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Transaction */
  $handler->display->display_options['fields']['field_transaction']['id'] = 'field_transaction';
  $handler->display->display_options['fields']['field_transaction']['table'] = 'field_data_field_transaction';
  $handler->display->display_options['fields']['field_transaction']['field'] = 'field_transaction';
  $handler->display->display_options['fields']['field_transaction']['label'] = 'Transactions';
  $handler->display->display_options['fields']['field_transaction']['click_sort_column'] = 'field_amount_amount';
  $handler->display->display_options['fields']['field_transaction']['settings'] = array(
    'view_mode' => 'default',
  );
  $handler->display->display_options['fields']['field_transaction']['delta_offset'] = '0';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Field: Project (field_project) */
  $handler->display->display_options['arguments']['field_project_target_id']['id'] = 'field_project_target_id';
  $handler->display->display_options['arguments']['field_project_target_id']['table'] = 'field_data_field_project';
  $handler->display->display_options['arguments']['field_project_target_id']['field'] = 'field_project_target_id';
  $handler->display->display_options['arguments']['field_project_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_project_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_project_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_project_target_id']['summary_options']['items_per_page'] = '25';
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
    'payment' => 'payment',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Status (field_payment_status) (reference filter) */
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['id'] = 'field_payment_status_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['table'] = 'field_data_field_payment_status';
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['field'] = 'field_payment_status_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['group'] = 1;
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['expose']['operator_id'] = 'field_payment_status_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['expose']['operator'] = 'field_payment_status_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['expose']['identifier'] = 'field_payment_status_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['reference_display'] = 'entity_ref_taxonomy_list:entityreference_1';
  $handler->display->display_options['filters']['field_payment_status_target_id_entityreference_filter']['reference_arguments'] = 'payment_status';
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

  /* Display: Payments */
  $handler = $view->new_display('panel_pane', 'Payments', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Payments';
  $handler->display->display_options['argument_input'] = array(
    'field_project_target_id' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field: Project (field_project)',
    ),
  );

  /* Display: Payment no filters */
  $handler = $view->new_display('panel_pane', 'Payment no filters', 'panel_pane_2');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'payment' => 'payment',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['argument_input'] = array(
    'field_project_target_id' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field: Project (field_project)',
    ),
  );
  $export['payments'] = $view;

  return $export;
}
