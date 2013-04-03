<?php

/**
 * Implements hook_drush_help()
 */
function om_migration_drush_help($command) {
  switch ($command) {
    case 'drush:dom-migration-extras':
      return dt('Run extra conversions and field changes needed for the dom migration');
  }
}

/**
 * Implements hook_drush_command()
 */
function om_migration_drush_command() {
  $items = array();
  $items['dom-migration-extras'] = array(
    'description' => dt('Run updates.'),
    'aliases' => array('dme'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN
  );
  return $items;
}

/**
 * Implements drush_hook_command()
 */
function drush_om_migration_dom_migration_extras() {
  drush_log('Running dom content updates.', 'success');
/*
  om_migration_update_cablecast_files();
  drush_log('Updated Cablecast legacy show ids to Cablecast URIs.', 'success');
  om_migration_update_geofield();
  drush_log('Updated geofields.', 'success');
  om_migration_update_voting();
  drush_log('Updated voting.', 'success');
*/
}