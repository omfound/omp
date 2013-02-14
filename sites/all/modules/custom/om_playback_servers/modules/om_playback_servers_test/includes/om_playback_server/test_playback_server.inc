<?php
/**
 * playback_server base class
 */
class testPlaybackServerController extends playbackServerController {

  /**
   * Methods dealing with metadata transmission.
   */
  public function create_metadata($metadata) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }
  public function check_metadata_status($metadata) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }
  public function update_metadata($metadata) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }
  public function delete_metadata($metadata) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }

  /**
   * Methods dealing with file transmission.
   */

  public function transfer_file($file_uri) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }
  public function check_file_status($file_uri) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }

  /**
   * Methods dealing with airings.
   */
  public function create_airing($schedule_obj) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }
  public function update_airing($schedule_obj) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }
  public function get_airing($schedule_obj) {
    $this->response_message(__FUNCTION__);
    $test_airing = new stdClass();
    $test_airing->title = 'A Test Airing';
    return array($test_airing);
  }
  public function delete_airing($schedule_obj) {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }

  /**
   * Methods dealing with system health
   */
  public function get_server_health() {
    $this->response_message(__FUNCTION__);
    return TRUE;
  }

  public function response_message($fn) {
    $message = t(__CLASS__ . ' :: ' . $fn . ' was executed successfully.');
    drupal_set_message($message, 'status');
  }

}