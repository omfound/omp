(function ($)  {
  Drupal.behaviors.product_filter = {
    attach: function (context, settings) {
    $.ajax(
      {url : 'closed_times',
        cache : false,
        success : function (data) {
          $(".fullcalendar").fullCalendar('removeEvents');
          $('.closed_dates', data).each(function(index){
              event = new Object();
              event.title = 'Closed';
              event.start = $(this).attr('date');
              event.allDay = true;
              event.className = 'closed-all-day';
              event.editable = ($(this).attr('editable') === '1');
              event.color = '#912711';
              event.backgroundColor = '#912711';
              event.eventBorderColor = '#912711';
              event.textColor = '#912711';
              dom_id: this.dom_id;
              $(".fullcalendar").fullCalendar('renderEvent', event, true);
          });
          $('.closed-time', data).each(function(index){
              event = new Object();
              event.title = 'Closed';
              event.start = $(this).attr('start');
              event.end = $(this).attr('end');
              event.allDay = false;
              event.className = 'closed-time';
              event.editable = ($(this).attr('editable') === '1');
              event.color = '#912711';
              event.backgroundColor = '#2B6893';
              event.eventBorderColor = '#912711';
              event.textColor = '#912711';
              dom_id: this.dom_id;
              $(".fullcalendar").fullCalendar('renderEvent', event, true);
          });
        }
      });
      var basePath = Drupal.settings.basePath;
      if (basePath == "/"){
	      basePath = '';
      }
	    var item = $('#block-views-calendar-product-view-block div.views-row');
	    $('.commerce-add-to-cart div[id^="edit-line-item-fields"]').hide();
	    $('.commerce-add-to-cart input[id^="edit-submit"]').hide();
	    $('.commerce-add-to-cart select[id^="edit-product-id"]').hide();
	    $('.commerce-add-to-cart .form-item-quantity').hide();
	    item.mousedown(function(){
	      if (!$(this).is('#selected-product')) {
	        item.each(function(index){
		        $(this).removeAttr('id');
		        $(this).find('div[id^="edit-line-item-fields"]').hide();
		        $(this).find('input[id^="edit-submit"]').hide();
		        $(this).find('.form-item-quantity').hide();
	        });
	        $(this).find('.form-item-quantity').show();;
	        $(this).attr('id', 'selected-product');
	        var nid = $(this).find('.nid .field-content').text();
	        var pid = $(this).find('.add-to-cart .field-content input[name="product_id"]').val();
	        if (typeof(pid) === 'undefined') {
	          var pid = $(this).find('.add-to-cart .field-content select[name="product_id"]').val();
	        }
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
                event.allDay = ($(this).attr('allDay') === '1');
                event.className = 'overlap';
                event.editable = ($(this).attr('editable') === '1');
                event.color = '#912711';
                event.backgroundColor = '#912711';
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
            //$('#selected-product .commerce-add-to-cart .form-submit').show();
	          $('#selected-product .commerce-add-to-cart').show();
	          $('#selected-product div[id^="edit-line-item-fields"]').show();
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

        }

	  });

          $('#left-side [id|=edit-quantity]').change(function(){
            alert('updating calendar');
            $(".fullcalendar").fullCalendar('removeEvents', function(event){
              if (event.className == 'overlap'){
                return true;
              }
            });
            quantity = $('#selected-product select[id^="edit-quantity"]').val();
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
                  event.allDay = ($(this).attr('allDay') === '1');
                  event.className = 'overlap';
                  event.editable = ($(this).attr('editable') === '1');
                  event.color = '#912711';
                  event.backgroundColor = '#912711';
                  event.eventBorderColor = '#912711';
                  event.textColor = '#912711';
                  dom_id: this.dom_id;
                  $(".fullcalendar").fullCalendar('renderEvent', event, true);
                });
              }
            });
          });


    }
  }
}(jQuery));
