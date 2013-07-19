<?php

/**
 * hook_preprocess_HOOK
 */
function om_jwplayer_preprocess_om_show_share_bar(&$variables) {
  global $base_url;
  drupal_add_css(drupal_get_path('module', 'om_jwplayer') . '/theme/share_bar.css');
  if (module_exists('om_clickable_agenda')) {
    drupal_add_library('om_clickable_agenda', 'backbone');
    $options = array('type' => 'file', 'group' => JS_DEFAULT);
    drupal_add_js(drupal_get_path('module', 'om_jwplayer') . '/theme/share_bar.js');
    $variables['share_url'] = $base_url.'/node/' . arg(1) . '/share';
  }
  else {
    drupal_set_message('The om_clickable_agenda is disabled, but the share bar is still in use. Required libraries are missing.');
  }
}

/**
 * hook_preprocess_HOOK
 */
function om_jwplayer_preprocess_om_show_share_page(&$variables) {
  $css_path = '/' . drupal_get_path('module', 'om_jwplayer') . '/theme/share_page.css';
  $variables['styles'] = '<link type="text/css" rel="stylesheet" href="' . $css_path .'" media="all" />';
  $width = isset($_GET['width']) ? $_GET['width'] : '420';
  $height = isset($_GET['height']) ? $_GET['height'] : '340';
  om_show_jwplayer_include($variables['node'], TRUE, $width, $height);
  $variables['scripts'] = drupal_get_js($scope = 'header', $javascript = NULL, $skip_alter = FALSE);
}
