(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.jwTest = {
    attach : function() {
      jwplayer.key="LbV5colrtkrBDNQUDLcd08vwBs7psJqbdJTVTYyxrAM=";
      var player = jwplayer("jwplayer-test").setup({ 
        playlist: 'http://dev-thornton.gotpantheon.com/node/29357/cuepoints',
        height: 500,
        width: 800,
        primary: "flash",
        listbar: {
          position: 'right',
          size: 300
        }
      });
    }
  };
})(jQuery, Drupal, this, this.document);

