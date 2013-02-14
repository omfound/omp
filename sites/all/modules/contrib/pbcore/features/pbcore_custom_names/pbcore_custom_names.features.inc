<?php
/**
 * @file
 * pbcore_custom_names.features.inc
 */

/**
 * Implements hook_views_api().
 */
function pbcore_custom_names_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}
