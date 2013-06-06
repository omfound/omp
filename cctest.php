<?php

try {
  print 'TESTING SOAP CALL <br/>';
  $client = new SoapClient('http://129.19.150.20/CablecastWS/CablecastWS.asmx?WSDL');
  $auth = array(
    'username' => 'Admin',
    'password' => 'M3d!a!!'
  );
  $channels  = $client->GetChannels($auth);
  var_dump($channels);
}
catch (Exception $e) {
  print $e->getMessage();
}

?>