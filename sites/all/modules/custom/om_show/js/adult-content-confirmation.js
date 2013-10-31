(function($) {
  Drupal.behaviors.adultContentPrompt = {
    attach: function(context) {
      var $target = $('.node', context);
      adultContentPrompt.attach($target);
    }
  };
  var adultContentPrompt = (function () {
    var userStatus; // tri-state: accepted, denied, challenge
    var p = {};
    p.attach = function($target) {
      if (getUserStatus() == 'challenge' || getUserStatus() == 'denied') {
        challenge($target);
      }
    }
    p.detach = function() {
      detach();
    }
    function getCookie() {
      return $.cookie('STYXKEY-adult-content-prompt');
    }
    function setCookie(value) {
      $.cookie('STYXKEY-adult-content-prompt', value, {expires: 7, path: '/'});
    }
    function challenge($target) {
      var $prompt = promptFactory();
      $target.prepend($prompt);
    }
    function handleYes() {
      setCookie('accepted');
      detach();
    }
    function handleNo() {
      setCookie('denied');
      userStatus = 'denied';
      window.location = '/';
    }
    function getUserStatus() {
      if (!userStatus) {
        var cookie = getCookie();
        userStatus = cookie ? cookie : 'challenge';
      }
      return userStatus;
    }
    function promptFactory() {
      var $prompt = $('<div/>').addClass('adult-content-prompt');
      var $strong = $('<strong/>').addClass('adult-content-strong').text('Warning: ');
      if (getUserStatus() == 'denied') {
        $message = $('<div/>').addClass('prompt-message')
          .text('This video contains adult content and is not available at this time.');
        $message.prepend($strong);
        $prompt.append($message);
      }
      if (getUserStatus() == 'challenge') {
        $message =  $('<div/>').addClass('prompt-message')
          .text('This video contains adult content. Clicking cancel will block adult content across the site. Do you wish to proceed?');
        $message.prepend($strong);
        $interfaceWrapper = $('<div/>').addClass('prompt-interface-wrapper clearfix');
        $yes = $('<div/>').addClass('prompt-interface prompt-yes')
          .text('Proceed')
          .click(handleYes);
        $no = $('<div/>').addClass('prompt-interface prompt-no')
          .text('Cancel and Return to Home Page')
          .click(handleNo);
        $interfaceWrapper.append($yes);
        $interfaceWrapper.append($no);
        $message.append($interfaceWrapper);
        $prompt.append($message);
      }
      return $prompt;
    }
    function detach() {
      $prompt = $('.adult-content-prompt');
      $prompt.find('.prompt-inteface').unbind('click');
      $prompt.remove();
    }
    return p;
  }());;
}(jQuery));
