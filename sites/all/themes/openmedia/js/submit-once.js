(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.submitOnce = {
    attach : function(context) {
      $('.submit-once', context).once('submit-once',
        function() {
          $(this).click(
            function() {
              $(this).attr('disabled', 'disabled');
              $(this).css('opacity', .5);
              var text = $(this).attr('data-submit-once');
              $(this).val(text);
              $(this).parents('form').submit(); 
            }
          )
        }
      );
    }
  };    
})(jQuery, Drupal, this, this.document);  
