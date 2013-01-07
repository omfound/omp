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
  $openmedia_network_url = 'http://google.com';
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
    $links[] = l('Profile', 'users/' . $user->name) . ' | ';
  }
  else {
    $links[] = l('Login', 'user') . ' | ';
    $links[] = l('Register', 'user/register') . ' | ';
  }
  $links[] = l('Help', 'help');
  $variables['links'] = $links;
}

function om_theme_assets_preprocess_om_callout_block(&$variables) {
  if (!empty($variables['block_info'])) {
     $variables['block_title'] = '<h3>' . l($variables['block_info']['block_title'], $variables['block_info']['url']) . '</h3>';
     $options = array('html' => TRUE);
     $variables['block_image'] = l('<img src="' . $variables['block_info']['image_path'] . '" />', $variables['block_info']['url'], $options);
  }
}