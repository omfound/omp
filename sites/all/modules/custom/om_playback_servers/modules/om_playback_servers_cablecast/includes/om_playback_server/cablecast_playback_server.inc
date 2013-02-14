<?php
class cablecastPlaybackServerController extends playbackServerController {
  /**
   * First few methods come from the playbackServerController interface.
   * --Methods dealing with metadata transmission.
   */
  public function create_metadata($pbs, $metadata = array()) {
    if (is_object($metadata)) {
      $metadata = array($metadata);
    }
    foreach ($metadata AS $show) {
      $reel = $this->create_reel($pbs, $show);
      // Map drupal fields to cablecast fields.
      $params = array (
        'LocalID'       => '', //string</LocalID>
        'Title'         => $show->title,
        'CGTitle'       => $show->title, //string</CGTitle>
        'ProjectID'     => 0, //int</ProjectID>
        'CGExempt'      => 'false', //boolean</CGExempt>
        'ProducerID'    => 0, //int</ProducerID>
        'CategoryID'    => 0, //int</CategoryID>
        'EventDate'     => date('Y-m-d\TH:i:s', $show->created), //dateTime</EventDate>
        'Comments'      => '',
        'CustomFields'  => array(),
        'OnDemand'  => FALSE,
        'OnDemandStatus'  => '',
        'CrawlLengthInSeconds' => 0,
        'CrawlText' => '',
        'BugText' => '',
        'Reels'=> $reel,
        'LocationID' => $pbs->location_id
      );
      $this->soap_request($pbs, 'CreateNewShowRecord', $params);
    }
  }
  public function check_metadata_status($pbs, $metadata = array()) {
    $shows = array();
    $output = array();
    die($metadata);
    if (is_numeric($metadata)) {
      $metadata = array($metadata);
    }
    foreach($metadata AS $id) {
      $response = $this->soap_request($pbs, 'GetShowInformation', array('ShowID' => $id));
      if (is_object($response->GetShowInformationResult)) {
        $shows[] = (array) $response->GetShowInformationResult;
      }
    }
    if (count($shows) == 1) {
      return array_shift($shows);
    }
    return $shows;
  }
  public function update_metadata($pbs, $metadata = array()) {
  }
  public function delete_metadata($pbs, $metadata = array()) {
  }
  /**
   * --Methods dealing with airings.
   */
  public function create_airing($pbs, $schedule_info = array()) {
    $schedule_item = array(
      'ChannelID'   => $pbs->output, //int</ChannelID>
      'LocationID'  => $pbs->location_id, //int</LocationID>
      'ShowID'      => $schedule_info['ShowID'], //int</ShowID>
      'RunDateTime' => date('Y-m-d\TH:i:s', $schedule_info['start']), //dateTime</RunDateTime>
      'RunLock'     => TRUE, //boolean</RunLock> 
      'RunBump'     => 0, //int</RunBump>
      'CGExempt'    => FALSE, //boolean</CGExempt>
      'BugText'     => '', //string</BugText>
      'CrawlText'   => '', //string</CrawlText>
      'CrawlLength' => 0, //int</CrawlLength>
    );
    $this->soap_request($pbs, 'AddScheduleEvent', $schedule_item);
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
      $airings = array();
      if (!empty($request->GetScheduleInformationResult->ScheduleInfo)) {
        if (is_object($request->GetScheduleInformationResult->ScheduleInfo)) {
          $request->GetScheduleInformationResult->ScheduleInfo = array($request->GetScheduleInformationResult->ScheduleInfo);
        }
        foreach ($request->GetScheduleInformationResult->ScheduleInfo AS $airing) {
          $airings[] = array(
            'uid' => $airing->ScheduleID,
            'start' => $airing->StartTime,
            'end' => $airing->EndTime
           );
        }
      }
      return $airings;
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
  private function create_reel($pbs, $file) {
    $format = 0;
    $duration = 0;
    $lang = $file->language;
    if (isset($file->field_om_show_media_format[$lang][0]['value'])) {
      if ($file->field_om_show_media_format[$lang][0]['value'] == 'hd') {
        $format = 1;
      }
      if ($file->field_om_show_media_format[$lang][0]['value'] == 'sd') {
        $format = 2;
      }
    }
    if (isset($file->field_om_show_duration[$lang][0]['value'])) {
      $duration = $file->field_om_show_duration[$lang][0]['value'];
    }
    return array(
      'NewReel' => array(
        'FormatID'=> $format, //int</FormatID>
        'CueSeconds'=> $duration , //int</LengthSeconds>
        'LengthSeconds'=> 0 , //int</LengthSeconds>
        'Title'=> 0, //int</Title>
        'Chapter'=> 0, //int</Chapter>
      ),
    );
  }
}