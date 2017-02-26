<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <?php print $content['top']; ?>
    </div>
  </div>
</div>


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

<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <?php print $content['bottom']; ?>
    </div>
  </div>
</div>