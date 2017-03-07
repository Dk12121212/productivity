/**
 * Created by brice on 07/03/2017.
 */

(function ($) {

    Drupal.behaviors.trackingTable = {
        attach: function (context, settings) {

            var i = Drupal.settings.rowNumber;
            $('#tab_logic')
              .append($("#attr").clone().attr('id', 'attr' + (i)));
            i++;

            $("#add_row").click(function () {
                $('#tab_logic')
                  .append($("#attr").clone().attr('id', 'attr' + (i)));
                i++;
            });
            $("#delete_row").click(function () {
                if (i > Drupal.settings.rowNumber) {
                    $("#attr" + (i - 1)).remove();
                    i--;
                }
            });
        }
    };

}(jQuery));