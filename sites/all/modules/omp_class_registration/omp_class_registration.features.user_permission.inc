<?php
/**
 * @file
 * omp_class_registration.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function omp_class_registration_user_default_permissions() {
  $permissions = array();

  // Exported permission: view any commerce_product entity of bundle omp_class_session.
  $permissions['view any commerce_product entity of bundle omp_class_session'] = array(
    'name' => 'view any commerce_product entity of bundle omp_class_session',
    'roles' => array(
      0 => 'Class Admin',
      1 => 'Instructor',
      2 => 'Station Director',
      3 => 'administrator',
      4 => 'anonymous user',
      5 => 'authenticated user',
    ),
    'module' => 'commerce_product',
  );

  return $permissions;
}
