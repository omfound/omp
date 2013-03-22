(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.clearOther = {
    attach : function(context) {
      $('select').change(function() {
        if($(this).val() == 'registration_registrant_type_anon') {
	  $('input').val("");
        }
      });
    }
  }
})(jQuery, Drupal, this, this.document);
