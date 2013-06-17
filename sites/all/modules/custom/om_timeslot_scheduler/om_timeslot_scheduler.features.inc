<?php
/**
 * @file
 * om_timeslot_scheduler.features.inc
 */

/**
 * Implements hook_views_api().
 */
function om_timeslot_scheduler_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function om_timeslot_scheduler_node_info() {
  $items = array(
    'om_timeslot_event' => array(
      'name' => t('OM Timeslot Event'),
      'base' => 'node_content',
      'description' => t('<b>Open Media System</b> - This content type represents a window of time to be scheduled into.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
