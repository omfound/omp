<?php
/**
 * @file
 * om_project.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function om_project_user_default_roles() {
  $roles = array();

  // Exported role: series producer.
  $roles['series producer'] = array(
    'name' => 'series producer',
    'weight' => '3',
  );

  return $roles;
}
