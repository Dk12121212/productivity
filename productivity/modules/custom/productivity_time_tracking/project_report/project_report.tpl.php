<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <p class="show-only-on-print"><?php print $date; ?></p>
      <div id="header" class="col-sm-12">
        <h1 id="project-title"><?php print t('Project Tracking Report'); ?></h1>
        <h2 id="gizra-logo">gizra</h2>
      </div>
      <div id="search-filter" class="row">
        <div class="col-sm-12">
          <div class="col-sm-4">
            <select id="project_filter" class="form-control">
              <?php foreach($projects as $nid => $project_name): ?>
                <option value="<?php print $nid;?>"<?php print ($nid == $current_project_id) ? 'selected' : ''; ?>><?php print $project_name; ?></option>
              <?php endforeach; ?>
            </select>
          </div>
            <button class="btn btn-primary apply" type="button">Apply</button>
          </div>
        </div>
      </div>
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
