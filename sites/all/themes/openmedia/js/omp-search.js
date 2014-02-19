(function($) {
  Drupal.behaviors.ompSearch = {
    attach: function() {
      $('#block-om-theme-assets-om-site-search').once(
        'omp-search',
        function() {
          $(this).find('.icon-search').click(
            function() {
              var $form = $(this).siblings('form');
              if ($form.is(':visible')) {
                $form.hide();
              }
              else {
                $form.show();
              }
              return false;
            }
          );
        }
      );
    }
  }
})(jQuery);
