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

            // Use .on to bind non existing yet elements.
            $('#table-tracking').on('click', '.deleteRow', function(){
                // Toggle delete flag and strikeout.
                $(this).parents('tr').toggleClass('strikeout').attr('delete', function(_, attr){ return (attr==0 ? 1 : 0)});
            });

            // Save all data rows.
            $("#submit").click(function () {
                $('#submit i').addClass('fa-spin');

                var table = $('#table-tracking').tableToJSON({
                    textExtractor: {
                        0: function (cellIndex, $cell) {
                            return $cell.parent('tr').attr('mlid') + '|' + $cell.parent('tr').attr('id') + '|' + $cell.parent('tr').attr('delete');
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
                    url: location.origin +  Drupal.settings.tracking.url,
                    data: JSON.stringify(tracking_data),
                    xhrFields: {
                        withCredentials: true
                    },
                    dataType: 'json',
                    success: function (data) {
                        // Marked saved item as saved, with new mlid, and remove class new.
                        for (i = 0; i < data.length; i++) {
                            if (data[i].new == 1) {
                                $('#' + data[i].attr).attr('mlid', data[i].mlid).removeAttr('class');
                            }
                            // Remove items marked as deleted.
                            if (data[i].delete == 1) {
                                $('#' + data[i].attr).remove();
                            }
                        }
                        // Remove new item marked as deleted.
                        $('tr').filter("[delete=1]").remove();

                        // Print debugging info.
                        console.log(data);
                        console.log(table);

                        // Stop spin.
                        $("#submit i").removeClass('fa-spin');
                    },
                    error: function (data) {
                        $("#submit i").removeClass('fa-spin');
                        $('#messages')
                          .append($("#templateMsg").clone().removeAttr('id').removeAttr('style'))
                          .children('div:last-child').children('#messageText').text(data.responseText);

                        console.log(data);
                        console.log("Error saving.");
                    }
                });
            });
        }
    };

}(jQuery));