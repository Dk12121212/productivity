<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <div class="row">
        <div class="col-sm-12"><?php print $message; ?></div>
      </div>
      <h3>Month <?php print "$year/$month"; ?></h3>
      <div class="row">
        <div class="col-lg-3 col-sm-6 col-xs-12">
          <div class="main-box infographic-box">
            <i class="fa fa-user red-bg"></i>
            <span class="headline">Billed hours (overtime)</span>
            <span class="value"><?php print $total_hours; ?></span>
          </div>
            <span class="">Overtime hour are hours paid on average lower than original rate due to over scope work.</span>
        </div>
        <div class="col-lg-3 col-sm-6 col-xs-12">
          <div class="main-box infographic-box">
            <i class="fa fa-eye yellow-bg"></i>
            <span class="headline">Hours not billed</span>
            <span class="value"><?php print $total_hours_not_billed; ?></span>
          </div>
        </div>
        <div class="col-lg-3 col-sm-6 col-xs-12">
          <div class="main-box infographic-box">
            <i class="fa fa-shopping-cart emerald-bg"></i>
            <span class="headline">Total Projects</span>
            <span class="value"><?php print $total_projects; ?></span>
          </div>
        </div>
        <div class="col-lg-3 col-sm-6 col-xs-12">
          <div class="main-box infographic-box">
            <i class="fa fa-money green-bg"></i>
            <span class="headline">Income <?php print $rate_str; ?></span>
            <span class="value"><?php print $total_ils; ?></span>
          </div>
        </div>
      </div>
      <?php print $table; ?>
    </div>
  </div>
</div>
