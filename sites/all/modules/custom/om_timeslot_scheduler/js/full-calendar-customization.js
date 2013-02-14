(function ($) {

Drupal.behaviors.fullCalendarScheduling = {
  attach: function (context, settings) {

    settings = {
      header: {
        left: 'prev,next today',
        center: 'title',
        right: 'month,agendaWeek,agendaDay'
      },
      editable: true,
      events: [],
    };

    data = $('#calendar_data').text();
    $('#calendar_data').hide();
    jsonData = $.parseJSON(data);
    $.each(jsonData,
      function() {
        this.title = '<a href="#">yozle</a>';
        settings.events.push(this);
      }
    );

    $('#timeslot_calendar').fullCalendar(settings);

  }
};

}(jQuery));
