<div class="row">
  <div class="main-box">
    <?php if($can_punch): ?>
    <div class="col-lg-12">
        <div class="main-box-body clearfix">
          <form class="form-inline" role="form">
            <div class="form-group">
              <select id="selectbasic" name="selectbasic" class="form-control">
                <option value="regular">Regular</option>
                <option value="sick">Sick</option>
                <option value="vacation">Vacation</option>
                <option value="miluim">Miluim</option>
                <option value="convention">Convention</option>
              </select>
            </div>
            <div class="checkbox checkbox-nice">
              <input type="checkbox" id="remember-me" />
              <label for="remember-me">
                Municipality
              </label>
            </div>
            <button type="submit" class="btn btn-success"><i class="fa fa-circle-o-notch"></i> Punch Now</button>
          </form>
        </div>
      </div>
    <?php endif; ?>
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
              <tr>
                <td class="text-center">
                  2013/08/08
                </td>
                <td class="text-center">
                  <a href="#">Robert De Niro</a>
                </td>
                <td class="text-center">
                  <span class="label label-success">Yes</span>
                </td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>
  </div>
</div>