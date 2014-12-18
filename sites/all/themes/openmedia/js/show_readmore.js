(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.ShowReadMore =  {
    attach : function(context, settings) {
      $('#description').readmore({
        maxHeight: 175,
        moreLink: '<a href="#">Read more &raquo;</a>'
      });
    }
  }
})(jQuery, Drupal, this, this.document);
