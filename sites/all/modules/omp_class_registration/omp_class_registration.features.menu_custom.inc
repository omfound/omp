<?php
/**
 * @file
 * omp_class_registration.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function omp_class_registration_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-class-admin.
  $menus['menu-class-admin'] = array(
    'menu_name' => 'menu-class-admin',
    'title' => 'Class admin',
    'description' => '',
  );
  // Exported menu: menu-instructor-menu.
  $menus['menu-instructor-menu'] = array(
    'menu_name' => 'menu-instructor-menu',
    'title' => 'Instructor menu',
    'description' => '',
  );
  // Exported menu: user-menu.
  $menus['user-menu'] = array(
    'menu_name' => 'user-menu',
    'title' => 'User menu',
    'description' => 'The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Class admin');
  t('Instructor menu');
  t('The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');
  t('User menu');


  return $menus;
}
