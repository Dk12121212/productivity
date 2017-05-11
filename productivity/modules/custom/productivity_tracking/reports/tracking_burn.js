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
  function create_new_url(project_id, base_url, all, year) {
    var val = $(".monthPicker").val();
    var res = val.split(",");
    var detailed = document.getElementById('detailed').checked;
    detailed  = detailed ? 1 : 0;

    // Full year link
    if (year) {
      if (res[1].trim() == 'all') {
        return false;
      }
      return base_url + "/node/" + project_id + "/issues-tracking/" + detailed + "/" + res[1].trim() + "/all";
    }

    // All time link.
    if (all) {
      return base_url + "/node/" + project_id + "/issues-tracking/" + detailed + "/" + "all/all";
    }

    // Specific month link
    return base_url + "/node/" + project_id + "/issues-tracking/" + detailed + "/" + res[1].trim() + "/" + get_month_num(res[0].trim());
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
    var input_date = get_month_name(settings['issues_tracking']['month']) + ', ' + settings['issues_tracking']['year'];
    $('.monthPicker').attr('value', input_date);

    $('#detailed').attr('checked', settings['issues_tracking']['detailed'] ? true : false);
  }


  Drupal.behaviors.monthlyReports = {
    attach: function (context, settings) {
      set_date_input(settings);
      $(".btn.year").popover({delay: { "show": 500, "hide": 100 }});

      // Apply filter button handler.
      $('#refresh').click(function() {
        window.location.href = create_new_url(settings['issues_tracking']['project_nid'], settings['issues_tracking']['base_url'], false, false);
      });

      $('.anytime').click(function() {
        window.location.href = create_new_url(settings['issues_tracking']['project_nid'], settings['issues_tracking']['base_url'], true, false);
      });

      $('.year').click(function() {
        var link = create_new_url(settings['issues_tracking']['project_nid'], settings['issues_tracking']['base_url'], true, true);
        if (!link) {
          // Initializes popovers for an element collection.
          $(".btn.year").popover('show');
        }
        else {
          window.location.href = link;
        }
      });

      $('input[name=month]').datepicker( {
        format: "MM, yyyy",
        minViewMode: 1,
        autoclose: true,
        startDate: "1/2014",
        startView: 1,
        todayBtn: "linked",
        keyboardNavigation: false,
        forceParse: false
      } );
    }
  };
})(jQuery);

