<?php
/**
 * @file
 * Triggering the process of updating the time tracking entities to update the
 * spent time in the issues in case the total hours does not match.
 */

// 33709 => unio 6.5
$project_nid = drush_get_option('project', 27);
$track_id = drush_get_option('track', FALSE);

// Now get all tracking logs with no issue refs, and create a stub tracking from
// each one of them.
// Get all Tracks.
$result = get_all_tracked_data($track_id, $project_nid);
$count_track = $result->rowCount();


$processed_tracking = [];
// Go over orphan tracks.
while($track = $result->fetchAssoc()) {
  print("Processing, track id: {$track['field_issues_logs_id']}.  \n");

  $old_track_nid = $track['entity_id'];
  $old_track_id = $track['field_issues_logs_id'];
  $old_track_node_wrapper = entity_metadata_wrapper('node', $old_track_nid);

  $pr_nid = $track['field_issues_logs_field_github_issue_target_id'];
  $pr_id = FALSE;

  // No PR related.
  if (!$pr_nid) {
    // Try to find the pr id in label.
    $re = '/\d+/';
    $str = $track['field_issues_logs_field_issue_label_value'];
    preg_match_all($re, $str, $matches);
    if (isset($matches[0][0])) {
      $pr_id = $matches[0][0];
    }
    else {
      print("No PR attached to old_track_id: $old_track_id  \n");
    }
  }
  else {
    // Found PR ref, let's look for issues.
    $pr_node = entity_metadata_wrapper('node', $pr_nid);
    $pr_id = $pr_node->field_issue_id->value();
  }

  $project_wrapper = entity_metadata_wrapper('node', $project_nid);

  // Use default repo from project if no issue ref.
  $default_repo = $project_wrapper->field_github_repository_name[0]->value();
  if ($track['field_github_project_id_value']) {
    $default_repo = $track['field_github_project_id_value'];
  }

  $gh_ids = [];
  $clean_repo = explode('/', $default_repo);
  $gh_user = $clean_repo[0];
  $clean_repo = $clean_repo[1];

  if ($pr_id) {
    // Try to complete the missing data:
    print("Looking up in GH for issue: {$pr_nid}.  \n");


    $pr_info = productivity_tracking_get_issue_info($clean_repo, $pr_id, $gh_user);

    // Check if id is issue.
    if (!isset($pr_info['issue']['pull_request'])) {
      $gh_ids[$pr_info['issue']['number']] = array(
        'estimate' => $pr_info['estimate'],
        'status' => $pr_info['issue']['state'] ? $pr_info['issue']['state'] : 'closed',
        'title' => $pr_info['issue']['title'],
      );
    }
    else {
      foreach ($pr_info['related_issues'] as $issue_info) {
        // Found a related issue.
        if (!isset($issue_info['issue']['pull_request'])) {
          $gh_ids[$issue_info['issue']['number']] = array(
            'estimate' => $issue_info['estimate'],
            'status' => $issue_info['issue']['state'] ? $issue_info['issue']['state'] : 'closed',
            'title' => $issue_info['issue']['title'],
          );
        }
      }
    }

  }

  $total_time_spent = $track['field_issues_logs_field_time_spent_value'];
  // No Issue was found, use old log id as identifier.
  if (empty($gh_ids)) {
    // Create one default item to make the loop run one time.
    // Default is is this case match to actual.
    $gh_ids[$track['field_issues_logs_id']] = array(
      'estimate' => $total_time_spent,
      'status' => 'closed',
      'title' => $track['field_issues_logs_field_issue_label_value'],
    );
  }

  foreach ($gh_ids as $gh_issue_number => $gh_issue_info) {
    // Set default estimate for non dev.
    if ($track['field_issues_logs_field_issue_type_value'] != 'dev') {
      if (!$gh_issue_info['estimate']) {
        $gh_issue_info['estimate'] = $total_time_spent;
      }
    }

    $issue = array(
      'uid' => $old_track_node_wrapper->author->getIdentifier(),
      // Use real nid as issue id to be able to reimport.
      'issue_id' => $gh_issue_number,
      'github_repo' => $default_repo,
      'estimate' => $gh_issue_info['estimate'],
      'project' => $old_track_node_wrapper->field_project->getIdentifier(),
      'title' => $gh_issue_info['title'],
      'status' => $gh_issue_info['status'],
    );

    $wrapper = get_new_tracking($issue);
    $node = $wrapper->value();

    // Create log for time divided by number of issue related.
    $logs = array();
    $logs['und'][] = create_multifields_track($track, $total_time_spent/ count($gh_ids), $clean_repo, $gh_user, $pr_id);

    if (!isset($processed_tracking[$gh_issue_number])) {
      // First time processing this node, erase all other tracking.
      $processed_tracking[$gh_issue_number] = TRUE;
    }
    else {
      if (isset($node->field_track_log['und'])) {
        foreach ($node->field_track_log['und'] as $existing_log) {
          $logs['und'][] = $existing_log;
        }
      }
    }
    $node->field_track_log = $logs;


    $wrapper->save();
    print("Saving Tracking. old_track_id: $old_track_id  \n");
  }
  $count_track--;
  print("remaining track: {$count_track}.  \n");
}


