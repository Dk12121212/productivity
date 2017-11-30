<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <?php print $content['top']; ?>
    </div>
  </div>
</div>

<div class="row" id="user-profile">
  <div class="col-lg-12 col-md-12 col-sm-12">
    <div class="main-box clearfix">
      <div class="tabs-wrapper profile-tabs">
        <ul class="nav nav-tabs">
          <li class="<?php print (!isset($_GET['active_tab']) || ($_GET['active_tab'] == 'tracking')) ? 'active' : ''; ?>"><a href="#tab-tracking" data-toggle="tab">Tracking</a></li>
          <li class="<?php print (isset($_GET['active_tab']) && ($_GET['active_tab'] == 'timewatch')) ? 'active' : ''; ?>"><a href="#tab-attendence" data-toggle="tab">Timewatch</a></li>
          <li class="<?php print (isset($_GET['active_tab']) && ($_GET['active_tab'] == 'totals')) ? 'active' : ''; ?>"><a href="#tab-totals" data-toggle="tab">Project totals</a></li>
        </ul>
        <div class="tab-content">

          <div class="tab-pane fade in <?php print (!isset($_GET['active_tab']) || ($_GET['active_tab'] == 'tracking')) ? 'active' : ''; ?>" id="tab-tracking">
            <?php print $content['tracking']; ?>
          </div>

          <div class="tab-pane fade in <?php print (isset($_GET['active_tab']) && ($_GET['active_tab'] == 'timewatch')) ? 'active' : ''; ?>" id="tab-attendence">
            <div class="main-box-body emerald-box col-sm-12"><?php print $content['attendance']; ?></div>
            <div class="main-box-body emerald-box col-sm-6"><?php print $content['attendance-left']; ?></div>
            <div class="main-box-body emerald-box col-sm-6"><?php print $content['attendance-right']; ?></div>
          </div>

          <div class="tab-pane fade in <?php print (isset($_GET['active_tab']) && ($_GET['active_tab'] == 'totals')) ? 'active' : ''; ?>" id="tab-totals">
            <div class="main-box-body emerald-box col-sm-6"><?php print $content['totals-left']; ?></div>
            <div class="main-box-body emerald-box col-sm-6"><?php print $content['totals-right']; ?></div>
          </div>

        </div>
      </div>
    </div>
  </div>
</div>

<div class="row">
  <div class="main-box emerald-box col-sm-12">
    <div class="main-box-body emerald-box col-sm-6">
      <?php print $content['bottom-right']; ?>
    </div>
    <div class="main-box-body emerald-box col-sm-6">
      <?php print $content['bottom-left']; ?>
    </div>
  </div>
</div>