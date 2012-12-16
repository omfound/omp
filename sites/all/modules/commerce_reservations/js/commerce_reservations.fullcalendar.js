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
      options.select = function(start, end, allDay) {
        if (!allDay){
          //First check for whether the selected time for the reservation is in the past.
          dontCheck = false;
          today = new Date();
          if (start < today){
	          $('#selected-product .commerce-add-to-cart #edit-submit').hide();
	          dontCheck = true;
          }
          var array = $('.fullcalendar').fullCalendar('clientEvents');
          if (array.length >= 1 && dontCheck == false){
            for(i in array){
              //Check for overlaps
              if (array[i].className == 'overlap'){
                if(!(array[i].start >= end || array[i].end <= start)){
	                $('#selected-product .commerce-add-to-cart #edit-submit').hide();
                }
              }
              //Check for closed days
              if (array[i].className == 'closed-all-day'){
                if (array[i].start.getDate() == start.getDate()){
                  if (array[i].start.getMonth() == start.getMonth()){
                    if (array[i].start.getYear() == start.getYear()){
	                    $('#selected-product .commerce-add-to-cart #edit-submit').hide();
                    }
                  }
                }
                if (array[i].start.getDate() == end.getDate()){
                  if (array[i].start.getMonth() == end.getMonth()){
                    if (array[i].start.getYear() == start.getYear()){
	                    $('#selected-product .commerce-add-to-cart #edit-submit').hide();
                    }   
                  }
                }
              //Check for closed times
              } else if (array[i].className == 'closed-time'){
                if (start >= array[i].start && start < array[i].end){
	                $('#selected-product .commerce-add-to-cart #edit-submit').hide();
                } else if(end >= array[i].start && end < array[i].end){
	                $('#selected-product .commerce-add-to-cart #edit-submit').hide();
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
          
          $('#selected-product .start-date-wrapper .date-month .form-select').val(startMonth);
          $('#selected-product .start-date-wrapper .date-day .form-select').val(startDate);
          $('#selected-product .start-date-wrapper .date-year .form-select').val(startYear);
          $('#selected-product .start-date-wrapper .date-hour .form-select').val(startHour);
          $('#selected-product .start-date-wrapper .date-minute .form-select').val(startMinutes);
          $('#selected-product .start-date-wrapper .date-ampm .form-select').val(ampm);
          
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
          
          $('#selected-product .end-date-wrapper .date-month .form-select').val(endMonth);
          $('#selected-product .end-date-wrapper .date-day .form-select').val(endDate);
          $('#selected-product .end-date-wrapper .date-year .form-select').val(endYear);
          $('#selected-product .end-date-wrapper .date-hour .form-select').val(endHour);
          $('#selected-product .end-date-wrapper .date-minute .form-select').val(endMinutes);
          $('#selected-product .end-date-wrapper .date-ampm .form-select').val(ampm);
        }
      }
      return options;
    }
  };

}(jQuery));