<?php

if (!function_exists('date_repeat_helper_fetch_all_date_formats') && module_exists('date')) {
  require_once(DRUPAL_ROOT . '/sites/all/libraries/date-repeat-helper/date-repeat-helper.inc');
}

function openmedia_preprocess_page(&$variables) {
  if ($_GET['q'] == 'classes') {
    $options = array(
      'type' => 'file',
      'group' => JS_LIBRARY
    );
    drupal_add_js('sites/all/libraries/masonry/jquery.masonry.min.js', $options);
    $options['group'] = JS_DEFAULT;
    drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/omp-grid.js', $options);
  }
}

function openmedia_preprocess_node(&$variables) {
  /** SHOW NODE **/
  if ($variables['node']->type == 'om_show') { openmedia_process_show($variables); }

  /** CLASS DISPLAY NODE NODE **/
  if ($variables['node']->type == 'class_display') {
    global $user;
    $node_meta = entity_metadata_wrapper('node', $variables['node']);
    $product = $node_meta->field_class_display_class->value();
    $product_meta = entity_metadata_wrapper('commerce_product', $product);
    /** --INSTRUCTOR INFO **/
    $instructor = $product_meta->field_class_instructor->value();
    if (!empty($instructor)) {
      $variables['instructor'] = $instructor->name;
      $variables['instructor_email'] = $instructor->mail;
      $instructor_information = profile2_by_uid_load($instructor->uid, 'instructor_information');
      $instructor_information_meta = entity_metadata_wrapper('profile2', $instructor_information);
      $variables['instructor_bio'] = $instructor_information_meta->field_instructor_bio->value();
    }
    /** --MATERIALS **/
    $materials_provided = $product_meta->field_materials_provided->value();
    $variables['materials_provided'] = $materials_provided;
    $what_to_bring = $product_meta->field_what_to_bring->value();
    $variables['what_to_bring'] = $what_to_bring;
    /** --CERTIFICATIONS **/
    $certs_required = $product_meta->field_class_required_certs->value();
    if (!empty($certs_required)) {
      $variables['certs_required'] = '';
      foreach ($certs_required AS $term) {
        $variables['certs_required'] .= $term->name . ', ';
      }
      $variables['certs_required'] = rtrim($variables['certs_required'], ', ');
    }
    $certs_earned = $product_meta->field_class_earned_certs->value();
    if (!empty($certs_earned)) {
      $variables['certs_earned'] = '';
      foreach ($certs_earned AS $term) {
        $variables['certs_earned'] .= $term->name . ', ';
      }
      $variables['certs_earned'] = rtrim($variables['certs_earned'], ', ');
    }
    /** --REGISTRATION BOX **/
    $registration_details = array();
    $registration = registration_entity_settings('commerce_product', $product->product_id);
    if (function_exists('om_membership_get_user_membership_products')) {
      $memberships = om_membership_get_user_membership_products($user);
      $discount_message = '';
      if (!empty($memberships)) {
        $price = $product_meta->field_class_member_price->value();
        if ($price['amount'] != 0) {
          $price = '$' . (round(($price['amount'] / 1000), 2));
        }
        else {
          $price = 'Free';
        }
        $discount_message = t('Includes membership discount.');
      }
    } 
    if (!isset($price)) {
      $price = $product_meta->commerce_price->value();
      $price = '$' . (round(($price['amount'] / 1000), 2));
    }
    else if(isset($price) && $price['amount'] == 0) {
       $price = 'Free';
    }
    $location = $product_meta->field_class_location->value();
    $coords = $product_meta->field_class_coordinates->value();
    $directions_link = '';
    if (!empty($coords['lat']) && !empty($coords['lon'])) {
      $options = array('attributes' => array('target' => '_blank'),'query' => array('q' => $coords['lat'] . ', ' . $coords['lon']));
      $directions_link = l('Get Directions', 'http://maps.google.com', $options);
    }
    $date_info = date_repeat_helper_fetch_all_date_formats('commerce_product', $product, 'field_class_date');
    $final_date = date_repeat_helper_ordered_dates($date_info);
    $options = array('attributes' => array('class' => 'gray-button'));
    if (!empty($variables['content']['field_class_display_class'])) {
      unset($variables['content']['field_class_display_class'][0]['capacity']);
      $variables['content']['field_class_display_class'][0]['submit']['#value'] = t('Register Now');
      $variables['content']['field_class_display_class'][0]['submit']['#attributes']['class'] = array('gray-button');
      $registration_button = drupal_render($variables['content']['field_class_display_class']);
    }
    // send details to theme function
    $registration_details = array(
      'price' => $price,
      'discount_message' => $discount_message,
      'dates' => $final_date,
      'location' => $location,
      'directions_link' => $directions_link,
      'seats_left' => $registration['capacity'] - registration_event_count('commerce_product', $product->product_id),
      'registration_button' => $registration_button
    );
    $variables['registration_box'] = theme('class_registration_box', array('registration_details' => $registration_details));
  }
}

