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
   */
  public function get_original_file_name($uri) {
    $show_id = $this->get_show_id($uri);
    $controller = om_playback_servers_entity_get_controller($this->pbs);
    $options = array('RestrictToOrphanedFiles' => FALSE, 'RestrictToShowID' => $show_id);
    $file = $controller->get_digital_files($this->pbs, $options);
    if (!empty($file->GetDigitalFilesResult) && !empty($file->GetDigitalFilesResult->DigitalFileInfo)) {
      if (is_object($file->GetDigitalFilesResult->DigitalFileInfo)) {
        $file->GetDigitalFilesResult->DigitalFileInfo = array($file->GetDigitalFilesResult->DigitalFileInfo);
      }
      foreach ($file->GetDigitalFilesResult->DigitalFileInfo AS $file_object) {
        $file_name = $file_object->FileName;
        $file_name = str_replace($show_id, '', $file_name);
        return $file_name;
      }
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
        if (is_array($digital_files)) {
          foreach ($digital_files AS $file) {
            $this->orphaned_files[$file->ID] = $file->FileName;
          }
        }
        else {
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
    $controller = om_playback_servers_entity_get_controller($this->pbs);
    $result = $controller->get_digital_files($this->pbs);
    if (!empty($result->GetDigitalFilesResult->DigitalFileInfo)) {
      foreach ($result->GetDigitalFilesResult->DigitalFileInfo AS $possible_file) {
        if ($file_id == $possible_file->ID) {
          $file = $possible_file;
          continue;
        }
      }
      if (!empty($file)) {
        $entity->field_om_show_duration = array(
          $entity->language => array(
            0 => array(
              'value' => $file->LengthInSeconds
            )
          )
        );
        $meta_data = $controller->create_metadata($this->pbs, $entity);
        if (!empty($meta_data->CreateNewShowRecordResult) && is_numeric($meta_data->CreateNewShowRecordResult)) {
          $new_file_name = $meta_data->CreateNewShowRecordResult . $file->FileName;
          $new_file_name = substr($new_file_name, 0, strripos($new_file_name, '.'));
          $options = array('ID' => $file_id, 'NewName' => $new_file_name);
          $controller->rename_file($this->pbs, $options);
          return 'cablecast://' . $meta_data->CreateNewShowRecordResult;
        }
      }
    }
    return FALSE;
  }
  /**
   * Return IA encoding status.
   **/
  public function get_ia_status($uri) {
    $meta_data = $this->get_show_record($uri);
    $status = '';
    if (!empty($meta_data) && !empty($meta_data['CustomFields']->CustomField)) {
      // NB: Account for inconsistant returns
      if (is_object($meta_data['CustomFields']->CustomField)) {
        $meta_data['CustomFields']->CustomField = array($meta_data['CustomFields']->CustomField);
      }
      foreach ($meta_data['CustomFields']->CustomField AS $field) {
        if ($field->Name == 'Archive-URL') {
           $status = 'Complete';
        }
        if ($field->Name == 'Archive-Upload') {
          if ($status != 'Complete') {
            $status = 'Processing';
          }
        }
      }
    }
    else {
      $status = 'Unqueued';
    }
    return $status;
  }
  /**
   * Get the VOD derivitive from IA.
   **/
  public function get_ia_url($uri) {
    $meta_data = $this->get_show_record($uri);
    if (!empty($meta_data) && !empty($meta_data['CustomFields'])) {
      // NB: Account for inconsistant returns
      if (is_object($meta_data['CustomFields']->CustomField)) {
        $meta_data['CustomFields']->CustomField = array($meta_data['CustomFields']->CustomField);
      }
      foreach ($meta_data['CustomFields']->CustomField AS $field) {
        if ($field->Name == 'Archive-URL') {
          return $field->Value;
        }
      }
    }
    return FALSE;
  }
  /**
   * Return the show record
   **/
  public function get_show_record($uri) {
    $show_id = $this->get_show_id($uri);
    $controller = om_playback_servers_entity_get_controller($this->pbs);
    $meta_data = $controller->check_metadata_status($this->pbs, $show_id);
    if (!empty($meta_data)) {
      return $meta_data;
    }
    else {
      return FALSE;
    }
  }
  /**
   * Given a uri return a matching entity.
   */
  public function get_entity_id_from_uri($uri) {
     $fields = field_info_fields();
     foreach ($fields AS $name => $field) {
       if ($field['type'] == 'cablecast_file_selector') {
         $table_name = array_keys($field['storage']['details']['sql']['FIELD_LOAD_CURRENT']);
         $table_name = $table_name[0];
         $field_name = $field['storage']['details']['sql']['FIELD_LOAD_CURRENT'][$table_name];
         $field_name = array_values($field_name);
         $field_name = $field_name[0];
         if (is_string($table_name) && is_string($field_name)) {
           $query = db_select($table_name, 't');
           $query->fields('t', array('entity_id'));
           $query->condition($field_name, $uri, '=');
           $resource = $query->execute();
           $result = $resource->fetchAll();
           if (!empty($result)) {
             $result = array_shift($result);
             return $result->entity_id;
           }
         }
       }
     }
     return FALSE;
  }
  public function get_file_validity($uri) {
    $show_id = $this->get_show_id($uri);
    $controller = om_playback_servers_entity_get_controller($this->pbs);
    dsm($this->pbs);
    dsm($show_id); 
    $meta_data = $controller->check_file_status($this->pbs, $show_id);
    dsm($meta_data);     
  }
}
