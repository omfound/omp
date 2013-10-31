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
      var $prompt = promptFactory();
      $('.adult-content-prompt').replaceWith($prompt);
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
      var $strong = $('<strong/>').addClass('adult-content-strong').text('warning');
      if (getUserStatus() == 'denied') {
        $message = $('<div/>').addClass('prompt-message')
          .text('This video contains adult content and is not available at this time.');
        $message.prepend($strong);
        $prompt.append($message);
      }
      if (getUserStatus() == 'challenge') {
        $message =  $('<div/>').addClass('prompt-message')
          .text('This video contains adult content. Do you wish to proceed?');
        $message.prepend($strong);
        $yes = $('<div/>').addClass('prompt-inteface prompt-yes')
          .text('Proceed')
          .click(handleYes);
        $no = $('<div/>').addClass('prompt-inteface prompt-no')
          .text('Return to Shows')
          .click(handleNo);
        $message.append($yes);
        $message.append($no);
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
