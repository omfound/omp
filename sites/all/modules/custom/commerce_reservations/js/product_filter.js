
// Registers the commerce reservations namespace.
Drupal.cr = Drupal.cr || {};

(function ($)  {
  Drupal.behaviors.product_filter = {
    attach: function (context, settings) {

    //quantity preloader
    $preloader = $('<img class = "preloader"/>');
    $preloader.attr('src', 'sites/all/modules/commerce_reservations/js/images/ajax-loader.gif');

    //basepath to site
    var basePath = Drupal.settings.basePath;
    if (basePath == "/"){
	    basePath = '';
    }

    tipContent = new Object();
    var item = $('#block-views-calendar-product-view-block div.views-row');
    $('.meta').remove();

    //Hide all of our commerce item fields on page load
    Drupal.behaviors.product_filter.hideItemFields();

    //Hide the calendar and product info box
    Drupal.behaviors.product_filter.hideCalendar();

    //The user has selected a reservable item
    $(item).mousedown(function() {
      //show the calendar
      Drupal.behaviors.product_filter.showCalendar();

      //grab the fields from the selected item and move them to the quantity pane
      Drupal.behaviors.product_filter.moveItemToQuantity($(this));

      //update the calendar with closed times for selected item
      var nid = $(this).find('.nid .field-content').text();
      var pid = $(this).find('.pid .field-content').text(); 
      if (typeof pid == 'undefined'){
        pid = $('#left-side select[name="product_id"]').val();
      }
      $(".fullcalendar").fullCalendar('removeEvents', function(event){
        if (event.className == 'overlap'){
          return true;
        }
      });

      //Initialize calendar events, wait for closures to add default
      Drupal.behaviors.product_filter.CalendarReloadItem(nid, pid, 1, basePath);
      $(".fullcalendar").ajaxStop(function() {
        Drupal.behaviors.product_filter.addDateToCalendar();
        $(this).unbind("ajaxStop");
      });

      //Populate details pane and calendar with defaults
      //Drupal.behaviors.product_filter.moveItemToDetails();
      newPid = $(this).find('.pid .field-content').text();
      Drupal.behaviors.product_filter.updateFormProduct(newPid, nid, pid);

      //The user has selected a time on the calendar
      $('.fullcalendar .fc-content').unbind().mouseup(function(){
        //deleted a bunch of stuff from here, may need to bring some back
      });
    });
    },

    //start updateFormProduct function
    updateFormProduct:function(newPid, nid, pid) {
      cartUrl = 'cr/product_form/'+newPid;
      var basePath = Drupal.settings.basePath;
      $.ajax({
          url : basePath + cartUrl,
          cache : false,
          success : function (data) {
            $('.view-reservation-calendar .view-footer #date-picker .date-details').empty();
            $('.view-reservation-calendar .view-footer #date-picker .date-details').append('<div id="commerce-reservations-cart" class="pickedDates add-to-cart">'+data+'</div>');
            //$('.view-reservation-calendar .view-footer #date-picker .date-details .commerce-add-to-cart').attr('action', '/cr/cart_add');

            //The user has changed the dates on the date picker
            $('.start-date-wrapper .form-select').focus(function(){
              previousStart = $(this).val();
            }).change(Drupal.behaviors.product_filter.addDateToCalendar);
            $('.end-date-wrapper .form-select').change(Drupal.behaviors.product_filter.addDateToCalendar);

            //The user has changed the quantity
            $('.view-footer [id|=edit-quantity]').change(function(){ 
              $(".fullcalendar").fullCalendar('removeEvents', function(event){
                if (event.className == 'overlap'){
                  return true;
                }
              });
              quantity = $('.view-footer [id|=edit-quantity]').val();
              Drupal.behaviors.product_filter.CalendarReloadItem(nid, pid, quantity, basePath);
              $(".fullcalendar").ajaxStop(function() {
                Drupal.behaviors.product_filter.addDateToCalendar();
                $(this).unbind("ajaxStop");
              });
            });
            //$('.view-reservation-calendar .view-footer #date-picker .date-details .commerce-add-to-cart').attr('action', '/cr/cart_add');
          }
      });
    },
    //end updateFormProduct function

    //start addDateToCalendar function
    addDateToCalendar:function() {
      previousStart = $('.start-date-wrapper .form-select').val();
      startYear = $('.start-date-wrapper .date-year .form-select').val();
      startMonth = $('.start-date-wrapper .date-month .form-select').val();
      //fullcalendar select option is expecting a 0 based month array
      startMonth = parseInt(startMonth) - 1;
      startDay = $('.start-date-wrapper .date-day .form-select').val();
      if ($('.start-date-wrapper .date-ampm .form-select').val() == 'pm'){
        startHour = $('.start-date-wrapper .date-hour .form-select').val();
        startHour = parseInt(startHour) + 12;
      } else{
        startHour = $('.start-date-wrapper .date-hour .form-select').val();
      }
      startMinutes = $('.start-date-wrapper .date-minute .form-select').val();
      endYear = $('.end-date-wrapper .date-year .form-select').val();
      endMonth = $('.end-date-wrapper .date-month .form-select').val();
      //fullcalendar select option is expecting a 0 based month array
      endMonth = parseInt(endMonth) - 1;
      endDay = $('.end-date-wrapper .date-day .form-select').val();
      if ($('.end-date-wrapper .date-ampm .form-select').val() == 'pm'){
        endHour = $('.end-date-wrapper .date-hour .form-select').val();
        endHour = parseInt(endHour) + 12;
      } else{
        endHour = $('.end-date-wrapper .date-hour .form-select').val();
      }              
      endMinutes = $('.end-date-wrapper .date-minute .form-select').val();
      startDate = new Date(startYear, startMonth, startDay, startHour, startMinutes, '00', '00');
      endDate = new Date(endYear, endMonth, endDay, endHour, endMinutes, '00', '00');
      startParse = Date.parse(startDate);
      endParse = Date.parse(endDate);
      if (startParse < endParse){
        selectionEvent = new Drupal.cr.selectedTime('Current Selection', startDate, endDate);
        $(".fullcalendar").fullCalendar('removeEvents', function(event){
          if (event.className == 'selected-time'){
            return true;
          }
        });
        $('.fullcalendar').fullCalendar('renderEvent', selectionEvent, true);
        $('.fullcalendar').fullCalendar('select', selectionEvent.start, selectionEvent.end, false);
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
    },
    //End addDateToCalendar function

    //Start updateDatePicker
    updateDatePicker:function() {
      view = $('.fullcalendar').fullCalendar('getView');
      if (view.name == 'agendaWeek') {
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
      }
    },

    showCalendar:function() {
      //nasty to hack to get position because currently calendar is being absolutely
      //positioned beneath the rest of the view elements..
      var reviewPosition = $('#block-views-calendar-product-view-block').position();
      var calendarTop = reviewPosition.top + 550;
      var calendarPosition = calendarTop+'px';
      $('.view-reservation-calendar').css('top', calendarPosition);
      $('#content').css('height', '1300px');
      $('.view-reservation-calendar').animate({
          opacity: '0.3'
        }, 500 );
      $('#reservations-header').fadeIn(1000);
      $('#block-system-main').animate({
        height: '600px'
      }, 500 );  
    },
    hideCalendar:function() {
      $('.view-reservation-calendar').hide();
      $('#reservations-header').hide();
      $('#content').css('height', 'auto');
      $('.view-reservation-calendar').css('top', '-9000px');

      /**
      $('.view-reservation-calendar').css('height', '0px');
      $('.view-reservation-calendar').css('visibility', 'hidden');
      $('#content').css('height', 'auto');
      $('#reservations-header').hide();
      $('.view-reservation-calendar').css('top', '-9000px');
      **/
    },

    hideItemFields:function() {
      $('#block-views-calendar-product-view-block .add-to-cart').hide();
      $('#block-views-calendar-product-view-block .body').hide();
      $('#block-views-calendar-product-view-block .price').hide();
      $('#block-views-calendar-product-view-block .certifications').hide();
      $('#block-views-calendar-product-view-block .large-image').hide();
      $('#block-views-calendar-product-view-block .nid').hide();
      $('#block-views-calendar-product-view-block .pid').hide();
      $('#block-views-calendar-product-view-block .member-cost').hide();
      $('#block-views-calendar-product-view-block .commercial-cost').hide();
    },

    Reservation:function(startDate, endDate, quantity) {
      this.startDate = startDate;
      this.endDate = endDate;
      this.quantity = quantity;
    },

    CalendarReloadItem:function(nid, pid, quantity, basePath) {
      $(".fc-agenda-allday .fc-agenda-axis").html('Closed</br>Days');
      $('.views-footer .form-item-quantity').append($preloader);
      $('.views-footer .date-details').addClass('preloader-active');

      $.ajax(
        {url : basePath + 'res-cal/' + pid + '/' + nid + '/' + quantity,
          cache : false,
          success : function (data) {
            $('.views-footer .date-details').removeClass('preloader-active');
            $preloader.detach();
            $('#content #content-inner .no-certification-message').remove();
            not_cert = $('#not_certified', data);
            if (not_cert.length > 0){
              logged_in = $('.logged-in');
              if (logged_in.length > 0){
	              $('#content #content-inner').append('<div class = "no-certification-message"><p>You do not have the proper certifications to reserve this item.</p><a href = "../classes">Take a Class!</a></div>');
	              $('.view-reservation-calendar').css('visibility', 'hidden');
                $('#content').css('height', 'auto');
              }  else{
	              $('#content #content-inner').append('<div class = "no-certification-message"><p>You are not logged in as a member. To reserve equipment please login or signup as a member.</p><a href = "../membership">Login or Become a Member!</a></div>');
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
                    height: '600px'
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
                //event.title = $(this).attr('title');
                //event.title = $(this).attr('title');
                event.title = 'Reserved';
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
                event.textColor = '#fff';
                dom_id: this.dom_id;
                $(".fullcalendar").fullCalendar('renderEvent', event, true);
              });
              $('.view-reservation-calendar').css('visibility', 'visible');
              $('#content').css('height', '1300px');
              $('.view-reservation-calendar').animate({
                opacity: '1'
              }, 500 );
              $('.page-reservations #block-system-main').animate({
                height: '600px'
              }, 1000 );
              $('.page-reservations #middle-wrapper').animate({
                height: '1260px'
              }, 1000 );
            }
          }
      });      
    },

    moveItemToQuantity:function($item) {
      $item.removeClass('selected_product');
      $item.addClass('selected_product');
      itemImage = $item.find('.large-image').clone();
      $(itemImage).show();
      itemTitle = $item.find('.title').clone();
      body = $item.find('.body').clone();
      addToCart = $item.find('.add-to-cart').clone();
      price = $item.find('.price').clone();
      certifications = $item.find('.certifications').clone();
      leftContent = $('<div id = leftContent></div>');
      rightContent = $('<div id = rightContent></div>');
      $('#leftContent').remove();
      $('#rightContent').remove();
      $(leftContent).append(addToCart).append(itemImage);
      $(rightContent).append(itemTitle).append(body).append(price).append(certifications);
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
      $(certifications).fadeIn(1000);
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
    },
    
    moveItemToDetails:function() {
      view = $('.fullcalendar').fullCalendar('getView');
      if (view.name == 'agendaWeek'){
        //dateFields = new Object();
        //$('.form-item-quantity').hide();
        //$('#leftContent .large-image').addClass('no-quantity');
        //$('#left-side .add-to-cart [id|=edit-line-item-fields]').show();
        //$('#left-side .form-submit').show();

        //Make sure the user hasn't tried to select multiple days and lost the add to cart form
        if ($('#left-side .add-to-cart').is('*')){
          dateFields = $('#left-side .add-to-cart').detach();
          var justDetached = true;
        } else if (!justDetached){
          addToCart = $(tipContent).find('.add-to-cart');
          dateFields = $(tipContent).detach();
          justDetached = false;
        }

        //Move dateFields into the details div
        //$('.date-details').html(dateFields);

        //update calendar on change events
        $('.start-date-wrapper .form-select').focus(function(){
          previousStart = $(this).val();
        }).change(Drupal.behaviors.product_filter.addDateToCalendar);
        $('.end-date-wrapper .form-select').change(Drupal.behaviors.product_filter.addDateToCalendar);
      }
    }
  }

  //here fixing model
  Drupal.cr.calendarEvent = function(title, start, end) {
    this.title = title;
    this.start = start;
    this.end = end;
    
    this.allDay = false;
    this.className = '';
    this.color = '#912711';
    this.backgroundColor = '#912711';
    this.eventBorderColor = '#912711';
    this.textColor = '#912711';
  }
  Drupal.cr.closedDay = function(title, start, end) {
    this.base = Drupal.cr.calendarEvent;
    this.base(title, start, end);

    this.allDay = true;
    this.className = 'closed-all-day';
  }
  Drupal.cr.closedDay.prototype = new Drupal.cr.calendarEvent;
  Drupal.cr.closedTime = function(title, start, end) {
    this.base = Drupal.cr.calendarEvent;
    this.base(title, start, end);

    this.className = 'closed-time';
  }
  Drupal.cr.closedTime.prototype = new Drupal.cr.calendarEvent;
  Drupal.cr.selectedTime = function(title, start, end) {
    this.base = Drupal.cr.calendarEvent;
    this.base(title, start, end);
    this.className = 'selected-time';
    this.backgroundColor = '#85B740';
    this.eventBorderColor = '#85B740';
    this.textColor = '#000';
  }
  Drupal.cr.selectedTime.prototype = new Drupal.cr.calendarEvent;
}(jQuery));
