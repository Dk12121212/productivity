<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Tracking admin'),
  'description' => t('Display tracking admin block'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_tracking_admin_theme',
);

/**
 * Render callback.
 */
function productivity_tracking_tracking_admin_content_type_render($subtype, $conf, $args, $context) {

  // Quit early if no permission.
  if (!user_access('administer nodes')) {
    return FALSE;
  }

  $variables = productivity_tracking_get_query_strings($args);

  $date = $variables['date'];
  $year = $variables['year'];
  $month = $variables['month'];

  $timestamp = strtotime($date);

  $all_active_users = productivity_user_get_active_uids($month, $year);
  $users = user_load_multiple($all_active_users);
  $variables['urls'] = [];
  // Create links with relative query string.
  foreach ($users as $uid => $user) {
    $variables['urls'][$user->name] = l($user->name, 'user', [
      'query' => [
        'uid' => $uid,
        'day' => date('d', $timestamp),
        'month' => date('m', $timestamp),
        'year' => date('Y', $timestamp)
      ]
    ]);
  }

  ksort($variables['urls']);
  $block = new stdClass();
  $block->module = 'productivity_tracking';
  $block->title = '';
  $block->content = theme('productivity_tracking_admin', $variables);
  return $block;
}

/**
 * Edit form.
 */
function productivity_tracking_tracking_admin_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_tracking_admin_theme(&$theme, $plugin) {
  $theme['productivity_tracking_admin'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'tracking-admin',
  );
}
