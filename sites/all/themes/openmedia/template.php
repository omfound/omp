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

/**
 * Implements hook_preprocess_HOOK
 */
function openmedia_preprocess_node(&$variables) {
  // Allow preprocessing for node types.
  $function = __FUNCTION__ . '__' . $variables['node']->type;
  if (function_exists($function)) {
    $function($variables);
  }
}

/**
 * Implements hook_preprocess_HOOK
 */
function openmedia_preprocess_node__class_display(&$variables) {
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
      if ($price != 0) {
        $price = '$' . $price;
      }
      else {
        $price = 'Free';
      }
      $discount_message = t('Includes membership discount.');
    }
  } 
  if (!isset($price)) {
    $price = $product_meta->commerce_price->value();
    $price = $price['amount'];
    if ($price != 0) {
      $price = '$' . (round(($price / 100), 2));
    }
    else {
      $price = 'Free';
    }
    $member_price = $product_meta->field_class_member_price->value();
    $discount_message = t('Member rate: $').$member_price.'<br />'.l('Login or sign up today!', 'user');
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
  $options = array('attributes' => array('class' => 'red-button'));
  if (!empty($variables['content']['field_class_display_class'])) {
    unset($variables['content']['field_class_display_class'][0]['capacity']);
    $variables['content']['field_class_display_class'][0]['submit']['#value'] = t('Register Now');
    $variables['content']['field_class_display_class'][0]['submit']['#attributes']['class'] = array('red-button');
    $registration_button = drupal_render($variables['content']['field_class_display_class']);
  }


  if ($registration['capacity'] == 0) {
    $seats_left = 'Unlimited';
  }
  else {
    $seats_left = $registration['capacity'] - registration_event_count('commerce_product', $product->product_id);
    if($seats_left <= 0) {
      $seats_left = 'No';
      $registration_button = '';
    }
  }

  // send details to theme function
  $registration_details = array(
    'price' => $price,
    'discount_message' => $discount_message,
    'dates' => $final_date,
    'location' => $location,
    'directions_link' => $directions_link,
    'seats_left' => $seats_left,
    'registration_button' => $registration_button
  );
  $variables['registration_box'] = theme('class_registration_box', array('registration_details' => $registration_details));
}

/**
 * Implements hook_preprocess_HOOK
 */
function openmedia_preprocess_node__om_show(&$variables) {
  // User picture
  if (isset($variables['picture']) && $variables['picture'] > 0) {
    $file = file_load($variables['picture']);
    $variables['picture_rendered'] = theme('image_style', array('style_name' => '30x30', 'path' => $file->uri));
  }
  // First do video and video area.
  if(!empty($variables['field_om_show_video'][0]['value'])) {
    $jwplayer = array();
    foreach($variables['field_om_show_video'] as $key => $info) {
      $jwplayer[$key]['path'] = $info['safe_value'];
      if($variables['field_show_thumbnail'][$variables['language']][0]['uri']) {
        $jwplayer[$key]['image'] = file_create_url($variables['field_show_thumbnail'][$variables['language']][0]['uri']); 
      }
    }
    drupal_add_js('sites/all/libraries/jwplayer/jwplayer.js');
    drupal_add_js(array('jwplayer' => $jwplayer), 'setting');
    drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/jwplayer-default.js');
  }
  $variables['video'] = drupal_render($variables['content']['field_om_show_video']);
  $options = array('attributes' => array('class' => array('inset-button', 'edit-button')), 'html' => TRUE);
  $variables['edit_link'] = l('<div class="icon"></div>Edit', 'node/' . $variables['node']->nid, $options);
  // Show details area (name and picture are already included in vars)
  $variables['created'] = 'Published: ' . date('n/d/Y', $variables['node']->created);
  $stats = statistics_get($variables['node']->nid);
  $variables['view_count'] = $stats['totalcount'] . ' Views';
  $path = $GLOBALS['base_url'].'/'.request_path();
  $comment_count = om_social_fb_comment_count($path);
  if ($comment_count != 0) { $variables['comment_count'] = $comment_count . ' Comments'; }
  $locally_produced = $variables['node']->field_om_locally_produced[$variables['language']][0]['value'];
  if ($locally_produced == 1) {
    $variables['locally_produced'] = 'Local Production';
  }
  if (!empty($variables['node']->field_om_theme[$variables['language']][0])) {
    $show_theme = 'in ';
    foreach ($variables['node']->field_om_theme[$variables['language']] AS $term) {
      $full_term = taxonomy_term_load($term['tid']);
      $show_theme .= $full_term->name . ', ';
    }
    $variables['show_theme'] = rtrim($show_theme, ', ');
  }
  // Description
  $variables['description'] = drupal_render($variables['content']['body']);
  if (!empty($variables['description'])) {
    drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/omp-show-hide.js');
  }
  // Voting
  if (module_exists('fivestar')) {
    if (!empty($vote_info['average']['value'])) {
      $vote_info = fivestar_get_votes('node', $variables['node']->nid);
      $current_vote = round(($vote_info['average']['value'] / 100) * 5);
      $variables['vote_summary'] = "<div id='vote-summary'>" . $current_vote . '/5</div>';
    }
    $variables['vote_widget'] = drupal_render($variables['content']['field_om_voting_on_video']);
  }
  $learn = l('Learn More About Voting', '<front>');
  $variables['vote_message'] = '<strong>' . t('Your Vote Counts!') . '</strong> ' . t('Lorem ipsum dolor sit amet, consectetur adipiscing elit. !link', array('!link' => $learn));
  // Node right.
  if (module_exists('om_social')) {
    $social = theme('om_social_vertical_sharing');
    $variables['node_right'] = $social;
  }
}

