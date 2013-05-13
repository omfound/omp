<?php 

function om_theme_assets_admin_form() {
  /**
   * Main banner
   */
  $form['main_banner_header'] = array(
    '#prefix' => '<h2>',
    '#markup' => t('Main Banner Image'),
    '#suffix' => '</h2>'
  );
  $form['main_banner_help'] = array(
    '#markup' => t('The site\'s main banner image, which links back to the home page. It should be 980px by 200px')
  );
  $form['theme_banner'] = array(
    '#title' => t('Main Banner'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('theme_banner', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['main_banner_divider'] = array(
    '#markup' => '<div class="divider"><div class="inner"></div></div>'
  );
  /**
   * Calls to action
   */
  $form['call_to_action_header'] = array(
    '#prefix' => '<h2>',
    '#markup' => t('Call to Action Images'),
    '#suffix' => '</h2>'
  );
  $form['call_to_action_help'] = array(
    '#markup' => t('Call to action images are the three large images on the front page. These images should drive your users to important pages on your site. Each image upload below is paired with a url. They should be as close as possible to 300px by 190px.')
  );
  $form['call_to_action_1'] = array(
    '#title' => t('Call to Action 1'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('call_to_action_1', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['call_to_action_url_1'] = array(
    '#title' => t('Call to Action URL 1'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_url_1', ''),
  );
  $form['call_to_action_2'] = array(
    '#title' => t('Call to Action 2'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('call_to_action_2', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['call_to_action_url_2'] = array(
    '#title' => t('Call to Action URL 2'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_url_2', ''),
  );
  $form['call_to_action_3'] = array(
    '#title' => t('Call to Action 3'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('call_to_action_3', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['call_to_action_url_3'] = array(
    '#title' => t('Call to Action URL 3'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_url_3', ''),
  );
  $form['main_banner_divider'] = array(
    '#markup' => '<div class="divider"><div class="inner"></div></div>'
  );
  return system_settings_form($form);
}