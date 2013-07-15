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
    $this->addFieldMapping('field_om_show_project', 'MappedProjectID');
    $this->addFieldMapping('uid', 'MappedProducerID');
    $this->addFieldMapping('field_om_show_duration', 'TotalSeconds');
    $this->addFieldMapping('field_archive_transfer', 'ArchiveTransfer');
    $this->addFieldMapping('field_om_theme', 'CategoryID');
    // NB: These are migration only fields. These fields shoud be manually created BEFORE running. 
    $this->addFieldMapping('field_cablecast_user', 'Producer'); 
    $this->addFieldMapping('field_cablecast_project', 'Project');
    $this->addFieldMapping('field_cablecast_category', 'Category'); 
    $this->addFieldMapping('field_om_show_playback_server_id', 'ShowID');
    // Add other mappings.
    $this->drupal_user_map = $this->get_user_map();
    $this->drupal_migration_user = variable_get('cablecast_migration_user');
    if (empty($this->drupal_migration_user)) {
      throw new Exception('No cablecast_migration_user has been set.');
    }
    $this->drupal_project_map = $this->get_project_map();
    $this->drupal_theme_map = $this->get_theme_map();
  }
  public function prepareRow($current_row) {
    $current_row->ArchiveTransfer = 0;
    // Try to match a drupal user with cablecast producer or use the default migration user.
    $current_row->MappedProducerID = $this->match_user($current_row->Producer);
    // Try to match a migration project or use the default migration user's project.
    $current_row->MappedProjectID = $this->match_project($current_row->MappedProducerID);
    // Try to map to the theme map.
    $current_row->CategoryID = $this->match_theme($current_row->Category);
  }
  // Build map of all users keyed cleaned_name => uid
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
  // Build map of all projects keyed uid => nid
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
  // Build map of all themes keyed category => term id
  public function get_theme_map() {
    return variable_get('cablecast_category_mapping', array()); 
  }
  // Remove spaces and lowercase for easier comparison.
  public function groom_string($name) {
    return str_replace(' ', '', strtolower($name));
  }
  /** 
   * Match a project to a uid. If one doesn't exist create a new one.
   * Each user should only have one migration project.
   */
  public function match_project($uid) {
    if (!empty($this->drupal_project_map[$uid])) {
      return $this->drupal_project_map[$uid];
    }
    else {
      return $this->create_new_project($uid);
    }
  }
  // Create a new project node and add it to the project map.
  public function create_new_project($uid) {
    $project = new stdClass();
    $project->type = 'om_project';
    $project->uid = $uid;
    $project->title = 'migration';
    node_save($project);
    $this->drupal_project_map[$uid] = $project->nid;
    return $project->nid;
  }
  // Attempt to match users by name otherwise return the migration user.
  public function match_user($name) {
    $name = $this->groom_string($name);
    if (!empty($this->drupal_user_map[$name])) {
      return $this->drupal_user_map[$name];
    }
    else {
      return $this->drupal_migration_user;
    }
  }
  public function match_theme($category) {
    $key = $this->groom_string($category);
    if (!empty($this->drupal_theme_map[$key])) {
      return $this->drupal_theme_map[$key];
    } 
    return FALSE;
  }
}
