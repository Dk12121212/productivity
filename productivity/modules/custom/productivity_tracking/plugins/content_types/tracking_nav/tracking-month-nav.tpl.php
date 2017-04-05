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
          <?php foreach($tracks as $key => $tracking): ?>
            <tr class="track-item">
              <?php foreach($tracking['days'] as $key => $tracks): ?>
                <td>
                  <ul class="list-unstyled">
                    <?php foreach($tracks as $track): ?>
                      <!--     User name   -->
                      <?php if ($track['type'] == 'name'): ?>
                        <li class="<?php print $track['type']; ?>">
                          <a href="<?php print $track['pr_href']; ?>" target="_blank"><?php print $track['length']; ?></a>
                        </li>
                      <?php endif; ?>
                      <!--     tracking data            -->
                      <?php  if ($track['type'] == 'tracking'): ?>
                        <li<?php print ' mlid="' . $track['mlid'] . '"'; if (!$expanded && $track['expandable'] ) { print ' style="display:none"';} ?>>
                          <a href="<?php print $track['pr_href']; ?>" data-toggle="tooltip" title="<?php print check_plain($track['title']); ?>" class="<?php print $track['class']; ?>" target="_blank"><?php print $track['length']; ?></a>
                        </li>
                      <?php endif; ?>
                      <!--      Non tracking data            -->
                      <?php if ($track['type'] == 'global'):  ?>
                        <li data-toggle="tooltip" title="<?php print check_plain($track['title']); ?>" class="<?php print $track['class']; ?>">
                          <?php print $track['length']; ?>
                        </li>
                      <?php endif; ?>
                    <?php endforeach; ?>
                    <li>
                      <strong><?php if (isset($tracking['sum']['days'][$key])) { print $tracking['sum']['days'][$key];} ?></strong>
                    </li>
                  </ul>
                </td>
              <?php endforeach; ?>
            </tr>
          <?php endforeach; ?>
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