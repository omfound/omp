<?php
/**
 * @file
 * om_broadcast_schedule.features.inc
 */

/**
 * Implements hook_node_info().
 */
function om_broadcast_schedule_node_info() {
  $items = array(
    'om_airing' => array(
      'name' => t('OM Airing'),
      'base' => 'node_content',
      'description' => t('<b>Open Media System</b> - This content type represents a scheduled airing on a channel.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
