<?php

function om_show_preprocess_om_show_upcoming_airings_display(&$variables) {
  $airings = om_show_upcoming_airings($variables['show']);
  if (!empty($airings)) {
    $variables['upcoming_airings'] = $airings;
  } 
}

function om_show_preprocess_om_show_upcoming_airings_all(&$variables) {
  $variables['airings'] = array();
  $count = 0;
  if (!empty($variables['user'])) {
    $airings =  om_show_upcoming_airings_user($variables['user']);
    foreach ($airings AS $airing_date) {
      foreach($airing_date AS $airing) {
        if ($count > 4) {
          return;
        }
        $count ++;  
        $alter = array('max_length' => 75, 'ellipsis' => TRUE);
        $title = views_trim_text($alter, $airing['title']);
        $variables['airings'][] = array(
          'show' => l($title, 'node/' . $airing['nid']),
          'airing' => $airing['airing'],
          'channel' => $airing['channel']
        );
      }
    }
  }
}

function om_show_preprocess_om_show_trending_page(&$variables) {
  $shows = array();
  foreach ($variables['results'] as $result) {
    $shows[$result->nid] = array(
      'title' => $result->title,
      'nid' => $result->nid,
      'created' => date('F j, Y', $result->created),
      'username' => $result->name,
      'theme_tid' => $result->field_om_theme_tid,
      'rating' => $result->bayesian,
      'votes' => $result->vote_count,
    );
    if (!empty($result->uri)) {
      $shows[$result->nid]['thumbnail_path'] = image_style_url('220x135', $result->uri);
    }
    else {
      $shows[$result->nid]['thumbnail_path'] = 'NO PATH DEFINED YET';
    }
  }

  if (!empty($shows)) {
    $variables['shows'] = $shows;
  }
}
