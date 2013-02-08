(function ($)  {
  Drupal.behaviors.product_filter = {
    attach: function (context, settings) {
      var basePath = Drupal.settings.basePath;
      if (basePath == "/"){
	      basePath = '';
      }
	    var item = $('#block-views-calendar-product-view-block div.views-row');
	    $('.commerce-add-to-cart #edit-line-item-fields').hide();
	    $('.commerce-add-to-cart #edit-submit').hide();
	    $('.commerce-add-to-cart #edit-product-id').hide();
	    item.mousedown(function(){
	      item.attr('id', 'selected-product');
	      var nid = $(this).find('.views-field-nid .field-content').text();
	      var pid = $(this).find('.views-field-field-crp-product-reference .field-content input[name="product_id"]').val();
	      //Remove events from the calendar
	      $(".fullcalendar").fullCalendar('removeEvents', function(event){
          if (event.className == 'overlap'){
            return true;
          }
        });
        $.ajax(
        {url : basePath + 'res-cal/' + pid + '/' + nid + '/' + 1,
          cache : false,
          success : function (data) {
	          $('a.fullcalendar-event-details', data).each(function(index){
                event = new Object();
                event.field = $(this).attr('field');
                event.index = $(this).attr('index');
                event.eid = $(this).attr('eid');
                event.entity_type = $(this).attr('entity_type');
                event.title = $(this).attr('title');
                event.start = $(this).attr('start');
                event.end = $(this).attr('end');
                event.url = $(this).attr('href');
                if ($(this).children('span').hasClass('closed-date')){
                  event.allDay = true;
                  event.className = 'closed-all-day';
                } else{
                  event.allDay = ($(this).attr('allDay') === '1');
                  event.className = 'overlap';
                }
                event.editable = ($(this).attr('editable') === '1');
                event.color = '#912711';
                if ($(this).children('span').hasClass('closed-hours')){
                  event.backgroundColor = '#2B6893';
                  event.className = 'closed-hours';
                } else {
                event.backgroundColor = '#912711';
                }
                event.eventBorderColor = '#912711';
                event.textColor = '#912711';
                dom_id: this.dom_id;
                $(".fullcalendar").fullCalendar('renderEvent', event, true);
              });
          }
        });
        $('.fullcalendar .fc-content').unbind().mouseup(function(){
          view = $('.fullcalendar').fullCalendar('getView');
          if (view.name == 'agendaWeek'){
            quantity = $('#selected-product select#edit-quantity').val();
	          $('#selected-product .commerce-add-to-cart').show();
	          $('#selected-product #edit-line-item-fields').show();
	          $('#selected-product .field-name-field-reservation-dates .form-select').change(function(){
              startYear = $('#selected-product .start-date-wrapper .date-year .form-select').val();
              startMonth = $('#selected-product .start-date-wrapper .date-month .form-select').val();
              //fullcalendar select option is expecting a 0 based month array
              startMonth = parseInt(startMonth) - 1;
              startDay = $('#selected-product .start-date-wrapper .date-day .form-select').val();
              if ($('#selected-product .start-date-wrapper .date-ampm .form-select').val() == 'pm'){
                startHour = $('#selected-product .start-date-wrapper .date-hour .form-select').val();
                startHour = parseInt(startHour) + 12;
              } else{
                startHour = $('#selected-product .start-date-wrapper .date-hour .form-select').val();
              }
              startMinutes = $('#selected-product .start-date-wrapper .date-minute .form-select').val();
              endYear = $('#selected-product .end-date-wrapper .date-year .form-select').val();
              endMonth = $('#selected-product .end-date-wrapper .date-month .form-select').val();
              //fullcalendar select option is expecting a 0 based month array
              endMonth = parseInt(endMonth) - 1;
              endDay = $('#selected-product .end-date-wrapper .date-day .form-select').val();
              if ($('#selected-product .end-date-wrapper .date-ampm .form-select').val() == 'pm'){
                endHour = $('#selected-product .end-date-wrapper .date-hour .form-select').val();
                endHour = parseInt(endHour) + 12;
              } else{
                endHour = $('#selected-product .end-date-wrapper .date-hour .form-select').val();
              }              
              endMinutes = $('#selected-product .end-date-wrapper .date-minute .form-select').val();
              startDate = new Date(startYear, startMonth, startDay, startHour, startMinutes, '00', '00');
              endDate = new Date(endYear, endMonth, endDay, endHour, endMinutes, '00', '00');
              $('.fullcalendar').fullCalendar('select', startDate, endDate, false);
            });
          }
        });
        $('#selected-product #edit-quantity').change(function(){ 
          $(".fullcalendar").fullCalendar('removeEvents', function(event){
            if (event.className == 'overlap'){
              return true;
            }
          });
          quantity = $('#selected-product #edit-quantity').val();
          $.ajax(
          {url : basePath + 'res-cal/' + pid + '/' + nid + '/' + quantity,
            cache : false,
            success : function (data) {
	            $('a.fullcalendar-event-details', data).each(function(index){
                  event = new Object();
                  event.field = $(this).attr('field');
                  event.index = $(this).attr('index');
                  event.eid = $(this).attr('eid');
                  event.entity_type = $(this).attr('entity_type');
                  event.title = $(this).attr('title');
                  event.start = $(this).attr('start');
                  event.end = $(this).attr('end');
                  event.url = $(this).attr('href');
                  if ($(this).children('span').hasClass('closed-date')){
                    event.allDay = true;
                    event.className = 'closed-all-day';
                  } else{
                    event.allDay = ($(this).attr('allDay') === '1');
                    event.className = 'overlap';
                  }
                  event.editable = ($(this).attr('editable') === '1');
                  event.color = '#912711';
                  if ($(this).children('span').hasClass('closed-hours')){
                    event.backgroundColor = '#2B6893';
                    event.className = 'closed-hours';
                  } else {
                  event.backgroundColor = '#912711';
                  }
                  event.eventBorderColor = '#912711';
                  event.textColor = '#912711';
                  dom_id: this.dom_id;
                  $(".fullcalendar").fullCalendar('renderEvent', event, true);
                });
            }
          });
        });
	    });
    }
  }
}(jQuery));