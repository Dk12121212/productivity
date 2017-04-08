<?php
/**
 * @file
 * productivity_tracking.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_tracking_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "multifield" && $api == "multifield") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function productivity_tracking_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function productivity_tracking_node_info() {
  $items = array(
    'tracking' => array(
      'name' => t('Tracking'),
      'base' => 'node_content',
      'description' => t('Work tracking.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
