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
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
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
