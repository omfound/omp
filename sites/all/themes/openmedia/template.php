<?php

if (!function_exists('date_repeat_helper_fetch_all_date_formats') && module_exists('date')) {
  require_once(DRUPAL_ROOT . '/sites/all/libraries/date-repeat-helper/date-repeat-helper.inc');
}

function openmedia_preprocess_html(&$variables) {
  if (!empty($_GET['iframe_mode'])) {
    $variables['classes_array'][] = 'iframe-mode';
    $sidebar_classes = array('one-sidebar sidebar-first', 'one-sidebar sidebar-second', 'two-sidebars');
    foreach ($variables['classes_array'] AS $key => $class) {
      if (in_array($class, $sidebar_classes)) {
        unset($variables['classes_array'][$key]);
      }
    }
  }
}

function openmedia_preprocess_page(&$variables) {
  drupal_add_library('openmedia', 'typekit');

  if ($variables['is_front']) {
    if (!empty($variables['page']['#views_contextual_links_info']['views_ui']['view_name'])) {
      if ($variables['page']['#views_contextual_links_info']['views_ui']['view_name'] == 'classes') {
        drupal_add_js('sites/all/libraries/masonry/jquery.masonry.min.js', $options);
        $options['group'] = JS_DEFAULT;
        drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/omp-grid.js', $options);
      }
    }
  }
  if ($_GET['q'] == 'classes') {
    $options = array(
      'type' => 'file',
      'group' => JS_LIBRARY
    );
    drupal_add_js('sites/all/libraries/masonry/jquery.masonry.min.js', $options);
    $options['group'] = JS_DEFAULT;
    drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/omp-grid.js', $options);
  }

  if (file_exists('sites/default/files/theme_assets/om_theme_dynamic_css.css')) {
    $css_options = array('type' => 'file', 'group' => CSS_THEME);
    drupal_add_css('sites/default/files/theme_assets/om_theme_dynamic_css.css', $css_options);
  }

  //Fix titles on user pages, otherwise broken due to
  //multiple links to user pages in user nav
  if (arg(0) == 'user') {
    switch(arg(1)) {
      case NULL:
        if (!user_is_logged_in()) drupal_set_title(t('Log in'));
        break;
      case 'register':
        drupal_set_title(t('Register'));
        break;
      case 'password':
        drupal_set_title(t('Request new password'));
        break;
      case 'login':
        drupal_set_title(t('Log in'));
        break;
    }
  }

  if (user_access('view iframe embed')) {
    if (arg(0) == 'archived-sessions' || arg(0) == 'live') {
      global $base_url;
      $path = $base_url.'/'.request_path().'?iframe_mode=true';
      $variables['page']['iframe_embed'] = '<iframe src="'.$path.'" width="760" height="1000" frameborder="0"></iframe>';
    }
  }

  if (!empty($_GET['iframe_mode'])) {
    $content = $variables['page']['content'];
    unset($variables['page']);
    $variables['page']['content'] = $content;
    $variables['theme_hook_suggestions'][] = 'page__iframe_mode';
  }
  drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/submit-once.js', array('type' => 'file', 'group' => JS_DEFAULT));
  drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/omp-search.js', array('type' => 'file', 'group' => JS_DEFAULT));
}

