(function ($)  {
  Drupal.behaviors.product_filter = {
    attach: function (context, settings) {
      $(".view-calendar-product-view").ajaxComplete(function(event, XMLHttpRequest, ajaxOptions){
     	  response = XMLHttpRequest.responseText;
     	  result = response.search(/"status": false/i);
     	  if(result == -1){
     	  	$("form.commerce-add-to-cart").each(function(){
     	  		$(this).attr("action",window.location.pathname);
     	  	});
     	  }
     	  else{
     	  	//console.log("failure binding on ajax complete");
     	  }
      });
    //attach the preloader for the quantity selector here
    $preloader = $('<img class = "preloader"/>');
    $preloader.attr('src', 'sites/all/modules/commerce_reservations/js/images/ajax-loader.gif');
    var basePath = Drupal.settings.basePath;
    if (basePath == "/"){
	    basePath = '';
    }
    tipContent = new Object();
    var item = $('#block-views-calendar-product-view-block div.views-row');
    $('.meta').remove();
    //Hide all of our commerce item fields on page load
    $('#block-views-calendar-product-view-block .add-to-cart').hide();
    $('#block-views-calendar-product-view-block .body').hide();
    $('#block-views-calendar-product-view-block .price').hide();
    $('#block-views-calendar-product-view-block .large-image').hide();
    $('#block-views-calendar-product-view-block .nid').hide();
    $('#block-views-calendar-product-view-block .member-cost').hide();
    $('#block-views-calendar-product-view-block .commercial-cost').hide();
    //Hide the calendar and product info box
    $('.view-reservation-calendar').css('height', '0px');
    $('.view-reservation-calendar').css('visibility', 'hidden');
    $('#content').css('height', 'auto');
    $('#reservations-header').hide();
    $('.view-reservation-calendar').css('top', '-9000px');
    //get all of the closed times from the commerce reservations settings variables and load them onto the calendar
    if (!$('body').data('closeTimesLoaded')) {
      $.ajax(
          {url : basePath + 'closed_times/',
            cache : false,
            success : function (data) {
              $('div.closed_dates', data).each(function(index){
                event = new Object();
                event.title = 'closed date';
                event.start = $(this).attr('date');
                event.end = $(this).attr('date');
                event.allDay = true;
                event.className = 'closed-all-day';
                event.color = '#912711';
                event.backgroundColor = '#912711';
                event.eventBorderColor = '#912711';
                event.textColor = '#912711';
                dom_id: this.dom_id;
                $(".fullcalendar").fullCalendar('renderEvent', event, true);
              });
              $('div.closed-time', data).each(function(index){
                event = new Object();
                event.title = 'closed time';
                event.start = $(this).attr('start');
                event.end = $(this).attr('end');
                event.allDay = false;
                event.className = 'closed-time';
                event.color = '#912711';
                event.backgroundColor = '#912711';
                event.eventBorderColor = '#912711';
                event.textColor = '#912711';
                dom_id: this.dom_id;
                $(".fullcalendar").fullCalendar('renderEvent', event, true);
              });
            }
      });
      $('body').data('closeTimesLoaded', true);
    }
    //The user has selected a reservable item
    $(item).mousedown(function() {
      //show the calendar
      $('.view-reservation-calendar').css('top', '625px');
      $('#content').css('height', '1300px');
      $('.view-reservation-calendar').animate({
          opacity: '0.3'
        }, 500 );
      $('#reservations-header').fadeIn(1000);
      $('#block-system-main').animate({
        height: '625px'
      }, 500 );  
      //here we grab the fields from the selected item and move them to the "item info" area on the page
      $(item).removeClass('selected_product');
      $(this).addClass('selected_product');
      itemImage = $(this).find('.large-image').clone();
      $(itemImage).show();
      itemTitle = $(this).find('.title').clone();
      body = $(this).find('.body').clone();
      addToCart = $(this).find('.add-to-cart').clone();
      price = $(this).find('.price').clone();
      var nid = $(this).find('.nid .field-content').text();
      leftContent = $('<div id = leftContent></div>');
      rightContent = $('<div id = rightContent></div>');
      $('#leftContent').remove();
      $('#rightContent').remove();
      $(leftContent).append(addToCart).append(itemImage);
      $(rightContent).append(itemTitle).append(body).append(price);
      $(leftContent).hide();
      $(rightContent).hide();
      $('#left-side').empty();
      $('#left-side').append(leftContent);
      $('#right-side').empty();
      $('#right-side').append(rightContent);
      $(leftContent).fadeIn(1000);
      $(rightContent).fadeIn(1000);
      $(body).fadeIn(1000);
      $(price).fadeIn(1000);
      datesID = $('#left-side').find('[id|=edit-line-item-fields-field-reservation-dates]');
      datesID.attr('id', 'pickedDates');
      $('.form-item-product-id').hide();
      $('#left-side .add-to-cart [id|=edit-line-item-fields]').hide();
      $('.form-item-quantity label').remove();
      $('<label for="quantity">QUANTITY</label>').insertBefore('.form-item-quantity .form-select');
      $('.form-item-quantity').hide();
      $('#left-side .form-submit').hide();
      $('#left-side .add-to-cart').show();
      var pid = $('#left-side input[name="product_id"]').val();
      if (typeof pid == 'undefined'){
        pid = $('#left-side select[name="product_id"]').val();
      }
      $(".fullcalendar").fullCalendar('removeEvents', function(event){
        if (event.className == 'overlap'){
          return true;
        }
      });
      $(".fc-agenda-allday .fc-agenda-axis").html('Closed</br>Days');
      $('#left-side .form-item-quantity').append($preloader);
      $('#leftContent .large-image').addClass('preloader-active');
      $.ajax(
        {url : basePath + 'res-cal/' + pid + '/' + nid + '/' + 1,
          cache : false,
          success : function (data) {
            $('#leftContent .large-image').removeClass('preloader-active');
            $preloader.detach();
            $('#content #content-inner .no-certification-message').remove();
            not_cert = $('#not_certified', data);
            if (not_cert.length > 0){
              logged_in = $('.logged-in');
              if (logged_in.length > 0){
	              $('#content #content-inner').append('<div class = "no-certification-message"><p>You do not have the proper certifications to reserve this item.</p><a href = "../class-list">Take a Class!</a></div>');
	              $('.view-reservation-calendar').css('visibility', 'hidden');
                $('#content').css('height', 'auto');
              }  else{
	              $('#content #content-inner').append('<div class = "no-certification-message"><p>You are not logged in as a member.</p><a href = "../personal-membership-plans">Login or Become a Member!</a></div>');
	              $('.view-reservation-calendar').css('visibility', 'hidden');
                $('#content').css('height', 'auto');
	            }
	            allowCommercial = $('#allow_commercial', data);
	            if (allowCommercial.length > 0){
		            $('#content #content-inner').append('<div class = "commercial-message"><p>You may also reserve this item as a commercial rental, at the commercial rates.</p><div class = "commercial-button">Commercial Reservation</div></div>');
		            $('.commercial-button').mousedown(function(){
		              $('#left-side .field-name-field-commercial-reservation input').attr('checked', 'checked');
		              $('.no-certification-message').hide();
		              $('.commercial-message').hide();
			            $('.form-item-quantity').show();
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
                  $('#content').css('height', '1300px'); 
                  $('.view-reservation-calendar').animate({
                    opacity: '1'
                  }, 500 );
                  $('.page-reservations #block-system-main').animate({
                    height: '625px'
                  }, 1000 );
                  $('.page-reservations #middle-wrapper').animate({
                    height: '1260px'
                  }, 1000 );
		            });
	            }
            } else{
              $('.form-item-quantity').show();
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
              $('#content').css('height', '1300px');
              $('.view-reservation-calendar').animate({
                opacity: '1'
              }, 500 );
              $('.page-reservations #block-system-main').animate({
                height: '625px'
              }, 1000 );
              $('.page-reservations #middle-wrapper').animate({
                height: '1260px'
              }, 1000 );
            }
          }
      });      
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
          //$('.fullcalendar').qtip({
          $('#block-views-calendar-product-view-block div.views-row').qtip({
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
                $('.qtip-content [id|=edit-quantity]').val(quantity);
                $('#pickedDates .start-date-wrapper .form-select').focus(function(){
	                previousStart = $(this).val();
                }).change(Drupal.behaviors.product_filter.addDateToCalendar);

                $('#pickedDates .end-date-wrapper .form-select').change(Drupal.behaviors.product_filter.addDateToCalendar);
              },
              beforeHide: function(){
                quantity = $('.qtip-contentWrapper [id|=edit-quantity]').val();
                //$('#left-side .add-to-cart').remove();
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
                      console.log(basePath + 'res-cal/' + pid + '/' + nid + '/' + quantity);
                      $('#leftContent .large-image').removeClass('preloader-active');
                      $preloader.detach();
                      $('#content #content-inner .no-certification-message').remove();
                      not_cert = $('#not_certified', data);
                      if (not_cert.length > 0){
	                      $('#content #content-inner').append('<div class = "no-certification-message"><p>You do not have the proper certifications to reserve this item.</p></div>');
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
                        $('#content').css('height', '1300px');
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
            console.log(basePath + 'res-cal/' + pid + '/' + nid + '/' + quantity);
            $('#leftContent .large-image').removeClass('preloader-active');
            $preloader.detach();
            $('#content #content-inner .no-certification-message').remove();
            not_cert = $('#not_certified', data);
            if (not_cert.length > 0){
	            $('#content #content-inner').append('<div class = "no-certification-message"><p>You do not have the proper certifications to reserve this item.</p></div>');
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
              $('#content').css('height', '1300px');
              $('.view-reservation-calendar').animate({
                height: '395px'
              }, 500 ); 
            }
          }
        });
      });
    });
    },

    addDateToCalendar:function() {
      previousStart = $('#pickedDates .start-date-wrapper .form-select').val();
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
    }

  }
}(jQuery));
