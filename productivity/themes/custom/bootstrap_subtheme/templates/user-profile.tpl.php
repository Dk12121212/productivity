<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>
<div class="row" id="user-profile">
  <div class="col-lg-3 col-md-4 col-sm-4">
    <div class="main-box clearfix">
      <header class="main-box-header clearfix">
        <h2><?php print $user->name; ?></h2>
      </header>
      <div class="main-box-body clearfix">
        <img src="<?php print 'http://www.gravatar.com/avatar/' . md5(strtolower(trim($user->mail))) . '.jpg';?>" alt="User gravater" class="profile-img img-responsive center-block"/>
      </div>
    </div>
  </div>
  <div class="col-lg-9 col-md-8 col-sm-8">
    <div class="main-box clearfix">
      <div class="tabs-wrapper profile-tabs">
        <ul class="nav nav-tabs">
          <li class="active"><a href="#tab-attendance" data-toggle="tab">Attendance</a></li>
        </ul>
        <div class="tab-content">
          <div class="tab-pane fade in active" id="tab-attendance">
          </div>
        </div>
      </div>
    </div>
  </div>
</div>