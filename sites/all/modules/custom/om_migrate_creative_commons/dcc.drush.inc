<?php

function dcc_drush_command() {
  $items = array();

  $items['dom-creative-commons'] = array(
    'description' => "Migrate Drupal 6 creative commons info.",
    'aliases' => array('dcc'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );

  return $items;
}

function drush_dcc_dom_creative_commons() {
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
