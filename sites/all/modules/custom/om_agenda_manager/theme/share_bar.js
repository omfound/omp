(function ($, Drupal, window, document, undefined) {
// Namespace global containers
Drupal.shareBar = {};
Drupal.shareBar.views = {};
Drupal.shareBar.models = {};
// Models:
// Extremely simple model to act as storage for player state and various resources.
Drupal.shareBar.models.shareBar = Backbone.Model.extend({
  initialize : function() {
    _.bindAll(this, 'onReady', 'onPlay');
    // Bind player events to this model.
    player = this.get('player');
    player.onReady(this.onReady);
    player.onPlay(this.onPlay);
  },
  onReady: function(){
    this.trigger('onReady');
  },
  onPlay: function(){
    this.trigger('onPlay');
  }
}); 
// Views:
// View to handle most of the interaction for the sharebar.
Drupal.shareBar.views.shareBar = Backbone.View.extend({
  events : {
    // Prevent form submit.
    'submit form' : 'preventSubmit',
    'click .show-hide' : 'toggleInterface',
    'change input.in-point' : 'interfaceChange',
    'change input.out-point' : 'interfaceChange',
    'change input.width' : 'interfaceChange',
    'change input.height' : 'interfaceChange',
    'click label.in-point' : 'setPoint',
    'click label.out-point' : 'setPoint'
  },
  initialize : function(player, domInterface) {
    // Standard bindall for this view.
    _.bindAll(this, 'initializeInterface', 'toggleInterface', 'buildEmbed', 'stopPlayer');
    // Attach this view to the dom element.
    this.setElement(domInterface);
    $(this.el).hide();
    // Instantiate new sharebar model.
    this.shareBarModel = new Drupal.shareBar.models.shareBar({'player' : player});
    // Listen for player events.
    this.shareBarModel.on('onReady', this.initializeInterface, this);
    this.shareBarModel.on('onPlay', this.setDurationOnce, this);
    // Set toggle to closed.
    this.toggleState = false;
  },
  initializeInterface : function() {
    url = document.URL;
    if (url.indexOf('embed=true') > 0) {
      this.remove();
    }
    url = url.split("?");
    url = url[0];
    this.shareBarModel.set('url', url);
    // Set width and height.
    player = this.shareBarModel.get('player');
    this.shareBarModel.set('interfaceWidth', 960);
    this.shareBarModel.set('interfaceHeight', 68);
    this.shareBarModel.set('width', 420);
    this.shareBarModel.set('height', player.config.height);
    // Resize interface.
    $(this.el).width(this.shareBarModel.get('interfaceWidth')); 
    // Set Default interface values.
    $(this.el).find('input.in-point').val(0).trigger('change');
    $(this.el).find('input.out-point').val(0).trigger('change');
    $(this.el).find('input.width').val(420);
    $(this.el).find('input.height').val(player.config.height);
    $(this.el).find('.facebook').val(url);
    this.buildEmbed();
    // Do stupid play for one second to get duration.
    // PILE ON THE PENUT BUTTER KLUDGE
    player.setVolume(0);
    player.play();
    this.playerInterval = setInterval(this.stopPlayer, 1000); 
  },
  stopPlayer : function() {
    player = this.shareBarModel.get('player');
    if (player.getPosition() > 0) {
      clearInterval(this.playerInterval);
      player.stop();
      player.setVolume(50);
      $(this.el).show();
    }
  },
  toggleInterface : function(e) {
    // Open or close the interface.
    if (this.toggleState == false) {
      this.toggleState = true;
      $(e.target).text('- Hide');
      $(this.el).find('.inner').animate({'height' : this.shareBarModel.get('interfaceHeight')}, 500);
    }
    else {
      this.toggleState = false;
      $(e.target).text('+ Share This');
      $(this.el).find('.inner').animate({'height' : 0}, 500);
    }
  },
  preventSubmit : function(e) {
    e.preventDefault();
  },
  interfaceChange : function(e) {
    key = $(e.target).attr('name');
    value = $(e.target).val();
    this.shareBarModel.set(key, value);
    this.buildEmbed();
  },
  setPoint : function(e) {
    // Set a cuepoint.
    player = this.shareBarModel.get('player');
    position = player.getPosition();
    position = parseInt(position);
    if ($(e.target).hasClass('in-point')) {
      $(this.el).find('input.in-point').val(position).trigger('change');
    }
    if ($(e.target).hasClass('out-point')) {
      $(this.el).find('input.out-point').val(position).trigger('change');
    } 
  },
  setDurationOnce: function() {
    // Event handler to be tied to onPlay from the video player.
    // After the file has been buffered once the duration is availabble.
    // Snag it and stop listening. This could be combined into stop player above.
    player = this.shareBarModel.get('player');
    duration = player.getDuration();
    duration = parseInt(duration);
    $(this.el).find('input.out-point').val(duration).trigger('change');
    this.buildEmbed();
    this.shareBarModel.off('onPlay', this.setDurationOnce, this);
  },
  buildEmbed : function() {
    // Build iframe embed
    url = this.shareBarModel.get('url', url);
    url += '?embed=true&width=' + this.shareBarModel.get('width');
    url += '&height=' + this.shareBarModel.get('height');
    url += '&embedInPoint=' + this.shareBarModel.get('embedInPoint');
    url += '&embedOutPoint=' + this.shareBarModel.get('embedOutPoint');
    this.shareBarModel.set('embedUrl', url);
    url = "<iframe width='" + this.shareBarModel.get('width')  + "' height='" + this.shareBarModel.get('height') + "' frameborder='0' scrolling='no' src='" + url + "'></iframe>";
    $(this.el).find('input.embed').val(url);
  }
});

Drupal.behaviors.shareBar = {
  attach : function(context) {
   // NB: here I've hard coded ids for the tray and used the ambiguous player call.
   // This is due to the previous "frameworking" and lack of selectability other than arbitrary id.
   // For now this limits one tray to a page.
   $target = $('#session-video-embed-tray', context);
   player = jwplayer();
   var tray = new Drupal.shareBar.views.shareBar(player, $target);
  }
}
})(jQuery, Drupal, this, this.document);
