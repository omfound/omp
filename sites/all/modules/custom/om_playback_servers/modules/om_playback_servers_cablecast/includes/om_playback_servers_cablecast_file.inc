<?php
/**
 * cablecastFile class is a small pseudo-streamwrapper for use with the
 * Cablecast file selector field. This class will not work with PHP's file functions.
 * @TODO may be worth creating an actual stream wrapper at some point though
 * the analogy with the Cablecast is non-standard.
 */
class cablecastFile {
  private $pbs;
  private $orphaned_files;
  function __construct() {
    $pbsid = variable_get('default_cablecast');
    if (empty($pbsid)) {
      throw new Exception('No default Cablecast has been set.');
    }
    $pbs = om_playback_servers_load($pbsid);
    $pbs = array_shift($pbs);
    $this->set_playback_server($pbs);
  }
  /**
   * Setter for private $pbs.
   */
  public function set_playback_server($pbs) {
    if (is_object($pbs)) {
      $this->pbs = $pbs;
    }
    else {
      throw new Exception('Either a malformed Playback Server or no Playback Server was provided.');
    }
  }
  public function get_external_url($uri) {
   
  }
  /**
   * Given a cc uri return the filename.
   **/
  public function get_original_file_name($uri) {
    $show_id = $this->get_show_id($uri);
    $controller = om_playback_servers_entity_get_controller($this->pbs);
    $options = array('RestrictToOrphanedFiles' => FALSE, 'RestrictToShowID' => $show_id);
    $file = $controller->get_digital_files($this->pbs, $options);
    if (!empty($file->GetDigitalFilesResult->DigitalFileInfo)) {
      $file_name = $file->GetDigitalFilesResult->DigitalFileInfo->FileName;
      $file_name = str_replace($show_id, '', $file_name);
      return $file_name;
    }
    return FALSE;
  }
  public function get_show_id($uri) {
    $show_id = str_replace('cablecast://', '', $uri);
    if (is_numeric($show_id)) {
      return $show_id;
    }
    throw new Exception('Uri is malformed.');
  }
  /**
   * Get the list of orphaned files.
   **/
  public function get_orphaned_files() {
    if (empty($this->orphaned_files)) {
      $this->orphaned_files = array();
      $controller = om_playback_servers_entity_get_controller($this->pbs);
      $result = $controller->get_digital_files($this->pbs);
      if (!empty($result->GetDigitalFilesResult->DigitalFileInfo)) {
	$digital_files = $result->GetDigitalFilesResult->DigitalFileInfo;
	if (!$digital_files->ID) {
          foreach ($digital_files AS $file) {
            $this->orphaned_files[$file->ID] = $file->FileName;
          }
	}else{
	  $this->orphaned_files[$digital_files->ID] = $digital_files->FileName;
	}
      }
    }
    return $this->orphaned_files;
  }
  /**
   * Create a new show record and tie this file to that record.
   * Then return the uri.
   **/
  public function build_uri($entity, $file_id) {
    $files = $this->get_orphaned_files();
    if (!empty($files) && !empty($files[$file_id])) {
      $controller = om_playback_servers_entity_get_controller($this->pbs);
      $meta_data = $controller->create_metadata($this->pbs, $entity);
      if (!empty($meta_data->CreateNewShowRecordResult) && is_numeric($meta_data->CreateNewShowRecordResult)) {
        $new_file_name = $meta_data->CreateNewShowRecordResult . $files[$file_id];
        $new_file_name = substr($new_file_name, 0, strripos($new_file_name, '.'));
        $options = array('ID' => $file_id, 'NewName' => $new_file_name);
        $controller->rename_file($this->pbs, $options);
        return 'cablecast://' . $meta_data->CreateNewShowRecordResult;
      }
    }
    return FALSE;
  }
  /**
   * Return IA encoding status.
   **/
  public function get_ia_status($uri) {
    return 'Processing';
  }
  /**
   * Get the VOD derivitive from IA.
   **/
  public function get_ia_url($uri) {
    
  }
}
