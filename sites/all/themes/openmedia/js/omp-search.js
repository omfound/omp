(function($) {
  Drupal.behaviors.ompSearch = {
    attach: function() {
      $('#block-om-theme-assets-om-site-search').once(
        'omp-search',
        function() {
          var $screen = $('<div/>').attr('id', 'screen').css({'position': 'absolute', 'top': 0, 'left': 0, 'z-index': 10});
          $screen.width($('body').width());
          $screen.height($('body').height());
          $screen.hide();
          $('body').prepend($screen);
          $screen.click(
            function() {
              $('.icon-search').trigger('click');
            }
          );
          $(this).find('.icon-search').click(
            function() {
              var $form = $(this).siblings('form');
              if ($form.is(':visible')) {
                $form.hide();
                $screen.hide();
              }
              else {
                $form.show();
                $screen.show();
              }
              return false;
            }
          );
        }
      );
    }
  }
})(jQuery);
