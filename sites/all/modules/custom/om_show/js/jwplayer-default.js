(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwDefault = {
    attach : function() {
      var i;
      jwplayer.key="LbV5colrtkrBDNQUDLcd08vwBs7psJqbdJTVTYyxrAM=";

      for(i = 0; i < Drupal.settings.jwplayer.length; ++i) {
        if (typeof Drupal.settings.jwplayer[i].playlist !== "undefined") {
          var player = jwplayer("jwplayer-"+i).setup({
            playlist: Drupal.settings.jwplayer[i].playlist,
            height: Drupal.settings.jwplayer[i].height,
            width: Drupal.settings.jwplayer[i].width,
            image: Drupal.settings.jwplayer[i].image,
            autostart: Drupal.settings.jwplayer[i].autostart,
            primary: "flash",
            listbar: {
              position: 'right',
              size: 410
            }
          });
        }
        else{
          var player = jwplayer("jwplayer-" + i).setup({
            file: Drupal.settings.jwplayer[i].path,
            height: Drupal.settings.jwplayer[i].height,
            width: Drupal.settings.jwplayer[i].width,
            image: Drupal.settings.jwplayer[i].image,
            autostart: Drupal.settings.jwplayer[i].autostart
          });
        }
        if (Drupal.settings.jwplayer[i].embedInPoint) {
          player.seek(Drupal.settings.jwplayer[i].embedInPoint - 1);
        }
        if (Drupal.settings.jwplayer[i].embedOutPoint) {
          player.embedOutPoint = Drupal.settings.jwplayer[i].embedOutPoint;
          var interval = setInterval(
            function() {
              if (parseInt(player.getPosition()) >= player.embedOutPoint) {
                clearInterval(interval);
                player.pause();
              } 
            }, 
          1000);
        }
      }
    }
  };
})(jQuery, Drupal, this, this.document);

