<?php
/**
 * @file
 * om_project.features.inc
 */

/**
 * Implements hook_node_info().
 */
function om_project_node_info() {
  $items = array(
    'om_project' => array(
      'name' => t('OM Project'),
      'base' => 'node_content',
      'description' => t('<strong>Open Media System</strong> - This content type is used to group a collection of shows as a series and manage permissions.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
