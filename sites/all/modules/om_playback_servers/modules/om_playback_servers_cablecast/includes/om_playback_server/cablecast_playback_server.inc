<?php
class cablecastPlaybackServerController extends playbackServerController {
  /**
   * First few methods come from the playbackServerController interface.
   * --Methods dealing with metadata transmission.
   */
  public function create_metadata($pbs, $metadata = array()) {
    
  }
  public function check_metadata_status($pbs, $metadata = array()) {
    
  }
  public function update_metadata($pbs, $metadata = array()) {
  }
  public function delete_metadata($pbs, $metadata = array()) {
    
  }
  /**
   * --Methods dealing with airings.
   */
  public function create_airing($pbs, $schedule_info = array()) {
    
  }
  public function update_airing($pbs, $schedule_info = array()) {
    
  }
  public function get_airing($pbs, $schedule_info = array()) {
    if (!empty($schedule_info)) {
      $schedule_request = array (
        'ChannelID' => $pbs->output,
        'FromDate' => date("Y-m-d\TH:i:s", $schedule_info['start']),
        'ToDate' => date("Y-m-d\TH:i:s", $schedule_info['end']),
        'restrictToShowID' => 0
      );
      $request = $this->soap_request($pbs, 'GetScheduleInformation', $schedule_request);
      dsm($request);
    }
    else {
      throw new Exception('Cablecast Playback Server: received empty schedule information');
    }
  }
  public function delete_airing($pbs, $schedule_info = array()) {
    
  }
  /**
   * --Methods dealing with system health
   */
  public function get_server_health($pbs) {
    $channels = $this->soap_request($pbs, 'GetChannels');
    dsm($channels);
  }
  // Custom and helper methods
  /**
   * Make a soap request to the pbs provided.
   */
  private function soap_request($pbs, $function, $data = array()) {
    try {
      $endpoint = $pbs->uri . '/CablecastWS/CablecastWS.asmx?WSDL';
      $client = new SoapClient($endpoint, array('cache_wsdl' => 0));
      $auth = array(
        'username' => $pbs->user,
        'password' => $pbs->password
      );
      $data = array_merge($data, $auth);
      return $client->{$function}($data);
    }
    catch(Exception $e) {
      if (is_object($pbs)) {
        $message =  'Cablecast Playback Server: ' . $pbs->name . ' threw exception: ' . $e->getMessage();
      }
      else {
        $message =  'Cablecast Playback Server: malformed playback server: ' . $e->getMessage();
      }
      throw new Exception($message);
    }
  }
}