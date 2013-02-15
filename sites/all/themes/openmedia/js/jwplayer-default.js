(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwDefault = {
    attach : function() {
      var i;
      for(i = 0; i < Drupal.settings.jwplayer.length; ++i) {
        jwplayer("jwplayer-"+i).setup({
          file: Drupal.settings.jwplayer[i].path,
          height: 360,
          image: Drupal.settings.jwplayer[i].image,
          width: 640
        });
      }
    }
  };
})(jQuery, Drupal, this, this.document);

