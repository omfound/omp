<?php

/**
 * Implements hook_om_playback_servers_om_playback_server
 */
function om_playback_servers_om_playback_servers_om_playback_server() {
  return array(
    'pbs_base' => array(
      'title' => t('Playback Server'),
      'description' => t('Adds empty interface to be extended by real pbs'),
      'type' => 'om_playback_server',
      'path' => drupal_get_path('module', 'om_playback_servers') . '/includes/playback_server',
      'file' => 'om_playback_servers.inc',
      'playback_server' => array(
        'class' => 'playbackServerController',
      ),
    )
  );
}

/**
 * playback_server base class
 */
abstract class playbackServerController {

  /**
   * Methods dealing with metadata transmission.
   */
  abstract function create_metadata($pbs, $metadata = array());
  abstract function check_metadata_status($pbs, $metadata = array());
  abstract function update_metadata($pbs, $metadata = array());
  abstract function delete_metadata($pbs, $metadata = array());
  /**
   * Optional method to handle decoding uris
   */
  abstract function metadata_record_from_uri($pbs, $uri);
  /**
   * Methods dealing with file transmission.
   */

  public function transfer_file($pbs, $file_uri) {
    // This method may be legacy and TBD
  } 
  public function check_file_status($pbs, $parameters) {
    
  }

  /**
   * Methods dealing with airings.
   */
  abstract function create_airing($pbs, $schedule_obj = array());
  abstract function update_airing($pbs, $schedule_obj = array());
  abstract function get_airing($pbs, $schedule_obj = array());
  abstract function delete_airing($pbs, $schedule_obj = array());

  /**
   * Methods dealing with system health
   */
  abstract function get_server_health($pbs);

  /**
   * Optional method to handle file storage. Given a uri.. react appropriately.
   */
  public function handle_file_storage($uri) {
    
  }
}