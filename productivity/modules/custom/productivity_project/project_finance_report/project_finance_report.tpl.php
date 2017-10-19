<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <div class="row">
        <div class="col-sm-12"><?php print $message; ?></div>
      </div>
      <?php foreach($tables as $year => $table): ?>
        <h3>Year <?php print $year; ?></h3>
        <?php print $table; ?>
      <?php endforeach; ?>
    </div>
  </div>
</div>
