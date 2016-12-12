<?php
/**
 * @file
 * productivity_payment.multifield.inc
 */

/**
 * Implements hook_multifield_default_multifield().
 */
function productivity_payment_multifield_default_multifield() {
  $export = array();

  $multifield = new stdClass();
  $multifield->disabled = FALSE; /* Edit this to true to make a default multifield disabled initially */
  $multifield->api_version = 1;
  $multifield->machine_name = 'field_transaction';
  $multifield->label = 'field_transaction';
  $multifield->description = '';
  $export['field_transaction'] = $multifield;

  return $export;
}
