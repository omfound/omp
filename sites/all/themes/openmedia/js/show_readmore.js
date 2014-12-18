(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.ShowReadMore =  {
    attach : function(context, settings) {
      $('#description').readmore({
        maxHeight: 100,
        moreLink: '<a href="#">Read more &raquo;</a>'
      });
    }
  }
})(jQuery, Drupal, this, this.document);
