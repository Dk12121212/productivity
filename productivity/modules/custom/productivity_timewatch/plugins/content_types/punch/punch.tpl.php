<div class="main-box">
  <div class="row">
    <?php if($can_punch): ?>
    <div class="col-lg-6 col-md-6">
        <div class="main-box-body clearfix">
          <form action="<?php print $self_url; ?>" method="post" class="form-inline" role="form">
            <div class="checkbox checkbox-nice">
              <input type="checkbox" name="madan" value='municipality' id="remember-me" />
              <label for="remember-me">
                Municipality
              </label>
            </div>
            <input type="hidden" name="dayType" value="regular">
            <button type="submit" class="btn btn-success">Punch Now</button>
          </form>

        </div>
      </div>
      <div class="col-lg-6 col-md-6">
        <form action="<?php print $self_url; ?>" method="post" class="form-inline" role="form">
          <div class="form-group">
            <?php print  "Mark $day/$month/$year as:";?>
            <select id="selectbasic" name="dayType" class="form-control">
              <option value="sick">Sick</option>
              <option value="vacation">Vacation</option>
              <option value="miluim">Miluim</option>
              <option value="convention">Convention</option>
            </select>
          </div>
          <button type="submit" class="btn btn-info">Submit</button>
        </form>
      </div>
    </div>

    <?php endif; ?>
    <?php if($timewatch): ?>
    <div class="row">
      <div class="col-lg-12">
        <header class="main-box-header clearfix">
          <h2 class="pull-left">Punches on <?php print "$day/$month/$year";?></h2>
        </header>
        <div class="main-box-body clearfix">
          <div class="table-responsive">
            <table class="table">
              <thead>
                <tr>
                  <th>Time In</th>
                  <th>Time Out</th>
                  <th class="text-center">Municipality</th>
                </tr>
              </thead>
              <tbody>
              <?php foreach($timewatch['days'] as $punch): ?>
                <tr>
                  <td class="text-center">
                    <?php print $punch['03.entry']; ?>
                  </td>
                  <td class="text-center">
                    <?php print ($punch['05.total'] != '0:00') ? $punch['04.exit'] : t('Not punch yet'); ?>
                  </td>
                  <td class="text-center">
                    <span class="label label-success"><?php print $punch['06.project'] == 'Regular' ? 'NO' : 'YES'; ?></span>
                  </td>
                </tr>
              <?php endforeach; ?>
              </tbody>
            </table>
          </div>
        </div>
      </div>
    <?php endif; ?>
  </div>
</div>