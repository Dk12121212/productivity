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
  // Get week number form query string, or default to current week.
  $week = date('W', strtotime($variables['date']));
  $week_year = $variables['year'];
  $uid = $variables['uid'];

  $start_dto = new DateTime();
  $end_dto = new DateTime();
  $start_dto->setISODate($week_year, $week);
  $end_dto->setISODate($week_year, $week);
  $end_dto->modify('+8 days');

  $dates = [];
  $dates['start']['month'] = $start_dto->format('m');
  $dates['start']['year'] = $start_dto->format('Y');
  $dates['start']['day'] = $start_dto->format('d');
  $dates['end']['month'] = $end_dto->format('m');
  $dates['end']['year'] = $end_dto->format('Y');
  $dates['end']['day'] = $end_dto->format('d');

  $variables['tracking'] = productivity_tracking_get_tracking_totals($dates, $uid);

  $block = new stdClass();
  $block->module = 'productivity_tracking';
  // Display date included.
  $end_dto->modify('-1 days');
  $block->title = "Weekly project breakdown - Week : $week -> {$start_dto->format('d.m.Y')} till {$end_dto->format('d.m.Y')}";
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
