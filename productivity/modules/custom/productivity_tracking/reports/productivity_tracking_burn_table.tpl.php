<div class="back-link">
  <?php print $backlink; ?>
</div>
<div>
  <ul class="nav nav-tabs" role="tablist">
    <?php foreach ($tables as $name => $data): ?>
      <!-- Nav tabs -->
      <li role="presentation" class="<?php print $data['class']; ?>">
<!--        <span class="badge badge-primary">--><?php //print $data['totals']['data']['actual']; ?><!--</span>-->
        <span class="badge badge-danger"><?php print $data['totals']['data']['overtime']['data']; ?></span>
        <a href="#<?php print $name; ?>" aria-controls="<?php print $name; ?>" role="tab" data-toggle="tab"><?php print $data['title']; ?></a>
      </li>
    <?php endforeach; ?>
  </ul>

  <div class="tab-content">
    <?php foreach ($tables as $name => $data): ?>
      <!-- Tab panes -->
      <div role="tabpanel" class="tab-pane <?php print $data['class']; ?>" id="<?php print $name; ?>"><?php print $data['table']; ?></div>
    <?php endforeach; ?>
  </div>
</div>
