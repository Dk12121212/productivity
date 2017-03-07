/**
 * Created by brice on 07/03/2017.
 */

(function ($) {

    Drupal.behaviors.trackingTable = {
        attach: function (context, settings) {

            var i = Drupal.settings.rowNumber;

            $('#table-tracking')
              .append($("#attr").clone().attr('id', 'attr' + (i)));
            i++;

            $("#add_row").click(function () {
                $('#table-tracking')
                  .append($("#attr").clone().attr('id', 'attr' + (i)));
                i++;
            });

            $("#delete_row").click(function () {
                if (i > Drupal.settings.rowNumber) {
                    $("#attr" + (i - 1)).remove();
                    i--;
                }
            });

            $("#submit").click(function () {
                var table = $('#table-tracking').tableToJSON({
                    textExtractor : {
                        0 : function(cellIndex, $cell) {
                            return $cell.parent('tr').attr('mlid');
                        },
                        1 : function(cellIndex, $cell) {
                            return $cell.find('select').val();
                        },
                        2 : function(cellIndex, $cell) {
                            return $cell.find('input').val();
                        },
                        3 : function(cellIndex, $cell) {
                            return $cell.find('input').val();
                        },
                        4 : function(cellIndex, $cell) {
                            return $cell.find('input').val();
                        },
                        5 : function(cellIndex, $cell) {
                            return $cell.find('select').val();
                        },
                        6 : function(cellIndex, $cell) {
                            return $cell.find('input').val();
                        }
                    }
                });
                console.log(table);


            });
        }
    };

}(jQuery));