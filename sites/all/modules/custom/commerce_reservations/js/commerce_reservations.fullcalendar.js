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
    options.eventMouseover = function(event){
    }
    options.dayClick = function(date, allDay, jsEvent, view){
      if (view.name == 'month'){
        $('.fullcalendar').fullCalendar('changeView', 'agendaWeek');
        $('.fullcalendar').fullCalendar('gotoDate', date);
      }
    }
    options.viewDisplay = function(view) {
      if(view.name == 'month'){
	      $('.fullcalendar').fullCalendar('removeEvents', function(event){
        if (event.className == 'closed-time'){
          return true;
        }
      });
      } else if(view.name == 'agendaWeek'){
        var basePath = Drupal.settings.basePath;
	      $.ajax(
        {url : basePath + 'closed_times/',
          cache : false,
          success : function (data) {
            $('div.closed-time', data).each(function(index){
              event = new Object();
              event.title = 'closed time';
              event.start = $(this).attr('start');
              event.end = $(this).attr('end');
              event.allDay = false;
              event.className = 'closed-time';
              event.color = '#56a4da';
              event.backgroundColor = '#ac3d33';
              event.eventBorderColor = '#56a4da';
              event.textColor = 'white';
              dom_id: this.dom_id;
              $(".fullcalendar").fullCalendar('renderEvent', event, true);
            });
          }
    });

      }
    }
    options.selectable = true;
    options.selectHelper = true;
    options.unselectAuto = false;
    options.select = function(start, end, allDay) {
      if (!allDay){
        dontCheck = false;
        today = new Date();
        if (start < today){
	        $('.fullcalendar').qtip('api').updateContent('<p class = "error">You cannot make a reservation in the past.<p>', false);
	        dontCheck = true;
        }
        var array = $('.fullcalendar').fullCalendar('clientEvents');
        if (array.length >= 1 && dontCheck == false){
          for(i in array){
            //Check for overlaps
            if (array[i].className == 'overlap'){
              if(!(array[i].start >= end || array[i].end <= start)){
                $('.fullcalendar').qtip('api').updateContent('<p class = "error">You cannot make a reservation overlapping time when there are no items available.  Please reselect your times.', false);
              }
            }
            //Check for closed days
            if (array[i].className == 'closed-all-day'){
              if (array[i].start.getDate() == start.getDate()){
                if (array[i].start.getMonth() == start.getMonth()){
                  if (array[i].start.getYear() == start.getYear()){
                    $('.fullcalendar').qtip('api').updateContent('<p class = "error">You cannot pickup or return an item at the studio during a time that we are closed, please select a start time during studio hours.</p>', false);
                  }
                }
              }
              if (array[i].start.getDate() == end.getDate()){
                if (array[i].start.getMonth() == end.getMonth()){
                  if (array[i].start.getYear() == start.getYear()){
                    $('.fullcalendar').qtip('api').updateContent('<p class = "error">You cannot pickup or return an item at the studio during a time that we are closed, please select an end time during studio hours.</p>', false);
                  }   
                }
              }
            } else if (array[i].className == 'closed-time'){
              if (start >= array[i].start && start < array[i].end){
                $('.fullcalendar').qtip('api').updateContent('<p class = "error">You cannot pickup or return an item during hours the station is closed.</p>');
              } else if(end >= array[i].start && end < array[i].end){
                $('.fullcalendar').qtip('api').updateContent('<p class = "error">You cannot pickup or return an item during hours the station is closed.</p>');
              }
            }
          }
        }
        startMonth = start.getMonth() + 1;
        startDate = start.getDate();
        startYear = start.getFullYear();
        startHour = start.getHours();
        if (startHour > 12){
	        startHour = startHour - 12;
	        ampm = 'pm';
        } else{
	        ampm = 'am';
        }
        startMinutes = start.getMinutes();
        if (startMinutes == 0){
	        startMinutes = "00";
        }
        
        $('#pickedDates .start-date-wrapper .date-month .form-select').val(startMonth);
        $('#pickedDates .start-date-wrapper .date-day .form-select').val(startDate);
        $('#pickedDates .start-date-wrapper .date-year .form-select').val(startYear);
        $('#pickedDates .start-date-wrapper .date-hour .form-select').val(startHour);
        $('#pickedDates .start-date-wrapper .date-minute .form-select').val(startMinutes);
        $('#pickedDates .start-date-wrapper .date-ampm .form-select').val(ampm);
        
        endMonth = end.getMonth() + 1;
        endDate = end.getDate();
        endYear = end.getFullYear();
        endHour = end.getHours();
        if (endHour > 12){
	        endHour = endHour - 12;
	        ampm = 'pm';
        } else{
	        ampm = 'am';
        }
        endMinutes = end.getMinutes();
        if (endMinutes == 0){
	        endMinutes = "00";
        }
        
        $('#pickedDates .end-date-wrapper .date-month .form-select').val(endMonth);
        $('#pickedDates .end-date-wrapper .date-day .form-select').val(endDate);
        $('#pickedDates .end-date-wrapper .date-year .form-select').val(endYear);
        $('#pickedDates .end-date-wrapper .date-hour .form-select').val(endHour);
        $('#pickedDates .end-date-wrapper .date-minute .form-select').val(endMinutes);
        $('#pickedDates .end-date-wrapper .date-ampm .form-select').val(ampm);
      }
    };
    return options;
  }
};

}(jQuery));

function formatDate(date){
  var month = date.getMonth() + 1;
  month = addZero(month);
  var day = date.getDate();
  day = addZero(day);
  var year = date.getFullYear();
  var hour = date.getHours();
  hour = addZero(hour);
  var minute = date.getMinutes();
  minute = addZero(minute);
  var formattedDate = month + "/" + day + "/" + year + " - " + hour + ":" + minute;
  return formattedDate;
}

function addZero(time){
  if (time < 10){
    time = "0" + time;
  }
  return time;
}
