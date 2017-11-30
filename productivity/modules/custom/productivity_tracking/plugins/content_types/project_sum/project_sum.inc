<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Project summary'),
  'description' => t('Display projects total tracking'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_tracking_project_sum_theme',
);

/**
 * Render callback.
 */
function productivity_tracking_project_sum_content_type_render($subtype, $conf, $args, $context) {
  $variables = productivity_tracking_get_query_strings($args);

  $uid = $variables['uid'];

  $dates = [];
  $dates['start']['month'] = $variables['month'];
  $dates['start']['year'] = $variables['year'];
  $variables['tracking'] = productivity_tracking_get_tracking_totals($dates, $uid);

  $block = new stdClass();
  $block->module = 'productivity_tracking';
  $block->title = 'Monthly project breakdown';
  $block->content = theme('productivity_tracking_project_sum', $variables);
  return $block;
}

/**
 * Edit form.
 */
function productivity_tracking_project_sum_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_tracking_project_sum_theme(&$theme, $plugin) {
  $theme['productivity_tracking_project_sum'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'project-sum',
  );
}
