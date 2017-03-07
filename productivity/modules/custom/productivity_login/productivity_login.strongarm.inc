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
    'client_id' => 'TO FILL',
    'client_secret' => 'TO FILL',
    'github_scopes' => 'user:email',
  );
  $export['openid_connect_client_github'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'openid_connect_userinfo_mapping_claims';
  $strongarm->value = array(
    0 => 'name',
    1 => 'zoneinfo',
  );
  $export['openid_connect_userinfo_mapping_claims'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'openid_connect_userinfo_mapping_property_field_github_username';
  $strongarm->value = 'name';
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
  $strongarm->value = 'user/login';
  $export['site_403'] = $strongarm;

  return $export;
}
