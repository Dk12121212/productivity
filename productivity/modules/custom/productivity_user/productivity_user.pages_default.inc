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
      'bottom-right' => NULL,
      'bottom-left' => NULL,
      'totals' => NULL,
      'totals-right' => NULL,
      'totals-left' => NULL,
      'attendance-right' => NULL,
      'attendance-left' => NULL,
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
  $pane->pid = 'new-944b021e-0656-4993-8b95-6248659ad9b3';
  $pane->panel = 'attendance';
  $pane->type = 'punch';
  $pane->subtype = 'punch';
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
  $pane->uuid = '944b021e-0656-4993-8b95-6248659ad9b3';
  $display->content['new-944b021e-0656-4993-8b95-6248659ad9b3'] = $pane;
  $display->panels['attendance'][0] = 'new-944b021e-0656-4993-8b95-6248659ad9b3';
  $pane = new stdClass();
  $pane->pid = 'new-b9b1e897-9398-4660-a025-c8020915547e';
  $pane->panel = 'attendance-right';
  $pane->type = 'monthly_totals';
  $pane->subtype = 'monthly_totals';
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
  $pane->uuid = 'b9b1e897-9398-4660-a025-c8020915547e';
  $display->content['new-b9b1e897-9398-4660-a025-c8020915547e'] = $pane;
  $display->panels['attendance-right'][0] = 'new-b9b1e897-9398-4660-a025-c8020915547e';
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
  $pane->pid = 'new-57a2022d-7626-458a-a75a-9483abd3908d';
  $pane->panel = 'totals-left';
  $pane->type = 'project_sum_per_week';
  $pane->subtype = 'project_sum_per_week';
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
  $pane->uuid = '57a2022d-7626-458a-a75a-9483abd3908d';
  $display->content['new-57a2022d-7626-458a-a75a-9483abd3908d'] = $pane;
  $display->panels['totals-left'][0] = 'new-57a2022d-7626-458a-a75a-9483abd3908d';
  $pane = new stdClass();
  $pane->pid = 'new-a4207580-bc6c-4e0d-ac44-7733f62b2006';
  $pane->panel = 'totals-right';
  $pane->type = 'project_sum';
  $pane->subtype = 'project_sum';
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
  $pane->uuid = 'a4207580-bc6c-4e0d-ac44-7733f62b2006';
  $display->content['new-a4207580-bc6c-4e0d-ac44-7733f62b2006'] = $pane;
  $display->panels['totals-right'][0] = 'new-a4207580-bc6c-4e0d-ac44-7733f62b2006';
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
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_view__panel_context_6d375b45-fd41-47e5-9c61-1152c708b984'] = $handler;

  return $export;
}
