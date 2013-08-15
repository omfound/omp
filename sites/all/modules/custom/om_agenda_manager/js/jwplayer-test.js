(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwTest = {
    attach : function() {
      jwplayer.key="LbV5colrtkrBDNQUDLcd08vwBs7psJqbdJTVTYyxrAM=";
      var player = jwplayer("jwplayer-test").setup({ 
        playlist: Drupal.settings.jwplayer[i].playlist,
        height: Drupal.settings.jwplayer[i].height,
        width: Drupal.settings.jwplayer[i].width,
        image: Drupal.settings.jwplayer[i].image,
        autostart: Drupal.settings.jwplayer[i].autostart,
        primary: "flash",
        listbar: {
          position: 'right',
          size: 410
        },
        events: {
          onPlaylistItem: function(event) {
            console.log(event);
            console.log(jwplayer().getPlaylistItem(event.index));
          }
        }
      });
    }
  };
})(jQuery, Drupal, this, this.document);

