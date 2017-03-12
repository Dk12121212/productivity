/**
 * Created by brice on 07/03/2017.
 */

(function ($) {

    Drupal.behaviors.trackingTable = {
        attach: function (context, settings) {
            // Get counter.
            var i = Drupal.settings.rowNumber;

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
                    textExtractor: {
                        0: function (cellIndex, $cell) {
                            return $cell.parent('tr').attr('mlid');
                        },
                        // Project nid.
                        1: function (cellIndex, $cell) {
                            return $cell.find('select').val();
                        },
                        // Repo.
                        2: function (cellIndex, $cell) {
                            return $cell.find('input').val();
                        },
                        // Issue.
                        3: function (cellIndex, $cell) {
                            return $cell.find('input').val();
                        },
                        // PR.
                        4: function (cellIndex, $cell) {
                            return $cell.find('input').val();
                        },
                        // Description.
                        5: function (cellIndex, $cell) {
                            return $cell.find('input').val();
                        },
                        // Work type.
                        6: function (cellIndex, $cell) {
                            return $cell.find('select').val();
                        },
                        // Time
                        7: function (cellIndex, $cell) {
                            return $cell.find('input').val();
                        }
                    }
                });

                var tracking_data = {"tracking": table, 'data': Drupal.settings.tracking}
                $.ajax({
                    type: "post",
                    url: "http://localhost/productivity/www/tracking/save-tracking?XDEBUG_SESSION_START=11945",
                    data: JSON.stringify(tracking_data),
                    xhrFields: {
                        withCredentials: true
                    },
                    dataType: 'json',
                    success: function (data) {
                        window.location.target();
                        console.log(data);
                        console.log(table);
                    }
                });
            });
        }
    };

}(jQuery));