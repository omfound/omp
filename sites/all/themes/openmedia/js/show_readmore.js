(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.ShowReadMore =  {
    attach : function(context, settings) {
      $('.field-name-body .field-item').readmore({
        maxHeight: 75,
        moreLink: '<a href="#">Read more &raquo;</a>'
      });
    }
  }
})(jQuery, Drupal, this, this.document);
