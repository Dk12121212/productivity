<h2>{{ month }} - {{ year }}</h2>
<div class="row">
  <div class="col-md-10 col-md-push-1 col-md-pull-1">
    <form class="form-horizontal tracking-form" role="form">
      <fieldset>
        <!-- Form Name -->
        <legend>Tracking for 1/1/2017</legend>

        <!-- Day type (inline) -->
        <div class="form-group">
          <label class="col-md-2 control-label">Day type</label>
          <div class="col-md-10">
            <label class="radio-inline" for="daytype-0">
              <input type="radio" value="regular" checked="checked">
              Regular
            </label>
            <label class="radio-inline" for="daytype-1">
              <input type="radio" value="sick">
              Sick
            </label>
            <label class="radio-inline" for="daytype-2">
              <input type="radio" value="vacation">
              Vacation
            </label>
            <label class="radio-inline" for="daytype-3">
              <input type="radio" value="miluim">
              Miluim
            </label>
            <label class="radio-inline" for="daytype-4">
              <input type="radio" value="convention">
              Convention
            </label>
          </div>
        </div>

        <div class="regular-day-wrapper">
          <!-- Select Project -->
          <div class="form-group">
            <label class="col-md-2 col-xs-12 control-label" for="project">Project</label>
            <div class="col-md-8 col-xs-10">
              <select id="project" name="project" class="form-control">
              </select>
            </div>
            <div class="col-md-2 col-xs-2">
              <a class="btn btn-primary"><i class="fa fa-refresh"></i></a>
            </div>
          </div>

          <!-- Issues tracker -->
          <div class="form-group">
            <label class="col-md-2 col-xs-12 control-label">Issues</label>
            <div class="col-md-8 col-xs-12">
              <div class="row issues-row">
                <div class="col-md-6 col-xs-6">
                  <input name="issue-label" type="text" required="true" placeholder="#1: example" class="form-control input-md issue-label">
                </div>
                <div class="col-md-3 col-xs-3">
                  <select name="issues-hours" class="form-control" id="issue-type">
                  </select>
                </div>
                <div class="col-md-3 col-xs-3">
                  <input name="issue-time" type="number" step="0.10" min="0" placeholder="4" class="form-control input-md issue-time">
                </div>
              </div>
            </div>
          </div>
        </div>

        <!-- Total hours-->
        <div class="form-group">
          <label class="col-md-2 control-label">Total hours</label>
          <div class="col-md-8 total-hours">
            <span>8</span>
          </div>
        </div>

        <!-- Button -->
        <div class="form-group">
          <label class="col-md-2 control-label" for="submit"></label>
          <div class="col-md-10">
            <button id="submit" name="submit" type="submit" class="btn btn-primary"><i class="fa fa-check"></i> Save</button>
            <a class="btn btn-success"><i class="fa fa-plus-circle"></i> New</a>
            <a class="btn btn-danger"><i class="fa fa-times"></i> Remove</a>
          </div>
        </div>


      </fieldset>
    </form>
  </div>
</div>
<table class="table table-striped table-hover track-item-table table-condensed">
  <thead>
  <tr>
    <th>#</th>
    <?php foreach($days as $item): ?>
      <th>item</th>
    <?php endforeach; ?>
  </tr>
  </thead>
  <tbody>
  <tr class="track-item">
    <th scope="row"> {{ name }}</th>
    <?php foreach($tracking as $tracks): ?>
    <td>
      <ul class="list-unstyled">
      <?php foreach($tracks as $track): ?>
        <li>
          <a href="LINK TO TRACKING DAY" popover-trigger="mouseenter" popover="project name" class="dev">8hours</a>
        </li>
      <?php endforeach; ?>
      </ul>
    </td>
    <?php endforeach; ?>
  </tr>
  </tbody>
</table>