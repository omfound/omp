(function($){
  Drupal.behaviors.videoPlayer = {
    attach: function(){
      for(var x in Drupal.settings.video_player){
        jwplayer(Drupal.settings.video_player[x].id).config(Drupal.settings.video_player[x]);
      }    
    }                                 
  };
})(jQuery);
