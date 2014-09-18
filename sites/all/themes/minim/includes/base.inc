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
  dsm($vars);
  if(strpos($vars['field_om_calendar'][0]['url'], '/pub') !== false) { 
    $edit_view = str_replace('/pub', '/edit?rm=minimal', $vars['field_om_calendar'][0]['url']);
  }elseif(strpos($vars['field_om_calendar'][0]['url'], '/edit') !== false) {
    $edit_view = str_replace('/edit', '/edit?rm=minimal', $vars['field_om_calendar'][0]['url']);
  }else{
    $edit_view = $vars['field_om_calendar'][0]['url'];
  }
  $vars['edit_view'] = $edit_view;
}

dsm('DOES THIS FUNCTION LOAD');
function minim_preprocess_field(&$variables) {
  dsm('HELLO');
  dsm($variables);
  // Allow preprocessing for fields
  $function = __FUNCTION__ . '__' . $variables['element']['#field_name'];
  dsm($function);
  if (function_exists($function)) {
    $function($variables);
  }
}
