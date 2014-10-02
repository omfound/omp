<?php 

function om_theme_assets_admin_form() {
  om_theme_assets_build_dynamic_css();
  /**
   * Fieldset factory
   */
  $fieldset = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );
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
  $form['main_banner_fieldset'] = $fieldset;
  $form['main_banner_fieldset']['#title'] = t('Main Banner Image');
  $form['main_banner_fieldset']['theme_banner'] = array(
    '#title' => t('Main Banner'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('theme_banner', ''),
    '#upload_location' => 'public://theme_assets/',
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
    '#markup' => t('Call to action images are the three large images on the front page. These images should drive your users to important pages on your site. Each image upload below is paired with a title and url. Title should be a short phrase to go with the call to action. Url should be a valid internal Drupal path like node/471 or about-us. They should be as close as possible to 300px by 190px.')
  );
  $form['call_to_action_fieldset'] = $fieldset;
  $form['call_to_action_fieldset']['#title'] = t('Call to Action Images');
  $form['call_to_action_fieldset']['call_to_action_1'] = array(
    '#title' => t('Call to Action 1'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('call_to_action_1', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['call_to_action_fieldset']['call_to_action_title_1'] = array(
    '#title' => t('Call to Action Title 1'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_title_1', ''),
  );
  $form['call_to_action_fieldset']['call_to_action_url_1'] = array(
    '#title' => t('Call to Action URL 1'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_url_1', ''),
    '#element_validate' => array('_om_theme_assets_url_validate'),
  );
  $form['call_to_action_fieldset']['call_to_action_2'] = array(
    '#title' => t('Call to Action 2'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('call_to_action_2', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['call_to_action_fieldset']['call_to_action_title_2'] = array(
    '#title' => t('Call to Action Title 2'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_title_2', ''),
  );
  $form['call_to_action_fieldset']['call_to_action_url_2'] = array(
    '#title' => t('Call to Action URL 2'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_url_2', ''),
    '#element_validate' => array('_om_theme_assets_url_validate'),
  );
  $form['call_to_action_fieldset']['call_to_action_3'] = array(
    '#title' => t('Call to Action 3'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('call_to_action_3', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['call_to_action_fieldset']['call_to_action_title_3'] = array(
    '#title' => t('Call to Action Title 3'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_title_3', ''),
  );
  $form['call_to_action_fieldset']['call_to_action_url_3'] = array(
    '#title' => t('Call to Action URL 3'),
    '#type' => 'textfield',
    '#default_value' => variable_get('call_to_action_url_3', ''),
    '#element_validate' => array('_om_theme_assets_url_validate'),
  );
  /**
   * Info Tags
   */
  $form['info_tags_header'] = array(
    '#prefix' => '<h2>',
    '#markup' => t('Info Tags'),
    '#suffix' => '</h2>'
  );
  $form['info_tags_help'] = array(
    '#markup' => t('Info tags are shorter smaller calls to actions that appear on every page. They should be very concise and to the point. Each info tag is grouped into a highlight, label, link and url. The highlight must be extremely short 1-3 characters like a channel number or "GO". The label is the bold text that appears right of the highlight. The link is the text for the link that goes below the label. The url should be a valid path where the item sends users.')
  );
  $form['info_tags_fieldset'] = $fieldset;
  $form['info_tags_fieldset']['#title'] = t('Info Tags');
  $form['info_tags_fieldset']['info_tags_highlight_1'] = array(
    '#title' => t('Info Tag Highlight 1'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_highlight_1', ''),
  );
  $form['info_tags_fieldset']['info_tags_label_1'] = array(
    '#title' => t('Info Tag Label 1'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_label_1', ''),
  );
  $form['info_tags_fieldset']['info_tags_link_1'] = array(
    '#title' => t('Info Tag Link Text 1'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_link_1', ''),
  );
  $form['info_tags_fieldset']['info_tags_url_1'] = array(
    '#title' => t('Info Tag URL 1'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_url_1', ''),
  );
  $form['info_tags_fieldset']['info_tags_highlight_2'] = array(
    '#title' => t('Info Tag Highlight 2'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_highlight_2', ''),
  );
  $form['info_tags_fieldset']['info_tags_label_2'] = array(
    '#title' => t('Info Tag Label 2'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_label_2', ''),
  );
  $form['info_tags_fieldset']['info_tags_link_2'] = array(
    '#title' => t('Info Tag Link Text 2'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_link_2', ''),
  );
  $form['info_tags_fieldset']['info_tags_url_2'] = array(
    '#title' => t('Info Tag URL 2'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_url_2', ''),
  );
  $form['info_tags_fieldset']['info_tags_highlight_3'] = array(
    '#title' => t('Info Tag Highlight 3'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_highlight_3', ''),
  );
  $form['info_tags_fieldset']['info_tags_label_3'] = array(
    '#title' => t('Info Tag Label 3'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_label_3', ''),
  );
  $form['info_tags_fieldset']['info_tags_link_3'] = array(
    '#title' => t('Info Tag Link Text 3'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_link_3', ''),
  );
  $form['info_tags_fieldset']['info_tags_url_3'] = array(
    '#title' => t('Info Tag URL 3'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_url_3', ''),
  );
  $form['info_tags_fieldset']['info_tags_highlight_4'] = array(
    '#title' => t('Info Tag Highlight 4'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_highlight_4', ''),
  );
  $form['info_tags_fieldset']['info_tags_label_4'] = array(
    '#title' => t('Info Tag Label 4'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_label_4', ''),
  );
  $form['info_tags_fieldset']['info_tags_link_4'] = array(
    '#title' => t('Info Tag Link Text 4'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_link_4', ''),
  );
  $form['info_tags_fieldset']['info_tags_url_4'] = array(
    '#title' => t('Info Tag URL 4'),
    '#type' => 'textfield',
    '#default_value' => variable_get('info_tags_url_4', ''),
  );
  /** 
   * Social Network Buttons
   */
  $form['social_network_buttons_header'] = array(
    '#prefix' => '<h2>',
    '#markup' => t('Social Media'),
    '#suffix' => '</h2>'
  );
  $form['social_network_buttons_help'] = array(
    '#markup' => t('Urls to various social media network sites. Leave blank to hide any network.')
  );
  $form['social_network_buttons_fieldset'] = $fieldset;
  $form['social_network_buttons_fieldset']['#title'] = t('Social Media');
  $form['social_network_buttons_fieldset']['facebook_url'] =  array(
    '#title' => t('Facebook'),
    '#description' => t('Facebook url like http://www.facebook.com/pages/Open-Media-Foundation/209082215492?fref=ts'),
    '#type' => 'textfield',
    '#default_value' => variable_get('facebook_url', ''),
  );
  $form['social_network_buttons_fieldset']['twitter_url'] =  array(
    '#title' => t('Twitter'),
    '#description' => t('Twitter url like http://twitter.com/OMFoundation'),
    '#type' => 'textfield',
    '#default_value' => variable_get('twitter_url', ''),
  );
  /**
   * profile menu
   */
  $form['persistant_site_links_header'] = array(
    '#prefix' => '<h2>',
    '#markup' => t('Persistant Site Links'),
    '#suffix' => '</h2>'
  );
  $form['persistant_site_links_help'] = array(
    '#markup' => t('Options to disable menu items in the top right navigation.')
  );
  $form['persistant_site_links'] = $fieldset;
  $form['persistant_site_links']['#title'] = t('Persistant Site Links');
  $form['persistant_site_links']['om_loginout_link'] = array(
    '#title' => t('Include Login/Logout Links'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('om_loginout_link', TRUE),
  ); 
  $form['persistant_site_links']['om_register_link'] = array(
    '#title' => t('Include Register Link'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('om_register_link', TRUE),
  ); 
  $form['persistant_site_links']['om_profile_link'] = array(
    '#title' => t('Include Profile Link'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('om_profile_link', TRUE),
  ); 
  $form['persistant_site_links']['om_help_link'] = array(
    '#title' => t('Include Help Link'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('om_help_link', TRUE),
  ); 
  $form['persistant_site_links']['om_cart_link'] = array(
    '#title' => t('Include Shopping Cart Link'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('om_cart_link', TRUE),
  ); 

  /**
   * Main banner
   */
  $form['show_status_images_header'] = array(
    '#prefix' => '<h2>',
    '#markup' => t('Show Status Images'),
    '#suffix' => '</h2>'
  );
  $form['show_status_images_help'] = array(
    '#markup' => t('Images shown on the show page while it is live or processing.')
  );
  $form['show_status_images_fieldset'] = $fieldset;

  $form['show_status_images_fieldset']['#title'] = t('Show Status Images');
  $form['show_status_images_fieldset']['show_processing'] = array(
    '#title' => t('Show Processing Image'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('show_processing', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['show_status_images_fieldset']['show_ondemand'] = array(
    '#title' => t('Show OnDemand Image'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('show_ondemand', ''),
    '#upload_location' => 'public://theme_assets/',
  );
  $form['show_status_images_fieldset']['show_live'] = array(
    '#title' => t('Show Live Image'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('show_live', ''),
    '#upload_location' => 'public://theme_assets/',
  );

  /**
   * Adding admin section
   */
  if (user_access('admin omp theme')) {
    $form['admin_theme_omp_header'] = array(
      '#prefix' => '<h2>',
      '#markup' => t('Open Media Theme Administration'),
      '#suffix' => '</h2>'
    );
    $form['admin_theme_omp_help'] = array(
      '#markup' => t('Various theme settings like color scheme. Colors should be valid hexadecimal values with "#" symbols.')
    );
    $form['admin_theme_omp_fieldset'] = $fieldset;
    $form['admin_theme_omp_fieldset']['#title'] = t('Admin OMP Theme');
    $form['admin_theme_omp_fieldset']['main_nav_bar_background'] = array(
      '#title' => t('Navbar Background Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_bar_background', ''),
    );
    $form['admin_theme_omp_fieldset']['main_nav_color'] = array(
      '#title' => t('Main Menu Text Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_color', ''),
    );
    $form['admin_theme_omp_fieldset']['main_nav_background'] = array(
      '#title' => t('Main Menu Background Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_background', ''),
    );
    $form['admin_theme_omp_fieldset']['main_nav_color_hover'] = array(
      '#title' => t('Main Menu Text Color Hover'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_color_hover', ''),
    );
    $form['admin_theme_omp_fieldset']['main_nav_background_hover'] = array(
      '#title' => t('Main Menu Background Color Hover'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_background_hover', ''),
    );
    $form['admin_theme_omp_fieldset']['main_nav_dropdown_color'] = array(
      '#title' => t('Main Menu Drop Down Text Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_dropdown_color', ''),
    );
    $form['admin_theme_omp_fieldset']['main_nav_dropdown_background'] = array(
      '#title' => t('Main Menu Drop Down Background Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_dropdown_background', ''),
    );
    $form['admin_theme_omp_fieldset']['main_nav_dropdown_color_hover'] = array(
      '#title' => t('Main Menu Drop Down Text Color Hover'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_dropdown_color_hover', ''),
    );
    $form['admin_theme_omp_fieldset']['main_nav_dropdown_background_hover'] = array(
      '#title' => t('Main Menu Drop Down Background Color Hover'),
      '#type' => 'textfield',
      '#default_value' => variable_get('main_nav_dropdown_background_hover', ''),
    );
    $form['admin_theme_omp_fieldset']['header_shadow_color'] = array(
      '#title' => t('Header Shadow Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('header_shadow_color', ''),
    );
    $form['admin_theme_omp_fieldset']['content_border_color'] = array(
      '#title' => t('Content Border Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('content_border_color', ''),
    );
    $form['admin_theme_omp_fieldset']['site_link_color'] = array(
      '#title' => t('Site Link Color'),
      '#description' => t('The small menu in the header.'),
      '#type' => 'textfield',
      '#default_value' => variable_get('site_link_color', ''),
    );
    $form['admin_theme_omp_fieldset']['background_texture'] = array(
      '#title' => t('Background Texture Tile'),
      '#description' => t('Repeating background image. Should be as small as possible.'),
      '#type' => 'managed_file',
      '#default_value' => variable_get('background_texture', ''),
      '#upload_location' => 'public://theme_assets/',
    );
    $form['admin_theme_omp_fieldset']['background_color'] = array(
      '#title' => t('Solid Background Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('background_color', ''),
    );
    $form['admin_theme_omp_fieldset']['front_content_background_color'] = array(
      '#title' => t('Front Content Background Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('front_content_background_color', ''),
    );
    $form['admin_theme_omp_fieldset']['title_color'] = array(
      '#title' => t('Title Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('title_color', ''),
    );
    $form['admin_theme_omp_fieldset']['title_font'] = array(
      '#title' => t('Title Font'),
      '#type' => 'textfield',
      '#default_value' => variable_get('title_font', ''),
    );
    $form['admin_theme_omp_fieldset']['info_tag_color'] = array(
      '#title' => t('Info Tag Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('info_tag_color', ''),
    );

    /**
     * Dashboard theme settings
     */
    $form['admin_theme_dashboard_header'] = array(
      '#prefix' => '<h2>',
      '#markup' => t('Open Media Dashboard Theme Administration'),
      '#suffix' => '</h2>'
    );
    $form['admin_theme_dashboard_help'] = array(
      '#markup' => t('Various theme settings like color scheme. Colors should be valid hexadecimal values with "#" symbols.')
    );
    $form['admin_theme_dashboard_fieldset'] = $fieldset;
    $form['admin_theme_dashboard_fieldset']['#title'] = t('Dashboard Theme');
    $form['admin_theme_dashboard_fieldset']['om_dashboard_title_color'] = array(
      '#title' => t('Title Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('om_dashboard_title_color', ''),
    );
    $form['admin_theme_dashboard_fieldset']['om_dashboard_shadow_color'] = array(
      '#title' => t('Shadow Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('om_dashboard_shadow_color', ''),
    );
    $form['admin_theme_dashboard_fieldset']['om_dashboard_pane_bg'] = array(
      '#title' => t('Pane Background Color'),
      '#type' => 'textfield',
      '#default_value' => variable_get('om_dashboard_pane_bg', ''),
    );

  /**
  * Footer
  */
  $form['main_footer'] = array(
    '#prefix' => '<h2>',
    '#markup' => t('Footer Text'),
    '#suffix' => '</h2>'
  );
  $form['main_footer_help'] = array(
    '#markup' => t('The site\'s footer text')
  );
  $form['main_footer_fieldset'] = $fieldset;
  $form['main_footer_fieldset']['#title'] = t('Main Footer Text');
  $form['main_footer_fieldset']['footer_address'] = array(
    '#title' => t('Address'),
    '#type' => 'textfield',
    '#default_value' => variable_get('footer_address', ''),
  );
  $form['main_footer_fieldset']['phone_number'] = array(
    '#title' => t('Phone Number'),
    '#type' => 'textfield',
    '#default_value' => variable_get('phone_number', ''),
  );
  $form['main_footer_fieldset']['email'] = array(
    '#title' => t('Email Address'),
    '#type' => 'textfield',
    '#default_value' => variable_get('email', ''),
  );
  $form['main_footer_fieldset']['omf_project'] = array(
    '#title' => t('Project of Open Media Foundation Logo'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('omf_project', ''),
  );

  /**
  * Show Pages 
  */
  $form['show_page'] = array(
    '#prefix' => '<h2>',
    '#markup' => t('Show Pages'),
    '#suffix' => '</h2>'
  );
  $form['show_page_help'] = array(
    '#markup' => t('Show / video page settings')
  );
  $form['show_page_fieldset'] = $fieldset;
  $form['show_page_fieldset']['#title'] = t('Show / Video Page Settings');
  $form['show_page_fieldset']['show_page_left_width'] = array(
    '#title' => t('Anonymous left column width'),
    '#type' => 'textfield',
    '#default_value' => variable_get('show_page_left_width', 550),
  );
  $form['show_page_fieldset']['show_page_right_width'] = array(
    '#title' => t('Anonymous right column width'),
    '#type' => 'textfield',
    '#default_value' => variable_get('show_page_right_width', 140),
  );
  $form['show_page_fieldset']['show_page_left_width_user'] = array(
    '#title' => t('Authenticated left column width'),
    '#type' => 'textfield',
    '#default_value' => variable_get('show_page_left_width_user',550),
  );
  $form['show_page_fieldset']['show_page_right_width_user'] = array(
    '#title' => t('Authenticated right column width'),
    '#type' => 'textfield',
    '#default_value' => variable_get('show_page_right_width_user', 140),
  );

  }
  $form['#submit'][] = 'om_theme_assets_admin_form_submit';
  return system_settings_form($form);
}

/** 
 * Validate an above url to be both valid and internal.
 */
function _om_theme_assets_url_validate($element, &$form_state) {
  if (!empty($element['#value'])) {
    if (url_is_external($element['#value'])) {
      $message = t('!name must be an internal path (i.e. Drupal path like about-us or node/371).', array('!name' => $element['#title']));
      form_error($element, $message);
    }
    $item_alias = drupal_get_normal_path($element['#value']);
    $item = menu_get_item($item_alias);
    if (empty($item)) {
      $message = t('!name must be a valid internal path (i.e. Drupal path like about-us or node/371).', array('!name' => $element['#title']));
      form_error($element, $message);
    }
  }
}

/** 
 * Submit handler for saving files.
 */
function om_theme_assets_admin_form_submit(&$form, &$form_state) {
  $file_elements = array('theme_banner', 'call_to_action_1', 'call_to_action_2', 'call_to_action_3', 'background_texture', 'show_live', 'show_processing', 'show_ondemand');
  foreach ($file_elements AS $file_field) {
    if (!empty($form_state['values'][$file_field])) {
      global $user;
      $file = file_load($form_state['values'][$file_field]);
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      file_usage_add($file, 'om_theme_assets', $file_field, $user->uid);
    }
  }
}
