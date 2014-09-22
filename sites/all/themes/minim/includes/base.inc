<?php
/**
 * Preprocess and Helper Functions for core
 **/

/**
 * Implements hook_preprocess_hook
 */
function minim_preprocess_html(&$variables) {
  // Suggest seperate header and footer script variables in addition to scripts if needed.
  $variables['header_scripts'] = drupal_get_js('header');
  $variables['footer_scripts'] = drupal_get_js('footer');

  if (!empty($_GET['iframe_mode'])) {
    $variables['classes_array'][] = 'iframe-mode';
    //TODO: may need to remove sidebars etc here
  }
}

/**
 * Implements hook_preprocess_block
 * 
 * Adds granular preprocess functions for blocks based on instance and plugin id
 * Plugin ID Example: minim_preprocess_block__pluginid
 * Instance Example: minim_preprocess_block_instance__instanceid
 *
 * @see minim/processors/blocks.inc
 */
function minim_preprocess_block(&$vars) {
  $sub_functions = array();
  $block_id = $vars['block']->module . '_' . $vars['block']->delta;
  $sub_functions[] = __FUNCTION__ . '__' . $block_id;

  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($vars);
    }
  }
}

/**
 * Implements hook_preprocess_HOOK
 */
function minim_preprocess_node (&$vars) {
  if(strpos($vars['field_om_calendar'][0]['url'], '/pub') !== false) { 
    $edit_view = str_replace('/pub', '/edit?rm=minimal', $vars['field_om_calendar'][0]['url']);
  }elseif(strpos($vars['field_om_calendar'][0]['url'], '/edit') !== false) {
    $edit_view = str_replace('/edit', '/edit?rm=minimal', $vars['field_om_calendar'][0]['url']);
  }else{
    $edit_view = $vars['field_om_calendar'][0]['url'];
  }
  $vars['edit_view'] = $edit_view;

  $function = __FUNCTION__ . '__' . $vars['node']->type;
  if (function_exists($function)) {
    $function($vars);
  }
}

function minim_preprocess_field(&$vars) {
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $vars['element']['#field_name'];
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($vars);
    }
  }
}

/**
 * Implements hook_preprocess_HOOK
 */
function minim_preprocess_node__om_show(&$variables) {
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

function minim_preprocess_page (&$variables) {
  dsm(arg(0));
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
  dsm($variables);
}
