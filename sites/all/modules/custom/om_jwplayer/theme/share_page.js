(function ($, Drupal, window, document, undefined) {
Drupal.behaviors.sharePage = {
  attach : function(context) {
    alert('included');
  }
}
})(jQuery, Drupal, this, this.document);
