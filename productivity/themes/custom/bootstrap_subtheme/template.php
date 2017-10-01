<?php
/**
 * @file
 * template.php
 */

/**
 * Node preprocess.
 */
function bootstrap_subtheme_preprocess_node(&$variables) {
  $node = $variables['node'];
  $view_mode = $variables['view_mode'];
  $variables['theme_hook_suggestions'][] = "node__{$node->type}__{$view_mode}";
  $preprocess_function = "bootstrap_subtheme_preprocess_node__{$node->type}__{$view_mode}";
  if (function_exists($preprocess_function)) {
    $preprocess_function($variables);
  }
}

/**
 * Preprocess Project node.
 */
function bootstrap_subtheme_preprocess_node__project__full(&$variables) {
  // use node because wrapper don't work with multifield.
  $node = $variables['node'];
  $wrapper = entity_metadata_wrapper('node', $node);
  $variables['days'] = productivity_project_get_total_days($wrapper->field_hours->value());

  $rows = array();
  $variables['table'] = _bootstrap_subtheme_create_rate_table($node, $wrapper, $rows);

  $totals = productivity_tracking_get_tracking_total($node->nid);
  $variables['project_total'] = $totals[0]->total_done ;
  $variables['project_estimated'] = number_format($totals[0]->total_estimate);

  // Add charts.
  $chart = productivity_project_get_developer_chart($node);
  $variables['developer_chart'] = drupal_render($chart);

  $chart = _bootstrap_subtheme_get_hours_type_chart($rows);
  $variables['hours_chart'] = drupal_render($chart);

  $variables['burn_rate_chart'] = _bootstrap_subtheme_burn_rate_chart($node, $wrapper);

  $variables['total_budget'] = productivity_project_get_total_budget($wrapper);

  $variables['project_scope'] = productivity_project_get_scope($wrapper);

  $display = array('settings' => array('format_type' => 'short'));
  $field = field_view_field('node', $node, 'field_date', $display);
  $variables['project_date_start'] = render($field);

  $variables['stakeholders'] = _bootstrap_subtheme_stakeholder_markup($wrapper);

}

function _bootstrap_subtheme_burn_rate_chart($project_node, $wrapper) {
  if (isset($project_node->field_table_rate['und'])) {
    // Go over rate type.
    $data = [];
    $data_issue_estimate = [];
    // Avoid counting estimation of same issue previously processed, this can
    // happen when same issue has tracking on multiple weeks.
    $data_issue_estimate_processed = [];
    $stub = [];
    // Collect data.
    foreach ($wrapper->field_table_rate as $type) {
      $rate_code = $type->field_issue_type->value();
      $tracking = productivity_tracking_get_tracking($project_node->nid, $rate_code);
      $data[$rate_code]['actual'] = [];
      // Prepare table for tracking data.
      while ($track_record = $tracking->fetchAssoc()) {
        // Pr data.
        $pr_time = $track_record['field_track_log_field_time_spent_value'];

        // Bypass issue with no time.
        if ($pr_time == '0.00') {
          continue;
        }
        $pr_date = $track_record['field_track_log_field_date_value'];
        $actual = $track_record['field_track_log_field_time_spent_value'];
        $issue_id = $track_record['field_issue_id_value'];
        $estimate = $track_record['field_time_estimate_value'];
        $week_number = date('W', strtotime($pr_date));
        $week_number = intval($week_number);

        $actual_acumulated = isset($data[$rate_code]['actual'][$week_number][1]) ? $data[$rate_code]['actual'][$week_number][1] : 0;
        $data[$rate_code]['actual'][$week_number] = [
          $week_number,
          $actual_acumulated + $actual
        ];

        // We collect current status of all issues.
        if (!isset($data_issue_estimate_processed[$rate_code][$issue_id])) {
          $data_issue_estimate_processed[$rate_code][$issue_id] = TRUE;
          if (!isset($data_issue_estimate[$rate_code][$week_number][$issue_id])) {
            $data_issue_estimate[$rate_code][$week_number][$issue_id] = $estimate;
            if (!isset($data_issue_estimate[$rate_code][$week_number]['total'])) {
              $data_issue_estimate[$rate_code][$week_number]['total'] = $estimate;
            }
            else {
              $data_issue_estimate[$rate_code][$week_number]['total'] += $estimate;
            }
          }
        }

        // Create a unified structure.
        $stub[$week_number] = [
          $week_number,
          0
        ];
      }
    }
    // Sort by week number.
    foreach ($wrapper->field_table_rate as $type) {
      $rate_code = $type->field_issue_type->value();
      // Sort array by week number.
      foreach ($data[$rate_code] as $data_name => &$data_type) {
        ksort($data_type, SORT_NUMERIC);
      }

      // Convert actual totla to intval, we have to do this after total is done.
      foreach ($data[$rate_code]['actual'] as $week_num => &$actual_total) {
        intval($actual_total[1]);
      }

      // Total lines
      foreach ($data[$rate_code] as $data_name => &$data_type) {
        $data[$rate_code]['total'] = $stub;
        foreach ($data[$rate_code]['total'] as &$total) {
          $total[1] = intval($type->field_scope->interval->value());
        }
        ksort($data_type, SORT_NUMERIC);
      }
      // Create estimate curve line data.
      foreach ($data_issue_estimate[$rate_code] as $week_num => $issue_estimates) {
        $data[$rate_code]['estimate'][$week_num] = [$week_num, intval($issue_estimates['total'])];
        ksort($data[$rate_code]['estimate'], SORT_NUMERIC);
      }
    }

    // Render charts.
    $rendered_charts = [];
    foreach ($data as $rate_code => $rate_data) {
      if (empty($rate_data['actual'])) {
        continue;
      }
      $chart = [
        '#type' => 'chart',
        '#chart_type' => 'line',
        '#title' => t('Burn Rate: ') . $rate_code,
      ];
      // Test with a gap in the data.
      $chart['actual'] = [
        '#type' => 'chart_data',
        '#title' => "Actual $rate_code",
        '#data' => _bootstrap_subtheme_accumulate_array($rate_data['actual']),
      ];
      $chart['total'] = [
        '#type' => 'chart_data',
        '#title' => "Total $rate_code",
        '#data' => $rate_data['total'],
      ];
      $chart['estimate'] = [
        '#type' => 'chart_data',
        '#title' => "Estimated $rate_code",
        '#data' => _bootstrap_subtheme_accumulate_array($rate_data['estimate']),
      ];
      $chart_container = [];
      $chart_container['chart'] = $chart;
      $rendered_charts[] = drupal_render($chart_container);
    }
    return $rendered_charts;
  }
  return FALSE;
}

