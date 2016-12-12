<?php
/**
 * @file
 * productivity_payment.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function productivity_payment_taxonomy_default_vocabularies() {
  return array(
    'bank_account' => array(
      'name' => 'Bank account',
      'machine_name' => 'bank_account',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'payment_status' => array(
      'name' => 'Payment Status',
      'machine_name' => 'payment_status',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
