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

  // Punch was pressed, add a record for it.
  if (isset($_POST)) {
    if (isset($_POST['dayType'])) {
      $madan = FALSE;
      if (isset($_POST['madan'])) {
        // Get nid for Madan.
        $madan = node_load(variable_get('productivity_maddan_project_nid', FALSE));
      }
      if ($_POST['dayType'] == 'regular') {
        $wrapper = productivity_timewatch_punch($account, $madan);
        $time = $wrapper->field_session_date->value();
        drupal_set_message(t('Punched @type at @entry_time', [
          '@entry_time' =>  isset($time['value2']) ? date('H:i', $time['value2']) : date('H:i', $time['value']),
          '@type' => isset($time['value2']) ? 'Exit' : 'Entry',
        ]));
      }
      else {
        $timestamp = strtotime($variables['date']);
        productivity_timewatch_punch_non_regular($account, $_POST['dayType'], $timestamp);
        drupal_set_message(t('Added @day_type day on @date', [
          '@date' => $variables['date'],
          '@day_type' => $_POST['dayType'],
        ]));
      }
    }
  }

  $variables['can_punch'] = ($uid == $user->uid) || ($user->uid == 1);

  // URL for form submit.
  $timestamp = strtotime("$day.$month.$year");
  $variables['self_url'] = url('user', [
    'query' => [
      'uid' => $uid,
      'day' => date('d', $timestamp),
      'month' => date('m', $timestamp),
      'year' => date('Y', $timestamp),
      'tab-active-attendance' => '1',
    ]
  ]);

  $variables['timewatch'] = productivity_timewatch_get_employee_sessions($account, $month, $year, $day);
  $content = theme('productivity_timewatch_punch', $variables);

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
