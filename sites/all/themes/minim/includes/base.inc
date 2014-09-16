<?php
/**
 * Preprocess and Helper Functions for core
 **/

/**
 * Implements hook_preprocess_hook
 */
function minim_preprocess_html(&$variables) {
  // Suggest seperate header and footer script variables in addition to scripts if needed.
  $variables['header_scripts'] = drupal_get_js('header');
  $variables['footer_scripts'] = drupal_get_js('footer');
}

/**
 * Implements hook_preprocess_block
 * 
 * Adds granular preprocess functions for blocks based on instance and plugin id
 * Plugin ID Example: minim_preprocess_block__pluginid
 * Instance Example: minim_preprocess_block_instance__instanceid
 *
 * @see minim/processors/blocks.inc
 */
function minim_preprocess_block(&$vars) {
  dsm($vars);
  //$sane_plugin_id = str_replace(':', '__', $vars['plugin_id']);
  //$sane_plugin_id = str_replace('-', '_', $sane_plugin_id);
  //$sub_functions = array();
  //$sub_functions[] = __FUNCTION__ . '__' . $sane_plugin_id;
  //$sub_functions[] = __FUNCTION__ . '_' . 'instance' . '__' . $vars['elements']['#contextual_links']['block']['route_parameters']['block'];

  //foreach ($sub_functions AS $function) {
    //if (function_exists($function)) {
      //$function($vars);
    //}
  //}
}
