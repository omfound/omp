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

function minim_preprocess_node (&$vars) {
  if(strpos($node->field_om_calendar[0]['url'], '/pub') !== false) { 
    $edit_view = str_replace('/pub', '/edit?rm=minimal', $node->field_om_calendar[0]['url']);
  }elseif(strpos($node->field_om_calendar[0]['url'], '/edit') !== false) {
    $edit_view = str_replace('/edit', '/edit?rm=minimal', $node->field_om_calendar[0]['url']);
  }else{
    $edit_view = $node->field_om_calendar;
  }
  $vars['edit_view'] = $edit_view;
  dsm($vars);
}
