(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.dashboard = {
    attach : function(context) {
      var $container = $('#om-dashboard', context);
      $container.find('.pane').css('margin-right', 0);
      var masonryOptions = {
        itemSelector : '.pane',
        columnWidth : 350,
        gutterWidth : 30
      };
      $container.imagesLoaded( function(){
        $container.masonry(masonryOptions);
      });
    }
  };
})(jQuery, Drupal, this, this.document);