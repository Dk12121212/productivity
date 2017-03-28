<?php
/**
 * @file
 * productivity_user.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function productivity_user_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view__panel_context_6d375b45-fd41-47e5-9c61-1152c708b984';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'User page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'user';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'bottom' => NULL,
      'attendance' => NULL,
      'tracking' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'c620dd81-89ce-4499-8b41-f6775125b90a';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'user_view__panel_context_6d375b45-fd41-47e5-9c61-1152c708b984';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-1b6e3ba6-16bb-4a48-8a35-f438be61d566';
  $pane->panel = 'top';
  $pane->type = 'tracking_admin';
  $pane->subtype = 'tracking_admin';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '1b6e3ba6-16bb-4a48-8a35-f438be61d566';
  $display->content['new-1b6e3ba6-16bb-4a48-8a35-f438be61d566'] = $pane;
  $display->panels['top'][0] = 'new-1b6e3ba6-16bb-4a48-8a35-f438be61d566';
  $pane = new stdClass();
  $pane->pid = 'new-f0ea2851-c06b-4e90-a71d-faa1b15a0362';
  $pane->panel = 'top';
  $pane->type = 'tracking_nav';
  $pane->subtype = 'tracking_nav';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'f0ea2851-c06b-4e90-a71d-faa1b15a0362';
  $display->content['new-f0ea2851-c06b-4e90-a71d-faa1b15a0362'] = $pane;
  $display->panels['top'][1] = 'new-f0ea2851-c06b-4e90-a71d-faa1b15a0362';
  $pane = new stdClass();
  $pane->pid = 'new-7a848676-0f7d-47a1-be90-c01244c3f13c';
  $pane->panel = 'tracking';
  $pane->type = 'tracking_form';
  $pane->subtype = 'tracking_form';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '7a848676-0f7d-47a1-be90-c01244c3f13c';
  $display->content['new-7a848676-0f7d-47a1-be90-c01244c3f13c'] = $pane;
  $display->panels['tracking'][0] = 'new-7a848676-0f7d-47a1-be90-c01244c3f13c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_view__panel_context_6d375b45-fd41-47e5-9c61-1152c708b984'] = $handler;

  return $export;
}
