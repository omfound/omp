(function ($) {

/**
 * FullCalendar plugin implementation.
 */

Drupal.fullcalendar.plugins.commerce_reservations = {
  options: function (fullcalendar, settings) {
    var options = {}; 
    options.disableResizing = true;
    options.eventClick = function(event){
      if (!Drupal.settings.commerce_reservations.staff) {
        return false;
      }else{
        if (event.url) {
          window.open(event.url);
          return false;
        }
        return false;
      }
    }  
    options.dayClick = function(date, allDay, jsEvent, view){
      if (view.name == 'month'){
        $('.fullcalendar').fullCalendar('changeView', 'agendaWeek');
        $('.fullcalendar').fullCalendar('gotoDate', date);
      }
    }
    options.selectable = true;
    options.selectHelper = true;
    options.unselectAuto = false;
    options.select = function(start, end, allDay) {
      dateInvalid = false;
      dateDiff = Math.abs(end - start);
      dateDiffHours = dateDiff / (1000*60*60);
      if (!allDay){
        dontCheck = false;
        today = new Date();
        if (start < today){
          $('.date-status').html('<p class = "error">You cannot make a reservation in the past.<p>');
	        dontCheck = true;
          $('.view-footer .form-submit').hide();
          dateInvalid = true;
        }
        var array = $('.fullcalendar').fullCalendar('clientEvents');
        if (array.length >= 1 && dontCheck == false){
          for(i in array){
            //Check for overlaps
            if (array[i].className == 'overlap' || array[i].className == 'unavailable-date' || array[i].className == 'unavailable-time'){
              if(!(array[i].start >= end || array[i].end <= start)){
                $('.date-status').html('<p class = "error">You cannot make a reservation overlapping time when there are no items available.  Please reselect your times.</p>');
                $('.view-footer .form-submit').hide();
                dateInvalid = true;
              }
            }

            //if staff ignore hours
            if (!Drupal.settings.commerce_reservations.staff) {
              //Check for closed days
              if (array[i].className == 'closed-date'){
                if (array[i].start.getDate() == start.getDate()){
                  if (array[i].start.getMonth() == start.getMonth()){
                    if (array[i].start.getYear() == start.getYear()){
                      $('.date-status').html('<p class = "error">You cannot pickup or return an item at the studio during a time that we are closed, please select a start time during studio hours.</p>');
                      $('.view-footer .form-submit').hide();
                      dateInvalid = true;
                    }
                  }
                }
                if (array[i].start.getDate() == end.getDate()){
                  if (array[i].start.getMonth() == end.getMonth()){
                    if (array[i].start.getYear() == start.getYear()){
                      $('.date-status').html('<p class = "error">You cannot pickup or return an item at the studio during a time that we are closed, please select a start time during studio hours.</p>');
                      $('.view-footer .form-submit').hide();
                      dateInvalid = true;
                    }   
                  }
                }
              } else if (array[i].className == 'closed-time'){
                if (start >= array[i].start && start < array[i].end){
                  $('.date-status').html('<p class = "error">You cannot pickup or return an item during hours the station is closed.</p>');
                  $('.view-footer .form-submit').hide();
                  dateInvalid = true;
                } else if(end >= array[i].start && end < array[i].end){
                  $('.date-status').html('<p class = "error">You cannot pickup or return an item during hours the station is closed.</p>');
                  $('.view-footer .form-submit').hide();
                  dateInvalid = true;
                }
              }
              if (Drupal.settings.commerce_reservations.maximum_length != 0) {
                if (dateDiffHours > Drupal.settings.commerce_reservations.maximum_length) {
                  $('.date-status').html('<p class = "error">You cannot make a reservation greater than '+Drupal.settings.commerce_reservations.maximum_length+' hours.</p>');
                  $('.view-footer .form-submit').hide();
                  dateInvalid = true;
                }  
              }
              if (Drupal.settings.commerce_reservations.reservation_window != 0) {
                var endDateWindow = new Date();
                if (end > endDateWindow.addDays(Drupal.settings.commerce_reservations.reservation_window)) {
                  $('.date-status').html('<p class = "error">You cannot make a reservation more than '+Drupal.settings.commerce_reservations.reservation_window+' days past today.</p>');
                  $('.view-footer .form-submit').hide();
                  dateInvalid = true;
                }
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
        } else if (startHour == 12) {
          ampm = 'pm';
        } else {
	        ampm = 'am';
        }
        startMinutes = start.getMinutes();
        if (startMinutes == 0){
	        startMinutes = "00";
        }
        
        $('.start-date-wrapper .date-month .form-select').val(startMonth);
        $('.start-date-wrapper .date-day .form-select').val(startDate);
        $('.start-date-wrapper .date-year .form-select').val(startYear);
        $('.start-date-wrapper .date-hour .form-select').val(startHour);
        $('.start-date-wrapper .date-minute .form-select').val(startMinutes);
        $('.start-date-wrapper .date-ampm .form-select').val(ampm);
        
        endMonth = end.getMonth() + 1;
        endDate = end.getDate();
        endYear = end.getFullYear();
        endHour = end.getHours();
        if (endHour > 12){
	        endHour = endHour - 12;
	        ampm = 'pm';
        } else if (endHour == 12) {
	        ampm = 'pm';
        } else{
	        ampm = 'am';
        }
        endMinutes = end.getMinutes();
        if (endMinutes == 0){
	        endMinutes = "00";
        }
        
        $('.end-date-wrapper .date-month .form-select').val(endMonth);
        $('.end-date-wrapper .date-day .form-select').val(endDate);
        $('.end-date-wrapper .date-year .form-select').val(endYear);
        $('.end-date-wrapper .date-hour .form-select').val(endHour);
        $('.end-date-wrapper .date-minute .form-select').val(endMinutes);
        $('.end-date-wrapper .date-ampm .form-select').val(ampm);

        //HERE we remove previously selected times and unselect
        $(".fullcalendar").fullCalendar('removeEvents', function(event){
          if (event.className == 'selected-time'){
            return true;
          }
        });
        
        //add placeholder event for selection
        selectionEvent = new Object();
        selectionEvent.title = 'Your Selection';
        selectionEvent.start = start.toUTCString();
        selectionEvent.end = end.toUTCString();
        selectionEvent.allDay = false;
        selectionEvent.className = 'selected-time';
        selectionEvent.backgroundColor = '#85B740';
        selectionEvent.eventBorderColor = '#85B740';
        selectionEvent.textColor = '#000';
        $('.fullcalendar').fullCalendar('renderEvent', selectionEvent, true);

        if (!dateInvalid) {
          $('.date-status').html('');
          $('.view-footer .form-submit').show();
        }
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

Date.prototype.addDays = function(days) {
  var dat = new Date(this.valueOf());
  dat.setDate(dat.getDate() + days);
  return dat;
}
