<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Tracking form'),
  'description' => t('Display tracking form'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_user_tracking_form_theme',
);

/**
 * Render callback.
 */
function productivity_user_tracking_form_content_type_render($subtype, $conf, $args, $context) {
  drupal_add_css(drupal_get_path('module', 'productivity_user') . '/plugins/content_types/tracking_form/tracking.css');
  $variables = [];
  $variables['tracking'] = [];
  $variables['days'] = [];


  $block = new stdClass();
  $block->module = 'productivity_user';
  $block->title = '';
  $block->content = theme('productivity_user_tracking_form', $variables);

  return $block;
}

/**
 * Edit form.
 */
function productivity_user_tracking_form_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_user_tracking_form_theme(&$theme, $plugin) {
  $theme['productivity_user_tracking_form'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'tracking-form',
  );
}
