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
          <li class=""><a href="#tab-tracking" data-toggle="tab">Tracking</a></li>
          <li class="active"><a href="#tab-attendence" data-toggle="tab">Timewatch</a></li>
        </ul>
        <div class="tab-content">
          <div class="tab-pane fade in " id="tab-tracking">
            <?php print $content['tracking']; ?>
          </div>
          <div class="tab-pane fade in active" id="tab-attendence">
            <?php print $content['attendance']; ?>
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