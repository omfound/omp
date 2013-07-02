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
  $options = array();
  if ($user->uid > 0) {
    if (variable_get('om_loginout_link', TRUE)) {
      $options['attributes']['class'] = array('om-logout');
      $links[] = l('Logout', 'user/logout', $options);
    }
    if (variable_get('om_profile_link', TRUE)) {
      $options['attributes']['class'] = array('om-profile');
      $clean_name = strtolower(str_replace(' ', '-', $user->name));
      $links[] = l('Profile', 'users/' . $clean_name, $options);
    }
  }
  else {
    if (variable_get('om_loginout_link', TRUE)) {
      $options['attributes']['class'] = array('om-login');
      $links[] = l('Login', 'user', $options);
    }
    if (variable_get('om_register_link', TRUE)) {
      $options['attributes']['class'] = array('om-membership');
      $links[] = l('Register', 'membership', $options);
    }
  }
  if (variable_get('om_help_link', TRUE)) {
    $options['attributes']['class'] = array('om-help');
    $links[] = l('Help', 'help', $options);
  }
  if (variable_get('om_cart_link', TRUE)) {
    if (drupal_valid_path('cart')) {
      $options['attributes']['class'] = array('om-cart');
      $links[] = l('Shopping Cart', 'cart', $options);
    }
  }
  $last = count($links) - 1;
  foreach ($links as $key => $link) {
    if ($key != $last) {
      $links[$key] = $link.' | ';
    }
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
  $variables['main_nav_bar_background'] = variable_get('main_nav_bar_background', '');
  $variables['main_nav_color'] = variable_get('main_nav_color', '');
  $variables['main_nav_background'] = variable_get('main_nav_background', '');
  $variables['main_nav_color_hover'] = variable_get('main_nav_color_hover', '');
  $variables['main_nav_background_hover'] = variable_get('main_nav_background_hover', '');

  $variables['site_links_color'] = variable_get('site_link_color', '');

  $variables['main_nav_dropdown_color'] = variable_get('main_nav_dropdown_color', '');
  $variables['main_nav_dropdown_background'] = variable_get('main_nav_dropdown_background', '');
  $variables['main_nav_dropdown_color_hover'] = variable_get('main_nav_dropdown_color_hover', '');
  $variables['main_nav_dropdown_background_hover'] = variable_get('main_nav_dropdown_background_hover', '');

  $variables['header_shadow_color'] = variable_get('header_shadow_color', '');
  $variables['content_border_color'] = variable_get('content_border_color', '');

  $variables['om_dashboard_title_color'] = variable_get('om_dashboard_title_color', '');
  $variables['om_dashboard_pane_bg'] = variable_get('om_dashboard_pane_bg', '');
  $variables['om_dashboard_shadow_color'] = variable_get('om_dashboard_shadow_color', '');

  $texture_fid = variable_get('background_texture', '');
  if (is_numeric($texture_fid)) {
    $texture_file = file_load($texture_fid);
    if (is_object($texture_file)) {
      $stream_wrapper = file_stream_wrapper_get_instance_by_uri($texture_file->uri);
      $variables['background_texture'] =  $stream_wrapper->getExternalUrl();
    }
  }
  $front_hex_color = variable_get('front_content_background_color', '');
  if (!empty($front_hex_color)) {
    $variables['front_content_background_color'] = $front_hex_color;
  }

  $hex_color = variable_get('background_color', '');
  if (!empty($hex_color)) {
    $variables['background_color'] = om_theme_assets_hex_to_rgba($hex_color);
  }
  
  $variables['title_color'] = variable_get('title_color', '');
  
  $variables['info_tag_color'] = variable_get('info_tag_color', '');
}
