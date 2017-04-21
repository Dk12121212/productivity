<form id="trackform" name="trackform">
  <div class="row clearfix">
    <div class="col-md-12 column">
      <legend style="text-align: center;"><?php print "$username: $day/$month/$year"; if($today) { print ' - (Today)'; }; ?></legend>
      <table id="table-tracking" class="table table-bordered table-hover">
        <thead>
          <tr>
            <th class="text-center" data-override="mlid">#</th>
            <th class="text-center" data-override="project_nid">Project</th>
            <th class="text-center" data-override="repo">Repo</th>
            <th class="text-center" data-override="issue">Issues #</th>
            <th class="text-center" data-override="pr">PR #</th>
            <th class="text-center" data-override="description">Description</th>
            <th class="text-center" data-override="type" >Type</th>
            <th class="text-center" data-override="time_spent">Time</th>
            <th class="text-center">Del</th>
          </tr>
        </thead>
        <tbody>
          <?php foreach($rows as $track_row): ?>
            <?php print $track_row; ?>
          <?php endforeach; ?>
        </tbody>
      </table>
    </div>
  </div>

  <div>
    <button id="submit" name="submit" type="submit" class="btn btn-primary "><i class="fa fa-circle-o-notch"></i> Save</button>
    <button id="add_row" type="button" class="btn btn-success"><i class="fa fa-plus-circle"></i> Add Row</button>
  </div>

</form>

<!-- Messages -->
<div id="messages"></div>

<!-- Template for message Error -->
<div id="templateMsg" class="alert alert-danger" style="display: none;">
  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">×</button>
  <i class="fa fa-times-circle fa-fw fa-lg"></i>
  <strong>Oh snap!</strong>
  <span id="messageText"></span>
  <a href="#" class="alert-link">Contact site administrator</a>.
</div>

<!-- Stub row -->
<table style="display: none;">
  <tbody>
   <?php print $row_template; ?>
  </tbody>
</table>