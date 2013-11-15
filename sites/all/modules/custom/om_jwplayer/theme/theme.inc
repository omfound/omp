<?php

/**
 * hook_preprocess_HOOK
 */
function om_jwplayer_preprocess_om_show_share_bar(&$variables) {
  global $base_url;
  drupal_add_css(drupal_get_path('module', 'om_jwplayer') . '/theme/share_bar.css');
  drupal_add_library('om_jwplayer', 'backbone');
  $options = array('type' => 'file', 'group' => JS_DEFAULT);
  drupal_add_js(drupal_get_path('module', 'om_jwplayer') . '/theme/share_bar.js');
  $variables['share_url'] = $base_url.'/node/' . arg(1) . '/share';
}

/**
 * hook_preprocess_HOOK
 */
function om_jwplayer_preprocess_om_show_share_page(&$variables) {
  $css_path = '/' . drupal_get_path('module', 'om_jwplayer') . '/theme/share_page.css';
  $variables['styles'] = '<link type="text/css" rel="stylesheet" href="' . $css_path .'" media="all" />';
  $width = isset($_GET['width']) ? $_GET['width'] : '420';
  $height = isset($_GET['height']) ? $_GET['height'] : '340';
  if (!empty($variables['node']->field_om_show_video[$variables['node']->language][0]['value'])) {
    $variables['video'] = om_show_render_video_url($variables['node']->field_om_show_video[$variables['node']->language][0]['value'], $width, $height, true);
  }
  $variables['scripts'] = drupal_get_js($scope = 'header', $javascript = NULL, $skip_alter = FALSE);
}
