<?php
/**
 * @file
 * omp_class_registration.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function omp_class_registration_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-class-admin:admin/commerce/products/add/omp-class-session
  $menu_links['menu-class-admin:admin/commerce/products/add/omp-class-session'] = array(
    'menu_name' => 'menu-class-admin',
    'link_path' => 'admin/commerce/products/add/omp-class-session',
    'router_path' => 'admin/commerce/products/add/omp-class-session',
    'link_title' => 'Add Class Session',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: menu-class-admin:admin/content/webform
  $menu_links['menu-class-admin:admin/content/webform'] = array(
    'menu_name' => 'menu-class-admin',
    'link_path' => 'admin/content/webform',
    'router_path' => 'admin/content/webform',
    'link_title' => 'Class Evaluations',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-44',
  );
  // Exported menu link: menu-class-admin:admin/structure/taxonomy/omp_certifications/add
  $menu_links['menu-class-admin:admin/structure/taxonomy/omp_certifications/add'] = array(
    'menu_name' => 'menu-class-admin',
    'link_path' => 'admin/structure/taxonomy/omp_certifications/add',
    'router_path' => 'admin/structure/taxonomy/%/add',
    'link_title' => 'Add Certification',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: menu-class-admin:admin/structure/taxonomy/omp_subjects/add
  $menu_links['menu-class-admin:admin/structure/taxonomy/omp_subjects/add'] = array(
    'menu_name' => 'menu-class-admin',
    'link_path' => 'admin/structure/taxonomy/omp_subjects/add',
    'router_path' => 'admin/structure/taxonomy/%/add',
    'link_title' => 'Add Subject',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Exported menu link: menu-class-admin:node/add/omp-class-display
  $menu_links['menu-class-admin:node/add/omp-class-display'] = array(
    'menu_name' => 'menu-class-admin',
    'link_path' => 'node/add/omp-class-display',
    'router_path' => 'node/add/omp-class-display',
    'link_title' => 'Add Class Display',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-class-admin:om-saved-classes-calendar
  $menu_links['menu-class-admin:om-saved-classes-calendar'] = array(
    'menu_name' => 'menu-class-admin',
    'link_path' => 'om-saved-classes-calendar',
    'router_path' => 'om-saved-classes-calendar',
    'link_title' => 'Create new class session like existing one',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-43',
  );
  // Exported menu link: user-menu:user/logout
  $menu_links['user-menu:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '10',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add Certification');
  t('Add Class Display');
  t('Add Class Session');
  t('Add Subject');
  t('Class Evaluations');
  t('Create new class session like existing one');
  t('Log out');


  return $menu_links;
}
