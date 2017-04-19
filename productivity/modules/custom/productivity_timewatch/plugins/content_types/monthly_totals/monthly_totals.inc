<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Employee timewatch totals'),
  'description' => t('Display month totals for employees'),
  'category' => t('Productivity'),
);

/**
 * Render callback.
 */
function productivity_timewatch_monthly_totals_content_type_render($subtype, $conf, $args, $context) {
  $variables = productivity_tracking_get_query_strings($args);

  $year = $variables['year'];
  $month = $variables['month'];
  $uid = $variables['uid'];

  $account = user_load($uid);
  $timewatch = productivity_timewatch_get_employee_sessions($account, $month, $year);

  // Return early in of no tracking.
  if (!isset($timewatch['summary']['1.Regular'])) {
    return;
  }

  $block = new stdClass();
  $block->module = 'productivity_tracking';
  $block->title = 'Timewatch summary';
  $block->content = productivity_timewatch_create_summary_table($timewatch['summary']);;
  return $block;
}

/**
 * Edit form.
 */
function productivity_timewatch_monthly_totals_content_type_edit_form($form, &$form_state) {
  return $form;
}