<?php
/**
 * @file
 * om_project.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function om_project_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_project_basic_info|node|om_project|form';
  $field_group->group_name = 'group_om_project_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Basic Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_om_project_logo',
      1 => 'field_om_project_contact',
      2 => 'field_om_project_credits',
      3 => 'field_om_project_type',
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
  $export['group_om_project_basic_info|node|om_project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_project_contact|node|om_project|form';
  $field_group->group_name = 'group_om_project_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Project Contact and Credits',
    'weight' => '3',
    'children' => array(
      0 => 'field_om_project_contact',
      1 => 'field_om_project_company',
      2 => 'field_om_project_credits',
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
  $export['group_om_project_contact|node|om_project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_project_licensing|node|om_project|form';
  $field_group->group_name = 'group_om_project_licensing';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Project Licensing',
    'weight' => '12',
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
  $export['group_om_project_licensing|node|om_project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_project_metadata|node|om_project|form';
  $field_group->group_name = 'group_om_project_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '3',
    'children' => array(
      0 => 'field_om_locally_produced',
      1 => 'field_om_theme',
      2 => 'field_om_rating',
      3 => 'field_om_language',
      4 => 'field_om_genre',
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
  $export['group_om_project_metadata|node|om_project|form'] = $field_group;

  return $export;
}
