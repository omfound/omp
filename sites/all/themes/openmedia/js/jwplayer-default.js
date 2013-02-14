(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwDefault = {
    attach : function() {
      console.log(Drupal.settings);
    }
  };
})(jQuery, Drupal, this, this.document);