/**
 * Create an accumlated array for charts.
 */
function _bootstrap_subtheme_accumulate_array($array) {
  $first = reset($array);
  $first = $first[0];

  foreach ($array as $week_key => &$week) {
    // Bypass first value.
    if ($week_key == $first) {
      $sum = $week[1];
      $first = FALSE;
      continue;
    }
    $week[1] += $sum;
    $sum = $week[1];
  }

  return $array;
}
/**
 * Return field values rendered by their display settings.
 */
function _bootstrap_subtheme_render(&$rows, $key, $entity, $entity_type, $fields) {
  foreach ($fields as $field_name) {
    $rows[$key][$field_name] = field_view_field($entity_type, $entity, $field_name, 'full');
    $rows[$key][$field_name] = render($rows[$key][$field_name]);
  }
}

/**
 * Create the stakeholder table markup.
 */
function _bootstrap_subtheme_stakeholder_markup($wrapper) {
  $header = array(
    'Role',
    'Name',
    'Email address',
    'Phone number'
  );
  $rows = array();
  foreach ($wrapper->field_stakeholder as $key => $stakeholder) {
    $profile = profile2_load_by_user($stakeholder->getIdentifier(), 'stakeholder');
    $profile_wrapper = entity_metadata_wrapper('profile2', $profile);
    $rows[] = array(
      'field_role' => $profile_wrapper->field_role->name->value(),
      'field_name' => $profile_wrapper->field_full_name->value(),
      'field_email' => $stakeholder->mail->value(),
      'field_phone' => $profile_wrapper->field_phone->value()
    );
  }

  return theme('table', ['header' => $header, 'rows' => $rows]);
}

/**
 * Create a rendered table with all rate date.
 */
function _bootstrap_subtheme_create_rate_table($node, $wrapper, &$rows) {
  if (!empty($node->field_table_rate['und'])) {
    // Insert all the Table Rate multifield to an array by field.
    foreach ($wrapper->field_table_rate as $key => $rate) {

      $fields = array(
        'field_issue_type',
        'field_scope',
        'field_rate',
        'field_rate_type',
      );
      _bootstrap_subtheme_render($rows, $key, $rate->value(), 'multifield', $fields);

      // Total with new tracking datas
      $totals = productivity_tracking_get_tracking_total($node->nid, $rate->field_issue_type->value());
      $rows[$key]['hours_new'] = $totals[0]->total_done;

      // Override work type titles.
      $rows[$key]['field_issue_type'] = empty($rows[$key]['field_issue_type_label']) ? $rows[$key]['field_issue_type'] : $rows[$key]['field_issue_type_label'];
      unset($rows[$key]['field_issue_type_label']);
    }
  }

  $header = array(
    'Type',
    'Total Scope',
    'Rate',
    'Rate Type',
    'Hours',
  );

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * HTML preprocess.
 */
function bootstrap_subtheme_preprocess_html(&$variables) {
  // Add ng-app="plApp" attribute to the body tag.
  $variables['attributes_array']['ng-app'] = 'productivityApp';
  $variables['body_attributes_array']['class'][] = 'pace-done';
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');

}

function bootstrap_subtheme_preprocess_page(&$variables) {
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');
  $menu = menu_get_item();
  $variables['path'] = $menu['path'];
}

/**
 * Implements hook_element_info_alter().
 *
 * Remove bootstrap's textfield processing to avoid having the "form-control"
 * class on textfields - It adds some hard-to-reset CSS.
 */
function bootstrap_subtheme_element_info_alter(&$elements) {
  foreach ($elements['textfield']['#process'] as $delta => $callback) {
    if ($callback == '_bootstrap_process_input') {
      unset($elements['textfield']['#process'][$delta]);
    }
  }
}

/**
 * Get a chart render array from the calculated rows when displaying a project.
 *
 * @param $rows
 *   Rows from the "Hours by type" table.
 *
 * @return Array
 *   Pre-rendered array for a pie chart.
 */
function _bootstrap_subtheme_get_hours_type_chart($rows) {
  $types = array();
  $hours = array();
  foreach ($rows as $row) {
    $types[] = strip_tags($row['field_issue_type']);
    $hours[] = floatval(strip_tags($row['hours_new']));
  }

  $chart = array(
    '#type' => 'chart',
    '#title' => t('Hours by type'),
    '#chart_type' => 'pie',
    '#legend_position' => 'right',
    '#data_labels' => FALSE,
    '#tooltips' => TRUE,
  );

  $chart['pie_data'] = array(
    '#type' => 'chart_data',
    '#title' => t('type'),
    '#labels' => $types,
    '#data' => $hours,
  );

  $chart_container['chart'] = $chart;

  return $chart_container;
}
