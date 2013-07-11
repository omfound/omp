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
   * Options to pass to the Cablecast api call.
   */
  protected $apiOptions;
  /**
   * Result set
   */
  protected $results;
  protected $currentDateMarker;
  protected $rowNumber;

  function __construct($options = array(), $pbs, $apiOptions = array()) {
    if (!module_exists('om_playback_servers_cablecast')) {
      throw new Exception('Cablecast Playback Server module is missing. Please download and/or enable it.');
    }
    parent :: __construct($options);
    $this->options = $options;
    $this->pbs = $pbs;
    $this->pbsController = om_playback_servers_entity_get_controller($this->pbs);
    $this->apiOptions = $apiOptions;
    // Perform result collection
    $this->collectResults();
  }
  /**
   * Function to recursively collect all Cablecast shows.
   */
  protected function collectResults() {
    $cache = cache_get('cablecast_migration', 'cache');
    if (empty($cache) || empty($cache->data)) {
      $this->currentDateMarker = '1900-01-01T12:00:00';
      $this->_collectResults();
      cache_set('cablecast_migration', $this->results, 'cache', CACHE_TEMPORARY);
    }
    else {
      $this->result = $cache->data;
    }
  }
  protected function _collectResults() {
    $result = $this->pbsController->last_modified_search($this->pbs, array('SearchDate' => $this->currentDateMarker));
    if (!empty($result->LastModifiedSearchResult->ShowInfo)) {
      foreach ($result->LastModifiedSearchResult->ShowInfo AS $show) {
        $this->results[] = $show;
        $this->currentDateMarker = $show->LastModified;
      }
      $this->_collectResults();
    }
    cache_set('cablecast_migration', $this->results, 'cache', CACHE_TEMPORARY);
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
  public function computeCount() {
    return empty($this->results) ? 0 : count($this->results);
  }
  public function performRewind() {
    $this->rowNumber = 0;
  }
  public function getNextRow() {
    if (!isset($this->rowNumber)) {
      $this->rowNumber = 0;
    }
    else {
      $this->rowNumber ++;
    }
    dsm($this->rowNumer);
    if (!empty($this->results[$this->rowNumber])) {
      return $this->results[$this->rowNumber];
    }
    $this->rowNumber --;
    return NULL;
  }  
}
