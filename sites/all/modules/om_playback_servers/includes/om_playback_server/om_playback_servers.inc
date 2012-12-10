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
  abstract function create_metadata($pbs, $metadata);
  abstract function check_metadata_status($pbs, $metadata);
  abstract function update_metadata($pbs, $metadata);
  abstract function delete_metadata($pbs, $metadata);

  /**
   * Methods dealing with file transmission.
   */

  abstract function transfer_file($pbs, $file_uri); // This method may be legacy and TBD
  abstract function check_file_status($pbs, $parameters);

  /**
   * Methods dealing with airings.
   */
  abstract function create_airing($pbs, $schedule_obj);
  abstract function update_airing($pbs, $schedule_obj);
  abstract function get_airing($pbs, $schedule_obj);
  abstract function delete_airing($pbs, $schedule_obj);

  /**
   * Methods dealing with system health
   */
  abstract function get_server_health();

  /**
   * Optional method to handle file storage. Given a uri.. react appropriately.
   */
  abstract function handle_file_storage($uri);

  /**
   * Shared function to ensure responses are properly formatted.
   */
  public function format_response($object, $type) {
    $missing = array();
    switch ($type) {
      case 'airing':
        if (empty($object->guid)) {
          $missing[] = 'guid';
        }
        if (empty($object->start)) {
          $missing[] = 'start';
        }
        if (empty($object->end)) {
          $missing[] = 'end';
        }
        if (empty($object->show_id)) {
          $missing[] = 'show';
        }
        break;
      case 'status':
        break;
    }
    if (empty($missing)) {
      return TRUE;
    }
    else {
      return $missing;
    }
  }
  
  public function generalize_data_structure($airing, $map) {
    $formated_airing = array();
    foreach ($map AS $key => $value) {
      $formated_airing[$value] = $airing[$key];
    }
    return $formated_airing;
  }
}