/**
 * Create a well formated log track multifileld.
 */
function create_multifields_track($track, $total_time_spent, $clean_repo, $gh_user, $pr_id) {
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

  $log = array();
  $old_track_node = $old_track_node_wrapper->value();
  $log['field_date']['und'][0]['value'] = $old_track_node->field_work_date['und'][0]['value'];
  $log['field_issue_label']['und'][0]['value'] = $track['field_issues_logs_field_issue_label_value'];
  $status = 'closed';
  // PR id.
  if ($pr_node) {
    // pr_id is the pr we found in title name or ref from node.
    $pr_info = productivity_tracking_get_issue_info($clean_repo, $pr_id, $gh_user);
    $status = $pr_info['issue']['state'];

    if ($last_date) {
      $log['field_last_push']['und'][0]['value'] = $last_date;
    }
  }
  if ($pr_id) {
    $log['field_issue_id']['und'][0]['value'] = $pr_id;
  }

  $term = productivity_tracking_get_term_status($status);
  $log['field_issue_status']['und'][0]['target_id'] = $term->tid;

  if ($old_track_node_wrapper->field_employee->value()) {
    $log['field_github_username']['und'][0]['value'] = $old_track_node_wrapper->field_employee->field_github_username->value();
    $log['field_employee']['und'][0]['target_id'] = $old_track_node_wrapper->field_employee->getIdentifier();
  }
  $log['field_time_spent']['und'][0]['value'] = $total_time_spent;
  $log['field_issue_type']['und'][0]['value'] = $track['field_issues_logs_field_issue_type_value'];

  return $log;
}

/**
 * Get old tracking logs.
 */
function get_all_tracked_data($track_id, $project_nid = FALSE) {
  $query = db_select('field_data_field_issues_logs', 'il');

  // Project.
  $query
    ->leftJoin('field_data_field_project', 'p', 'il.entity_id = p.entity_id');

  // issue or PR
  $query
    ->leftJoin('field_data_field_issue_id', 'g_id', 'il.field_issues_logs_field_github_issue_target_id = g_id.entity_id');
  $query
    ->leftJoin('field_data_field_github_project_id', 'repo', 'il.field_issues_logs_field_github_issue_target_id = repo.entity_id');

  $query
    ->fields('il')
    ->fields('repo', array('field_github_project_id_value'))
    // GH issue nid.
    ->orderBy('il.field_issues_logs_id', 'DESC');

  if ($project_nid) {
    $query
      ->condition('p.field_project_target_id', $project_nid);
  }

  if ($track_id) {
    $query
      ->condition('il.field_issues_logs_id', $track_id);
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
  $wrapper->body->value->set($issue['title']);
  $wrapper->field_time_estimate->set($issue['estimate']);

  if ($issue['issue_id']) {
    $wrapper->field_issue_id->set($issue['issue_id']);
  }
  $wrapper->field_github_project_id->set($issue['github_repo']);


  $term = productivity_tracking_get_term_status($issue['status']);

  $wrapper->field_issue_status->set($term);
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