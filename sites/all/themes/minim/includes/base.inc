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
  $sub_functions = array();
  $block_id = $vars['block']->module . '_' . $vars['block']->delta;
  $sub_functions[] = __FUNCTION__ . '__' . $block_id;

  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($vars);
    }
  }
}

function minim_preprocess_om_show_live_block (&$vars) {
  foreach ($vars['buttons'] as $key => $button) {
    $vars['buttons'][$key] = str_replace('om-live-button-content', 'pure-button', $button);
  }
}
