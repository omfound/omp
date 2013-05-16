<?php

/**
 * Implements hook_preprocess_HOOK
 */
function om_theme_assets_preprocess_om_round_social_media(&$variables) {
  $links = array();
  $options = array('attributes' => array('target' => '_blank'));
  $facebook_url = variable_get('facebook_url', FALSE);
  if (!empty($facebook_url)) {
    $options['attributes']['class'] = array('facebook');
    $links[] = l('Facebook', $facebook_url, $options);
  }
  $twitter_url = variable_get('twitter_url', FALSE);
  if (!empty($twitter_url)) {
    $options['attributes']['class'] = array('twitter');
    $links[] = l('Twitter', $twitter_url, $options);
  }
  $openmedia_network_url = 'http://omp.omfound.org';
  if (!empty($openmedia_network_url)) {
    $options['attributes']['class'] = array('om-network');
    $links[] = l('Open Media Network', $openmedia_network_url, $options);
  }
  $variables['links'] = $links;
}

/**
 * Implements hook_preprocess_HOOK
 */
function om_theme_assets_preprocess_om_site_links(&$variables) {
  global $user;
  $links = array();
  if ($user->uid > 0) {
    $links[] = l('Logout', 'user/logout') . ' | ';
    $clean_name = strtolower(str_replace(' ', '-', $user->name));
    $links[] = l('Profile', 'users/' . $clean_name) . ' | ';
  }
  else {
    $links[] = l('Login', 'user') . ' | ';
    $links[] = l('Register', 'membership') . ' | ';
  }
  $links[] = l('Help', 'help');
  if (drupal_valid_path('cart')) {
    $links[] = ' | '.l('Shopping Cart', 'cart');
  }
  $variables['links'] = $links;
}

/**
 * Implements hook_preprocess_HOOK
 */
function om_theme_assets_preprocess_om_callout_block(&$variables) {
  if (!empty($variables['block_info'])) {
     $variables['block_title'] = '<h3>' . l($variables['block_info']['block_title'], $variables['block_info']['url']) . '</h3>';
     $options = array('html' => TRUE);
     $variables['block_image'] = l('<img src="' . $variables['block_info']['image_path'] . '" />', $variables['block_info']['url'], $options);
  }
}

/**
 * Implements hook_preprocess_HOOK
 */
function om_theme_assets_preprocess_om_theme_dynamic_css(&$variables) {
  $variables['main_nav_background'] = variable_get('main_nav_background', '');
  $variables['main_nav_color'] = variable_get('main_nav_color', '');
  $variables['main_nav_color_hover'] = variable_get('main_nav_color_hover', '');
  $variables['main_nav_background_hover'] = variable_get('main_nav_background_hover', '');

  $variables['main_nav_dropdown_color'] = variable_get('main_nav_dropdown_color', '');
  $variables['main_nav_dropdown_background'] = variable_get('main_nav_dropdown_background', '');
  $variables['main_nav_dropdown_color_hover'] = variable_get('main_nav_dropdown_color_hover', '');
  $variables['main_nav_dropdown_background_hover'] = variable_get('main_nav_dropdown_background_hover', '');

  $texture_fid = variable_get('background_texture', '');
  if (is_numeric($texture_fid)) {
    $texture_file = file_load($texture_fid);
    if (is_object($texture_file)) {
      $stream_wrapper = file_stream_wrapper_get_instance_by_uri($texture_file->uri);
      $variables['background_texture'] = $stream_wrapper->getExternalUrl();
    }
  }
  $hex_color = variable_get('background_color', '');
  if (!empty($hex_color)) {
    $variables['background_color'] = om_theme_assets_hex_to_rgba($hex_color);
  }
  
  $variables['title_color'] = variable_get('title_color', '');
  
  $variables['info_tag_background'] = variable_get('info_tag_background', '');
}