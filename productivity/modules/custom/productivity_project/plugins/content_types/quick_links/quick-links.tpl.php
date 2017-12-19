<div class="main-box-body clearfix noprint">
  <div class="panel-group accordion" id="accordion">
    <div class="panel panel-default">

      <div class="panel-heading">
        <h4 class="panel-title">
          <a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion" href="#collapseOne">
            Project quick links
          </a>
        </h4>
      </div>
      <div id="collapseOne" class="panel-collapse collapse">
        <div class="panel-body">
          <div class="main-box clearfix project-box emerald-box col-sm-12">
            <div class="main-box-body clearfix">

              <div class="quick-links main-box clearfix">
                <div class="main-box-body clearfix">
                  <?php foreach($urls as $key => $url): ?>
                    <span class="label <?php print $active == $key ? 'label-danger' : 'label-default '; ?>"><?php print $url; ?></span>
                  <?php endforeach; ?>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>

<style>
  .quick-links a {
    color: white;
    line-height: 3;
  }
</style>