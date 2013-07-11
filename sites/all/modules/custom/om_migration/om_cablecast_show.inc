<?php

class omCablecastShowMigration extends Migration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migrate Cablecast shows to Drupal.');
    $pbsid = variable_get('default_cablecast');
    if (empty($pbsid)) {
      throw new Exception('No default Cablecast has been set.');
    }
    $pbs = om_playback_servers_load($pbsid);
    $pbs = array_shift($pbs);
    if (!class_exists('MigrateSourceCablecast')) {
      require_once('/' . drupal_get_path('module', 'om_migration') . '/includes/cablecast.inc');
    }
    $this->source = new MigrateSourceCablecast(array(), $pbs, array());
    $this->destination = new MigrateDestinationNode('om_show'); 
    // map source and destination keys
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
    $this->addFieldMapping('body', 'ShowID'); 
  }
}