function openmedia_library() {
  return array(
    'typekit' => array(
      'title' => 'TypeKit',
      'website' => 'http://typekit.com',
      'version' => 1,
      'js' => array(
        'https://use.typekit.net/nqe8fpz.js' => array(),
        drupal_get_path('theme', 'openmedia') . '/js/typekit.js' => array(),
      )
    ),
    'readmore' => array(
      'title' => 'Readmore JS',
      'website' => 'https://github.com/jedfoster/Readmore.js',
      'version' => '1',
      'js' => array(
        drupal_get_path('theme', 'openmedia') . '/js/readmore.min.js' => array(),
      )
    ),
  );
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
function openmedia_preprocess_field(&$variables, $hook) {
  // Allow preprocessing for fields
  $function = __FUNCTION__ . '__' . $variables['element']['#field_name'];
  if (function_exists($function)) {
    $function($variables);
  }
}

function openmedia_preprocess_field__field_om_show_video(&$variables) {
  $url = $variables['items'][0]['#markup'];
  $video = om_show_render_video_url($url);
  if (!empty($video)) {
    $variables['video'] = $video;
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
    foreach ($certs_required AS $key => $rid) {
      $role = user_role_load($rid);
      $variables['certs_required'] .= $role->name . ', ';
    }
    $variables['certs_required'] = rtrim($variables['certs_required'], ', ');
  }
  $certs_earned = $product_meta->field_class_earned_certs->value();
  if (!empty($certs_earned)) {
    $variables['certs_earned'] = '';
    foreach ($certs_earned AS $key => $rid) {
      $role = user_role_load($rid);
      $variables['certs_earned'] .= $role->name . ', ';
    }
    $variables['certs_earned'] = rtrim($variables['certs_earned'], ', ');
  }
  /** --REGISTRATION BOX **/
  $registration_details = array();
  $registration = registration_entity_settings('commerce_product', $product->product_id);
  $commerce_price = $product_meta->commerce_price->value();
  $commerce_price = $commerce_price['amount'];
  
  if (function_exists('om_membership_get_user_membership_products')) {
    $memberships = om_membership_user_memberships($user, true); 
    $discount_message = '';
    if (!empty($memberships)) {
      $price = $product_meta->field_class_member_price->value();
      if ($price > $commerce_price) {
        $price = $commerce_price;
      }
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
    $price = $commerce_price;
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
    if (user_is_logged_in()) {
      $registration_button = drupal_render($variables['content']['field_class_display_class']);
    } 
    else {
      $registration_button = '<a class="red-button" href="/user">Register</a>';
    }
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
  drupal_add_library('openmedia', 'readmore');
  drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/show_readmore.js', array('type' => 'file', 'group' => JS_THEME));

  // User picture
  if (isset($variables['picture']) && $variables['picture'] > 0) {
    $file = file_load($variables['picture']);
    $variables['picture_rendered'] = theme('image_style', array('style_name' => '30x30', 'path' => $file->uri));
  }

  $variables['video'] = drupal_render($variables['content']['field_om_show_video']);
  $show_status_images = om_theme_assets_show_status_images();
  $video_info = array();
  $url = $variables['content']['field_om_show_video']['#items'][0]['value'];
//Link to Archive.org page
  if (isset($variables['field_archive_derivatives']['0']['value'])) {
    $string = $variables['field_archive_derivatives']['0']['value'];
    $test_archive = json_decode($variables['field_archive_derivatives']['0']['value'], true);
    $array_check = is_array($test_archive);
    if ($array_check == TRUE) {
      reset($test_archive);
      $first_key = key($test_archive);
      $archive_link = $test_archive["$first_key"]['metadata']['identifier']['0'];
      $variables['archive_link'] = $archive_link;
    }
  }
  if (!empty($url)) {
    if ($youtube_id = om_show_youtube_id($url)) {
      $livestream_status = om_show_youtube_livestream_status($youtube_id);
      if (!empty($livestream_status) && $livestream_status == 'active') {
        $video_info['status'] = 'live';
        $video_info['image'] = $show_status_images['live']; 
      }else{
        $video_info['status'] = 'ondemand';
        $video_info['image'] = $show_status_images['ondemand'];
      }
    }
  }else{
    $video_info['status'] = 'processing';
    $video_info['image'] = $show_status_images['processing'];
  }
  $variables['video_info'] = $video_info;

  $options = array('attributes' => array('class' => array('inset-button', 'edit-button')), 'html' => TRUE);
  if (drupal_valid_path('node/'.$variables['node']->nid.'/edit')) {
    $variables['edit_link'] = l('<div class="icon"></div>Edit', 'node/' . $variables['node']->nid.'/edit', $options);
  }
  // Show details area (name and picture are already included in vars)
  $variables['name'] = strip_tags($variables['name']);
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
    $show_theme = 'in Theme Block ';
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
  if (function_exists('alternative_rating_show_average')) {
    $bayesian_score = round(alternative_rating_show_average($variables['node']->nid), 2);
    $help = theme('advanced_help_topic', 
      array(
        'module' => 'om_voting',
        'topic' => 'about-bayesian-average',
      )
    );
    $variables['bayesian_score'] = "<div id='bayesian-score'><div class='score'>Bayesian Score: $bayesian_score</div> $help</div>";
  }
  $learn = l('Learn More About Voting', 'help/om_voting/about-om-voting');
  $variables['vote_message'] = '<strong>' . t('Your Vote Counts!') . '</strong> ' . t('!link', array('!link' => $learn));
  // Node right.
  if (module_exists('om_social')) {
    $social = theme('om_social_vertical_sharing');
    $variables['node_right'] = $social;
  }
  // Link to project
  if (!empty($variables['node']->field_om_show_project[$variables['node']->language])) {
    $project = node_load($variables['node']->field_om_show_project[$variables['node']->language][0]['nid']);
    $variables['project_link'] = l($project->title, 'node/' . $project->nid);
  }
  $variables['upcoming_airings'] = theme('om_show_upcoming_airings_display', array('show' => $variables['node']));
}

function openmedia_preprocess_node__om_project(&$variables) {
  drupal_add_js(path_to_theme() . '/js/omp-project.js', array('group' => JS_THEME));
  $variables['project_title'] = $variables['title'];
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
  if (str_word_count($variables['description']) > 70 ) {
    $variables['read_more'] = '<p class="read-more-button">Read More</p>';
  }
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
 
  if(!empty($shows)) { 
      $score_array = array();
      foreach ($shows AS $show_nid) {
        $bayesian_score = alternative_rating_bayesian_value($show_nid);
        $score_array[$show_nid] = $bayesian_score; 
        $img = openmedia_get_thumbnail_from_show_nid($show_nid);
        if (!empty($img)) {
          $variables['show_grid'] .= l($img, 'node/' . $show_nid, $options);
        }
      }
        $highest_show = (max($score_array));
        $highest_score_nid = array_search($highest_show, $score_array);
        $node_load = node_load($highest_score_nid);
        $node_array = node_view($node_load);
   
    if (module_exists('fivestar')) {
      if (!empty($vote_info['average']['value'])) {
        $vote_info = fivestar_get_votes('node', $highest_score_nid);
        $current_vote = round(($vote_info['average']['value'] / 100) * 5);
        $variables['vote_summary'] = "<div id='vote-summary'>" . $current_vote . '/5</div>';
      }
      $variables['vote_widget'] = drupal_render($node_array['field_om_voting_on_video']);
    }
    if (module_exists('om_social')) {
      $social = theme('om_social_vertical_sharing');
      $variables['node_right'] = $social;
    }
    if (isset($node_load->title)) {
      $variables['video_title'] = $node_load->title;
    }
   if (isset($node_load->body['und']['0']['value'])) {
      $variables['video_description'] = $node_load->body['und']['0']['value'];
    }
    if (!empty($node_load->field_om_show_date)) {
      $new_date = date("m-d-y", strtotime($node_load->field_om_show_date['und']['0']['value']));
      $variables['video_published'] = $new_date;
    }
    $variables['video_views'] = $node_load;
    $stream_wrapper = file_stream_wrapper_get_instance_by_uri($node_load->field_show_thumbnail['und']['0']['uri']);
    $show_thumbnail = $stream_wrapper->getExternalUrl();
    if(!empty($node_load)) {
      $video = $node_load->field_om_show_video['und']['0']['value']; 

      $variables['video'] = theme('video_player', array('id' => 'project-player',
                                                     'image' => $show_thumbnail,
                                                     'file' => $video,
                                                     'width' => 680,
                                                     'height' => 400
                                                     ));
    }
  }
}

function openmedia_preprocess_video_player(&$variables) {
  drupal_add_js('sites/all/libraries/jwplayer/jwplayer.js', array('type' => 'file', 'group' => JS_LIBRARY));
  drupal_add_js(drupal_get_path('theme', 'openmedia') . '/js/video-player.js', array('type' => 'file', 'group' => JS_THEME));
  $settings = array(
                   'video_player' => array($variables)
                   );
  drupal_add_js($settings, array('type' => 'setting', 'group' => JS_THEME));
}

function openmedia_theme($existing, $type, $theme, $path) {
  return array(
    'class_registration_box' => array(
      'path' => $path . '/templates',
      'template' => 'class_registration_box',
      'variables' => array('registration_details' => array())
    ),
    'video_player' => array(
      'path' => $path . '/templates',
      'template' => 'video_player',
      'variables' => array(
                       'file' => '',
                       'width' => '',
                       'height' => '',
                       'id' => '',  
                     )
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

/**
 * Implements hook_preprocess_HOOK
 */
function openmedia_preprocess_views_view_unformatted(&$variables) {
  $rows_rendered = array();
  if (!empty($variables['rows'])) {
    foreach ($variables['rows'] AS $id => $row) {
      $complete_row = "<div class='" . $variables['classes_array'][$id] . "'>";
      $complete_row .= $row;
      $complete_row .= "</div>";
      $rows_rendered[] = array('row' => $complete_row);
    }
  }
  $variables['rows_rendered'] = $rows_rendered;
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }

  switch($variables['view']->name) {
    case 'calendar_product_view':
      //drupal_add_js(path_to_theme() . '/js/om_reservations.js', array('group' => JS_THEME));
      //drupal_add_css(path_to_theme() . '/css/reservations.css');
      break;
    case 'show_grid':
      drupal_add_js(path_to_theme() . '/js/om_show_grid.js', array('group' => JS_THEME));
      break;
  }

}

function openmedia_preprocess_views_view_fields__reservation_orders(&$variables) {
  //add bootstrap button css
  drupal_add_css('sites/all/themes/openmedia/css/bootstrap-buttons.css');

  //generate utility buttons
  $link_options = array(
    'query' => drupal_get_destination(),
    'attributes' => array(
      'class' => 'checkout_button',
    ),
  );

  $status = $variables['row']->field_field_checkout_status[0]['raw']['value'];
  $link_options['attributes']['class'] = array('btn', 'btn-primary');
  $variables['cr']['buttons'][] = l('Contract', 'cr/contract/' . $variables['row']->commerce_line_item_order_id, $link_options);
  switch ($status) {
    case 'Awaiting Checkout':
      $link_options['attributes']['class'] = array('btn', 'btn-primary');
      $variables['cr']['buttons'][] = l('Prepare', 'cr/res_prep/' . $variables['row']->line_item_id, $link_options);
      $link_options['attributes']['class'] = array('btn', 'btn-primary');
      $variables['cr']['buttons'][] = l('Check Out', 'cr/res_checkout/' . $variables['row']->line_item_id, $link_options);
      $link_options['attributes']['class'] = array('btn', 'btn-warning');
      $variables['cr']['buttons'][] = l('No Show', 'cr/res_noshow/' . $variables['row']->line_item_id, $link_options);
      $link_options['attributes']['class'] = array('btn', 'btn-danger');
      $variables['cr']['buttons'][] = l('Cancel Reservation', 'cr/res_cancel/' . $variables['row']->line_item_id, $link_options);
      break;
    case 'Prepared':
      $link_options['attributes']['class'] = array('btn', 'btn-primary');
      $variables['cr']['buttons'][] = l('Update', 'cr/res_prep/' . $variables['row']->line_item_id, $link_options);
      $link_options['attributes']['class'] = array('btn', 'btn-primary');
      $variables['cr']['buttons'][] = l('Check Out', 'cr/res_checkout/' . $variables['row']->line_item_id, $link_options);
      $link_options['attributes']['class'] = array('btn', 'btn-warning');
      $variables['cr']['buttons'][] = l('No Show', 'cr/res_noshow/' . $variables['row']->line_item_id, $link_options);
      $link_options['attributes']['class'] = array('btn', 'btn-danger');
      $variables['cr']['buttons'][] = l('Cancel Reservation', 'cr/res_cancel/' . $variables['row']->line_item_id, $link_options);
      break;
    case 'Checked Out':
    case 'Overdue':
      $link_options['attributes']['class'] = array('btn', 'btn-primary');
      $variables['cr']['buttons'][] = l('Update', 'cr/res_prep/' . $variables['row']->line_item_id, $link_options);
      $link_options['attributes']['class'] = array('btn', 'btn-primary');
      $variables['cr']['buttons'][] = l('Check In', 'cr/res_checkin/' . $variables['row']->line_item_id, $link_options);
      break;
  } 
  if ($payment_info = om_membership_order_payment_details($variables['row']->commerce_line_item_order_id)) {
    $link_options = array(
      'query' => drupal_get_destination(),
      'attributes' => array(
        'class' => 'payment_link',
      ),
    );
    if ($payment_info['paid'] == 'payment_status_money_transferred') {
      $payment_label = 'Paid';
    }
    else if ($payment_info['method'] == 'admin') {
      $payment_label = 'Created by Admin';
    }
    else if ($payment_info['method'] == 'pay_later') {
      $payment_label = 'Paid Later / Not Paid!';
    }
    else if ($payment_info['method'] = 'free_order') {
      $payment_label = 'Free Order';
    }
    $variables['cr']['payment'] = l($payment_label, 'payment/'.$payment_info['id'].'/edit', $link_options);
  }else{
    $variables['cr']['payment'] = t('No Payment');
  }

  $user = user_load($variables['row']->commerce_order_commerce_line_item_uid);
  $membership_orders = om_membership_get_user_membership_orders($user, $active = TRUE);
  $pay_later = false;
  if (!empty($membership_orders)) {
    foreach ($membership_orders as $key => $info) {
      $variables['cr']['payment_details'] = $info->payment;
    }
    $variables['cr']['membership'] = true;
  }
  else {
    $variables['cr']['membership'] = false;
  }
}

/**
 * Implements hook_preprocess_HOOK
 */
function openmedia_preprocess_views_view_fields(&$variables) {
  $fields_rendered = '';
  if (!empty($variables['fields'])) {
    foreach ($variables['fields'] AS $id => $field) {
      // Seperator
      if (!empty($field->separator)) {
        $fields_rendered .= $field->separator;
      }
      $fields_rendered .= $field->wrapper_prefix; 
      $fields_rendered .= $field->label_html; 
      $fields_rendered .= $field->content;
      $fields_rendered .= $field->wrapper_suffix;
    }
  }
  $variables['fields_rendered'] = $fields_rendered;
  // Allow for more granular preproces_functions
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }
}

function openmedia_preprocess_views_view_fields__show_grid(&$vars) {
  openmedia_improved_thumbnail($vars);
}

function openmedia_preprocess_views_view_fields__project_show_list(&$vars) {
  openmedia_improved_thumbnail($vars);
}

function openmedia_improved_thumbnail(&$vars) {
  $view = $vars['view'];
  if(strpos($vars['fields']['field_show_thumbnail']->content, 'no_image.jpg') !== false) {
    $node = node_load($vars['fields']['field_show_thumbnail']->raw);
    if (!empty($node->field_om_show_video[LANGUAGE_NONE][0]['value'])) {
      if ($url = internet_archive_thumb_from_nid($vars['row']->nid)) {
        if (!empty($_SERVER['HTTP_X_SSL'])) {
          $url = str_replace('http', 'https', $url);
        }
        $image = '<img typeof="foaf:Image" src="' . $url . '" width="220" height="135" alt="" />';
        $url = l($image, 'node/'.$vars['fields']['field_show_thumbnail']->raw, array('html' => true));
        $content = '<div class="field-content">';
        $content .= $url;
        $content .= '</div>';
        $vars['fields']['field_show_thumbnail']->content = $content;
      }
    }
  }
}

function openmedia_order_payment_info($order_id) {
  $query = "
    SELECT status, remote_id 
    FROM {commerce_payment_transaction}
    WHERE commerce_payment_transaction.order_id = :oid";

  $results = db_query($query, array(':oid' => $order_id));

  $info = array();
  foreach ($results as $result) {
    $info['status'] = $result->status;
    $info['id'] = $result->remote_id;
  }
  
  return $info;
}

function openmedia_preprocess_views_view_field(&$variables) {
  if ($variables['view']->name == 'upcoming_airings') {
    if (is_numeric($variables['output']) && $variables['field']->field == 'field_om_show_id') { 
      $query = db_select('node', 'n');
      $query->condition('nid', $variables['output']);
      $query->fields('n', array('nid', 'title'));
      $resource = $query->execute();
      $result = $resource->fetchAssoc();
      $variables['output'] = l($result['title'], 'node/' . $result['nid']);
    }
  }
}

function openmedia_render_fivestar_widget($nid) {
  $node = node_load($nid);
  $node_view = node_view($node);
  return drupal_render($node_view['field_om_voting_on_video']);
}

function openmedia_preprocess_block(&$variables) {
  if ($variables['block_html_id'] == 'block-views-project-show-list-block') {
    $variables['classes_array'][] = 'clearfix';
  }
}

