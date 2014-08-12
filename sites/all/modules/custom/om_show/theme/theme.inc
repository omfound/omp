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

function om_show_trending_page(&$variables) {
  dsm('testing');
  watchdog('brian', 'inside trending page');
  foreach ($variables['results'] as $result) {
    dsm($result);
  }
}
