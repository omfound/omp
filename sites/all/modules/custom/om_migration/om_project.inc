<?php
// User Migration class
class omProjectMigration extends Migration {
  // class constructor
  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('om_projects_group'));
    $this->description = t('Migrate Drupal 6 projects cck nodes');
    $query = Database::getConnection('default', 'legacy')->select('node','n');
    $query->join('content_type_om_project', 'ctp', 'n.nid=ctp.nid');
    $query->leftJoin('node_revisions', 'r', 'n.nid=r.nid');
    $query->leftJoin('content_field_om_locally_produced', 'locally_produced', 'n.nid=locally_produced.nid');
    $query->leftJoin('content_field_om_theme', 'theme', 'n.nid=theme.nid');
    $query->leftJoin('content_field_om_genre', 'genre', 'n.nid=genre.nid');
    $query->leftJoin('content_field_om_language', 'language', 'n.nid=language.nid');
    $query->leftJoin('content_field_om_rating', 'rating', 'n.nid=rating.nid');
    $query->fields('n', array('nid', 'title', 'uid', 'status', 'created', 'created', 'changed'));
    $query->fields('r', array('body'));
    $query->fields('ctp', array('field_om_public_email_value', 'field_om_public_contact_info_value', 'field_om_project_episodes_value', 'field_public_om_credits_value', 'field_om_project_type_nid'));
    $query->fields('locally_produced', array('field_om_locally_produced_value'));
    $query->fields('theme', array('field_om_theme_nid'));
    $query->fields('genre', array('field_om_genre_value'));
    $query->fields('language', array('field_om_language_value'));
    $query->fields('rating', array('field_om_rating_value'));
    $query->condition('n.type', 'om_project', '=');
    $this->source = new MigrateSourceSQL($query, array(), null, array('map_joinable' => FALSE));
    // No need to force users to reset their passwords
    $this->destination = new MigrateDestinationNode('om_project');

    // map source and destination keys
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'D6 Unique Node ID',
          'alias' => 'n',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Create the field mappings
    // order: $destination, $source
    $this->addFieldMapping('field_old_project_id', 'nid');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_om_project_episodes', 'field_om_project_episodes_value');
    $this->addFieldMapping('field_om_project_contact_details', 'field_om_public_contact_info_value');
    $this->addFieldMapping('field_om_project_contact', 'field_om_public_email_value');
    $this->addFieldMapping('field_om_project_credits', 'field_public_om_credits_value');
    $this->addFieldMapping('field_om_locally_produced', 'field_om_locally_produced_value');
    $this->addFieldMapping('field_om_project_type', 'field_om_project_type_nid');
    $this->addFieldMapping('field_om_theme', 'field_om_theme_nid');
    $this->addFieldMapping('field_om_genre', 'field_om_genre_value');
    $this->addFieldMapping('field_om_language', 'field_om_language_value');
    $this->addFieldMapping('field_om_rating', 'field_om_rating_value');
  }
  // end omUserMigration class constructor

  // massage the user roles before saving
  // TODO: customize for DOM roles for D6 and D7
  public function prepareRow($current_row) {
    // If this project's user has not been migrated -- ignore this project.
    if (!empty($current_row->uid)) {
      $user = user_load($current_row->uid);
      if (empty($user)) {
        $current_row->uid = 13693;
      }
    }
    // Make sure this project actually has shows.
    if (!$this->check_for_shows($current_row->nid)) {
      return FALSE;
    }
    $current_row->field_om_project_type_nid = $this->legacy_node_lookup($current_row->field_om_project_type_nid);
    if (!empty($current_row->field_om_theme_nid)) {
      $theme_name = $this->legacy_node_lookup($current_row->field_om_theme_nid);
      if (!empty($theme_name)) {
        $current_row->field_om_theme_nid = $this->migration_lookup($theme_name);
      }
    }
    $current_row->field_om_language_value = $this->migration_lookup($current_row->field_om_language_value);
    return TRUE;
  }
  
  public function get_term_name($tid) {
    $query = Database::getConnection('default', 'legacy')->select('term_data','term');
    $query->fields('term', array('name'));
    $query->condition('tid', $old_tid, '=');
    $resource = $query->execute();
    $result = $resource->fetchAll();
    if (!empty($result)) {
      $result = array_shift($result);
      return $result->name;
    }
    return FALSE;
  }
  public function legacy_node_lookup($nid) {
    $query = Database::getConnection('default', 'legacy')->select('node','n');
    $query->fields('n', array('title'));
    $query->condition('nid', $nid, '=');
    $resource = $query->execute();
    $result = $resource->fetchAll();
    if (!empty($result)) {
      $result = array_shift($result);
      return $result->title;
    }
    return FALSE;
  }
  public function migration_lookup($term) {
    $botched_terms = array(
      'en' => "English",
      'eng' => "English",
      'sp' => "Spanish",
      'spa' => "Spanish",
      'ara' => "Arabic",
      'jpn' => "Japanese",
      'Music' => "Music & Entertainment",
      'African American' => 'Cultural Perspectives'
    );
    if (!empty($botched_terms[$term])) {
      return $botched_terms[$term];
    }
    else {
      return $term;
    }
  }
  public function check_for_shows($nid) {
    $query = Database::getConnection('default', 'legacy')->select('og_ancestry','og');
    $query->fields('og', array('nid'));
    $query->condition('group_nid', $nid, '=');
    $resource = $query->execute();
    $result = $resource->fetchAll();
    if (!empty($result)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
} // close the omUserMigration class