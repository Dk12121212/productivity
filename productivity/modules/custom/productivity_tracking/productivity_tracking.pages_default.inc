<?php
/**
 * @file
 * productivity_tracking.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function productivity_tracking_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'dashboard_tracking';
  $page->task = 'page';
  $page->admin_title = 'Dashboard-tracking';
  $page->admin_description = '';
  $page->path = 'dashboard-tracking';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_dashboard_tracking__panel';
  $handler->task = 'page';
  $handler->subtask = 'dashboard_tracking';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'general';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '7f01b441-6c2a-4992-bca7-b7a4a8ac61da';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_dashboard_tracking__panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-0a8c71a5-a064-4cc6-9e75-7180abee162d';
  $pane->panel = 'bottom';
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
  $pane->uuid = '0a8c71a5-a064-4cc6-9e75-7180abee162d';
  $display->content['new-0a8c71a5-a064-4cc6-9e75-7180abee162d'] = $pane;
  $display->panels['bottom'][0] = 'new-0a8c71a5-a064-4cc6-9e75-7180abee162d';
  $pane = new stdClass();
  $pane->pid = 'new-272f1a99-da75-4d3d-81d0-a0cecf62d3bc';
  $pane->panel = 'top';
  $pane->type = 'tracking_nav';
  $pane->subtype = 'tracking_nav';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
    'all_users' => 1,
    'form_build_id' => 'form-h4gngG7WbF7jw3_CYIlN-vniZMoiujoQ6wkTd2KqpLI',
    'form_token' => '68d0y8cqacKtxPptEA_or4mCeWqsvuUv1iEvdli2J4k',
    'form_id' => 'productivity_tracking_tracking_nav_content_type_edit_form',
    'config_item_1' => NULL,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '272f1a99-da75-4d3d-81d0-a0cecf62d3bc';
  $display->content['new-272f1a99-da75-4d3d-81d0-a0cecf62d3bc'] = $pane;
  $display->panels['top'][0] = 'new-272f1a99-da75-4d3d-81d0-a0cecf62d3bc';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['dashboard_tracking'] = $page;

  return $pages;

}
