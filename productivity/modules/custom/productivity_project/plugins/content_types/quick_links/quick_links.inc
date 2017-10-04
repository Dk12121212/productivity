<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Project quick links'),
  'description' => t('Display lnks to active projects'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_quick_links_theme',
);

/**
 * Render callback.
 */
function productivity_project_quick_links_content_type_render($subtype, $conf, $args, $context) {

  // Quit early if no permission.
  if (!user_access('administer nodes')) {
    return FALSE;
  }
  // Get project active this month and previous month.
  $active_projects = productivity_project_get_project_by_date(FALSE, FALSE, 1);
  $variables['urls'] = [];
  // Create links with relative query string.
  $variables['active'] = FALSE;
  foreach ($active_projects as $nid => $name) {
    $variables['urls'][$name] = l($name, "node/$nid");
    // Current project.
    $current_node = menu_get_object('node');
    if ($current_node && $current_node->nid == $nid) {
      $variables['active'] = $name;
    }
  }

  ksort($variables['urls']);
  $block = new stdClass();
  $block->module = 'productivity_project';
  $block->title = '';
  $block->content = theme('productivity_quick_links', $variables);
  return $block;
}

/**
 * Edit form.
 */
function productivity_project_quick_links_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_quick_links_theme(&$theme, $plugin) {
  $theme['productivity_quick_links'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'quick-links',
  );
}
