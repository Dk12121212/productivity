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
          <?php foreach($days_link as $key => $link): ?>
            <th <?php if($day == $key) { print 'class="active"'; } ?>><?php print $link; ?></th>
          <?php endforeach; ?>
        </tr>
        </thead>
        <tbody>
          <?php foreach($tracks as $tracking): ?>
            <tr class="track-item">
              <?php foreach($tracking['data']['days'] as $key => $tracks): ?>
                <td>
                  <ul class="list-unstyled">
                    <?php $classes = ''?>
                    <?php foreach($tracks as $track): ?>
                      <?php if ($track['type'] == 'name' && !$expanded): ?>
                        <!--     User name   -->
                        <li class="<?php print $track['type']; ?>">
                          <a href="<?php print $track['pr_href']; ?>" target="_blank"><?php print $track['length']; ?></a>
                        </li>
                      <?php endif; ?>
                      <?php  if (isset($track['class']) && $track['class'] == 'tracking'): ?>
                        <!--     tracking data            -->
                        <?php $classes .= ' ' . $track['project_nid']; ?>
                        <li<?php print ' mlid="' . $track['mlid'] . '"'; if (!$expanded && $track['expandable'] ) { print ' style="display:none"';} ?>>
                          <a href="<?php print $track['pr_href']; ?>" data-toggle="tooltip" title="<?php print check_plain("{$track['projectName']}: {$track['title']}"); ?>" class="<?php print $track['class'] . ' ' . $track['project_nid']; ?>" target="_blank"><?php print $track['length']; ?></a>
                        </li>
                      <?php endif; ?>
                      <?php if ($track['type'] == 'global'):  ?>
                        <!--      Non tracking data            -->
                        <li data-toggle="tooltip" title="<?php print check_plain($track['title']); ?>" class="<?php print $track['class']; ?>">
                          <?php print $track['length']; ?>
                        </li>
                      <?php endif; ?>
                    <?php endforeach; ?>
                    <li data-toggle="tooltip" title="Total logged" class="<?php print $classes; ?>">
                      <strong><?php if (isset($tracking['data']['sum']['days'][$key])) { print $tracking['data']['sum']['days'][$key];} ?></strong>
                    </li>
                    <li data-toggle="tooltip" title="Timewatch total">
                      <strong><?php if (isset($tracking['timewatch']['days_sum'][$key])) { print $tracking['timewatch']['days_sum'][$key];} ?></strong>
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
  .table>thead>tr>th.active {
    background-color: #F5F60C;
  }
  .table td, .table th {
    text-align: center;
  }
  .highlight {
    font-weight: bold;
    background: yellow;
  }
  .table tbody > tr.track-item > td {
    vertical-align: bottom;
  }
  table tbody > tr.track-item .weekend {
    color: blueviolet;
  }
  table tbody > tr.track-item .vacation {
    color: #002F31;
  }
  table tbody > tr.track-item .holiday {
    color: brown;
  }
  table tbody > tr.track-item .empty {
    color: red;
  }
  table tbody > tr.track-item .Sick {
    color: #761c19;
  }
  table tbody > tr.track-item .Miluim {
    color: darkgreen;
  }
  table tbody > tr.track-item .Convention {
      color: seagreen;
  }
</style>