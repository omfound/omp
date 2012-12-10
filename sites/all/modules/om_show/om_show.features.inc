<?php
/**
 * @file
 * om_show.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function om_show_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function om_show_node_info() {
  $items = array(
    'om_show' => array(
      'name' => t('OM Show'),
      'base' => 'node_content',
      'description' => t('<b>Open Media System</b> - This content type where the shows metadata is stored.  The actual videos for a show are managed by the Media Mover module.'),
      'has_title' => '1',
      'title_label' => t('Show Title'),
      'help' => '',
    ),
  );
  return $items;
}
