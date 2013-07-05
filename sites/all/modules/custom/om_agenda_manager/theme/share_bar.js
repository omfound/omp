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
    _.bindAll(this, 'initializeInterface', 'toggleInterface', 'buildEmbed');
    // Attach this view to the dom element.
    this.setElement(domInterface);
    // Instantiate new sharebar model.
    this.shareBarModel = new Drupal.shareBar.models.shareBar({'player' : player});
    this.shareBarModel.on('onReady', this.initializeInterface, this);
    this.shareBarModel.on('onPlay', this.setDurationOnce, this);
    // Set toggle to closed.
    this.toggleState = false;
    // Hijack the dom interface
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
    this.shareBarModel.set('interfaceHeight', $(this.el).find('form').outerHeight());
    this.shareBarModel.set('width', player.config.width);
    this.shareBarModel.set('height', player.config.height);
    // Resize interface.
    $(this.el).width(this.shareBarModel.get('interfaceWidth')); 
    // Set Default interface values.
    $(this.el).find('input.in-point').val(0).trigger('change');
    $(this.el).find('input.out-point').val(0).trigger('change');
    $(this.el).find('input.width').val(player.config.width);
    $(this.el).find('input.height').val(player.config.height);
    $(this.el).find('.facebook').val(url);
    this.buildEmbed();
    // Do stupid play for one second to get duration.
   player.play();
   player.stop();
  },
  toggleInterface : function(e) {
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
    console.log(key);
    console.log(value);
    this.shareBarModel.set(key, value);
    this.buildEmbed();
  },
  setPoint : function(e) {
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
    console.log(this.shareBarModel.get('embedOutPoint'));
    if (this.shareBarModel.get('embedOutPoint') == undefined) {
      player = this.shareBarModel.get('player');
      duration = player.getDuration();
      duration = parseInt(duration);
      $(this.el).find('input.out-point').val(duration).trigger('change');
      this.buildEmbed();
    }
  },
  buildEmbed : function() {
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
