(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwDefault = {
    attach : function() {
      var i;
      for(i = 0; i < Drupal.settings.jwplayer.length; ++i) {
        if (typeof Drupal.settings.jwplayer[i].playlist !== "undefined") {
          jwplayer("jwplayer-"+i).setup({
            playlist: Drupal.settings.jwplayer[i].playlist,
            height: Drupal.settings.jwplayer[i].height,
            width: Drupal.settings.jwplayer[i].width,
            image: Drupal.settings.jwplayer[i].image,
            primary: "flash",
            listbar: {
              position: 'right',
              size: 410
            }
          });
        }
        else{
          jwplayer("jwplayer-"+i).setup({
            file: Drupal.settings.jwplayer[i].path,
            height: Drupal.settings.jwplayer[i].height,
            width: Drupal.settings.jwplayer[i].width,
            image: Drupal.settings.jwplayer[i].image,
            width: 550 
          });
        }
      }
    }
  };
})(jQuery, Drupal, this, this.document);

