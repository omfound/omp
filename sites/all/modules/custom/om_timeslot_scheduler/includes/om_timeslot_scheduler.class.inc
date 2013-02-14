<?php

class omTimeslotSchedulerScheduleController {

  protected $errors = array();

  public $schedule_run;

  public function __construct() {
    // Store Initial Values
  }
  
  /**
   * Create a schedule run object
   */
  public function buildScheduleRun($schedule_run) {
    return new omTimeslotSchedulerscheduleRun($schedule_run);
  }
  
  /**
   * Generate preview of schedule
   */
  public static function previewSchedule($schedule_run) {
  }
  
  /**
   * Commit schedule
   */
  public function commitSchedule($schedule_run) {
    
  }
}


class omTimeslotSchedulerscheduleRun {
  
  protected $errors = array();
  
  /**
   * Field validations for applicable vars. Only needed for vars coming from other systems.
   */
  public $validations = array('channel_tid' => 'is_numeric', 'start' => 'is_numeric', 'end' => 'is_numeric');
  
  public $channel_tid, $start, $end, $bulk_operation, $airing_list, $gaps, $timeslots, $available_shows;
  
  public function __construct($schedule_run = array()) {
   try {
     $this->checkVars('start', $schedule_run);
     $this->checkVars('end', $schedule_run);
     $this->checkVars('channel_tid', $schedule_run);
   }
   catch (Exception $e) {
     $this->setError($e, __FUNCTION__, 'error');
   }
   $this->setVars($schedule_run);
  }
  
  /**
   * Determine if this run is during adult hours
   */
  public function isAdultHours() {
  
  }
  
  public function getTimeslots() {
    //dsm('brozle');
    $this->timeslots = array();
    $query = db_select('field_data_field_om_timeslot_date', 'date');
    $query->fields('date', array('entity_id'));
    $query->join('field_data_field_om_timeslot_channel', 'channel', 'date.entity_id=channel.entity_id');
    $query->condition('field_om_timeslot_date_value', $this->start, '>');
    $query->condition('field_om_timeslot_date_value2', $this->start, '<');
    $result = $query->execute();
    while($row = $result->fetchAsscoc()) {
      if (empty($this->timeslots[$row['nid']])) {
        $node = node_load($row['nid']);
        $this->timeslots[$row['nid']] = $node;
      }
    }
    if (empty($this->timeslots)) {
      $message = t('No timeslot events were found for the provided date range.');
      throw new Exception($message);
    }
  }
  
  /**
   * Build the list of shows to schedule with their own starts and stops.
   */
  public function buildAiringList() {
    if (empty($this->timeslots)) {
      return;
    }
  }
  
  /**
   * Build the list of shows to schedule with their own starts and stops.
   */
  public function getGaps() {
    if (empty($this->timeslots)) {
      return;
    }
  }
  
  /**
   * Implement a rule.
   */
  public function implementRule($rule = '') {
    if (empty($this->timeslots)) {
      return;
    }
    //om_timeslot_scheduler_entity_get_rules();
  }
  
  protected function checkVars($key, $vars) {
    if (empty($vars[$key]) && (is_array($vars) || is_object($vars))) {
      $message = t('An array or object was sent to the scheduling run without a valid key.');
      throw new Exception($message);
    }
    else {
      if (is_object($vars)) {
        $vars = (array)$vars;
      }
      if (!empty($this->validations[$key])) {
        if (is_array($vars)) {
          if (!$this->validations[$key]($vars[$key])) {
            $message = t('Schedule run is has a malformed value for key: !key Value was: !value', array('!key' => $key, '!value' => $vars[$key]));
            throw new Exception($message);
          }
        }
        else {
          if (!$this->validations[$key]($vars)) {
            $message = t('Schedule run is has a malformed value for key: !key Value was: !value', array('!key' => $key, '!value' => $vars));
            throw new Exception($message);
          }
        }
      }
    }
  }
  
  protected function setVars($vars) {
    foreach ($vars AS $key => $value) {
      $this->{$key} = $value;
    }
  }
  
  public function getErrors() {
    return $this->errors;
  }
  
  public function setError($error, $key, $severity) {
    $this->errors[$key]['error'] = $error;
    $this->errors[$key]['severity'] = $severity;
  }
}