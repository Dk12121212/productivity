<div id="month-nav">
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
          <?php foreach($tracking['days'] as $key => $tracks): ?>
            <td>
              <ul class="list-unstyled">
                <?php foreach($tracks as $track): ?>
                    <?php if (isset($track['pr_href'])): ?>
                      <li mlid="<?php print $track['mlid']; ?>">
                      <a href="<?php print $track['pr_href']; ?>" data-toggle="tooltip" title="<?php print check_plain($track['title']); ?>" class="<?php print $track['type']; ?>" target="_blank">
                        <?php print $track['length']; ?>
                      </a>
                    <?php endif; ?>
                    <!--      Non tracking data            -->
                    <?php if (!isset($track['pr_href'])): ?>
                      <li data-toggle="tooltip" title="<?php print check_plain($track['title']); ?>" class="<?php print $track['type']; ?>">
                        <?php print $track['length']; ?>
                    <?php endif; ?>
                  </li>
                <?php endforeach; ?>
                <li>
                  <strong><?php if (isset($tracking['sum']['days'][$key])) { print $tracking['sum']['days'][$key];} ?></strong>
                </li>
              </ul>
            </td>
          <?php endforeach; ?>
        </tr>
        </tbody>
      </table>
    </div>
  </div>
</div>


<style>
  .table tbody > tr.track-item > td {
    vertical-align: bottom;
  }
</style>