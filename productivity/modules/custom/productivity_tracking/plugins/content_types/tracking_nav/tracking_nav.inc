<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Tracking nav'),
  'description' => t('Display month navigation'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_tracking_nav_theme',
);

/**
 * Render callback.
 */
function productivity_tracking_tracking_nav_content_type_render($subtype, $conf, $args, $context) {
  $variables = productivity_tracking_get_query_strings($args);

  $uid = $variables['uid'];
  $date = $variables['date'];
  $year = $variables['year'];
  $month = $variables['month'];
  $day = $variables['day'];

  // Build date links.
  $date_relative = [
    'next_day' => strtotime($date . "+1 days"),
    'previous_day' => strtotime($date . "-1 days"),
    'next_month' => strtotime($date . "+1 month"),
    'previous_month' => strtotime($date . "-1 month"),
  ];

  // Create links with relative query string.
  foreach ($date_relative as $key => $timestamp) {
    $variables['urls'][$key] = url('user', [
      'query' => [
        'uid' => $variables['uid'],
        'day' => date('d', $timestamp),
        'month' => date('m', $timestamp),
        'year' => date('Y', $timestamp)
      ]
    ]);
  }

  $variables['tracking'] = productivity_tracking_get_month_structure($month, $year, $uid);

  $variables['days_link'] = [];
  // URLS for each day
  for ($i = 1; $i <= date('t', strtotime('1.' . $month . '.' . $year)); $i++) {
    $timestamp = strtotime($i . '.' . $month . '.' . $year);
    $variables['days_link'][$i] = l($i, 'user', [
      'query' => [
        'uid' => $uid,
        'day' => date('d', $timestamp),
        'month' => date('m', $timestamp),
        'year' => date('Y', $timestamp)
      ]
    ]);
  }

  $block = new stdClass();
  $block->module = 'productivity_tracking';
  $block->title = '';
  $block->content = theme('productivity_tracking_month_nav', $variables);
  return $block;
}

/**
 * Edit form.
 */
function productivity_tracking_tracking_nav_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_tracking_nav_theme(&$theme, $plugin) {
  $theme['productivity_tracking_month_nav'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'tracking-month-nav',
  );
}
