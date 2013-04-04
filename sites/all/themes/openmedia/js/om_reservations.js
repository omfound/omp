(function ($)  {
  Drupal.behaviors.om_reservations = {
    attach: function (context, settings) {
      //Hide the calendar and product info box
      $('.view-reservation-calendar').css('height', '0px');
      $('.view-reservation-calendar').css('visibility', 'hidden');
      $('#reservations-header').hide();
      $('.view-reservation-calendar').css('top', '-9000px');
      $('.nid').hide();
      $('.body').hide();
      $('.add-to-cart').hide();
      $('#content').append('<div id="date-div"></div>');
      $('#date-div').hide();
      $('.views-row').mousedown(function(){
        $('.view-reservation-calendar').css('top', '530px');
        $('.view-reservation-calendar').css('visibility', 'visible');
        $('.view-reservation-calendar').css('height', 'auto');
        $('#reservations-header').fadeIn(1000);
        $('#block-views-reservations-cart-block-1').css('margin-top', '675px');
        itemTitle = $(this).find('.title').clone();
        itemImage = $(this).find('.small-image').clone();
        body = $(this).find('.body').clone();
        addToCart = $(this).find('.add-to-cart').clone();
        $(this).find('.add-to-cart').hide();
        leftContent = $('<div id = leftContent></div>');
        rightContent = $('<div id = rightContent></div>');
        $('#leftContent').remove();
        $('#rightContent').remove();
        $(addToCart).show();
        $(leftContent).append(itemImage).append(addToCart);
        $(rightContent).append(itemTitle).append(body);
        $(leftContent).hide();
        $(rightContent).hide();
        $('#left-side').empty();
        $('#left-side').append(leftContent);
        $('#right-side').empty();
        $('#right-side').append(rightContent);
        $(leftContent).fadeIn(1000);
        $(rightContent).fadeIn(1000);
        $(body).fadeIn(1000);

      $('.fullcalendar .fc-content').unbind().mouseup(function(){
        view = $('.fullcalendar').fullCalendar('getView');
        if (view.name == 'agendaWeek'){
          quantity = $('#left-side [id|=edit-quantity]').val();
          dateFields = new Object();
          $('.form-item-quantity').hide();
          $('#leftContent .large-image').addClass('no-quantity');
          $('#left-side .add-to-cart [id|=edit-line-item-fields]').show();
          $('#left-side .form-submit').show();
          //Make sure the user hasn't tried to select multiple days and lost the add to cart form
          if ($('#left-side .add-to-cart').is('*')){
            dateFields = $('#left-side .add-to-cart').detach();
            var justDetached = true;
          } else if (!justDetached){
            addToCart = $(tipContent).find('.add-to-cart');
            dateFields = $(tipContent).detach();
            justDetached = false;
          }
          $('.fullcalendar').qtip({
            content: dateFields,
            show: {
              when: {event: 'mouseup'}, 
              effect: {type: 'fade', length: 200}
            },
            position: {
              target: $('.fullcalendar'),
              adjust: {mouse: false},
              scroll: false,
              corner: {
                target: 'topRight',
                tooltip: 'topLeft'
              }
            },
            style: {
              width: {
                max: 230
              },
              background: '#f5f5f5',
              tip: {
                corner: 'topLeft',
                color: '#f5f5f5'
              },
              border: {
                color: '#d5d5d5',
                radius: 2
              }
            },
            hide: { 
              when: {event: 'unfocus'}, 
              fixed: true 
            },
            api: {
              beforeShow: function(){
                if (typeof(this.options.content.text) == 'function'){
                  this.destroy();
                }
              },
              onShow: function(){
                //TODO: Find a way to add chosen to form select elements
                $('.qtip-content [id|=edit-quantity]').val(quantity);
                $('#pickedDates .start-date-wrapper .form-select').focus(function(){
	                previousStart = $(this).val();
                }).change(function(){
                  startYear = $('#pickedDates .start-date-wrapper .date-year .form-select').val();
                  startMonth = $('#pickedDates .start-date-wrapper .date-month .form-select').val();
                  //fullcalendar select option is expecting a 0 based month array
                  startMonth = parseInt(startMonth) - 1;
                  startDay = $('#pickedDates .start-date-wrapper .date-day .form-select').val();
                  if ($('#pickedDates .start-date-wrapper .date-ampm .form-select').val() == 'pm'){
                    startHour = $('#pickedDates .start-date-wrapper .date-hour .form-select').val();
                    startHour = parseInt(startHour) + 12;
                  } else{
                    startHour = $('#pickedDates .start-date-wrapper .date-hour .form-select').val();
                  }
                  startMinutes = $('#pickedDates .start-date-wrapper .date-minute .form-select').val();
                  endYear = $('#pickedDates .end-date-wrapper .date-year .form-select').val();
                  endMonth = $('#pickedDates .end-date-wrapper .date-month .form-select').val();
                  //fullcalendar select option is expecting a 0 based month array
                  endMonth = parseInt(endMonth) - 1;
                  endDay = $('#pickedDates .end-date-wrapper .date-day .form-select').val();
                  if ($('#pickedDates .end-date-wrapper .date-ampm .form-select').val() == 'pm'){
                    endHour = $('#pickedDates .end-date-wrapper .date-hour .form-select').val();
                    endHour = parseInt(endHour) + 12;
                  } else{
                    endHour = $('#pickedDates .end-date-wrapper .date-hour .form-select').val();
                  }              
                  endMinutes = $('#pickedDates .end-date-wrapper .date-minute .form-select').val();
                  startDate = new Date(startYear, startMonth, startDay, startHour, startMinutes, '00', '00');
                  endDate = new Date(endYear, endMonth, endDay, endHour, endMinutes, '00', '00');
                  startParse = Date.parse(startDate);
                  endParse = Date.parse(endDate);
                  if (startParse < endParse){
                    $('.fullcalendar').fullCalendar('select', startDate, endDate, false);
                  } else{
	                  $(this).val(previousStart);
	                  $(this).qtip({
		                  content: "Please pick a date and time that is before your end date and time.",
		                  show: {
                        when: {event: 'mouseup'}, 
                        effect: {type: 'fade', length: 200}
                      }
	                  });
                  }
                });
                $('#pickedDates .end-date-wrapper .form-select').change(function(){
                  startYear = $('#pickedDates .start-date-wrapper .date-year .form-select').val();
                  startMonth = $('#pickedDates .start-date-wrapper .date-month .form-select').val();
                  //fullcalendar select option is expecting a 0 based month array
                  startMonth = parseInt(startMonth) - 1;
                  startDay = $('#pickedDates .start-date-wrapper .date-day .form-select').val();
                  if ($('#pickedDates .start-date-wrapper .date-ampm .form-select').val() == 'pm'){
                    startHour = $('#pickedDates .start-date-wrapper .date-hour .form-select').val();
                    startHour = parseInt(startHour) + 12;
                  } else{
                    startHour = $('#pickedDates .start-date-wrapper .date-hour .form-select').val();
                  }
                  startMinutes = $('#pickedDates .start-date-wrapper .date-minute .form-select').val();
                  endYear = $('#pickedDates .end-date-wrapper .date-year .form-select').val();
                  endMonth = $('#pickedDates .end-date-wrapper .date-month .form-select').val();
                  //fullcalendar select option is expecting a 0 based month array
                  endMonth = parseInt(endMonth) - 1;
                  endDay = $('#pickedDates .end-date-wrapper .date-day .form-select').val();
                  if ($('#pickedDates .end-date-wrapper .date-ampm .form-select').val() == 'pm'){
                    endHour = $('#pickedDates .end-date-wrapper .date-hour .form-select').val();
                    endHour = parseInt(endHour) + 12;
                  } else{
                    endHour = $('#pickedDates .end-date-wrapper .date-hour .form-select').val();
                  }              
                  endMinutes = $('#pickedDates .end-date-wrapper .date-minute .form-select').val();
                  startDate = new Date(startYear, startMonth, startDay, startHour, startMinutes, '00', '00');
                  endDate = new Date(endYear, endMonth, endDay, endHour, endMinutes, '00', '00');
                  $('.fullcalendar').fullCalendar('select', startDate, endDate, false);
                });
              },
              beforeHide: function(){
                quantity = $('.qtip-contentWrapper [id|=edit-quantity]').val();
                $('#left-side .add-to-cart').remove();
                tipContent = this.options.content.text[0].outerHTML;
                $('#leftContent .large-image').removeClass('no-quantity');
                $('#left-side #leftContent .large-image').before(tipContent);
                $('.qtip-content').empty();
                $('#left-side .add-to-cart [id|=edit-line-item-fields]').hide();
                $('#left-side .add-to-cart .form-submit').hide();
                $('#left-side [id|=edit-quantity]').val(quantity);
                $('#left-side .add-to-cart .form-item-quantity').show();
                $('#left-side [id|=edit-quantity]').change(function(){
                  $(".fullcalendar").fullCalendar('removeEvents', function(event){
                    if (event.className == 'overlap'){
                      return true;
                    }
                  });
                  quantity = $('#left-side [id|=edit-quantity]').val();
                  $('#left-side .form-item-quantity').append($preloader);
                  $('#leftContent .large-image').addClass('preloader-active');
                  $.ajax(
                  {url : basePath + 'res-cal/' + pid + '/' + nid + '/' + quantity,
                    cache : false,
                    success : function (data) {
                      $('#leftContent .large-image').removeClass('preloader-active');
                      $preloader.detach();
                      $('#block-system-main .block-inner .content .no-certification-message').remove();
                      not_cert = $('#not_certified', data);
                      if (not_cert.length > 0){
	                      $('#block-system-main .block-inner .content').append('<div class = "no-certification-message"><p>You do not have the proper certifications to reserve this item.</p></div>');
                      } else{
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
                        $('.view-reservation-calendar').css('visibility', 'visible');
                        $('.view-reservation-calendar').animate({
                          height: '395px'
                        }, 500 );
                      }
                    }
                  });
                });
                this.destroy();
              }
            }
          });
        }
      });
    }
  }
}(jQuery));
