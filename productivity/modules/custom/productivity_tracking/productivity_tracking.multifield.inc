<?php
/**
 * @file
 * productivity_tracking.multifield.inc
 */

/**
 * Implements hook_multifield_default_multifield().
 */
function productivity_tracking_multifield_default_multifield() {
  $export = array();

  $multifield = new stdClass();
  $multifield->disabled = FALSE; /* Edit this to true to make a default multifield disabled initially */
  $multifield->api_version = 1;
  $multifield->machine_name = 'field_track_log';
  $multifield->label = 'field_track_log';
  $multifield->description = '';
  $export['field_track_log'] = $multifield;

  return $export;
}
