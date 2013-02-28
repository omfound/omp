(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.showHide = {
    attach : function(context, settings) {
      $('.show-hide', context).each(
        function() {
          $(this).once('omp-show-hide', 
            function() {
              // stash content
              $inner = $(this).find('.inner');
              // build link
              $link = $('<a/>');
              $link.attr({'class' : 'show-hide-toggle inset-button', 'href' : '#'}).text('Show More');
              $link.data('originalHeight', $inner.outerHeight());
              $link.data('contentContainer', $inner);
              $(this).append($link);
              // style inner
              $inner.css({height : 0, overflow : 'hidden'});
              // set up toggle
              $link.toggle(
                function() {
                  $content = $(this).data('contentContainer');
                  $content.animate({'height' : $(this).data('originalHeight')}, 500);
                  $(this).text('Show Less');
                },
                function() {
                  $content = $(this).data('contentContainer');
                  $content.animate({'height' : 0}, 500);
                  $(this).text('Show More');
                }
              );
            }
          );
        }
      );
    }
  };
})(jQuery, Drupal, this, this.document);