<?php

function om_migration_drush_command() {
  $items = array();
  $items['migrate-member-orders'] = array(
    'description' => "Migrate memberships from DOM civi DB to commerce orders",
    'aliases'     => array('ommo'),
    'bootstrap'   => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'drupal dependencies'  => array('om_migration'),
  );
  return $items;
}

function drush_om_migration_migrate_member_orders() {
  $arr = om_migration_civi_product_relationships();
  foreach ($arr as $k => $v) {
    drush_print("here's $k => $v\n");
  }
}
