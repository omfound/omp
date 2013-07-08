(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwDefault = {
    attach : function() {
      var i;
      for(i = 0; i < Drupal.settings.jwplayer.length; ++i) {
        if (typeof Drupal.settings.jwplayer[i].playlist !== "undefined") {
          player = jwplayer("jwplayer-"+i).setup({
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
          if (Drupal.settings.jwplayer[i].embedInPoint) {
            player.seek(Drupal.settings.jwplayer[i].embedInPoint - 1);
          }
          if (Drupal.settings.jwplayer[i].embedOutPoint) {
            player.embedOutPoint = Drupal.settings.jwplayer[i].embedOutPoint;
            interval = setInterval(
              (function(player) {
                return function() {
                  console.log(player);
                }
              })(this),
            1000);
          }
        }
        else{
          jwplayer("jwplayer-" + i).setup({
            file: Drupal.settings.jwplayer[i].path,
            height: Drupal.settings.jwplayer[i].height,
            width: Drupal.settings.jwplayer[i].width,
            image: Drupal.settings.jwplayer[i].image,
          });
        }
      }
    }
  };
})(jQuery, Drupal, this, this.document);

