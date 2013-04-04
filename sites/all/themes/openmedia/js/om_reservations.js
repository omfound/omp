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
            quantity = $('#selected-product select#edit-quantity').val();
          $('#date-div').append(addToCart);
          $('#date-div').show();
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

      });
    }
  }
}(jQuery));
