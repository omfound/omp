(function ($)  {
  Drupal.behaviors.product_filter = {
    attach: function (context, settings) {
      var basePath = Drupal.settings.basePath;
      if (basePath == "/"){
	      basePath = '';
      }
	    var item = $('#block-views-calendar-product-view-block div.views-row');
	    item.mousedown(function(){
	      item.attr('id', 'selected-product');
	      var nid = $(this).find('.nid .field-content').text();
	      var pid = $(this).find('.views-field-field-crp-product-reference .field-content input[name="product_id"]').val();
	      console.log(pid);
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
	          console.log(data);
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
    }
  }
}(jQuery));