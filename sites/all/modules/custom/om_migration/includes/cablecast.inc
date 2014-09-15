<?php

class CablecastMigrationCache {
  /**
   * Playback server to use for migration. Should be a well formed om_playback_server entity.
   */
  protected $pbs;
  /**
   * Playback server controller instance. Determined by playback server entity.
   */
  protected $pbsController;
  /**
   * Date used to recursively get show list.
   */
  protected $currentDateMarker;
  /**
   * Result set array of cablecast show objects.
   */
  protected $results;
  function __construct($pbs) {
    // Most importantly make sure that the cablecast module is available.
    if (!module_exists('om_playback_servers_cablecast')) {
      throw new Exception('Cablecast Playback Server module is missing. Please download and/or enable it.');
    }
    $this->pbs = $pbs;
    // Store controller for convenience
    $this->pbsController = om_playback_servers_entity_get_controller($this->pbs);
  }
  /**
   * Collect all shows from cablecast using last_modified_search method.
   */
  public function collectResults() {
    $this->currentDateMarker = '1900-01-01T12:00:00';
    $this->_collectResults();
    cache_set('cablecast_migration', $this->results, 'cache', CACHE_PERMANENT);
  }
  /**
   * Recursive helper called above.
   */ 
  protected function _collectResults() {
    $result = $this->pbsController->last_modified_search($this->pbs, array('SearchDate' => $this->currentDateMarker));
    if (!empty($result->LastModifiedSearchResult->ShowInfo)) {
      foreach ($result->LastModifiedSearchResult->ShowInfo AS $show) {
        $this->results[] = $show;
        $this->currentDateMarker = $show->LastModified;
      }
      $this->_collectResults();
    }
  }
  /**
   * Validate that shows in the cache have good files on the Cablecast.
   */
  public function validateResults() {
    if (empty($this->results)) {
      $cache = cache_get('cablecast_migration', 'cache');
      $this->results = $cache->data;
    }
    $file_options = array('IncludeValidFiles' => TRUE, 'IncludeInvalidFiles' => FALSE, 'RestrictToOrphanedFiles' => FALSE);
    $files = $this->pbsController->get_digital_files($this->pbs, $file_options);
    $valid_ids = array();
    if (!empty($files->GetDigitalFilesResult->DigitalFileInfo)) {
      foreach ($files->GetDigitalFilesResult->DigitalFileInfo  AS $file) {
        $show_id = array();
        preg_match('~^(\d+)~', $file->FileName, $show_id);
        if (!empty($show_id)) {
          $valid_ids[] = $show_id[0];
        }
      }
    }
    foreach($this->results AS $key => $result) {
      if (!in_array($result->ShowID, $valid_ids)) {
        unset($this->results[$key]);
      }
    }
    cache_set('cablecast_migration', array_values($this->results), 'cache', CACHE_PERMANENT);
  }
  /**
   * Return current result count from cache.
   */
  public function computeCount() {
    if (empty($this->results)) {
      $cache = cache_get('cablecast_migration', 'cache');
      $this->results = $cache->data;
    }
    return empty($this->results) ? 0 : count($this->results);
  }
}

/**
 * Implementation of MigrateSource, to handle imports from remote MS SQL Server db servers.
 */
class MigrateSourceCablecast extends MigrateSource {
  /**
   * Options to pass to the default migrate parent class.
   */
  protected $options;
  /**
   * Result set array of cablecast show objects.
   */
  protected $results;
  /**
   * Current iterator row number.
   */
  protected $rowNumber;

  function __construct($options = array()) {
    parent :: __construct($options);
    $this->options = $options;
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
      $link = l('Build it.', 'admin/content/migrate/cablecast_cache');
      $message = t('The Cablecast migration cache has not been built. !build', array('!build' => $link));
      drupal_set_message($message);
    }
    $this->results = $cache->data;    
  }
  /**
   * Return a string representing the source query.
   *
   * @return string
   */
  public function __toString() {
    $pbs = om_migration_get_default_cablecast();
    return drupal_json_encode($pbs);
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
