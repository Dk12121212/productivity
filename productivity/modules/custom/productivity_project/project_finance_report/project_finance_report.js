'use strict';

(function ($) {


  /**
   * Create new URL from project id and date.
   *
   * @param base_url
   *  The base URL of the page.
   *
   * @returns {string}
   *  New URL string.
   */
  function create_new_url(base_url) {
    var project_id = $('#project_filter').val();
    // Full year link
    return base_url + "/node/" + project_id + "/project-work-report";
  }

  Drupal.behaviors.monthlyReports = {
    attach: function (context, settings) {
      $('#project_filter').select2();

      // Apply filter button handler.
      $('.apply').click(function() {
        window.location.href = create_new_url(settings['monthly_report']['base_url'], false, false);
      });

    }
  };
})(jQuery);

