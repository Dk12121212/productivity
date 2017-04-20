(function ($) {

    Drupal.behaviors.trackingNav = {
        attach: function (context, settings) {
            // Highlight project hours.
            $('#project-sum .badge').hover(function () {
                var project_nid = $(this).attr('nid');
                if (project_nid != undefined) {
                    $('#month-nav .' + project_nid).toggleClass('highlight');
                }
            });
        }
    };

}(jQuery));