<?php
/**
 * @file
 * omp_class_registration.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function omp_class_registration_user_default_roles() {
  $roles = array();

  // Exported role: Class Admin.
  $roles['Class Admin'] = array(
    'name' => 'Class Admin',
    'weight' => '13',
  );

  // Exported role: Instructor.
  $roles['Instructor'] = array(
    'name' => 'Instructor',
    'weight' => '9',
  );

  // Exported role: Registrant.
  $roles['Registrant'] = array(
    'name' => 'Registrant',
    'weight' => '8',
  );

  return $roles;
}
