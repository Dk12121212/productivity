<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; Display monthly employee report.
 */
function productivity_timewatch_monthly_employee_report_callback($account = FALSE, $year = FALSE, $month = FALSE, $uid_sign = FALSE) {
  return productivity_timewatch_monthly_employee_report($account, $year, $month, $uid_sign);
}

/**
 * Menu callback; Display monthly employee report PDF.
 */
use TijsVerkoyen\CssToInlineStyles\CssToInlineStyles;
function productivity_timewatch_monthly_employee_report_pdf_callback($account, $year, $month, $uid_sign = FALSE) {

  $html = productivity_timewatch_build_report($account, $year, $month, $uid_sign);
  if (!$html) {
    return "No Data for this user.";
  }

  // Set inline CSS.
  $css1 = drupal_get_path('theme', 'bootstrap_subtheme') . '/bootstrap/css/bootstrap.css';
  $css2 = drupal_get_path('module', 'productivity_timewatch') . '/monthly_employee_report/monthly_employee_report_pdf.css';
  $css = file_get_contents($css1);
  $css .= file_get_contents($css2);
  $cssToInlineStyles = new CssToInlineStyles($html, $css);

  $html = $cssToInlineStyles->convert();

  // Generate PDF.
  $dompdf = new Dompdf\Dompdf();
  $dompdf->setBasePath(url($css, array('absolute' => TRUE)));
  $dompdf->loadHtml($html);
  $dompdf->render();
  $filename = $account->name . "-$year-$month.pdf";
  $pdf_content = $dompdf->output($filename);
  $file = file_save_data($pdf_content, 'private://' . $filename, FILE_EXISTS_REPLACE);
  $http_headers = array(
    'Content-Type' => 'application/pdf',
    'Content-Disposition' => 'attachment; filename="' . $filename . '"',
    'Content-Length' => $file->filesize,
  );
  file_transfer($file->uri, $http_headers);
}

/**
 * Load all resources for the page.
 * @param $local
 */
