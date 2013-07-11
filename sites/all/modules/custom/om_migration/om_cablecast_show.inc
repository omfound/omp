<?php

class omCablecastShowMigration extends Migration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migrate Cablecast shows to Drupal.');
    // Use the default Cablecast.
    $pbsid = variable_get('default_cablecast');
    if (empty($pbsid)) {
      throw new Exception('No default Cablecast has been set.');
    }
    $pbs = om_playback_servers_load($pbsid);
    $pbs = array_shift($pbs);
    // Not sure how to get migrate to automatically include new sources (if it's possible at all)
    if (!class_exists('MigrateSourceCablecast')) {
      require_once('/' . drupal_get_path('module', 'om_migration') . '/includes/cablecast.inc');
    }
    // Set our source and destination
    $this->source = new MigrateSourceCablecast(array(), $pbs, array());
    $this->destination = new MigrateDestinationNode('om_show'); 
    // Here we rip off the SQL map class as it performs well enough.
    // If we wanted more custom messaging or were to distribute this migration we would want our own.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'ShowID' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Cablecast show id.',
          'alias' => 'n',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    // Field mappings
    $this->addFieldMapping('title', 'Title');
    $this->addFieldMapping('field_om_show_broadcast_file', 'ShowUri');
    $this->addFieldMapping('field_om_show_project', 'MappedProjectID');
    $this->addFieldMapping('field_cablecast_project', 'Project');
    $this->addFieldMapping('uid', 'MappedProducerID');
    $this->addFieldMapping('field_cablecast_user', 'Producer');
    $this->addFieldMapping('field_om_show_duration', 'TotalSeconds');
    // Add other mappings.
    $this->drupal_user_map = $this->get_user_map();
    $this->drupal_migration_user = variable_get('cablecast_migration_user');
    if (empty($this->drupal_migration_user)) {
      throw new Exception('No cablecast_migration_user has been set.');
    }
    $this->drupal_project_map = $this->get_project_map();
  }
  public function prepareRow($current_row) {
    // Turn show id into cablecast uri
    $current_row->ShowUri = "cablecast://" . $current_row->ShowID;
    // Try to match a drupal user with cablecast producer or use the default migration user.
    $current_row->MappedProducerID = $this->match_user($current_row->Producer);
    // Try to match a migration project or use the default migration user's project.
    $current_row->MappedProjectID = $this->match_project($current_row->MappedProducerID);
  }
  public function get_user_map() {
    $output = array();
    $query = db_select('users', 'u');
    $query->fields('u', array('uid', 'name'));
    $resource = $query->execute();
    while ($row = $resource->fetchAssoc()) {
      $output[$this->groom_string($row['name'])] = $row['uid'];
    }
    return $output;
  }
  public function get_project_map() {
    $output = array();
    $query = db_select('node', 'n');
    $query->fields('n', array('uid', 'nid'));
    $query->condition('title', 'migration', '=');
    $resource = $query->execute();
    while ($row = $resource->fetchAssoc()) {
      $output[$row['uid']] = $row['nid'];
    }
    return $output;
  }
  public function groom_string($name) {
    return str_replace(' ', '', strtolower($name));
  }
  public function match_project($uid) {
    if (!empty($this->drupal_project_map[$uid])) {
      return $this->drupal_project_map[$uid];
    }
    else {
      return $this->create_new_project($uid);
    }
  }
  public function create_new_project($uid) {
    $project = new stdClass();
    $project->type = 'om_project';
    $project->uid = $uid;
    $project->title = 'migration';
    node_save($project);
    $this->drupal_project_map[$uid] = $project->nid;
    return $project->nid;
  }
  public function match_user($name) {
    $name = $this->groom_string($name);
    if (!empty($this->drupal_project_map[$name])) {
      return $this->drupal_project_map[$name];
    }
    else {
      return $this->drupal_migration_user;
    }
  }
}
