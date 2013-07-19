<?php

/**
 * Implementation of MigrateSource, to handle imports from remote MS SQL Server db servers.
 */
class MigrateSourceCablecast extends MigrateSource {
  /**
   * Playback server to use for migration. Should be a well formed om_playback_server entity.
   */
  protected $pbs;
  /**
   * Playback server controller instance. Determined by playback server entity.
   */
  protected $pbsController;
  /**
   * Options to pass to the default migrate parent class.
   */
  protected $options;
  /**
   * Result set array of cablecast show objects.
   */
  protected $results;
  /**
   * Date used to recursively get show list.
   */
  protected $currentDateMarker;
  /**
   * Current iterator row number.
   */
  protected $rowNumber;

  function __construct($options = array(), $pbs) {
    // Most importantly make sure that the cablecast module is available.
    if (!module_exists('om_playback_servers_cablecast')) {
      throw new Exception('Cablecast Playback Server module is missing. Please download and/or enable it.');
    }
    parent :: __construct($options);
    $this->options = $options;
    $this->pbs = $pbs;
    // Store controller for convenience
    $this->pbsController = om_playback_servers_entity_get_controller($this->pbs);
    $this->rowNumber = 0;
    // Perform result collection
    $this->collectResults();
  }
  /**
   * Function to recursively collect all Cablecast shows.
   */
  protected function collectResults() {
    // Temporarily cache results as _collectResults is tied to potentially many Cablecast requests.
    $cache = cache_get('cablecast_migration', 'cache');
    if (empty($cache) || empty($cache->data)) {
      $this->currentDateMarker = '1900-01-01T12:00:00';
      $this->_collectResults();
      cache_set('cablecast_migration', $this->results, 'cache', CACHE_PERMANENT);
    }
    else {
      $this->results = $cache->data;
    }
  }
  /** 
   * Recursively iterate through all shows on the Cablecast.
   */
  protected function _collectResults() {
    $result = $this->pbsController->last_modified_search($this->pbs, array('SearchDate' => $this->currentDateMarker));
    $file_options = array('IncludeValidFiles' => TRUE, 'IncludeInvalidFiles' => TRUE, 'RestrictToOrphanedFiles' => FALSE);
    if (!empty($result->LastModifiedSearchResult->ShowInfo)) {
      foreach ($result->LastModifiedSearchResult->ShowInfo AS $show) {
        $file_options['RestrictToShowID'] = $show->ShowID;
        $file = $this->pbsController->get_digital_files($this->pbs, $file_options);
        $file_record = $file->GetDigitalFilesResponse->GetDigitalFilesResult[0];
        if (!empty($file_record) && file_record['IsValid'] == TRUE) {
          $this->results[] = $show;
          $this->currentDateMarker = $show->LastModified;
        }
      }
      $this->_collectResults();
    }
  }
  /**
   * Return a string representing the source query.
   *
   * @return string
   */
  public function __toString() {
    return drupal_json_encode($this->pbs);
  }
  /**
   * Returns a list of fields available to be mapped from the source query.
   *
   * @return array
   *  Keys: machine names of the fields (to be passed to addFieldMapping)
   *  Values: Human-friendly descriptions of the fields.
   */
  public function fields() {
    return array(
      'ShowID' => 'Unique identifier of show on Cablecast',
      'Title' => 'Show title',
      'Category' => 'Human category name',
      'Producer' => 'Name of producer',
      'Project' => 'Name of project',
      'TotalSeconds' => 'Duration of show'
    ); 
  }
  /** 
   * Return show count
   */
  public function computeCount() {
    return empty($this->results) ? 0 : count($this->results);
  }
  /**
   * Reset row number.
   */
  public function performRewind() {
    $this->rowNumber = 0;
  }
  /**
   * Increment row number and return result, if any.
   */
  public function getNextRow() {
    if (!empty($this->results[$this->rowNumber])) {
      $result = $this->results[$this->rowNumber];
      $this->rowNumber ++;
      return $result;
    }
    return NULL;
  }  
}
