(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.YourBehaviorName =  {
    attach : function(context, settings) {
      console.log('this is my test');
    }
  }
})(jQuery, Drupal, this, this.document);


