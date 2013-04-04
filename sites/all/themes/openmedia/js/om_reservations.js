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

        /**
        $('.fullcalendar .fc-content').unbind().mouseup(function(){
            $('#date-div').append(addToCart);
            $('#date-div').show();
            console.log("!");
        });**/

      });
    }
  }
}(jQuery));
