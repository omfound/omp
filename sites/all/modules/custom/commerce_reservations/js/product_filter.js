
// Registers the commerce reservations namespace.
Drupal.cr = Drupal.cr || {};

(function ($)  {
  Drupal.behaviors.product_filter = {
    attach: function (context, settings) {
      //basepath to site
      var basePath = Drupal.settings.basePath;
      if (basePath == "/"){
        basePath = '';
      }

      //clickable reservation items
      var item = $('#block-views-calendar-product-view-block div.views-row');

      //Hide all of our commerce item fields on page load
      Drupal.behaviors.product_filter.hideItemFields();

      //Hide the calendar
      Drupal.behaviors.product_filter.hideCalendar();

      //The user has selected a reservable item
      $(item).unbind();
      $(item).mousedown(function() {
        //show the calendar
        Drupal.behaviors.product_filter.showCalendar();

        //grab the fields from the selected item and move them to the quantity pane
        Drupal.behaviors.product_filter.showItemDetails($(this));

        //nid & pid of selected item
        var nid = $(this).find('.nid .field-content').text();
        var pid = $(this).find('.pid .field-content').text(); 

        //Add existing reservations for this item to calendar
        Drupal.behaviors.product_filter.addItemReservationsToCalendar(nid, pid, 1, basePath);

        //Render the current selection based on date picker values
        $(".fullcalendar").ajaxStop(function() {
          Drupal.behaviors.product_filter.addItemReservationsToCalendar(nid, pid, 1, basePath);
          $(this).unbind("ajaxStop");
        });

        //Populate details pane and calendar with defaults
        Drupal.behaviors.product_filter.loadProductForm(pid, nid);
      });
    },

    //start loadProductForm function
    loadProductForm:function(newPid, nid) {
      cartUrl = 'cr/product_form/'+newPid;
      var basePath = Drupal.settings.basePath;
      $.ajax({
          url : basePath + cartUrl,
          cache : false,
          success : function (data) {
            //populate date picker with new product form
            $('.view-reservation-calendar .view-footer #date-picker .date-details').empty();
            $('.view-reservation-calendar .view-footer #date-picker .date-details').append('<div id="commerce-reservations-cart" class="pickedDates add-to-cart">'+data+'</div>');

            //add quantity change preloader
            $preloader = $('<img class = "preloader"/>');
            $preloader.attr('src', 'sites/all/modules/custom/commerce_reservations/js/images/ajax-loader.gif');
            $('.view-footer .form-item-quantity').append($preloader);
            $('.view-footer .form-item-quantity img').hide();

            //Update calendar selections when values in date picker are changed
            $('.start-date-wrapper .form-select').focus(function(){
              previousStart = $(this).val();
            }).change(Drupal.behaviors.product_filter.addDateSelectionToCalendar);
            $('.end-date-wrapper .form-select').change(Drupal.behaviors.product_filter.addDateSelectionToCalendar);

            //Update calendar reservations when quantity in date picker is changed
            $('.view-footer [id|=edit-quantity]').change(function(){ 
              $(".fullcalendar").fullCalendar('removeEvents', function(event){
                if (event.className == 'overlap'){
                  return true;
                }
              });
              quantity = $('.view-footer [id|=edit-quantity]').val();
              Drupal.behaviors.product_filter.addItemReservationsToCalendar(nid, newPid, quantity, basePath);
              $(".fullcalendar").ajaxStop(function() {
                Drupal.behaviors.product_filter.addDateSelectionToCalendar();
                $(this).unbind("ajaxStop");
              });
            });

            //fire add date for default values
            Drupal.behaviors.product_filter.addDateSelectionToCalendar();
          }
      });
    },
    //end loadProductForm function

    //start addDateSelectionToCalendar function
    addDateSelectionToCalendar:function() {
      //get start date values from date picker
      previousStart = $('.start-date-wrapper .form-select').val();
      startYear = $('.start-date-wrapper .date-year .form-select').val();
      startMonth = $('.start-date-wrapper .date-month .form-select').val();
      startMonth = parseInt(startMonth) - 1;
      startDay = $('.start-date-wrapper .date-day .form-select').val();
      if ($('.start-date-wrapper .date-ampm .form-select').val() == 'pm'){
        startHour = $('.start-date-wrapper .date-hour .form-select').val();
        startHour = parseInt(startHour) + 12;
      } else{
        startHour = $('.start-date-wrapper .date-hour .form-select').val();
      }
      startMinutes = $('.start-date-wrapper .date-minute .form-select').val();

      //get end date values from date picker
      endYear = $('.end-date-wrapper .date-year .form-select').val();
      endMonth = $('.end-date-wrapper .date-month .form-select').val();
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

      //check validity of selection and add to calendar
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
        $('.date-status').html('<p class="error">Please pick a date and time that is before your end date and time.</p>');
      } 
    },
    //End addDateSelectionToCalendar function

    //start showCalendar function
    showCalendar:function() {
      //nasty to hack to get position because currently calendar is being absolutely
      //positioned beneath the rest of the view elements..
      var reviewPosition = $('#block-views-calendar-product-view-block').position();
      var calendarTop = reviewPosition.top + 550;
      var calendarPosition = calendarTop+'px';
      $('.view-reservation-calendar').css('top', calendarPosition);
      $('.view-reservation-calendar').fadeIn(200);
      $('#reservations-header').fadeIn(200);
    },
    //end showCalendar function

    //start hideCalendar function
    hideCalendar:function() {
      $('.view-reservation-calendar').css('visibility', 'hidden');
      $('#reservations-header').hide();
    },
    //end hideCalendar function

    //start hideItemFields function
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
    //end hideItemFields function

    //start addItemReservationsToCalendar function
    addItemReservationsToCalendar:function(nid, pid, quantity, basePath) {
      //remove all current events from calendar
      $(".fullcalendar").fullCalendar('removeEvents', function(event){
        if (event.className == 'overlap'){
          return true;
        }
      });

      //remove confusing all day label
      $(".fc-agenda-allday .fc-agenda-axis").html('');

      //activate preloader on quantity form
      $('.view-footer .form-item-quantity img').show();
      $('.view-footer .date-details').addClass('preloader-active');
      $('.view-footer input#edit-submit').hide();

      //load item reservations
      $.ajax(
        {url : basePath + 'res-cal/' + pid + '/' + nid + '/' + quantity,
          cache : false,
          success : function (data) {
            $('.view-footer .date-details').removeClass('preloader-active');
            $('.view-footer .form-item-quantity img').hide();
            $('.view-footer input#edit-submit').show();

            $('#content #content-inner .no-certification-message').remove();
            not_cert = $('#not_certified', data);
            if (not_cert.length > 0){
              //Hide calendar and display appropriate certificate message
              Drupal.behaviors.product_filter.notCertifiedMessage();

	            allowCommercial = $('#allow_commercial', data);
	            if (allowCommercial.length > 0){
		            $('#content #content-inner').append('<div class = "commercial-message"><p>You may also reserve this item as a commercial rental, at the commercial rates.</p><div class = "commercial-button">Commercial Reservation</div></div>');
		            $('.commercial-button').mousedown(function(){
		              $('#left-side .field-name-field-commercial-reservation input').attr('checked', 'checked');
		              $('.no-certification-message').hide();
		              $('.commercial-message').hide();
                  Drupal.behaviors.product_filter.addReservations(data);
		            });
	            }
            } else{
              Drupal.behaviors.product_filter.addReservations(data);
            }
          }
      });      
    },
    //end addItemReservationsToCalendar function

    //start addReservations function
    addReservations:function(data) {
      $('a.fullcalendar-event-details', data).each(function(index){
        reservedEvent = new Drupal.cr.reservedTime('Reserved', $(this).attr('start'), $(this).attr('end'), $(this));
        dom_id: this.dom_id;
        $(".fullcalendar").fullCalendar('renderEvent', reservedEvent, true);
      });
      $('.view-reservation-calendar').css('visibility', 'visible');
      $('#content').css('height', '1300px');
      $('.view-reservation-calendar').fadeIn(200);
    },
    //end addReservations function

    //start notCertifiedMessage function
    notCertifiedMessage:function() {
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
    },
    //end notCertifiedMessage function

    //start showItemDetails function
    showItemDetails:function($item) {
      //mark item as selected 
      $item.removeClass('selected_product');
      $item.addClass('selected_product');

      //clone relevent details from item
      itemImage = $item.find('.large-image').clone();
      itemTitle = $item.find('.title').clone();
      body = $item.find('.body').clone();
      price = $item.find('.price').clone();
      certifications = $item.find('.certifications').clone();

      //build left and right panes of item detail panel
      leftContent = $('<div id = leftContent></div>');
      rightContent = $('<div id = rightContent></div>');
      $(leftContent).append(itemImage).hide();
      $(leftContent).children().show();
      $(rightContent).append(itemTitle).append(body).append(price).append(certifications).hide();
      $(rightContent).children().show();
      $('#left-side').empty().append(leftContent);
      $('#right-side').empty().append(rightContent);;
      $(leftContent).fadeIn(200);
      $(rightContent).fadeIn(200);
    }
    //end showItemDetails function
  }

  //Full Calendar Event Models
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
  Drupal.cr.reservedTime = function(title, start, end, $reservation) {
    this.base = Drupal.cr.calendarEvent;
    this.base(title, start, end);
    this.className = 'overlap';
    this.backgroundColor = '#912711';
    this.eventBorderColor = '#912711';
    this.textColor = '#fff';
    this.field = $reservation.attr('field'); 
    this.index = $reservation.attr('index');

    this.eid = $reservation.attr('eid');
    this.entity_type = $reservation.attr('entity_type');
    if (Drupal.settings.commerce_reservations.staff) {
      this.url = 'administer_reservations?field_last_name_value=&field_reservation_dates_value%5Bvalue%5D%5Bdate%5D=&field_reservation_dates_value2%5Bvalue%5D%5Bdate%5D=&field_checkout_status_value%5B%5D=Awaiting+Checkout&field_checkout_status_value%5B%5D=No+Show&field_checkout_status_value%5B%5D=Checked+Out&field_checkout_status_value%5B%5D=Checked+In&field_checkout_status_value%5B%5D=Overdue&line_item_id='+$reservation.attr('eid');
    }else{
      this.url = $reservation.attr('href');
    }
    this.className = 'overlap';
    this.editable = true;
    this.color = '#912711';
  }
  Drupal.cr.reservedTime.prototype = new Drupal.cr.calendarEvent;
}(jQuery));
