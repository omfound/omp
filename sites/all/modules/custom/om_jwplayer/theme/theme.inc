<?php

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
