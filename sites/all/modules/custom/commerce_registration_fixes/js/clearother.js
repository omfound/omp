(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.clearOther = {
    attach : function(context) {
      alert('clearing the stuff');
      $('select').change(function() {
        alert($(this).val());
      });
    }
  }
})(jQuery, Drupal, this, this.document);
