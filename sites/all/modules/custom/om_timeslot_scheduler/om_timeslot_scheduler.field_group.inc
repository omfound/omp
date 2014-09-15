<?php
/**
 * @file
 * om_timeslot_scheduler.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function om_timeslot_scheduler_field_group_info() {
  $export = array();

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic_info|node|om_timeslot_event|form';
  $field_group->group_name = 'group_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_timeslot_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Basic Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_om_timeslot_channel',
      1 => 'field_om_timeslot_theme',
      2 => 'field_om_timeslot_leader',
      3 => 'field_om_timeslot_trailer',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_basic_info|node|om_timeslot_event|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_scheduling_info|node|om_timeslot_event|form';
  $field_group->group_name = 'group_scheduling_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'om_timeslot_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Scheduling Info',
    'weight' => '3',
    'children' => array(
      0 => 'field_om_timeslot_rule',
      1 => 'field_om_timeslot_date',
      2 => 'field_om_timeslot_automation',
      3 => 'field_om_timeslot_producer',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_scheduling_info|node|om_timeslot_event|form'] = $field_group;

  return $export;
}
