<?php
class cablecastPlaybackServerController extends playbackServerController {
  /**
   * Methods dealing with metadata transmission.
   */
  public function create_metadata($pbs, $show) {
    // Create a show record
    $json = $this->make_cablecast_show($pbs, $show);
    $show_result = $this->execute_cablecast_curl($pbs, 'test/api/shows', $json, 'POST');
    // Create media
    $json = $this->make_cablecast_media($pbs, $show);
    $media = $this->execute_cablecast_curl($pbs, 'test/api/media', $json, 'POST');
    // Create reel
    if ($show->field_om_show_duration['und'][0]['value']) {
      $json = $this->make_cablecast_reel($pbs, $show, $show_result, $media);
      $reel = $this->execute_cablecast_curl($pbs, 'test/api/reels', $json, 'POST');
    }
    return $show_result;
  }

  public function check_metadata_status($pbs, $show_id = NULL) {
    if (empty($show_id)) {
      $time = date('Y-m-d');
      $query = '?lastmodified=' . $time . '&lastmodifiedcomparator=<';
      $first_page = $this->execute_cablecast_curl($pbs, 'test/api/shows', $query, 'GET');
      return $first_page;
    }
    else {
      // We do a specfiic show lookup.
      $command = 'test/api/shows/' . $show_id;
      $result = $this->execute_cablecast_curl($pbs, $command, '', 'GET');
      return $result;
    }
  }

  public function update_metadata($pbs, $shows = array()) {
    // Here we would already have a show id and do not need to do this in the future: strictly testing
    $first_page = $this->check_metadata_status();
    $show = new stdClass();
    $show->field_om_show_pbs_uid['und'][0] = $first_page['Results'][0]['ShowID'];
    // end test scenario

    $cc_show = $this->check_metadata_status($show);
    // Here is where we would make changes ot the reocord...
    $cc_show['Title'] = 'Leo is making big changes here...';
    $cc_show = drupal_json_encode($cc_show);
    $command = 'test/api/shows/' . $first_page['Results'][0]['ShowID'];
    $result = $this->execute_cablecast_curl($command, $cc_show, 'PUT');
  }

  public function delete_metadata($pbs, $metadata) {
    
  }

  /**
   * Methods dealing with file transmission.
   */
  public function transfer_file($pbs, $file_uri) {
    
  }

  public function update_file($pbs, $show) {
    $files = $this->check_file_status('');
    $file_record = $files[0];
    $file_record['FileName'] = 'leos_file_now.mpeg';
    $file_id = $file_record['ID'];
    $file_record = drupal_json_encode($file_record);
    $response = $this->execute_cablecast_curl('test/api/digitalfiles/' . $file_id, $file_record, 'PUT');
    dsm($response);
  }

  public function check_file_status($pbs, $params) {
    if (!empty($params['filename'])) {
      
    }
    else {
      $query = '';
      if (!empty($params)) {
        $query = '?' . http_build_query($params);
      }
      $result = $this->execute_cablecast_curl($pbs, 'test/api/digitalfiles', $query, 'GET');
    }
    return $result;
  }

  /**
   * Methods dealing with airings.
   */
  public function get_airing($pbs, $schedule_obj) {
      $start = date('Y-m-d\TH:i:s', $schedule_obj['start']);
      $end = date('Y-m-d\TH:i:s', $schedule_obj['end']);
      $channel_id = '';
      if (isset($pbs->output)) {
        $channel_id = '&channelid=' . $pbs->output;
      }
      $query = '?pagesize=' . 200 . '&starttime=' . $start . '&endtime=' . $end . $channel_id;
      $first_page = $this->execute_cablecast_curl($pbs, 'test/api/schedule', $query, 'GET');
      $results = array();
      $airing_map = array(
        'RunDateTime' => 'start',
        'end' => 'end',
        'ScheduleID' => 'uid',
        'ShowID' => 'show_id',
        'duration' => 'duration',
        'title' => 'title',
      );
      if (!empty($first_page['Results'])) {
        foreach($first_page['Results'] AS $airing) {
           $show_data = $this->check_metadata_status($pbs, $airing['ShowID']);
           $airing['title'] = $show_data['Title'];
           $airing['duration'] = $show_data['Reels'][0]['Length'];
           $airing['RunDateTime'] = strtotime($airing['RunDateTime']);
           $airing['end'] = $airing['RunDateTime'] + $show_data['Reels'][0]['Length'];
           $results[] = $this->generalize_data_structure($airing, $airing_map);
        }
        return $results;
      }
      return array();
  }

