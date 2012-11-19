<?php
/**
 * @file
 * omp_class_registration.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function omp_class_registration_commerce_product_default_types() {
  $items = array(
    'omp_class_session' => array(
      'type' => 'omp_class_session',
      'name' => 'Class Session',
      'description' => 'Represents exact class held during some period of time, for example set of lessons teaching “Light Production” that take place in March 2012 (either single day, or repeating classes). This is what is actually sold to students when they register for class.',
      'help' => '',
      'revision' => '1',
      'module' => 'commerce_product_ui',
    ),
  );
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function omp_class_registration_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function omp_class_registration_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function omp_class_registration_node_info() {
  $items = array(
    'omp_class_display' => array(
      'name' => t('Class Display'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'webform' => array(
      'name' => t('Webform'),
      'base' => 'node_content',
      'description' => t('Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_registration_type().
 */
function omp_class_registration_default_registration_type() {
  $items = array();
  $items['om_class_registration'] = entity_import('registration_type', '{
    "name" : "om_class_registration",
    "label" : "OM Class Registration",
    "locked" : "0",
    "weight" : "0",
    "data" : null,
    "rdf_mapping" : []
  }');
  return $items;
}
