<?php
/**
 * @file
 * Triggering the process of updating the time tracking entities to update the
 * spent time in the issues in case the total hours does not match.
 */

// 33709 => unio 6.5
$project_nid = drush_get_option('project', FALSE);
$skip_issues = drush_get_option('skip-issues', FALSE);

// Prepare query.
$issues_result = productivity_issue_get_all($project_nid, 'issue');
$count_issues = $issues_result->rowCount();

$processed_mfs = array();
// Create one new tracking per issue.
while(!$skip_issues && ($record = $issues_result->fetchAssoc())) {

  // Create an associative array:
  $old_issue = array(
    'nid' =>  $record['nid'],
    'uid' => $record['uid'],
    'title' => $record['title'],
    'estimate' => $record['field_time_estimate_value'],
    'issue_id' => $record['field_issue_id_value'],
    'type' => $record['field_github_content_type_value'],
    'related_issue' => $record['field_issue_reference_target_id'],
    'related_issue_gh_id' => $record['ri_field_issue_id_value'],
    'actual' => $record['field_actual_hours_value'],
    'github_repo' => $record['field_github_project_id_value'],
    'employee' => $record['field_employee_value'],
    'project' => $record['field_project_target_id'],
  );

  // Get or create tracking node.
  $wrapper = get_new_tracking($old_issue);
  // Save logs for issue.
  $result = get_tracked_data($old_issue['github_repo'], $old_issue['issue_id']);
  $logs = array();

  while($track = $result->fetchAssoc()) {
    $logs['und'][] = create_multifields_track($track);
    $processed_mfs[$track['field_issues_logs_id']] = TRUE;
  }

  $node = $wrapper->value();
  $node->field_track_log = $logs;
  $wrapper->save();
  print("Saving Tracking.  \n");
  $count_issues--;
  print("remaining issues: {$count_issues}.  \n");
}

// Now get all tracking logs with no issue refs, and create a stub tracking from
// each one of them.
// Get all Tracks.
$result = get_tracked_data();
$count_track = $result->rowCount();

// We should mark the mlid of processed tracks.
while($track = $result->fetchAssoc()) {
  // Create the stub info.
  // Don't process same track again.
  if ($processed_mfs[$track['field_issues_logs_id']]) {
    $count_track--;
    print("Skiping, remaining track: {($count_track)}.  \n");
    continue;
  }
  $logs['und'][] = create_multifields_track($track);
  $old_track_nid = $track['entity_id'];
  $old_track_node_wrapper = entity_metadata_wrapper('node', $old_track_nid);

  $issue = array(
    'uid' => $logs['und'][0]['field_employee']['und'][0]['target_id'],
    // Use real nid as issue id to be able to reimport.
    'issue_id' => $old_track_nid,
    'github_repo' => 'no-repo',
    'estimate' => 0,
    'employee' => $logs['und'][0]['field_employee']['und'][0]['target_id'],
    'project' => $old_track_node_wrapper->field_project->getIdentifier(),
    'title' => $old_track_node_wrapper->field_project->label() . date('-c' , $old_track_node_wrapper->field_work_date->value()),
  );

  $wrapper = get_new_tracking($issue);
  $node = $wrapper->value();
  $node->field_track_log = $logs;
  $wrapper->save();
  print("Saving Tracking.  \n");
  $count_track--;
  print("remaining track: {$count_track}.  \n");
}


/**
 * Create a well formated log track multifileld.
 */
function create_multifields_track($track) {
  $old_track_nid = $track['entity_id'];
  $old_track_node_wrapper = entity_metadata_wrapper('node', $old_track_nid);
  $pr_nid = $track['field_issues_logs_field_github_issue_target_id'];
  $pr_wrapper = entity_metadata_wrapper('node', $pr_nid);

  // Get last push
  $last_date = 0;
  $pr_node = $pr_wrapper->value();

  if ($pr_node && $pr_node->field_push_date['und']) {
    foreach ($pr_node->field_push_date['und'] as $date) {
      $last_date = $date['value'];
    }
  }
  // Get time spent average.
  $number_of_issue = count($pr_node->field_issue_reference['und']);
  $total_time_spent = $track['field_issues_logs_field_time_spent_value'];
  if ($number_of_issue > 1) {
    // Get average.
    $total_time_spent /= $number_of_issue;
  }

  $log = array();
  $old_track_node = $old_track_node_wrapper->value();
  $log['field_date']['und'][0]['value'] = $old_track_node->field_work_date['und'][0]['value'];
  $log['field_issue_label']['und'][0]['value'] = $track['field_issues_logs_field_issue_label_value'];
  // PR id.
  if ($pr_node) {
    $log['field_issue_id']['und'][0]['value'] = $pr_wrapper->field_issue_id->value();
    if ($last_date) {
      $log['field_last_push']['und'][0]['value'] = $last_date;
    }
  }
  $log['field_github_username']['und'][0]['value'] = $old_track_node_wrapper->field_employee->field_github_username->value();
  $log['field_time_spent']['und'][0]['value'] = $total_time_spent;
  $log['field_issue_type']['und'][0]['value'] = $track['field_issues_logs_field_issue_type_value'];
  $log['field_employee']['und'][0]['target_id'] = $old_track_node_wrapper->field_employee->getIdentifier();

  return $log;
}
/**
 * Get old tracking logs.
 */
