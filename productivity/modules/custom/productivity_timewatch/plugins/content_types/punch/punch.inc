<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Timewatch punch in and out'),
  'description' => t('Add punch buttons'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_timewatch_punch_theme',
);

/**
 * Render callback.
 */
function productivity_timewatch_punch_content_type_render($subtype, $conf, $args, $context) {

  global $user;

  $variables = productivity_tracking_get_query_strings($args);

  $day = $variables['day'];
  $year = $variables['year'];
  $month = $variables['month'];
  $uid = $variables['uid'];
  $account = user_load($uid);

  $variables['can_punch'] = ($uid == $user->uid) || ($user->uid == 1);
  $variables['timewatch'] = productivity_timewatch_get_employee_sessions($account, $month, $year, $day);


  $content = theme('productivity_timewatch_punch', $variables);
  dpm($variables);

  $block = new stdClass();
  $block->module = 'productivity_timewatch';
  $block->title = '';
  $block->content = $content;
  return $block;
}

/**
 * Edit form.
 */
function productivity_timewatch_punch_content_type_edit_form($form, &$form_state) {
  return $form;
}


/**
 * Delegated hook_theme().
 */
function productivity_timewatch_punch_theme(&$theme, $plugin) {
  $theme['productivity_timewatch_punch'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'punch',
  );
}
