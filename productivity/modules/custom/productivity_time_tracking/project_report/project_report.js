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
  function create_new_url(base_url, all, year) {
    var project_id = $('#project_filter').val();
    var val = $(".monthPicker").val();
    // Full year link
    return base_url + "/node/" + project_id + "/project-work-report/" + val;

  }

  /**
   * Set the current year and month on date input.
   */
  function set_date_input(settings) {
    // get the current month and year.
    var input_date = settings['monthly_report']['year'];
    $('.monthPicker').attr('value', input_date);

  }

  Drupal.behaviors.monthlyReports = {
    attach: function (context, settings) {
      set_date_input(settings);

      $('#project_filter').select2();
      $(".btn.year").popover({delay: { "show": 500, "hide": 100 }});

      // Apply filter button handler.
      $('.apply').click(function() {
        window.location.href = create_new_url(settings['monthly_report']['base_url'], false, false);
      });

      $('input[name=month]').datepicker( {
        format: "yyyy",
        minViewMode: 2,
        autoclose: true,
        startDate: "2012",
        startView: 2,
        todayBtn: "linked",
        keyboardNavigation: false,
        forceParse: false
      } );
    }
  };
})(jQuery);

