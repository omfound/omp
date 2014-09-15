(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.ompGrid = {
    attach : function() {
      var $container = $('div.omp-grid div.view-content');
      var masonryOptions = {
        itemSelector : '.views-row',
        columnWidth : 222,
        gutterWidth : 30
      };
      $container.find('.views-row').css({margin : "10px 0 10px 0"});
      $container.imagesLoaded( function(){
        $container.masonry(masonryOptions);
      });
    }
  };
})(jQuery, Drupal, this, this.document);