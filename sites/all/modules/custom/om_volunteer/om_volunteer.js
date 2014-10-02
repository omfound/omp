(function($) {
  Drupal.behaviors.omVolunteer = {
    attach: function() {
      $('#om-volunteer-discount-pane .form-submit').once('om-volunteer', function() {
        $(this).click(handleClick);
      });
    }
  };
  function handleClick() {
    var r = confirm("Are you sure you want to apply an alternate payment method? Transactions are non-refundable.");
    if (!r) {
      return false;
    }
  }
})(jQuery);