function productivity_timewatch_monthly_employee_load_resources($local = FALSE) {
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_timewatch') . '/monthly_employee_report/monthly_employee_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_timewatch') . '/monthly_employee_report/monthly_employee_report.css');
  // No CDN.
  if ($local) {

    // Add Datepicker lib.
    drupal_add_js(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/bootstrap-datepicker/js/bootstrap-datepicker.js');
    drupal_add_css(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/bootstrap-datepicker/css/bootstrap-datepicker.min.css');
    // Add select 2
    drupal_add_js(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/select2/js/select2.js');
    drupal_add_css(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/select2/css/select2.min.css');
  }
  else {
    // Add JavaScript file with the base url of the page.
    drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
    drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
    drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

    // Add Datepicker lib.
    drupal_add_js("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/js/bootstrap-datepicker.min.js", array('type' => 'external'));
    drupal_add_css("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/css/bootstrap-datepicker.min.css", array('type' => 'external'));
  }
}

/**
 * Create the employee monthly report, with printable version.
 */
function productivity_timewatch_monthly_employee_report($account = FALSE, $year = FALSE, $month = FALSE, $uid_sign) {
  global $base_url;
  // Load External resources.
  productivity_timewatch_monthly_employee_load_resources();
  $variables = array();

  // Initialize variables.
  $variables['employees'] = user_load_multiple(productivity_account_get_employee_uids());
  $variables['current_uid'] = 0;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';
  $variables['table'] = '';
  $variables['year'] = !empty($year) ? $year : date('Y');
  $variables['month'] = !empty($month) ? $month : date('m', strtotime("-1 month"));
  $variables['pdf_url'] = FALSE;

  // Add to JS settings current Month/Year.

  drupal_add_js(array(
    'report' => array(
      'base_url' => $base_url,
      'pdf_url_start' => url('monthly-employee-report/pdf'),
      'pdf_url_end' => "/$year/$month",
      'year' => $variables['year'],
      'month' => $variables['month'],
      'employees' => $variables['employees'],
    ),
  ), 'setting');

  // No project given, return early.
  if (!$account) {
    $variables['report'] = '';
    return theme('productivity_timewatch_monthly_employee_report', $variables);
  }

  // No working day return early.
  if (!$variables['report'] = productivity_timewatch_build_report($account, $year, $month, $uid_sign)) {
    $variables['no_result'] = TRUE;
    $variables['message'] = t('No work done this month.');
  }

  $variables['current_uid'] = $account->uid;
  $variables['pdf_url'] = url('monthly-employee-report/pdf') . "/{$account->uid}/$year/$month";


  return theme('productivity_timewatch_monthly_employee_report', $variables);
}

/**
 * Build table report with summary.
 */
function productivity_timewatch_build_report($account, $year, $month, $uid_sign = FALSE){
  // No working day return early.
  if (!$result = productivity_timewatch_get_employee_sessions($account, $month, $year)) {
    return FALSE;
  }

  $variables_report = array();
  $variables_report['year'] = $year;
  $variables_report['month']= $month;
  $wrapper = entity_metadata_wrapper('user', $account);
  $variables_report['fullname'] = $wrapper->field_full_name->value() ? $wrapper->field_full_name->value() : $account->name;
  $variables_report['date'] = date("F Y", strtotime("$year-$month-01"));


  $uid = $account->uid;
  $mop_manager = variable_get('productivity_mop_manager_uid', '15');
  $date_sign = variable_get("productivity_bypass_retro_date_{$year}_{$month}_{$uid}", FALSE);
  $date_sign_manager = variable_get("productivity_bypass_retro_date_{$year}_{$month}_{$uid}_{$mop_manager}", FALSE);


  // Sign button was clicked.
  if ($uid_sign) {
    if ($uid_sign == $uid && !$date_sign) {
      // Print random date, for testing and demos.
      $month_sign = $month + 1;
      $year_sign = $year;
      if ($month_sign == 13) {
        $month_sign = 1;
        $year_sign = $year + 1;
      }
      // Use for test.
      if ("$year_sign.$month_sign" != date('Y.n')) {
        $day_sign = rand(1, 20);
        $date_sign = strtotime("$year_sign-$month_sign-$day_sign");
      }
      else {
        $date_sign = time();
      }
      variable_set("productivity_bypass_retro_date_{$year}_{$month}_{$uid}", $date_sign);
    }
    // Mop manager sign.
    elseif ($uid_sign == variable_get('productivity_mop_manager_uid', '15') && !$date_sign_manager) {
      $month_sign = $month + 1;
      $year_sign = $year;
      if ($month_sign == 13) {
        $month_sign = 1;
        $year_sign = $year + 1;
      }
      // Use for test.
      if ("$year_sign.$month_sign" != date('Y.n')) {
        $day_sign = rand(1, 20);
        $date_sign_manager = strtotime("$year_sign-$month_sign-$day_sign");
      }
      else {
        $date_sign_manager = time();
      }
      variable_set("productivity_bypass_retro_date_{$year}_{$month}_{$uid}_{$mop_manager}", $date_sign_manager);
    }
  }


  $variables_report['date_sign'] = $date_sign ? date("F, d Y", $date_sign) : FALSE;
  $variables_report['date_sign_manager'] = $date_sign_manager ? date("F, d Y", $date_sign_manager): FALSE;

  // Create sign urls.
  $variables_report['href_sign_manager'] = url("monthly-employee-report/$uid/$year/$month/$mop_manager");
  $variables_report['href_sign'] = url("monthly-employee-report/$uid/$year/$month/$uid");

  // Main table headers.
  $header = array(
    t('Date'),
    t('Week day'),
    t('Entry'),
    t('Exit'),
    t('Total'),
    t('Project/ Type'),
    t('Source'),
    t('Retro'),
    t('All day Total'),
  );
  $variables_report['table'] = theme('table', array(
    'header' => $header,
    'rows' => $result['days']
  ));

  $variables_report['table_summary'] = productivity_timewatch_create_summary_table($result['summary']);
  $variables_report['table_summary_madaan'] = productivity_timewatch_create_summary_maddan_table($result['madaan'], $result['summary']);
  // Get all the projects for project input
  return theme('productivity_timewatch_monthly_employee_report_table', $variables_report);
}

/**
 * Create summary table displayed in footer.
 */
function productivity_timewatch_create_summary_maddan_table($summaries_madaan, $summaries) {
  if (!$summaries_madaan) {
    return FALSE;
  }
  $tables = '';
  // Create a table per Madaan project.
  foreach ($summaries_madaan as $summary) {
    // Headers.
    $header = array(
      t('Project/ Type'),
      t('Total'),
      t('%'),
    );

    // The total on madaan project is the larger number btw total and potential.
    $total_all = $summaries['6.potential']['total_minutes'] > $summaries['4.total']['total_minutes'] ? $summaries['6.potential']['total_minutes'] : $summaries['4.total']['total_minutes'];

    // Add Vacation, Reto, Sick and Miluim to total.
    $total = $summary['1.Attendance']['total_minutes'];
    $total += isset($summaries['1.Vacation']['total_minutes']) ? $summaries['1.Vacation']['total_minutes'] : 0;
    $total += isset($summaries['1.Miluim']['total_minutes']) ? $summaries['1.Miluim']['total_minutes'] : 0;
    $total += isset($summaries['1.Sick']['total_minutes']) ? $summaries['1.Sick']['total_minutes'] : 0;
    $total += isset($summary['2.retro']['total_minutes']) ? $summary['2.retro']['total_minutes'] : 0;

    $summary['1.Attendance']['total_minutes'] += isset($summaries['1.Convention']['total_minutes']) ? $summaries['1.Convention']['total_minutes'] : 0;

    $summary['6.potential_maddan'] = array(
      'name' => t('Potential (maddan)'),
      'total_minutes' => productivity_timewatch_format_total($summaries['6.potential']['total_minutes'], TRUE),
      'actual' => '100%',
    );


    $summary['7.Total'] = array(
      'name' => t('Total (inc. Sick, Retro,  Miluim and Vacation)'),
      'total_minutes' => productivity_timewatch_format_total($total, TRUE),
      'actual' => number_format(100 / $total_all * $total, 2) . '%',
    );

    // Convert calc actual to %
    $summary['1.Attendance']['actual'] = number_format(100 / $total_all * $summary['1.Attendance']['total_minutes'], 2) . '%';
    $summary['1.Attendance']['total_minutes'] = productivity_timewatch_format_total($summary['1.Attendance']['total_minutes'], TRUE);

    // Convert calc actual to %
    if (isset($summary['2.retro'])) {
      $summary['2.retro']['actual'] = number_format(100 / $total_all * $summary['2.retro']['total_minutes'], 2) . '%';
      $summary['2.retro']['total_minutes'] = productivity_timewatch_format_total($summary['2.retro']['total_minutes'], TRUE);
    }

    ksort($summary);

    $tables .= theme('table', array(
      'header' => $header,
      'rows' => $summary,
    ));
  }

  return $tables;
}