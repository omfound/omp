<?php

function minim_preprocess_om_show_live_block (&$vars) {
  foreach ($vars['buttons'] as $key => $button) {
    $vars['buttons'][$key] = str_replace('om-live-button-content', 'pure-button', $button);
  }
}

function minim_preprocess_om_site_links (&$vars) {
  if (user_is_logged_in()) {
    $vars['links'][] = l('Add Session', 'node/add/om-show', array('attributes' => array('class' => array('session-link'))));
  }
}

function minim_preprocess_field__field_om_show_video(&$variables) {
  $url = $variables['items'][0]['#markup'];
  dsm($url);
  $video = om_show_render_video_url($url);
  if (!empty($video)) {
    $variables['video'] = $video;
  }
}
