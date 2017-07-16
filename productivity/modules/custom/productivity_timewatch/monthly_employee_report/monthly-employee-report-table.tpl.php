<div class="report-container">
  <div id="header" class="show-only-on-print">
    <span id="project-title"><?php print t('Work Report for: @username - @date', array('@username' => $fullname, '@date' => $date)); ?></span>
  </div>

  <?php print $table; ?>
  <div class="row" style="page-break-before: always;">
    <h3>Summary</h3>
    <div class="col-sm-12">
      <?php print $table_summary; ?>
    </div>
  </div>
  <?php if (!empty($table_summary_madaan)): ?>
    <div class="row">
      <h3>Madaan</h3>
      <div class="col-sm-12">
        <?php print $table_summary_madaan; ?>
      </div>
    </div>
  <?php endif; ?>
  <h3>Signatures</h3>
  <div class="row">
    <div class="col-sm-6 mop-manager">
      <?php print variable_get('productivity_mop_manager', 'Brice Lenfant'); ?>(MOP manager):</br>
      <?php if ($date_sign_manager): ?>
      Digitaly signed on:  <?php print $date_sign_manager; ?>
      <?php endif; ?>
      <?php if (!$date_sign_manager): ?>
       <a href="<?php print $href_sign_manager; ?>" class="btn btn-primary">Click to Sign</a>
      <?php endif; ?>
    </div>
  </div>
  <div class="row">
    <hr>
  </div>
  <div class="row">
    <div class="col-sm-6 employee-signature">
      <?php print $fullname; ?>
      </br>
      <?php if ($date_sign): ?>
      Digitaly signed on:  <?php print $date_sign; ?>
      <?php endif; ?>
      <?php if (!$date_sign): ?>
        <a href="<?php print $href_sign; ?>" class="btn btn-primary">Click to Sign</a>
      <?php endif; ?>
    </div>

    <div class="col-sm-6 employee-signature" style="text-align: right">
      הריני מצהיר כי דו"ח שעות זה משקף את חלוקת שעות עבודתי במשימות השונות, וכי ידוע לי כי דוח זה ישמש לתביעת תמיכה כספית שתוגש ע"י החברה, ללשכת המדען הראשי, במשרד התעשייה המסחר והתעסוקה.
    </div>
  </div>
</div>