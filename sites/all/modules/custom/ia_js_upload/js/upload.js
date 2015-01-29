(function($) {
  Drupal.behaviors.evaporateUpload = {
    attach: function(context) {
      var evap = new Evaporate({
        signerUrl: '/ia/sign',
        aws_key: 'R7zRpLa4J2Gceu7k',
        bucket: 'jstestbucket',
      });

      $('#files').change(function(evt){
        files = evt.target.files;
        for (var i = 0; i < files.length; i++){
          evap.add({
            name: 'test_' + Math.floor(1000000000*Math.random()),
            file: files[i],
            xAmzHeadersAtInitiate : {
              'x-archive-auto-make-bucket': '1',
            },
            signParams: {
              foo: 'bar'
            },
            complete: function(){
              console.log('complete................yay!');
            },
            progress: function(progress){
              console.log('making progress: ' + progress);
            }
          });
        }
            
        $(evt.target).val('');
            
      }); 
    }
  };
}(jQuery));
