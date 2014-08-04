(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.YourBehaviorName =  {
    attach : function(context, settings) {
      console.log('this is my test');
       $('.read-more-button').click(function() { 
         $('.read-more-button').addClass("active");
       });
    }
  }
})(jQuery, Drupal, this, this.document);


