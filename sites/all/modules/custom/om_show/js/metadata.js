(function($) {
  Drupal.behaviors.metadata = {
    attach: function() {
      // Here we go 
      $('#edit-field-om-show-project-und').once('metadata',
        function() {
          $(this).change(
            function() {
              if ($(this).val() != '_none') {
                $(this).prop('disabled', true);
                $.ajax({
                  url: '/project-metadata/' + $(this).val(),
                  success: function(data) {
                    updateFields(data);
                    console.log('removing disable');
                    $(this).prop('disabled', false);
                  },
                  context: this
                });
              }
            }
          );
        }
      );
    }
  }; 
  function updateFields(data) {
    data = JSON.parse(data);
    for (var x in data) {
      if (data[x]) {
        $('#' + fieldMap[x]).val(data[x]);
      }
    }
  }
  var fieldMap = {
    'field_license' : 'edit-field-license-und',
    'field_om_theme' : 'edit-field-om-theme-und',
    'field_om_genre' : 'edit-field-om-genre-und',
    'field_om_rating' : 'edit-field-om-rating-und',
    'field_om_language' : 'edit-field-om-language-und',
  };
})(jQuery);
