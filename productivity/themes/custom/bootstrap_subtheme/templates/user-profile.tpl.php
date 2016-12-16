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
        <h2>Scarlett Johansson</h2>
      </header>

      <div class="main-box-body clearfix">
        <div class="profile-status">
          <i class="fa fa-circle"></i> Online
        </div>

        <img src="img/samples/scarlet-159.png" alt="" class="profile-img img-responsive center-block" />

        <div class="profile-label">
          <span class="label label-danger">Admin</span>
        </div>

        <div class="profile-stars">
          <i class="fa fa-star"></i>
          <i class="fa fa-star"></i>
          <i class="fa fa-star"></i>
          <i class="fa fa-star"></i>
          <i class="fa fa-star-o"></i>
          <span>Super User</span>
        </div>

        <div class="profile-since">
          Member since: Jan 2012
        </div>

        <div class="profile-details">
          <ul class="fa-ul">
            <li><i class="fa-li fa fa-truck"></i>Orders: <span>456</span></li>
            <li><i class="fa-li fa fa-comment"></i>Posts: <span>828</span></li>
            <li><i class="fa-li fa fa-tasks"></i>Tasks done: <span>1024</span></li>
          </ul>
        </div>

        <div class="profile-message-btn center-block text-center">
          <a href="#" class="btn btn-success">
            <i class="fa fa-envelope"></i>
            Send message
          </a>
        </div>
      </div>

    </div>
  </div>

  <div class="col-lg-9 col-md-8 col-sm-8">
    <div class="main-box clearfix">
      <div class="tabs-wrapper profile-tabs">
        <ul class="nav nav-tabs">
          <li class="active"><a href="#tab-newsfeed" data-toggle="tab">Newsfeed</a></li>
          <li><a href="#tab-activity" data-toggle="tab">Activity</a></li>
          <li><a href="#tab-friends" data-toggle="tab">Friends</a></li>
          <li><a href="#tab-chat" data-toggle="tab">Chat</a></li>
        </ul>

        <div class="tab-content">
          <div class="tab-pane fade in active" id="tab-newsfeed">

            <div id="newsfeed">
              <div class="story">
                <div class="story-user">
                  <a href="#">
                    <img src="img/samples/robert-300.jpg" alt=""/>
                  </a>
                </div>

                <div class="story-content">
                  <header class="story-header">
                    <div class="story-author">
                      <a href="#" class="story-author-link">
                        Robert Downey Jr.
                      </a>
                      posted a status update
                    </div>
                    <div class="story-time">
                      <i class="fa fa-clock-o"></i> just now
                    </div>
                  </header>
                  <div class="story-inner-content">
                    Now that we know who you are, I know who I am. I'm not a mistake!
                    It all makes sense! In a comic, you know how you can tell who the
                    arch-villain's going to be? He's the exact opposite of the hero.
                    And most times they're friends, like you and me! I should've known
                    way back when... You know why, David? Because of the kids.
                    They called me Mr Glass.
                  </div>
                  <footer class="story-footer">
                    <a href="#" class="story-comments-link">
                      <i class="fa fa-comment fa-lg"></i> 8320 Comments
                    </a>
                    <a href="#" class="story-likes-link">
                      <i class="fa fa-heart fa-lg"></i> 82k Likes
                    </a>
                  </footer>
                </div>
              </div>

              <div class="story">
                <div class="story-user">
                  <a href="#">
                    <img src="img/samples/angelina-300.jpg" alt=""/>
                  </a>
                </div>

                <div class="story-content">
                  <header class="story-header">
                    <div class="story-author">
                      <a href="#" class="story-author-link">
                        Angelina Jolie
                      </a>
                      checked in at <a href="#">Place du Casino</a>
                    </div>
                    <div class="story-time">
                      <i class="fa fa-clock-o"></i> 3 Minutes ago
                    </div>
                  </header>
                  <div class="story-inner-content">
                    <div id="map-apple" class="map-content"></div>
                  </div>
                  <footer class="story-footer">
                    <a href="#" class="story-comments-link">
                      <i class="fa fa-comment fa-lg"></i> 23k Comments
                    </a>
                    <a href="#" class="story-likes-link">
                      <i class="fa fa-heart fa-lg"></i> 159k Likes
                    </a>
                  </footer>
                </div>
              </div>

              <div class="story">
                <div class="story-user">
                  <a href="#">
                    <img src="img/samples/ryan-300.jpg" alt=""/>
                  </a>
                </div>

                <div class="story-content">
                  <header class="story-header">
                    <div class="story-author">
                      <a href="#" class="story-author-link">
                        Ryan Gossling
                      </a>
                      uploaded 5 new photos to album <a href="#">Bora Bora</a>
                    </div>
                    <div class="story-time">
                      <i class="fa fa-clock-o"></i> 8 Hours ago
                    </div>
                  </header>
                  <div class="story-inner-content">
                    <div class="story-images clearfix">
                      <a href="img/samples/tahiti-1.jpg" class="story-image-link">
                        <img src="img/samples/tahiti-1.jpg" alt="" class="img-responsive"/>
                      </a>
                      <a href="img/samples/tahiti-2.jpg" class="story-image-link story-image-link-small">
                        <img src="img/samples/tahiti-2.jpg" alt="" class="img-responsive"/>
                      </a>
                      <a href="img/samples/tahiti-3.jpg" class="story-image-link story-image-link-small">
                        <img src="img/samples/tahiti-3.jpg" alt="" class="img-responsive"/>
                      </a>
                      <a href="img/samples/tahiti-3.jpg" class="story-image-link story-image-link-small">
                        <img src="img/samples/tahiti-3.jpg" alt="" class="img-responsive"/>
                      </a>
                      <a href="img/samples/tahiti-2.jpg" class="story-image-link story-image-link-small hidden-xs">
                        <img src="img/samples/tahiti-2.jpg" alt="" class="img-responsive"/>
                      </a>
                    </div>
                  </div>
                  <footer class="story-footer">
                    <a href="#" class="story-comments-link">
                      <i class="fa fa-comment fa-lg"></i> 46 Comments
                    </a>
                    <a href="#" class="story-likes-link">
                      <i class="fa fa-heart fa-lg"></i> 823 Likes
                    </a>
                  </footer>
                </div>
              </div>
            </div>

          </div>

          <div class="tab-pane fade" id="tab-activity">

            <div class="table-responsive">
              <table class="table">
                <tbody>
                <tr>
                  <td class="text-center">
                    <i class="fa fa-comment"></i>
                  </td>
                  <td>
                    Scarlett Johansson posted a comment in <a href="#">Avengers Initiative</a> project.
                  </td>
                  <td>
                    2014/08/08 12:08
                  </td>
                </tr>
                <tr>
                  <td class="text-center">
                    <i class="fa fa-truck"></i>
                  </td>
                  <td>
                    Scarlett Johansson changed order status from <span class="label label-primary">Pending</span>
                    to <span class="label label-success">Completed</span>
                  </td>
                  <td>
                    2014/08/08 12:08
                  </td>
                </tr>
                <tr>
                  <td class="text-center">
                    <i class="fa fa-check"></i>
                  </td>
                  <td>
                    Scarlett Johansson posted a comment in <a href="#">Lost in Translation opening scene</a> discussion.
                  </td>
                  <td>
                    2014/08/08 12:08
                  </td>
                </tr>
                <tr>
                  <td class="text-center">
                    <i class="fa fa-users"></i>
                  </td>
                  <td>
                    Scarlett Johansson posted a comment in <a href="#">Avengers Initiative</a> project.
                  </td>
                  <td>
                    2014/08/08 12:08
                  </td>
                </tr>
                <tr>
                  <td class="text-center">
                    <i class="fa fa-heart"></i>
                  </td>
                  <td>
                    Scarlett Johansson changed order status from <span class="label label-warning">On Hold</span>
                    to <span class="label label-danger">Disabled</span>
                  </td>
                  <td>
                    2014/08/08 12:08
                  </td>
                </tr>
                <tr>
                  <td class="text-center">
                    <i class="fa fa-check"></i>
                  </td>
                  <td>
                    Scarlett Johansson posted a comment in <a href="#">Lost in Translation opening scene</a> discussion.
                  </td>
                  <td>
                    2014/08/08 12:08
                  </td>
                </tr>
                <tr>
                  <td class="text-center">
                    <i class="fa fa-truck"></i>
                  </td>
                  <td>
                    Scarlett Johansson changed order status from <span class="label label-primary">Pending</span>
                    to <span class="label label-success">Completed</span>
                  </td>
                  <td>
                    2014/08/08 12:08
                  </td>
                </tr>
                <tr>
                  <td class="text-center">
                    <i class="fa fa-users"></i>
                  </td>
                  <td>
                    Scarlett Johansson posted a comment in <a href="#">Avengers Initiative</a> project.
                  </td>
                  <td>
                    2014/08/08 12:08
                  </td>
                </tr>
                </tbody>
              </table>
            </div>

          </div>

          <div class="tab-pane clearfix fade" id="tab-friends">
            <ul class="widget-users row">
              <li class="col-md-6">
                <div class="img">
                  <img src="img/samples/scarlet.png" alt=""/>
                </div>
                <div class="details">
                  <div class="name">
                    <a href="#">Scarlett Johansson</a>
                  </div>
                  <div class="time">
                    <i class="fa fa-clock-o"></i> Last online: 5 minutes ago
                  </div>
                  <div class="type">
                    <span class="label label-danger">Admin</span>
                  </div>
                </div>
              </li>
              <li class="col-md-6">
                <div class="img">
                  <img src="img/samples/kunis.png" alt=""/>
                </div>
                <div class="details">
                  <div class="name">
                    <a href="#">Mila Kunis</a>
                  </div>
                  <div class="time online">
                    <i class="fa fa-check-circle"></i> Online
                  </div>
                  <div class="type">
                    <span class="label label-warning">Pending</span>
                  </div>
                </div>
              </li>
              <li class="col-md-6">
                <div class="img">
                  <img src="img/samples/ryan.png" alt=""/>
                </div>
                <div class="details">
                  <div class="name">
                    <a href="#">Ryan Gossling</a>
                  </div>
                  <div class="time online">
                    <i class="fa fa-check-circle"></i> Online
                  </div>
                </div>
              </li>
              <li class="col-md-6">
                <div class="img">
                  <img src="img/samples/robert.png" alt=""/>
                </div>
                <div class="details">
                  <div class="name">
                    <a href="#">Robert Downey Jr.</a>
                  </div>
                  <div class="time">
                    <i class="fa fa-clock-o"></i> Last online: Thursday
                  </div>
                </div>
              </li>
              <li class="col-md-6">
                <div class="img">
                  <img src="img/samples/emma.png" alt=""/>
                </div>
                <div class="details">
                  <div class="name">
                    <a href="#">Emma Watson</a>
                  </div>
                  <div class="time">
                    <i class="fa fa-clock-o"></i> Last online: 1 week ago
                  </div>
                </div>
              </li>
              <li class="col-md-6">
                <div class="img">
                  <img src="img/samples/george.png" alt=""/>
                </div>
                <div class="details">
                  <div class="name">
                    <a href="#">George Clooney</a>
                  </div>
                  <div class="time">
                    <i class="fa fa-clock-o"></i> Last online: 1 month ago
                  </div>
                </div>
              </li>
              <li class="col-md-6">
                <div class="img">
                  <img src="img/samples/kunis.png" alt=""/>
                </div>
                <div class="details">
                  <div class="name">
                    <a href="#">Mila Kunis</a>
                  </div>
                  <div class="time online">
                    <i class="fa fa-check-circle"></i> Online
                  </div>
                  <div class="type">
                    <span class="label label-warning">Pending</span>
                  </div>
                </div>
              </li>
              <li class="col-md-6">
                <div class="img">
                  <img src="img/samples/ryan.png" alt=""/>
                </div>
                <div class="details">
                  <div class="name">
                    <a href="#">Ryan Gossling</a>
                  </div>
                  <div class="time online">
                    <i class="fa fa-check-circle"></i> Online
                  </div>
                </div>
              </li>
            </ul>
            <br/>
            <a href="#" class="btn btn-success pull-right">View all users</a>
          </div>

          <div class="tab-pane fade" id="tab-chat">
            <div class="conversation-wrapper">
              <div class="conversation-content">
                <div class="conversation-inner">

                  <div class="conversation-item item-left clearfix">
                    <div class="conversation-user">
                      <img src="img/samples/ryan.png" alt=""/>
                    </div>
                    <div class="conversation-body">
                      <div class="name">
                        Ryan Gossling
                      </div>
                      <div class="time hidden-xs">
                        September 21, 2013 18:28
                      </div>
                      <div class="text">
                        I don't think they tried to market it to the billionaire, spelunking,
                        base-jumping crowd.
                      </div>
                    </div>
                  </div>
                  <div class="conversation-item item-right clearfix">
                    <div class="conversation-user">
                      <img src="img/samples/kunis.png" alt=""/>
                    </div>
                    <div class="conversation-body">
                      <div class="name">
                        Mila Kunis
                      </div>
                      <div class="time hidden-xs">
                        September 21, 2013 12:45
                      </div>
                      <div class="text">
                        Normally, both your asses would be dead as fucking fried chicken, but you
                        happen to pull this shit while I'm in a transitional period so I don't wanna
                        kill you, I wanna help you.
                      </div>
                    </div>
                  </div>
                  <div class="conversation-item item-right clearfix">
                    <div class="conversation-user">
                      <img src="img/samples/kunis.png" alt=""/>
                    </div>
                    <div class="conversation-body">
                      <div class="name">
                        Mila Kunis
                      </div>
                      <div class="time hidden-xs">
                        September 21, 2013 12:45
                      </div>
                      <div class="text">
                        Normally, both your asses would be dead as fucking fried chicken, but you
                        happen to pull this shit while I'm in a transitional period so I don't wanna
                        kill you, I wanna help you.
                      </div>
                    </div>
                  </div>
                  <div class="conversation-item item-left clearfix">
                    <div class="conversation-user">
                      <img src="img/samples/ryan.png" alt=""/>
                    </div>
                    <div class="conversation-body">
                      <div class="name">
                        Ryan Gossling
                      </div>
                      <div class="time hidden-xs">
                        September 21, 2013 18:28
                      </div>
                      <div class="text">
                        I don't think they tried to market it to the billionaire, spelunking,
                        base-jumping crowd.
                      </div>
                    </div>
                  </div>
                  <div class="conversation-item item-right clearfix">
                    <div class="conversation-user">
                      <img src="img/samples/kunis.png" alt=""/>
                    </div>
                    <div class="conversation-body">
                      <div class="name">
                        Mila Kunis
                      </div>
                      <div class="time hidden-xs">
                        September 21, 2013 12:45
                      </div>
                      <div class="text">
                        Normally, both your asses would be dead as fucking fried chicken, but you
                        happen to pull this shit while I'm in a transitional period so I don't wanna
                        kill you, I wanna help you.
                      </div>
                    </div>
                  </div>

                </div>
              </div>
              <div class="conversation-new-message">
                <form>
                  <div class="form-group">
                    <textarea class="form-control" rows="2" placeholder="Enter your message..."></textarea>
                  </div>

                  <div class="clearfix">
                    <button type="submit" class="btn btn-success pull-right">Send message</button>
                  </div>
                </form>
              </div>
            </div>
          </div>
        </div>
      </div>

    </div>
  </div>
</div>




<div class="profile"<?php print $attributes; ?>>
  <?php dpm($user_profile); print render($user_profile); ?>
</div>
