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
        }
        else{
         player = jwplayer("jwplayer-" + i).setup({
            file: Drupal.settings.jwplayer[i].path,
            height: Drupal.settings.jwplayer[i].height,
            width: Drupal.settings.jwplayer[i].width,
            image: Drupal.settings.jwplayer[i].image,
          });
        }
        if (Drupal.settings.jwplayer[i].embedInPoint) {
          player.seek(Drupal.settings.jwplayer[i].embedInPoint - 1);
        }
        console.log(Drupal.settings.jwplayer[i]);
        if (Drupal.settings.jwplayer[i].embedOutPoint) {
          console.log('made it here');
          player.embedOutPoint = Drupal.settings.jwplayer[i].embedOutPoint;
          interval = setInterval(
            (function(player) {
              return function() {
                console.log('here weeee go');
                console.log(player);
              }
            })(this),
          1000);
        }
      }
    }
  };
})(jQuery, Drupal, this, this.document);

