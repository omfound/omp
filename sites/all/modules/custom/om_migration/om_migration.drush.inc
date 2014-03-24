<?php

/**
 * Implements hook_drush_help()
 */
function om_migration_drush_help($command) {
  switch ($command) {
    case 'drush:dom-migration-files':
      return dt('Convert legacy Cablecast Ids to cablecast uri (cablecast://show-id)');
    case 'drush:dom-migration-geo-fields':
      return dt('Move lat/lon pairs from legacy location table to geofield table.');
    case 'drush:dom-migration-voting':
      return dt('Move Voting api data from legacy table to new table.');
    case 'drush:dom-migration-creative-commons':
      return dt('Move Creative Commons data from legacy table to new table.');
  }
}

/**
 * Implements hook_drush_command()
 */
function om_migration_drush_command() {
  $items = array();
  $items['dom-migration-files'] = array(
    'description' => dt('Run Cablecast id updates.'),
    'aliases' => array('dmf'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN
  );
  $items['dom-migration-geo-fields'] = array(
    'description' => dt('Run geofield updates.'),
    'aliases' => array('dmgf'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN
  );
  $items['dom-migration-voting'] = array(
    'description' => dt('Run voting table updates.'),
    'aliases' => array('dmv'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN
  );
  $items['dom-creative-commons'] = array(
    'description' => dt('Run Creative Commons updates'),
    'aliases' => array('dcc'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
  );
  return $items;
}

/**
 * Implements drush_hook_command()
 */
function drush_om_migration_dom_migration_files() {
  drush_log('Running DOM file update.', 'success');
  om_migration_update_cablecast_files();
  drush_log('Updated Cablecast legacy show ids to Cablecast URIs.', 'success');
}

function drush_om_migration_dom_migration_geo_fields() {
  drush_log('Updated geofields.', 'success');
  om_migration_update_geofield();
  drush_log('Geofields migrated from legacy data.', 'success');
}

function drush_om_migration_dom_migration_voting() {
  drush_log('Updated voting data.', 'success');
  om_migration_update_voting();
  drush_log('Voting table updated with legacy data.', 'success');
}

function drush_om_migration_dom_creative_commons() {
  $start = drush_get_option('start');
  if (empty($start)) {
    drush_log('Start option required --start', 'error');
    return;
  }
  $batch_size = drush_get_option('batch_size');
  if (empty($batch_size)) {
    drush_log('Batch Size option required --batch_size', 'error');
    return;
  }
  om_migration_creative_commons_migration($start, $batch_size);
  drush_log('Creative commons migration complete.', 'success');
}
