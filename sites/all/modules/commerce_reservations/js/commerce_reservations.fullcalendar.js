(function ($) {

/**
 * FullCalendar plugin implementation.
 */

  Drupal.fullcalendar.plugins.commerce_reservations = {
    options: function (fullcalendar, settings) {
      var options = {};
      options.eventClick = function(event){
        return false;
      }
      options.selectable = true;
      options.selectHelper = true;
      options.unselectAuto = false;
      return options;
    }
  };

}(jQuery));