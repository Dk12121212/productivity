<?php
/**
 * @file
 * productivity_project.panels_default.inc
 */

/**
 * Implements hook_default_panels_mini().
 */
function productivity_project_default_panels_mini() {
  $export = array();

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'header_top';
  $mini->category = 'productivity';
  $mini->admin_title = 'header top';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'dashboard';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '179aeb25-2c52-4cf9-9f1e-929995797827';
  $display->storage_type = 'panels_mini';
  $display->storage_id = 'header_top';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-bfc3c87c-c3f7-4f30-9e1e-f5fe907508c8';
  $pane->panel = 'top';
  $pane->type = 'quick_links';
  $pane->subtype = 'quick_links';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
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
  $pane->uuid = 'bfc3c87c-c3f7-4f30-9e1e-f5fe907508c8';
  $display->content['new-bfc3c87c-c3f7-4f30-9e1e-f5fe907508c8'] = $pane;
  $display->panels['top'][0] = 'new-bfc3c87c-c3f7-4f30-9e1e-f5fe907508c8';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-bfc3c87c-c3f7-4f30-9e1e-f5fe907508c8';
  $mini->display = $display;
  $export['header_top'] = $mini;

  return $export;
}
