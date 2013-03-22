(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.clearOther = {
    attach : function(context) {
      alert('clearing the stuff');
    }
  }
})(jQuery, Drupal, this, this.document);
