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

  $date = $variables['date'];
  $year = $variables['year'];
  $month = $variables['month'];
  $uid = $variables['uid'];
  $path = menu_get_item()['map'][0];
  // Ajax callback is /tracking, case relevant for user page.
  if ($path == 'tracking') {
    $path = 'user';
  }

  // Build date links.
  $date_relative = [
    'next_day' => strtotime($date . "+1 days"),
    'previous_day' => strtotime($date . "-1 days"),
    'next_month' => strtotime($date . "+1 month"),
    'previous_month' => strtotime($date . "-1 month"),
  ];

  // Create links with relative query string.
  foreach ($date_relative as $key => $timestamp) {
    $variables['urls'][$key] = url($path, [
      'query' => [
        'uid' => $variables['uid'],
        'day' => date('d', $timestamp),
        'month' => date('m', $timestamp),
        'year' => date('Y', $timestamp)
      ]
    ]);
  }

  $variables['days_link'] = [];
  // URLS for each day
  for ($i = 1; $i <= date('t', strtotime('1.' . $month . '.' . $year)); $i++) {
    $timestamp = strtotime($i . '.' . $month . '.' . $year);
    $variables['days_link'][$i] = l($i, $path, [
      'query' => [
        'uid' => $uid,
        'day' => date('d', $timestamp),
        'month' => date('m', $timestamp),
        'year' => date('Y', $timestamp)
      ]
    ]);
  }

  if (empty($conf['all_users'])) {
    $variables['expanded'] = TRUE;
    $variables['tracks'][$uid] = [
      'uid' => $uid,
      'data' => productivity_tracking_get_month_structure($month, $year, $uid),
    ];
  }
  else {
    $variables['expanded'] = FALSE;
    $uids = productivity_user_get_active_uids($month, $year);
    foreach ($uids as $uid) {
      $user = user_load($uid);
      $variables['tracks'][$user->name] = [
        'uid' => $uid,
        'data' => productivity_tracking_get_month_structure($month, $year, $uid),
        ];
      ksort($variables['tracks']);
    }
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
  $conf = $form_state['conf'];
  $form['all_users'] = array(
    '#type' => 'checkbox',
    '#title' => t('All users'),
    '#default_value' => !empty($conf['all_users']) ? $conf['all_users'] : FALSE,
  );

  return $form;
}


function productivity_tracking_tracking_nav_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('all_users') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
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
