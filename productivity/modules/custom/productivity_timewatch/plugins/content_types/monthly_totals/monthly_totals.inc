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

  $dates = [];
  $dates['start']['month'] = $month;
  $dates['start']['year'] = $year;
  $total =  productivity_tracking_get_tracking_totals($dates, $uid);

  // Return early in of no tracking.
  if (!isset($timewatch['summary']['1.Regular'])) {
    return;
  }
  $regular = productivity_timewatch_format_total($timewatch['summary']['1.Regular']['total_minutes'], TRUE, 0);
  $devider = $regular *  $total['sum']['month'];
  $percent = 0;
  if ($devider) {
    $percent = number_format(100 / $devider, 1);
  }

  $content = productivity_timewatch_create_summary_table($timewatch['summary']);
  $content .= '<strong>';
  $content .=  t('Out of !regular Hours, you reported !actual Hours, which is !percent%', [
   '!regular' => $regular,
   '!actual' => $total['sum']['month'],
   '!percent' => $percent,
  ]);
  $content .= '</strong>';

  $block = new stdClass();
  $block->module = 'productivity_timewatch';
  $block->title = 'Timewatch summary';
  $block->content = $content;
  return $block;
}

/**
 * Edit form.
 */
function productivity_timewatch_monthly_totals_content_type_edit_form($form, &$form_state) {
  return $form;
}