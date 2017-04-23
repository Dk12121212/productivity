<?php
/**
 * Created by PhpStorm.
 * User: brice
 * Date: 14/02/2017
 * Time: 11:38 AM
 */

$project_nid = drush_get_option('project', 2587);

// Get all tracks for project.

$tracking = productivity_tracking_get_tracking_nodes($project_nid);


if (empty($count = $tracking->rowCount())) {
  print('No issues found for project: ' . $project_nid);
  return;
}

print "Going over $count tracking. \n";

// Prepare table for tracking data.
while($track_record = $tracking->fetchAssoc()) {
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
  if ($issue_id) {
    print "Updating node $nid \n";
    $wrapper = entity_metadata_wrapper('node', $nid);
    $issue_info = productivity_tracking_get_issue_info($clean_repo, $issue_id, $gh_user);
    $wrapper->field_time_estimate->set($issue_info['estimate']);

    // Save status.
    $term = productivity_tracking_get_term($issue_info['issue']['state']);
    $wrapper->field_issue_status->set($term);

    $wrapper->save();

  }

  $term = productivity_tracking_get_term($pr_info['issue']['state']);

  $count--;
  print "$count tracking left. \n";
}