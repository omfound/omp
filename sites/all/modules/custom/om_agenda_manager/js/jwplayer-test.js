(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwTest = {
    attach : function() {
      jwplayer.key="LbV5colrtkrBDNQUDLcd08vwBs7psJqbdJTVTYyxrAM=";
      var player = jwplayer("jwplayer-test").setup({ 
        playlist: 'http://dev-thornton.gotpantheon.com/node/29357/cuepoints',
        height: 600,
        width: 800,
        primary: "flash",
        listbar: {
          position: 'right',
          size: 310
        },
        events: {
          onPlaylistItem: function(event) {
            var currentPlaylistItem = jwplayer().getPlaylistItem(event.index);
            jwplayer().seek(currentPlaylistItem.mediaid);
            //console.log(event);
            //console.log(jwplayer().getPlaylistItem(event.index));
          }
        }
      });
    }
  };
})(jQuery, Drupal, this, this.document);

