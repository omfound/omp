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
            if (event.oldstate == "BUFFERING" && event.newstate == "PLAYING") {
              var currentPlaylistItem = jwplayer().getPlaylistItem(event.index);
              jwplayer().seek(currentPlaylistItem.mediaid);
            }
          }
        }
          onPlay: function(event) {
            if (event.oldstate == "BUFFERING" && event.newstate == "PLAYING") {
              var currentPlaylistItem = jwplayer().getPlaylistItem(event.index);
              jwplayer().seek(currentPlaylistItem.mediaid);
            }
          }
        }
      });
    }
  };
})(jQuery, Drupal, this, this.document);

