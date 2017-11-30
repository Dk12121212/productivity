<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Project summary per week'),
  'description' => t('Display projects total tracking per week'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_tracking_project_sum_per_week_theme',
);

/**
 * Render callback.
 */
function productivity_tracking_project_sum_per_week_content_type_render($subtype, $conf, $args, $context) {
  $variables = productivity_tracking_get_query_strings($args);

  $uid = $variables['uid'];

  $dates = [];
  $dates['start']['month'] = $variables['month'];
  $dates['start']['year'] = $variables['year'];
  // Dummy for test, need to replace this start week date,
  $dates['start']['day'] = 19;

  $dates['end']['month'] = $variables['month'];
  $dates['end']['year'] = $variables['year'];
  // Dummy for test, need to replace this end week date,
  $dates['end']['day'] = 25;

  $variables['tracking'] = productivity_tracking_get_tracking_totals($dates, $uid);

  $block = new stdClass();
  $block->module = 'productivity_tracking';
  $block->title = 'Weekly project breakdown';
  $block->content = theme('productivity_tracking_project_sum_per_week', $variables);
  return $block;
}

/**
 * Edit form.
 */
function productivity_tracking_project_sum_per_week_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_tracking_project_sum_per_week_theme(&$theme, $plugin) {
  $theme['productivity_tracking_project_sum_per_week'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'project-sum-week',
  );
}
