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
  $variables = [];

  // Build date links.
  $month = isset($_REQUEST['month']) ? $_REQUEST['month'] : date('m', time());
  $year = isset($_REQUEST['year']) ? $_REQUEST['year'] : date('Y', time());
  $day = isset($_REQUEST['day']) ? $_REQUEST['day'] : date('d', time());
  $uid = isset($_REQUEST['uid']) ? $_REQUEST['uid'] : $args[0];

  $variables['day'] = $day;
  $variables['month'] = $month;
  $variables['year'] = $year;


  $date = "$day.$month.$year";

  $date_relative = [
    'next_day' => strtotime($date . "+1 days"),
    'previous_day' => strtotime($date . "-1 days"),
    'next_month' => strtotime($date . "+1 month"),
    'previous_month' => strtotime($date . "-1 month"),
  ];

  // Create links with relative query string.
  foreach ($date_relative as $key => $timestamp) {
    $variables['urls'][$key] = url('user', [
        'query' => [
          'uid' => $uid,
          'day' => date('d', $timestamp),
          'month' => date('m', $timestamp),
          'year' => date('Y', $timestamp)
        ]
      ]);
  }


  // Build  project list.
  $variables['projects'] = productivity_project_get_all_projects();
  $variables['tracking'] = productivity_tracking_tracking_form_get_days($month, $year, $uid);

  $variables['days_link'] = [];
  // URLS for each day
  for ($i = 1; $i <= date('t', strtotime('1.' . $month . '.' . $year)); $i++) {
    $timestamp = strtotime($i . '.' . $month . '.' . $year);
    $variables['days_link'][$i] = l($i, 'user', [
      'query' => [
        'uid' => $uid,
        'day' => date('d', $timestamp),
        'month' => date('m', $timestamp),
        'year' => date('Y', $timestamp)
      ]
    ]);
  }

  $variables['rows'] = [];
  // TODO: Set this to be dynamic and per project.
  $variables['types'] = [
    'dev' => 'Development',
    'qa' => 'QA',
    'migrate' => 'Management',
    'designer' => 'Designer',
    'installation_setup' => 'Installation Setup',
    'support' => 'Support',
    'review' => 'Review',
  ];
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

  drupal_add_js([
    'rowNumber' => $row_number,
    'tracking' => [
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
 * Build an associative array by day.
 *
 * @param $month
 * @param $year
 *
 * @return array|mixed
 */
function productivity_tracking_tracking_form_get_days($month, $year, $uid, $weekend = 'FS') {
  // Global days
  $last_day_this_month  = date('t', strtotime('1.' . $month . '.' . $year));

  $assoc_globals = productivity_timewatch_get_global_days($year, $month);

  // Build skeleton of array, one item per day.
  $new_data = array();
  $new_data[$uid]  = array();
  $new_data[$uid]['sum']  = array();

  // Go over days of the month.
  for ($i = 1; $i <= $last_day_this_month; $i++) {
      // Add leading zeros.
    $key = str_pad($i, 2, '0', STR_PAD_LEFT);
    $new_data[$uid][$key]  = array();

    $timestamp = strtotime($key . '.' . $month . '.' . $year);
    $default_url = url('user', [
      'query' => [
        'uid' => $uid,
        'day' => date('d', $timestamp),
        'month' => date('m', $timestamp),
        'year' => date('Y', $timestamp)
      ]
    ]);

    // Mark weekends.
    $week_day = date( "w", strtotime($i . '.' . $month . '.' . $year));

    // TODO: add weekend preference to user account.
    // Weekend Friday Saturday.
    if ($weekend == 'FS') {
      $weekend_days = array(5, 6);
    }
    // Weekend Saturday Sunday.
    else {
      $weekend_days = array(6, 7);
    }

    // If Weekend.
    if (in_array($week_day, $weekend_days)) {
      $day_item = array(
        'id' => 'new',
        'type' => 'weekend',
        'day' => $key,
        'length' => 'W',
        'projectName' => 'Weekend',
        'employee' => $uid,
        'tracking' => FALSE,
        'href' => $default_url,
      );
      // Add item for weekend.
      $new_data[$uid][$key][] = $day_item;
    }
    // Add global day to user skeleton.
    if (isset($assoc_globals[$key])) {
      $assoc_globals[$key]['employee'] = $uid;
      $new_data[$uid][$key][] = $assoc_globals[$key];
    }
  }

  // Get tracking data.
  $tracking = productivity_tracking_get_tracking_by_user($uid, $year, $month);

  // Prepare table for tracking data.
  while($track_record = $tracking->fetchAssoc()) {
    // Pr data.
    $pr_time = $track_record['field_track_log_field_time_spent_value'];
    $pr_gh_id = $track_record['field_track_log_field_issue_id_value'];
    $pr_title = $track_record['field_track_log_field_issue_label_value'];
    $pr_work_type = $track_record['field_track_log_field_issue_type_value'];
    $pr_developer = $track_record['field_track_log_field_github_username_value'];
    $pr_developer_uid = $track_record['field_track_log_field_employee_target_id'];
    $pr_date = $track_record['field_track_log_field_date_value'];
    $track_id = $track_record['field_track_log_id'];
    $pr_status = $track_record['pr_status_name'];

    // Issue data.
    $repo_id = $track_record['field_github_project_id_value'];
    $estimate = $track_record['field_time_estimate_value'];
    $issue_id = $track_record['field_issue_id_value'];
    $issue_status = $track_record['name'];
    $nid = $track_record['nid'];
    $node_link = l('#', 'node/' . $nid . '/edit', array('attributes' => array('target' => '_blank')));
    $issue_title = $track_record['body_value'];
    $project_nid = $track_record['field_project_target_id'];

    $pr_url = "https://github.com/$repo_id/issues/$pr_gh_id";
    $pr_link = l("$repo_id/$pr_gh_id", $pr_url, array(
      'attributes' => array(
        'title' => $pr_title,
        'target' => '_blank',
      ),
    ));

    $issue_url = "https://github.com/$repo_id/issues/$issue_id";
    $issue_link = l("$issue_title", $issue_url, array('attributes' => array('target' => '_blank')));


    $day['projectName'] = $repo_id;
    $day['length'] = $pr_time;
    $day['day'] = date('d', strtotime($pr_date));
    $day['href'] = $pr_url;
    $day['type'] = $pr_work_type;
    $day['title'] = $pr_title;
    $day['tracking'] = TRUE;
    $day['repo'] = $repo_id;
    $day['pr'] = $pr_gh_id;
    $day['issue'] = $issue_id;
    $day['mlid'] = $track_id;
    $day['project_nid'] = $project_nid;
    // Don't allow to edit the fields outside of the PR.
    $day['disabled'] = 'disabled';
    $day['nodelink'] = $node_link;

    $key = $day['day'];
    $new_data[$uid][$key][] = $day;
  }

  // Fill in vacation other personal global days.
  $non_regular = productivity_timewatch_get_user_sessions($uid, $year, $month, TRUE);
  foreach ($non_regular as $special_day) {
    $wrapper = entity_metadata_wrapper('node', $special_day);

    $day['projectName'] = '';
    $day['length'] = strtoupper(substr($wrapper->field_session_type->label(), 0, 1));
    $day['day'] = date('d', strtotime($wrapper->field_session_date->value->value()));
    $day['href'] = url('node/' . $wrapper->getIdentifier() . '/edit');
    $day['type'] = $wrapper->field_session_type->label();
    $day['title'] = $wrapper->field_special_day_name->value();
    $day['tracking'] = FALSE;


    $key = $day['day'];
    $new_data[$uid][$key][] = $day;
  }

  // Fill empty days with create new stub template, and sum employee data.
  foreach ($new_data as $employee => &$row) {
    foreach ($row as $key => &$empty_day) {
      if ($key == 'sum') {
        continue;
      }
      if (empty($empty_day)) {
        $timestamp = strtotime($key . '.' . $month . '.' . $year);
        $default_url = url('user', [
          'query' => [
            'uid' => $uid,
            'day' => date('d', $timestamp),
            'month' => date('m', $timestamp),
            'year' => date('Y', $timestamp)
          ]
        ]);

        $empty_day[] = array(
          // Set id to new to get the proper link on angular.
          'id' => 'new',
          'type' => 'empty',
          'day' => (string) $key,
          'length' => 'E',
          'projectName' => 'Log work',
          'employee' => $employee,
          'tracking' => FALSE,
          'href' => $default_url,
        );
      }
      // Sums per employee and project.
      else {
        foreach ($empty_day as $track) {
          if ($track['type'] == 'regular') {
            if (empty($new_data[$employee]['sum'][$track['projectName']])) {
              $new_data[$employee]['sum'][$track['projectName']] = 0;
            }
            $new_data[$employee]['sum'][$track['projectName']] += $track['length'];
          }
        }
      }
    }
  }

  // Return single user.
  return $new_data[$uid];
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
