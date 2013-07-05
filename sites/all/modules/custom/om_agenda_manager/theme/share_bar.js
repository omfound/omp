(function ($, Drupal, window, document, undefined) {

// Namespace global containers
Drupal.shareBar = {};
Drupal.shareBar.views = {};
Drupal.shareBar.models = {};

// Models:
// Extremely simple model to act as storage for player state and various resources.
Drupal.shareBar.models.shareBar = Backbone.Model.extend({
  initialize : function() {
    player = this.get('player');
    this.set('width', player.config.width);  
  }
}); 
// Views:
// View to handle most of the interaction for the sharebar.
Drupal.shareBar.views.shareBar = Backbone.View.extend({
  events : {
    // Prevent form submit.
    'submit form' : 'preventSubmit',
    'click .show-hide' : 'toggleInterface'
  },
  initialize : function(player, domInterface) {
    // Standard bindall for this view.
    _.bindAll(this, 'initializeInterface', 'toggleInterface');
    // Attach this view to the dom element.
    this.setElement(domInterface);
    // Instantiate new sharebar model.
    // This model will automatically bind itself to the player object.
    this.shareBarModel = new Drupal.shareBar.models.shareBar({'player' : player});
    // We get the width from the player.
    this.shareBarModel.set('height', $(this.el).find('form').outerHeight());
    // Set toggle to closed.
    this.toggleState = false;
    // Hijack the dom interface
    this.initializeInterface();
  },
  initializeInterface : function() {
  },
  toggleInterface : function() {
    if (this.toggleState == false) {
      this.toggleState = true;
      console.log('open');
    }
    else {
      this.toggleState = false;
      console.log('closed');
    }
  },
  preventSubmit : function(e) {
    e.preventDefault();
  }
});

Drupal.behaviors.shareBar = {
  attach : function(context) {
   // NB: here I've hard coded ids for the tray and used the ambiguous player call.
   // This is due to the previous "frameworking" and lack of selectability other than arbitrary id.
   // For now this limits one tray to a page.
   $target = $('#session-video-embed-tray', context);
   player = jwplayer();
   // Initialize tray.
   var tray = new Drupal.shareBar.views.shareBar(player, $target);
  }
}
})(jQuery, Drupal, this, this.document);
