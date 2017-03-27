<div style="font-size:26px; text-align: center;">
  <a href="<?php print $urls['previous_month']; ?>" class=""><i class="fa fa-caret-left"></i></a>
  <span><?php print $month; ?> - <?php print $year; ?></span>
  <a href="<?php print $urls['next_month']; ?>" class=""><i class="fa fa-caret-right"></i></a>
</div>


<div class="row clearfix">
  <div class="col-md-12 column">
    <table class="table table-striped table-hover track-item-table table-condensed">
      <thead>
      <tr>
        <th>#</th>
        <?php foreach($days_link as $link): ?>
          <th><?php print $link; ?></th>
        <?php endforeach; ?>
      </tr>
      </thead>
      <tbody>
      <tr class="track-item">
        <?php foreach($tracking as $tracks): ?>
          <td>
            <ul class="list-unstyled">
              <?php foreach($tracks as $track): ?>
                <li>
                  <a href="<?php print $track['pr_href']; ?>" data-toggle="tooltip" title="<?php print $track['title']; ?>" class="<?php print $track['type']; ?>" target="_blank">
                    <?php print $track['length']; ?>
                  </a>
                </li>
              <?php endforeach; ?>
              <!--  TBD Summary of day -->
<!--              <li>-->
<!--                <strong>8.00</strong>-->
<!--              </li>-->
            </ul>
          </td>
        <?php endforeach; ?>
      </tr>
      </tbody>
    </table>
  </div>
</div>

<div class="row clearfix">
  <div class="col-md-12 column">
    <form class="form-horizontal">
      <fieldset>

        <!-- Form Name -->
        <legend>Tracking for <?php print "$username: $day/$month/$year"; ?></legend>

        <!-- Select Basic -->
<!--        <div class="form-group">-->
<!--          <label class="col-md-4 control-label" for="selectbasic">Day type</label>-->
<!--          <div class="col-md-4">-->
<!--            <select id="selectbasic" name="selectbasic" class="form-control">-->
<!--              <option value="regular">Regular</option>-->
<!--              <option value="sick">Sick</option>-->
<!--              <option value="vacation">Vacation</option>-->
<!--              <option value="miluim">Miluim</option>-->
<!--              <option value="convention">Convention</option>-->
<!--            </select>-->
<!--          </div>-->
<!--        </div>-->
      </fieldset>
    </form>

    <table id="table-tracking" class="table table-bordered table-hover">
      <thead>
      <tr>
        <th class="text-center" data-override="mlid">
          #
        </th>
        <th class="text-center" data-override="project_nid">
          Project
        </th>
        <th class="text-center" data-override="repo">
          Repo
        </th>
        <th class="text-center" data-override="issue">
          Issues #
        </th>
        <th class="text-center" data-override="pr">
          PR #
        </th>
        <th class="text-center" data-override="description">
          Description
        </th>
        <th class="text-center" data-override="type" >
          Type
        </th>
        <th class="text-center" data-override="time_spent">
          Time
        </th>
        <th class="text-center">
          Del
        </th>
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
  <button id="add_row" class="btn btn-success"><i class="fa fa-plus-circle"></i> Add Row</button>
</div>

<!-- Messages -->
<div id="messages">
</div>

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