function openmedia_preprocess_node__om_project(&$variables) {
  // Author Info
  // User picture
  if (isset($variables['picture']) && $variables['picture'] > 0) {
    $file = file_load($variables['picture']);
    $variables['picture_rendered'] = theme('image_style', array('style_name' => '30x30', 'path' => $file->uri));
  }
  $variables['created'] = 'Published: ' . date('n/d/Y', $variables['node']->created);
  // Logo
  if (isset($variables['node']->field_om_project_logo[$variables['language']][0])) {
    $variables['logo'] = theme('image_style', array('style_name' => '220x135', 'path' => $variables['node']->field_om_project_logo[$variables['node']->language][0]['uri']));
  }
  // Body
  $variables['description'] = drupal_render($variables['content']['body']);
  // Local production
  $locally_produced = $variables['node']->field_om_locally_produced[$variables['language']][0]['value'];
  if ($locally_produced == 1) {
    $variables['locally_produced'] = 'Local Production';
  }
  // Rating
  if (isset($variables['node']->field_om_rating[$variables['language']][0])) {
    $variables['rating'] = $variables['node']->field_om_rating[$variables['language']][0]['taxonomy_term']->name;
  }
  // Language
  if (isset($variables['node']->field_om_language[$variables['language']][0])) {
    $variables['project_language'] = $variables['node']->field_om_language[$variables['language']][0]['taxonomy_term']->name;
  }
  // Genre
  if (isset($variables['node']->field_om_genre[$variables['language']][0])) {
    $variables['genre'] = $variables['node']->field_om_genre[$variables['language']][0]['taxonomy_term']->name;
  }
  // Theme
  if (isset($variables['node']->field_om_theme[$variables['language']][0])) {
    $variables['theme'] = $variables['node']->field_om_theme[$variables['language']][0]['taxonomy_term']->name;
  }
  // Page Count
  $stats = statistics_get($variables['node']->nid);
  $variables['view_count'] = $stats['totalcount'] . ' Views';
  // Get Shows that reference this project
  $variables['show_grid'] = '';
  $options = array('html' => TRUE);
  $shows = openmedia_get_project_child_shows($variables['node']->nid);
  foreach ($shows AS $show_nid) {
    $img = openmedia_get_thumbnail_from_show_nid($show_nid);
    if (!empty($img)) {
      $variables['show_grid'] .= l($img, 'node/' . $show_nid, $options);
    }
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
        $variables['dates'] = '';
        $counter = 1;
        $num_items = count($details['dates']);
        foreach ($details['dates'] as $key => $date) {
          if (!empty($date['end'])) {
            $time = date('g:i a', $date['start']) . ' - ' . date('g:i a', $date['end']);
          }
          else {
            $time = date('g:i a', $date['start']);
          }
          if ($counter % 2 == 0) {
            $class = 'even';
          }
          else {
            $class = 'odd';
          }
          if ($counter == 1) {
            $class .= ' first';
          }
          if ($counter == $num_items) {
            $class .= ' last';
          } 
          $variables['dates'] .= '<div class="date-instance '.$class.'"><div>' . date('l, F jS, Y', $date['start']) . '</div><div>' . $time . '</div></div>';
          $counter++;
        }
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

/**
 * Get child shows associated with a project.
 *   @param $nid
 *     int node id
 *   @return $nids
 *     array node ids
 */
function openmedia_get_project_child_shows($nid) {
  $query = db_select('field_data_field_om_show_project', 'show_ref');
  $query->fields('show_ref', array('entity_id'));
  $query->condition('field_om_show_project_nid', $nid, '=');
  $resource = $query->execute();
  $nids = array();
  while ($row = $resource->fetchAssoc()) {
    $nids[] = $row['entity_id'];
  }
  return $nids;
}

/**
 * Get a rendered thumbnail from a show node id.
 *   @param $nid
 *     int node id
 *   @return $img
 *     string img or bool false
 */
function openmedia_get_thumbnail_from_show_nid($nid) {
  $preset = '100x70';
  $query = db_select('field_data_field_show_thumbnail', 'image');
  $query->fields('image', array('field_show_thumbnail_fid'));
  $query->condition('entity_id', $nid, '=');
  $resource = $query->execute();
  while ($result = $resource->fetchAssoc()) {
    $file = file_load($result['field_show_thumbnail_fid']);
    return theme('image_style', array('path' => $file->uri, 'style_name' => $preset));
  }
  return FALSE;
}

function openmedia_commerce_registration_order($variables) {
  $header = array(
    array(
      'data' => t('Email'),
      'field' => 'mail',
      'type' => 'property',
      'specifier' => 'mail'
    ),
    array(
      'data' => t('User'),
      'field' => 'user_uid',
      'type' => 'property',
      'specifier' => 'user'
    ),
    array(
      'data' => t('Class'),
      'field' => 'entity',
      'type' => 'property',
      'specifier' => 'entity'
    ),
    array(
      'data' => t('Quantity'),
      'field' => 'count',
      'type' => 'property',
      'specifier' => 'count'
    ),
    array(
      'data' => t('Purchased'),
      'field' => 'created',
      'sort' => 'desc',
      'type' => 'property',
      'specifier' => 'created'
    ),
    array(
      'data' => t('State'),
      'field' => 'state',
      'type' => 'property',
      'specifier' => 'state'
    ),
  );
  $title = "<div class='commerce-registration registration-list'><h2>";
  $title .= t('Class Registrations');
  $title .= "</h2>";
  $rows = array();

  foreach ($variables['registrations'] as $registration) {
    $wrapper = entity_metadata_wrapper('registration', $registration);
    $host_entity = $wrapper->entity->value();

    $host_label = entity_label($registration->entity_type, $host_entity);
    $host_uri = entity_uri($registration->entity_type, $host_entity);
    $user_col = '';
    if ($registration->user_uid) {
      $user = $wrapper->user->value();
      $uri = entity_uri('user', $user);
      $user_col = l($user->name, $uri['path']);
    }

    $link = $host_label;
    $display_nid = commerce_autodisplay_entity_display_lookup($registration->entity_id);
    if (isset($display_nid)) {
      $link = l($host_label, 'node/'.$display_nid);
    }

    $rows[] = array(
      l($wrapper->mail->value(), 'mailto:' . $wrapper->mail->value()),
      $user_col,
      $link,
      $registration->count,
      format_date($registration->created),
      entity_label('registration_state', $wrapper->state->value())
    );
  }
  $table = array(
    'header' => $header,
    'rows' => $rows
  );

  return $title . theme('table', $table) . theme('pager') . "</div>";
}

function openmedia_preprocess_views_view_unformatted($vars) {
  switch($vars['view']->name) {
    case 'calendar_product_view':
      drupal_add_js(path_to_theme() . '/js/om_reservations.js', array('group' => JS_THEME));
      break;
    case 'show_grid':
      drupal_add_js(path_to_theme() . '/js/om_show_grid.js', array('group' => JS_THEME));
      break;
  }
}
