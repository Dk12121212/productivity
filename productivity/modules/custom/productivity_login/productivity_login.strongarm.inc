<?php
/**
 * @file
 * productivity_login.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function productivity_login_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'openid_connect_clients_enabled';
  $strongarm->value = array(
    'github' => 'github',
  );
  $export['openid_connect_clients_enabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'openid_connect_client_github';
  $strongarm->value = array(
    'client_id' => '9169e930cd825924839a',
    'client_secret' => '5a17a3924075329cd58e8d3681c314478287a529',
    'github_scopes' => 'user:email,read:org',
  );
  $export['openid_connect_client_github'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'openid_connect_userinfo_mapping_claims';
  $strongarm->value = array(
    0 => 'name',
    1 => 'preferred_username',
    2 => 'zoneinfo',
  );
  $export['openid_connect_userinfo_mapping_claims'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'openid_connect_userinfo_mapping_property_field_github_username';
  $strongarm->value = 'preferred_username';
  $export['openid_connect_userinfo_mapping_property_field_github_username'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'openid_connect_userinfo_mapping_property_timezone';
  $strongarm->value = 'zoneinfo';
  $export['openid_connect_userinfo_mapping_property_timezone'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_403';
  $strongarm->value = '';
  $export['site_403'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_email_verification';
  $strongarm->value = 0;
  $export['user_email_verification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_register';
  $strongarm->value = '0';
  $export['user_register'] = $strongarm;

  return $export;
}
