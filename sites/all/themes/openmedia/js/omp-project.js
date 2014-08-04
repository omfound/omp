(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.YourBehaviorName =  {
    attach : function(context, settings) {
      console.log('this is my test');
       $('.read-more-button').click(function() { 
         $('#project-description .field-name-body').addClass("active");
       });
    }
  }
})(jQuery, Drupal, this, this.document);