  public function update_airing($pbs, $schedule_obj) {
    // We are getting fake results here for testing purposes again...
    $query = $this->get_airing();
    $schedule_id = $query['Results'][1]['ScheduleID'];
    $airing_record = $query['Results'][1];
    $airing_record['RunDateTime'] = '1984-03-02T01:00:00';
    $airing_record = drupal_json_encode($airing_record);
    
    $command = 'test/api/schedule/' . $schedule_id;
    $result = $this->execute_cablecast_curl($command, $airing_record, 'PUT');
    return $result;
  }

  public function create_airing($pbs, $schedule_item) {
    $query = $this->make_cablecast_airing($pbs, $schedule_item);
    $result = $this->execute_cablecast_curl($pbs, 'test/api/schedule', $query, 'POST');
    return $result;
  }

  public function delete_airing($pbs, $schedule_obj) {
    // We are getting fake results here for testing purposes again...
    $query = $this->get_airing();
    $schedule_id = $query['Results'][0]['ScheduleID'];

    $command = 'test/api/schedule/' . $schedule_id;
    $result = $this->execute_cablecast_curl($command, $json, 'DELETE');
    return $result;
  }

  /**
   * Methods dealing with system health
   */
  public function get_server_health() {
    $location_id = $this->execute_cablecast_curl('test/api/locations', '', 'GET', $this->uri);
    
  }

  public function get_server_location_id() {
    $location_id = $this->execute_cablecast_curl('test/api/locations', '', 'GET', $this->uri);
    return $location_id;
  }

  public function get_server_channel_info() {
    $channel_info = $this->execute_cablecast_curl('test/api/channels', '', 'GET', $this->uri);
    return $channel_info;
  }
  
  public function create_reel($show) {
    // Take the reel part of the show record
    // and POST to test/api/reels
    $reel = $this->make_cablecast_reel($show);
    $result = $this->execute_cablecast_curl('test/api/reels', $reel, 'POST');
    return $result;
  }
  
  public function update_reel($show) {
    // Take the reel part of the show record
    // and PUT to test/api/reels/realID
    $reel = $this->make_cablecast_reel($show);
    $path = 'test/api/reels/5606';

    $result = $this->execute_cablecast_curl($path , $reel, 'PUT');
    return $result;
  }

  public function handle_file_storage($uri) {
    
  }

  /**
   * Utility methods and stuff not from the interface
   */

