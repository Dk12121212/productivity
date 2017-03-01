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
                  <a href=" <?php print $track['href']; ?>" data-toggle="tooltip" title="<?php print $track['title']; ?>" class=" <?php print $track['type']; ?>">
                    <?php print $track['length']; ?>
                  </a>
                </li>
              <?php endforeach; ?>
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
        <legend>Tracking for <?php print "$day/$month/$year"; ?></legend>

        <!-- Select Basic -->
        <div class="form-group">
          <label class="col-md-4 control-label" for="selectbasic">Day type</label>
          <div class="col-md-4">
            <select id="selectbasic" name="selectbasic" class="form-control">
              <option value="regular">Regular</option>
              <option value="sick">Sick</option>
              <option value="vacation">Vacation</option>
              <option value="miluim">Miluim</option>
              <option value="convention">Convention</option>
            </select>
          </div>
        </div>
      </fieldset>
    </form>

    <table class="table table-bordered table-hover" id="tab_logic">
      <thead>
      <tr >
        <th class="text-center">
          #
        </th>
        <th class="text-center">
          Project
        </th>
        <th class="text-center">
          Issues #
        </th>
        <th class="text-center">
          PR #
        </th>
        <th class="text-center">
          Description
        </th>
        <th class="text-center">
          Time (0)
        </th>
      </tr>
      </thead>
      <tbody>
      </tbody>
    </table>
  </div>
</div>

<a id="add_row" class="btn btn-success"><i class="fa fa-plus-circle"></i> Add Row</a>
<a id='delete_row' class="pull-right btn btn-default"><i class="fa fa-minus-circle"></i> Delete Row</a>
<button id="submit" name="submit" type="submit" class="pull-left btn btn-primary"><i class="fa fa-check"></i> Save</button>

<script>

jQuery(document).ready(function(){
  jQuery('#tab_logic').append(jQuery("#templateRow").clone().attr('id', 'addr0'));
  var i=1;
  jQuery("#add_row").click(function(){
    jQuery('#tab_logic').append(jQuery("#templateRow").clone().attr('id', 'addr'+(i)));
    i++;
  });
  jQuery("#delete_row").click(function(){
    if(i>1){
      jQuery("#addr"+(i-1)).remove();
      i--;
    }
  });

});

</script>

<table style="display: none;">
  <tbody>
    <tr id="templateRow">
      <td>
        1
      </td>
      <td>
        <select id="selectbasic" name="selectbasic" class="form-control">
          <?php foreach ($projects as $key => $project): ?>
            <option value="<?php print $key; ?><"><?php print $project; ?></option>
          <?php endforeach; ?>
        </select>
      </td>
      <td>
        <input type="text" name='mail0' placeholder='#' class="form-control"/>
      </td>
      <td>
        <input type="text" name='mail0' placeholder='#' class="form-control"/>
      </td>
      <td>
        <input type="text" name='mobile0' placeholder='Description' class="form-control" disabled/>
      </td>
      <td>
        <input name="issue-time" type="number" step="0.10" min="0" placeholder="4" class="form-control input-md issue-time">
      </td>
    </tr>
  </tbody>
</table>