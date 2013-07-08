<?php

/**
 * hook_preprocess_HOOK
 */
function om_jwplayer_preprocess_om_show_share_bar(&$variables) {
  drupal_add_css(drupal_get_path('module', 'om_jwplayer') . '/theme/share_bar.css');
  if (module_exists('om_clickable_agenda')) {
    drupal_add_library('om_clickable_agenda', 'backbone');
    $options = array('type' => 'file', 'group' => JS_DEFAULT);
    drupal_add_js(drupal_get_path('module', 'om_jwplayer') . '/theme/share_bar.js');
  }
  else {
    drupal_set_message('The om_clickable_agenda is disabled, but the share bar is still in use. Required libraries are missing.');
  }
}

/**
 * hook_preprocess_HOOK
 */
function om_jwplayer_preprocess_om_show_share_page(&$variables) {
  $css_path = drupal_get_path('module', 'om_jwplayer') . '/theme/share_page.css';
  $variables['styles'] = '<link type="text/css" rel="stylesheet" href="' . $css_path .'" media="all" />';
  drupal_add_js('sites/all/libraries/jwplayer/jwplayer.js', array('type' => 'file', 'group' => JS_LIBRARY));
  drupal_add_js(drupal_get_path('module', 'om_jwplayer') . '/theme/share_page.js', array('type' => 'file', 'group' => JS_DEFAULT));
  $params = array();
  $params['width'] = isset($_GET['width']) ? $_GET['width'] : '420';
  $params['height'] = isset($_GET['height']) ? $_GET['height'] : '340';
  $params['embedInPoint'] = isset($_GET['embedInPoint']) ? $_GET['embedInPoint'] : FALSE;
  $params['embedOutPoint'] = isset($_GET['embedOutPoint']) ? $_GET['embedOutPoint'] : FALSE;
  $params = array('om_jwplayer' => $params);
  drupal_add_js($params, array('type' => 'setting'));
  $variables['scripts'] = drupal_get_js($scope = 'header', $javascript = NULL, $skip_alter = FALSE);
}
