'use strict';

(function ($) {


  var month = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  ];

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
    var val = $("#month").val();
    var valEnd = $("#month-end").val();
    var res = val.split(",");
    var resEnd = valEnd.split(",");

//  Temporary removed until implementation.
//    var estimated = document.getElementById('estimation-based').checked;
    var estimated = 0;

    // Full year link
    if (year) {
      if (res[2].trim() == 'all') {
        return false;
      }
      return base_url + "/node/" + project_id + "/monthly-report/" + res[2].trim() + "/all/" + estimated;
    }

    // All time link.
    if (all) {
      return base_url + "/node/" + project_id + "/monthly-report/all/all/" + estimated;
    }

    // Specific month link
    var dateParams = res[2].trim() + "/" + get_month_num(res[1].trim()) + "/" + res[0].trim() + "/" ;
    var dateParamsEnd = resEnd[2].trim() + "/" + get_month_num(resEnd[1].trim()) + "/" + resEnd[0].trim() + "/" ;
    return base_url + "/node/" + project_id + "/monthly-report/" + dateParams + dateParamsEnd + estimated;
  }

  /**
   * Convert num to month.
   */
  function get_month_name(month_num) {
    if (month_num == 'all') {
      return month_num;
    }
    return month[month_num - 1];
  }

  /**
   * Convert month to num.
   */
  function get_month_num(month_name) {
    var i;
    for (i = 0; i < 12; i++) {
      if (month[i] == month_name) {
        return i+1;
      }
    }
    return 'all';
  }

  /**
   * Set the current year and month on date input.
   */
  function set_date_input(settings) {
    // get the current month and year.
    var input_date = settings['monthly_report']['day'] + ', ' + get_month_name(settings['monthly_report']['month']) + ', ' +  settings['monthly_report']['year'];
    $('#month').attr('value', input_date);

    var input_date_end = settings['monthly_report']['day_end'] + ', ' + get_month_name(settings['monthly_report']['month_end']) + ', ' +  settings['monthly_report']['year_end'];
    $('#month-end').attr('value', input_date_end);

//    $('#estimation-based').attr('checked', settings['monthly_report']['estimate']);
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

      $('.anytime').click(function() {
        window.location.href = create_new_url(settings['monthly_report']['base_url'], true, false);
      });

      $('.year').click(function() {
        var link = create_new_url(settings['monthly_report']['base_url'], true, true);
        if (!link) {
          // Initializes popovers for an element collection.
          $(".btn.year").popover('show');
        }
        else {
          window.location.href = link;
        }
      });

      $('.monthPicker').datepicker( {
        format: "dd, MM, yyyy",
        minViewMode: 0,
        autoclose: true,
        startDate: "1/1/2014",
        startView: 0,
        todayBtn: "linked",
        keyboardNavigation: false,
        forceParse: false
      } );
    }
  };
})(jQuery);