function openmedia_process_show(&$variables) {
  if($variables['field_om_show_video'][$variables->language]) {
    $jwplayer = array();
    foreach($variables['field_om_show_video'] as $key => $info) {
      $jwplayer[$key]['path'] = $info['safe_value'];
      if($variables['field_show_thumbnail'][$variables->language][0]['uri']) {
        $jwplayer[$key]['image'] = file_create_url($variables['field_show_thumbnail'][$variables->language][0]['uri']); 
      }
    }
    drupal_add_js(array('jwplayer' => $jwplayer), 'setting');
    drupal_add_js(drupal_get_path('theme', 'openmedia').'/js/jwplayer-default.js');
  }
}

function openmedia_theme($existing, $type, $theme, $path) {
  return array(
    'class_registration_box' => array(
      'path' => $path . '/templates',
      'template' => 'class_registration_box',
      'variables' => array('registration_details' => array())
    )
  ); 
}

function openmedia_preprocess_class_registration_box(&$variables) {
  if (!empty($variables['registration_details'])) {
    $details = $variables['registration_details'];
    $variables['price'] = $details['price'];
    $variables['discount_message'] = $details['discount_message'];
    $variables['seats_left'] = $details['seats_left'];
    if (!empty($details['location'])) {
      if (!empty($details['directions_link'])) {
        $variables['directions_link'] = $details['directions_link'];
      }
      $variables['location_list'] = '<ul>';
      $variables['location_list'] .= '<li>' . $details['location']['thoroughfare'] . '</li>';
      if (!empty($details['location']['premise'])) {
        $variables['location_list'] .= '<li>' . $details['location']['premise'] . '</li>';
      }
      $variables['location_list'] .= '<li>' . $details['location']['locality'] . ', ' . $details['location']['administrative_area'] . ' ' . $details['location']['postal_code'] .'</li>';
      $variables['location_list'] .= '<li>' . $details['location']['country'] . '</li>';
      $variables['location_list'] .= '</ul>';
    }
    if (!empty($details['dates'])) {
      if (!empty($details['dates'])) {
        if (!empty($details['dates'][0]['end'])) {
          $time = date('g:i:s a', $details['dates'][0]['start']) . ' - ' . date('g:i:s a', $details['dates'][0]['end']);
        }
        else {
          $time = date('g:i:s a', $details['dates']['start']);
        }
        $variables['dates'] = '<div>' . date('l, F nS, Y', $details['dates'][0]['start']) . '</div><div>' . $time . '</div>';
      }
    }
    if (!empty($details['registration_button'])) {
      $variables['registration_button'] = $details['registration_button'];
    }
  }
}

function openmedia_region_info() {
  $region_info = &drupal_static(__FUNCTION__);
  if (!isset($region_info)) {
    global $theme;
    $query = db_select('block', 'b');
    $query->fields('b', array('region', 'pages', 'visibility'));
    $query->condition('theme', $theme, '=');
    $resource = $query->execute();
    while($result = $resource->fetchAssoc()) {
      if ($result['region'] != -1) {
        $match = drupal_match_path($_GET['q'], $result['pages']);
        if ($result['visibility'] == 0 && $match == FALSE) {
          $region_info[$result['region']] = TRUE;
        }
        if ($result['visibility'] == 1 && $match == TRUE) {
          $region_info[$result['region']] = TRUE;
        }
      }
    }
  }
  return $region_info;
}
