(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.YourBehaviorName =  {
    attach : function(context, settings) {
       $('.read-more-button').click(function() { 
         $('#project-description .field-name-body').toggleClass("active");
       });
    }
  }
})(jQuery, Drupal, this, this.document);


