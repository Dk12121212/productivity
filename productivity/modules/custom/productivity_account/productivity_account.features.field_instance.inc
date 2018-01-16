<?php
/**
 * @file
 * productivity_account.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function productivity_account_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-account-field_payment_terms'.
  $field_instances['node-account-field_payment_terms'] = array(
    'bundle' => 'account',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Payment term for account.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_payment_terms',
    'label' => 'Payment Terms',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 34,
    ),
  );

  // Exported field_instance: 'node-account-field_table_rate'.
  $field_instances['node-account-field_table_rate'] = array(
    'bundle' => 'account',
    'default_value' => array(
      0 => array(
        'field_hours' => array(
          'und' => array(
            0 => array(
              'value' => '',
            ),
          ),
        ),
        'field_issue_type' => array(
          'und' => array(
            0 => array(
              'value' => 'dev',
            ),
          ),
        ),
        'field_rate' => array(
          'und' => array(
            0 => array(
              'amount' => 120,
              'currency' => 'USD',
            ),
          ),
        ),
        'field_rate_type' => array(
          'und' => array(
            0 => array(
              'value' => 'hours',
            ),
          ),
        ),
        'field_scope' => array(
          'und' => array(
            0 => array(
              'interval' => 10,
              'period' => 'hour',
            ),
          ),
        ),
        'field_issue_type_label' => array(
          'und' => array(
            0 => array(
              'value' => '',
            ),
          ),
        ),
        'id' => NULL,
        'actions' => array(
          'remove_button' => 'Remove',
        ),
      ),
    ),
    'deleted' => 0,
    'description' => 'default customer rates, to define as default on all projects.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'multifield',
        'settings' => array(
          'view_mode' => 'default',
        ),
        'type' => 'multifield_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_table_rate',
    'label' => 'Rates',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'multifield',
      'settings' => array(),
      'type' => 'multifield_default',
      'weight' => 32,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Payment Terms');
  t('Payment term for account.');
  t('Rates');
  t('default customer rates, to define as default on all projects.');

  return $field_instances;
}