  /**
   * Execute a variety of http requests via curl to the cc.
   * 
   * @param $command
   *   The end point where the command will be sent. May sometimes include a resource id.
   *
   * @param $query
   *   For GET requests these are query parameters in standard form. For all other requests these
   *   are the http bodies (payload) with made of properly formatted JSON.
   *
   * @param $verb
   *   The verb to use for the http request.
   *
   * @param $server_uri
   *   For use only in situations where the class is instantiated outside of an entity. Otherwise
   *   the entity uri is used instead.
   *
   * @returns response from cc as array
   *
   */
  protected function execute_cablecast_curl($pbs, $command, $query = '', $verb = 'GET', $server_uri = '') {
    if (empty($server_uri)) {
      $server_uri = $pbs->uri;
    }

    $server_uri = rtrim($server_uri, '/');
    $command = ltrim($command, '/');

    $ch = curl_init();
    // TEMP -- sets curl to ignore the validity of a certificate.
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
    switch ($verb) {
      case 'GET':
        $complete_path = $server_uri . '/' . $command . $query;
        curl_setopt($ch, CURLOPT_URL, $complete_path);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
        break;
      case 'POST':
        $complete_path = $server_uri . '/' . $command;
        curl_setopt($ch, CURLOPT_URL, $complete_path);
        curl_setopt($ch, CURLOPT_POST, TRUE); 
        curl_setopt($ch, CURLOPT_POSTFIELDS, $query); 
        curl_setopt($ch, CURLOPT_HEADER, FALSE); 
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
        $header_data = array('Content-Length: ' . strlen($query), 'Content-Type: application/json');
        curl_setopt ($ch, CURLOPT_HTTPHEADER, $header_data);
        break;
      case 'PUT':
        $complete_path = $server_uri . '/' . $command;
        curl_setopt($ch, CURLOPT_URL, $complete_path);
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'PUT');
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
        $header_data = array('Content-Length: ' . strlen($query), 'Content-Type: application/json');
        curl_setopt ($ch, CURLOPT_HTTPHEADER, $header_data);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $query); 
        break;
      case 'DELETE':
        $complete_path = $server_uri . '/' . $command;
        curl_setopt($ch, CURLOPT_URL, $complete_path);
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'DELETE');
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
        break;
    }

    $output = curl_exec($ch);
    $response = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);
    if ($response > 300) {
      $message = t('The Cablecast at !uri returned http code: !response This occurred during operation: !verb !command ', array('!uri' => $pbs->uri, '!response' => $response, '!verb' => $verb, '!command' => $command));
      om_log_create_log_entry('om_playback_servers', 'cablecast', 0, 1, $message, array());
      throw new Exception($message);
    }

    return drupal_json_decode($output);
  }

  /**
   * The following three methods are formatters for creating new cc resources.
   * I'm thinking in the future there should be a helper class that takes these resources and formats them properly.
   * They all work in terms of arrays that are JSON encoded.
   */
  public function make_cablecast_show($pbs, $show) {
    $date_string = date('Y-m-d\TH:i:s');
    $json_array = array(
      'LocationID' => $pbs->location_id,
      'Title' => $show->title,
      'EventDate' => $date_string,
      'CustomFields' => array(),
    );
    $json = drupal_json_encode($json_array);
    
    return $json;
  }

  public function make_cablecast_airing($pbs, $airing) {
    // end test scenario
    $json_array = array(
      'ChannelID' => $pbs->output,
      'LocationID' => $pbs->location_id,
      'ShowID' => $airing['ShowID'],
      'RunDateTime' => date('Y-m-d\TH:i:s', $airing['start']),
      'RunBump' => 0,
      'RunLock' => FALSE,
      'RunType' => 0,
      'BugText' => '',
      'CrawlText' => '',
      'CrawlLength' => 0,
      'CrawlInterval' => 0,
      'CGExempt' => FALSE,
      'IDType' => 1,
      'ManualEventID' => 0
    );
    return drupal_json_encode($json_array);
  }

  public function make_cablecast_reel($pbs, $show, $show_record, $media_record) {
    $json_array = array(
      'ShowID' => $show_record['ShowID'],
      'Length' => $show->field_om_show_duration['und'][0]['value'],
      'Cue' => 0,
      'MediaID' => $media_record['MediaID'],
      'ReelNumber' => 1,
      'Title' => 1,
      'Chapter' => 1,
    );
    return drupal_json_encode($json_array);
  }

  public function make_cablecast_media($pbs, $show) {
    $date_string = date('Y-m-d\TH:i:s');
    $json_array = array(
      "LocationID" => $pbs->location_id,
      "FormatID" => 80,
      "MediaName" => $show->title,
      "DispositionID" => -1,
      "DispositionDate" => $date_string,
      "CreationDate" => $date_string,
      "PreAssignedDeviceID" => 0,
      "PreassignedDeviceSlot" => 1
    );
    return drupal_json_encode($json_array);
  }
}