function get_tracked_data($repo = FALSE, $issue_id = FALSE) {
  $query = db_select('field_data_field_issues_logs', 'il');
  // PR -> Issue
  $query
    ->leftJoin('field_data_field_issue_reference', 'gh', 'gh.entity_id = il.field_issues_logs_field_github_issue_target_id');
  // Issue -> info
  $query
    ->leftJoin('field_data_field_issue_id', 'g_id', 'gh.field_issue_reference_target_id = g_id.entity_id');
  $query
    ->leftJoin('field_data_field_github_project_id', 'repo', 'gh.field_issue_reference_target_id = repo.entity_id');

  $query
    ->fields('il')
    // GH issue nid.
    ->fields('gh', array('field_issue_reference_target_id'))
    ->orderBy('il.field_issues_logs_id', 'DESC');

  if ($issue_id) {
    $query
      ->condition('g_id.field_issue_id_value', $issue_id)
      ->condition('repo.field_github_project_id_value', $repo);
  }
  return $query->execute();
}

/**
 * Get the issue by ID
 */
function get_new_tracking($issue) {
  // List of issues for a project nid.
  $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'tracking')
      ->fieldCondition('field_issue_id', 'value', $issue['issue_id'])
      ->fieldCondition('field_github_project_id', 'value', $issue['github_repo'])
      ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
      ->range(0, 1)
      ->execute();

    if (!empty($result['node'])) {
      $nid = reset($result['node']);
      $node = node_load($nid->nid);
      print("Found existing new tracking {$node->title} \n");
    }
    else {
      // If stub issue or not found before create a new node.
      if ($issue['github_repo'] != 'no-repo') {
        $title = "Tracking for issue {$issue['github_repo']}/{$issue['issue_id']}";
      }
      else {
        $title = "Tracking for project: {$issue['title']}";
      }
      $values = array(
        'title' => $title,
        'type' => 'tracking',
        'uid' => $issue['uid'],
        'status' => 1,
      );
      print("Creating new $title \n");
      $node = entity_create('node', $values);

    }

  $wrapper = entity_metadata_wrapper('node', $node);
  $wrapper->field_project->set($issue['project']);
  $wrapper->field_time_estimate->set($issue['estimate']);
  $wrapper->field_issue_id->set($issue['issue_id']);
  $wrapper->field_github_project_id->set($issue['github_repo']);
  return $wrapper;
}

/**
 * Get entity reference connections.
 */
function productivity_issue_get_all($project_nid = FALSE, $issue_type = FALSE) {

  // List of issues for a project nid.
  $query = db_select('node', 'n');
  $query
    ->join('field_data_field_project', 'p', 'n.nid = p.entity_id');
  $query
    ->leftJoin('field_data_field_time_estimate', 'e', 'n.nid = e.entity_id');
  $query
    ->leftJoin('field_data_field_issue_id', 'i', 'n.nid = i.entity_id');
  $query
    ->leftJoin('field_data_field_github_content_type', 'ct', 'n.nid = ct.entity_id');
  $query
    ->leftJoin('field_data_field_issue_reference', 'ir', 'n.nid = ir.entity_id');
  // Field on GH issue.
  $query
    ->leftJoin('field_data_field_actual_hours', 'ah', 'n.nid = ah.entity_id');
  $query
    ->leftJoin('field_data_field_github_project_id', 'gpi', 'n.nid = gpi.entity_id');
  $query
    ->leftJoin('field_data_field_issue_id', 'ri', 'ir.field_issue_reference_target_id = ri.entity_id');
  $query
    ->leftJoin('field_data_field_employee', 'fe', 'n.nid = fe.entity_id');

  $query
    ->fields('n', array('title', 'nid', 'uid'))
    ->fields('e', array('field_time_estimate_value'))
    ->fields('i', array('field_issue_id_value'))
    ->fields('ct', array('field_github_content_type_value'))
    ->fields('ir', array('field_issue_reference_target_id'))
    ->fields('ri', array('ri' => 'field_issue_id_value'))
    ->fields('ah', array('field_actual_hours_value'))
    ->fields('gpi', array('field_github_project_id_value'))
    ->fields('fe', array('field_employee_target_id'))
    ->fields('p', array('field_project_target_id'));

    if ($project_nid) {
      $query
        ->condition('p.field_project_target_id', $project_nid);
    }

    $query
      ->condition('type', 'github_issue')
    ->condition('status', NODE_PUBLISHED);

  if ($issue_type) {
    $query->condition('field_github_content_type_value', $issue_type);
  }
  $result = $query->execute();



  return $result;
}