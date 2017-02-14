<?php
/**
 * Created by PhpStorm.
 * User: brice
 * Date: 14/02/2017
 * Time: 11:38 AM
 */

$project_nid = drush_get_option('project', 33709);

// Get all tracks for project.

$tracking = productivity_tracking_get_tracking($project_nid);


if (empty($count = $tracking->rowCount())) {
  print('No issues found for project: ' . $project_nid);
}

print "Going over $count tracking. \n";

$processed = [];

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

  // Issue data.
  $repo_id = $track_record['field_github_project_id_value'];
  $estimate = $track_record['field_time_estimate_value'];
  $issue_id = $track_record['field_issue_id_value'];
  $nid = $track_record['nid'];

  // Brak repo into usename and repo.
  $clean_repo = explode('/', $repo_id);
  $gh_user = $clean_repo[0];
  $clean_repo = $clean_repo[1];

  // Prevent duplicate
  if (!isset($processed["nid_$nid"]) && $issue_id) {
    print "Updating node $nid \n";
    $wrapper = entity_metadata_wrapper('node', $nid);
    $issue_info = productivity_tracking_get_issue_info($clean_repo, $issue_id, $gh_user);
    $wrapper->field_time_estimate->set($issue_info['estimate']);

    // Save status.
    $term = productivity_tracking_get_term_status($issue_info['issue']['state']);
    $wrapper->field_issue_status->set($term);

    $wrapper->save();

    $processed["nid_$nid"] = TRUE;
  }

  if ($pr_gh_id) {
    print "Checking track $track_id \n";
    $pr_info = productivity_tracking_get_issue_info($clean_repo, $pr_gh_id, $gh_user);

    // Save status.
    $term = productivity_tracking_get_term_status($pr_info['issue']['state']);

    $mf_update =
      db_update('field_data_field_track_log')
        ->fields(array(
          'field_track_log_field_issue_status_target_id' => $term->tid,
          )
        )
      ->condition('field_track_log_id', $track_id)
      ->execute();

  }

  $count--;
  print "$count tracking left. \n";
}