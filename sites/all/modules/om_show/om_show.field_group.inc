<?php
/**
 * @file
 * om_show.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function om_show_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_sed|node|om_show|form';
  $field_group->group_name = 'group_om_sed';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_show';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_om_show_basic_info';
  $field_group->data = array(
    'label' => 'SED',
    'weight' => '8',
    'children' => array(
      0 => 'field_om_show_duration',
      1 => 'field_om_show_episode_number',
      2 => 'field_om_show_season',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'SED',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_om_sed|node|om_show|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_show_basic_info|node|om_show|form';
  $field_group->group_name = 'group_om_show_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_show';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Show Details',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_om_locally_produced',
      2 => 'field_om_show_project',
      3 => 'field_title',
      4 => 'field_om_show_aired',
      5 => 'field_om_show_branding',
      6 => 'title',
      7 => 'group_om_sed',
      8 => 'group_om_vb',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Show Details',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_om_show_basic_info|node|om_show|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_show_contact|node|om_show|form';
  $field_group->group_name = 'group_om_show_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_show';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Show Contact and Credits',
    'weight' => '4',
    'children' => array(
      0 => 'field_om_show_credits',
      1 => 'field_om_project_contact',
      2 => 'field_om_project_company',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_show_contact|node|om_show|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_show_licensing|node|om_show|form';
  $field_group->group_name = 'group_om_show_licensing';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_show';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Show Licensing',
    'weight' => '5',
    'children' => array(
      0 => 'field_license',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_show_licensing|node|om_show|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_show_location|node|om_show|form';
  $field_group->group_name = 'group_om_show_location';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_show';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Location',
    'weight' => '6',
    'children' => array(
      0 => 'field_om_show_address',
      1 => 'field_om_show_geofield',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_show_location|node|om_show|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_show_media|node|om_show|form';
  $field_group->group_name = 'group_om_show_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_show';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '9',
    'children' => array(
      0 => 'field_om_show_duration',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_show_media|node|om_show|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_show_metadata|node|om_show|form';
  $field_group->group_name = 'group_om_show_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_show';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Show Metadata',
    'weight' => '3',
    'children' => array(
      0 => 'field_om_genre',
      1 => 'field_om_language',
      2 => 'field_om_rating',
      3 => 'field_om_theme',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_show_metadata|node|om_show|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_vb|node|om_show|form';
  $field_group->group_name = 'group_om_vb';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_show';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_om_show_basic_info';
  $field_group->data = array(
    'label' => 'VB',
    'weight' => '9',
    'children' => array(
      0 => 'field_om_show_broadcast_file',
      1 => 'field_om_show_original',
      2 => 'field_show_thumbnail',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'VB',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_om_vb|node|om_show|form'] = $field_group;

  return $export;
}
