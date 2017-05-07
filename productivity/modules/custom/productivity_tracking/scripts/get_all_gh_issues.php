<?php
/**
 * Fetch issues from GH and create or update tracking nodes.
 */

$repo_user = drush_get_option('gh_id', 'Gizra');
$repo = drush_get_option('gh_id', 'ic-infuse');
$min_issue_id = drush_get_option('min_issue_id', '1');
$max_issue_id = drush_get_option('max_issue_id', '151');

// TODO: deal with multiple project, in this case we don't want to assign issue
// to new projects, we probably want to set a range per project using a other
// option, for now we have just update to prevent this to be a problem.

// Add an option to not create new issues, just update.
$just_update= drush_get_option('just_update', TRUE);

// Disable issue caching.
$no_cache = drush_get_option('no_cache', FALSE);

for($issue_num = $min_issue_id; $issue_num <= $max_issue_id; $issue_num++) {
  $issue_or_pr = productivity_tracking_get_issue_info($repo, $issue_num, $repo_user, TRUE, $no_cache);
  $gh_username = '';
  $pr = $issue = [];
  productivity_admin_log("Processing $repo_user/$repo/$issue_num", 'success');
  if(isset($issue_or_pr['issue']['pull_request'])) {
    $pr = $issue_or_pr;
    $gh_username = $issue_or_pr['issue']['user']['login'];
    // Don't update PR for now. no need.
    productivity_admin_log("Bypass PR $repo_user/$repo/$issue_num", 'success');
    continue;
  }
  else {
    $issue = $issue_or_pr;
    // The user that opened the issue.
    $gh_username = $issue_or_pr['issue']['user']['login'];
  }
  $repository_info = [];
  $repository_info['full_name'] = "$repo_user/$repo";
  if (!$uid = productivity_tracking_get_uid_by_github_username($gh_username)) {
    //Default uid
    $uid = 1;
  }

  if (!productivity_tracking_save_tracking($issue, $pr, $uid, $repository_info, $just_update, FALSE)) {
    productivity_admin_log("Failed to update $repo_user/$repo/$issue_num  this might because the issue did not exist before.", 'error');
  }
  productivity_admin_log("Done $repo_user/$repo/$issue_num", 'success');
}