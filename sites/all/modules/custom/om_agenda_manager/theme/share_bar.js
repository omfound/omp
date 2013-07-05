(function ($, Drupal, window, document, undefined) {

// Namespace global containers
Drupal.shareBar = {};
Drupal.shareBar.views = {};
Drupal.shareBar.models = {};

// Models:
// Extremely simple model to act as storage.
Drupal.shareBar.models.shareBar = Backbone.Model.extend(); 
// Views:
// View to handle most of the interaction for the sharebar.
Drupal.shareBar.views.shareBar = Backbone.View.extend({
  initialize : function(player, domInterface) {
    
  }
});

Drupal.behaviors.shareBar = {
  attach : function(context) {
   $target = $('#session-video-embed-tray', context);
   player = jwplayer();
   console.log(player);
  }
}
})(jQuery, Drupal, this, this.document);
