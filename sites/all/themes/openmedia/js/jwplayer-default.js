(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwDefault = {
    attach : function() {
      var i;
      for(i = 0; i < Drupal.settings.jwplayer.length; ++i) {
        jwplayer("jwplayer-"+i).setup({
          file: Drupal.settings.jwplayer[i].path,
          height: 340,
          image: Drupal.settings.jwplayer[i].image,
          width: 550 
        });
      }
    }
  };
})(jQuery, Drupal, this, this.document);

