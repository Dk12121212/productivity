<!-- BEGIN Tables -->
<?php if (!$no_result): ?>
  <?php foreach ($tables as $index => $table): ?>
    <h2
      class="table-header"><?php print strtoupper($table_titles[$index]); ?></h2>
    <?php print $table; ?>
    <div class="col-sm-12">
      <span class="col-sm-2 pull-right"><?php print t('Total:'); ?>
        <?php print $total_per_types[$index] . ' ' . $total_currency_per_types[$index]; ?>
      </span>
    </div>
  <?php endforeach; ?>
  <div class="col-sm-12 well">
    <span>
      <strong>
        <?php print t('GRAND TOTAL:'); ?>
        <?php print $grand_total . ' ' . $total_currency_per_types[$index]; ?>
      </strong>
    </span>
  </div>
<?php endif; ?>
<!-- END Tables -->