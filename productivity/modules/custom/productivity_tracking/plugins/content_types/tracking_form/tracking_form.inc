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
  'hook theme' => 'productivity_tracking_form_theme',
);

/**
 * Render callback.
 */
function productivity_tracking_tracking_form_content_type_render($subtype, $conf, $args, $context) {
  drupal_add_css(drupal_get_path('module', 'productivity_tracking') . '/plugins/content_types/tracking_form/css/tracking.css');
  drupal_add_js(drupal_get_path('module', 'productivity_tracking') . '/plugins/content_types/tracking_form/js/jquery.tabletojson.min.js');
  drupal_add_js(drupal_get_path('module', 'productivity_tracking') . '/plugins/content_types/tracking_form/js/tracking-table.js');

  $variables = productivity_tracking_get_query_strings($args);

  $uid = $variables['uid'];
  $year = $variables['year'];
  $month = $variables['month'];
  $day = $variables['day'];

  $current_user = user_load($variables['uid']);
  $variables['username'] = $current_user->name;

  // Build  project list.
  $variables['projects'] = productivity_project_get_project_by_date($month, $year);
  // Get month data and tracking.
  // TODO: customize view per developer, custom Weekend and holidays.
  $tracks = productivity_tracking_get_month_structure($month, $year, $uid);
  $variables['tracking'] = $tracks['days'];

  $variables['rows'] = [];
  // TODO: Set this to be dynamic and per project.
  $variables['types'] = [
    'dev' => 'Development',
    'qa' => 'QA',
    'management' => 'Management',
    'designer' => 'Designer',
    'installation_setup' => 'Installation Setup',
    'support' => 'Support',
    'training' => 'Training',
  ];

  $variables['row_template'] = theme('productivity_tracking_table_row', [
      'tracking' => [
        'mlid' => 'new',
        'nodelink' => '',
        'project_nid' => 0,
        'disabled' => FALSE,
        'repo' => '',
        'issue' => '',
        'pr' => '',
        'title' => '',
        'type' => 'dev',
        'length' => 0,
      ],
      'row_number' => FALSE,
      'id' => '',
      'types' => $variables['types'],
      'projects' => $variables['projects'],
    ]
  );

  // Prepare existing tracking.
  $row_number = 0;
  foreach($variables['tracking'][$day] as $track) {
    if ($track['tracking']) {
      $variables['rows'][] = theme('productivity_tracking_table_row', [
        'tracking' => $track,
        'types' => $variables['types'],
        'projects' => $variables['projects'],
        'row_number' => $row_number,
      ]);
      $row_number++;
    }
  }

  $request = $_GET;
  unset($request['q']);
  $q_string = '?' . http_build_query($request);
  // Support Xdebug on the fly.
  if (isset($_COOKIE['XDEBUG_SESSION']) && !isset($_GET['XDEBUG_SESSION'])) {
    $q_string .= "&XDEBUG_SESSION_START={$_COOKIE['XDEBUG_SESSION']}";
  }

  // Push data to JS.
  drupal_add_js([
    'rowNumber' => $row_number,
    'tracking' => [
      'url' =>  base_path() . "tracking/save-tracking$q_string",
      'uid' => $uid,
      'date_str' => "$day.$month.$year",
    ],
  ], 'setting');

  $block = new stdClass();
  $block->module = 'productivity_tracking';
  $block->title = '';
  $block->content = theme('productivity_tracking_form', $variables);
  return $block;
}

/**
 * Edit form.
 */
function productivity_tracking_tracking_form_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_tracking_form_theme(&$theme, $plugin) {
  $theme['productivity_tracking_form'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'tracking-form',
  );
  $theme['productivity_tracking_table_row'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'tracking-table-row',
  );
}
