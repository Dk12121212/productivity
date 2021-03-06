<?php
/**
 * @file
 * productivity_payment.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function productivity_payment_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'payments';
  $page->task = 'page';
  $page->admin_title = 'Payments';
  $page->admin_description = '';
  $page->path = 'payments';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'project admin',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_payments_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'payments';
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
  );
  $display = new panels_display();
  $display->layout = 'general';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '815073fb-afb3-4f02-b215-e68ea1fc148d';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_payments_panel_context';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-2846164a-6d17-4aa0-897b-de62008d44dc';
  $pane->panel = 'top';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => '',
    'title' => '',
    'title_heading' => 'h2',
    'body' => '<a href=/node/add/payment>Add new payment</a>',
    'format' => 'full_html',
    'substitute' => TRUE,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '2846164a-6d17-4aa0-897b-de62008d44dc';
  $display->content['new-2846164a-6d17-4aa0-897b-de62008d44dc'] = $pane;
  $display->panels['top'][0] = 'new-2846164a-6d17-4aa0-897b-de62008d44dc';
  $pane = new stdClass();
  $pane->pid = 'new-68a8d365-4c8f-451e-a782-34113737a9b7';
  $pane->panel = 'top';
  $pane->type = 'views_panes';
  $pane->subtype = 'payments-panel_pane_1';
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
  $pane->uuid = '68a8d365-4c8f-451e-a782-34113737a9b7';
  $display->content['new-68a8d365-4c8f-451e-a782-34113737a9b7'] = $pane;
  $display->panels['top'][1] = 'new-68a8d365-4c8f-451e-a782-34113737a9b7';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['payments'] = $page;

  return $pages;

}
