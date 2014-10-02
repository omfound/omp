<?php
// User Migration class
class omShowMigration extends Migration {
  // class constructor
  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('om_projects_group'));
    $this->description = t('Migrate Drupal 6 projects cck nodes');
    $query = Database::getConnection('default', 'legacy')->select('node','n');
    $query->join('node_revisions', 'r', 'n.nid=r.nid');
    $query->leftJoin('content_type_om_show', 'cts', 'n.nid=cts.nid');
    $query->leftJoin('content_field_om_locally_produced', 'locally_produced', 'n.nid=locally_produced.nid');
    $query->leftJoin('content_field_om_theme', 'theme', 'n.nid=theme.nid');
    $query->leftJoin('content_field_om_genre', 'genre', 'n.nid=genre.nid');
    $query->leftJoin('content_field_om_language', 'language', 'n.nid=language.nid');
    $query->leftJoin('content_field_om_rating', 'rating', 'n.nid=rating.nid');
    $query->leftJoin('location_instance', 'loc_in', 'n.nid=loc_in.nid');
    $query->leftJoin('location', 'loc', 'loc_in.lid=loc.lid');
    $query->leftJoin('internet_archive', 'ia', 'n.nid=ia.nid');
    $query->fields('n', array('nid', 'title', 'uid', 'status', 'created', 'created', 'changed'));
    $query->fields('r', array('body'));
    $query->fields('cts', array('field_om_show_tightrope_id_value', 'field_om_show_original_list', 'field_om_show_capture_fid', 'field_om_show_episode_number_value', 'field_om_show_season_value', 'field_om_show_duration_value'));
    $query->fields('locally_produced', array('field_om_locally_produced_value'));
    $query->fields('theme', array('field_om_theme_nid'));
    $query->fields('genre', array('field_om_genre_value'));
    $query->fields('language', array('field_om_language_value'));
    $query->fields('rating', array('field_om_rating_value'));
    $query->fields('loc', array('latitude', 'longitude'));
    $query->fields('ia', array('item', 'filename', 'derivatives'));
    $query->condition('n.type', 'om_show', '=');
    $this->source = new MigrateSourceSQL($query, array(), null, array('map_joinable' => FALSE));
    // No need to force users to reset their passwords
    $this->destination = new MigrateDestinationNode('om_show');

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
    $this->addFieldMapping('field_old_show_id', 'nid');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_om_locally_produced', 'field_om_locally_produced_value');
    $this->addFieldMapping('field_om_theme', 'field_om_theme_nid');
    $this->addFieldMapping('field_om_genre', 'field_om_genre_value');
    $this->addFieldMapping('field_om_language', 'field_om_language_value');
    $this->addFieldMapping('field_om_rating', 'field_om_rating_value');
    $this->addFieldMapping('field_om_show_playback_server_id', 'field_om_show_tightrope_id_value');
    $this->addFieldMapping('field_om_show_project', 'field_om_show_original_list');
    $this->addFieldMapping('field_show_thumbnail', 'field_om_show_capture_fid');
    $this->addFieldMapping('field_om_show_episode_number', 'field_om_show_episode_number_value');
    $this->addFieldMapping('field_om_show_season', 'field_om_show_season_value');
    $this->addFieldMapping('field_om_show_duration', 'field_om_show_duration_value');
    $this->addFieldMapping('field_om_show_video', 'item');
    $this->addFieldMapping('field_old_lat', 'latitude');
    $this->addFieldMapping('field_old_lon', 'longitude');
  }

  public function prepareRow($current_row) {
    // If this project's user has not been migrated -- ignore this project.
    if (!empty($current_row->uid)) {
      $user = user_load($current_row->uid);
      if (empty($user)) {
        $current_row->uid = 13693;
      }
    }
    // Make sure this project actually has shows.
    if (!empty($current_row->field_om_theme_nid)) {
      $theme_name = $this->legacy_node_lookup($current_row->field_om_theme_nid);
      if (!empty($theme_name)) {
        $current_row->field_om_theme_nid = $this->migration_lookup($theme_name);
      }
    }
    $current_row->field_om_language_value = $this->migration_lookup($current_row->field_om_language_value);
    
    $project_nid = $this->get_projects($current_row->nid);
    if (!empty($project_nid) && is_numeric($project_nid) && $project_nid != 1) {
      $current_row->field_om_show_original_list = $project_nid;
    }
    else {
      $current_row->field_om_show_original_list = 19171;
    }
    $file = $this->lookup_file($current_row->field_om_show_capture_fid);
    if (!empty($file)) {
      $current_row->field_om_show_capture_fid = $file;
    }
    if (!empty($current_row->item)) {
      $derivatives = unserialize($current_row->derivatives);
      if (!empty($derivatives) && is_array($derivatives)) {
        foreach ($derivatives AS $key => $derivative) {
          if (is_numeric(stripos($key, 'mp4'))) {
            $current_row->item = 'http://www.archive.org/download/' . $current_row->item . '/' . $derivative['name'];
          }
        }
      }
    }
    //print_r($current_row);
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

  public function get_projects($nid) {
    $query = Database::getConnection('default', 'legacy')->select('og_ancestry','og');
    $query->fields('og', array('group_nid'));
    $query->condition('nid', $nid, '=');
    $resource = $query->execute();
    $result = $resource->fetchAll();
    if (!empty($result)) {
      $nid = array_shift($result);
      $nid = $nid->group_nid;
      $query = Database::getConnection('default', 'default')->select('field_data_field_old_project_id','op');
      $query->fields('op', array('entity_id'));
      $query->condition('field_old_project_id_value', $nid, '=');
      $resource = $query->execute();
      $result = $resource->fetchAll();
      if (!empty($result)) {
        $project_nid = array_shift($result);
        $project_nid = $project_nid->entity_id;
        return $project_nid;
      }
    }
    return FALSE;
  }

  public function lookup_file($fid) {
    $query = Database::getConnection('default', 'legacy')->select('files','f');
    $query->fields('f', array('filepath'));
    $query->condition('fid', $fid, '=');
    $resource = $query->execute();
    $result = $resource->fetchAll();
    if (!empty($result)) {
      $file = array_shift($result);
      $file = 'http://denveropenmedia.org/' . $file->filepath;
      if (file_exists($file)) {
        return $file;
      }
    }
    return FALSE;
  }
} // close the omUserMigration class
