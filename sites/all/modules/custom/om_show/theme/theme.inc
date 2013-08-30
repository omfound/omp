<?php

function om_show_preprocess_om_show_upcoming_airings(&$variables) {
  $airings = om_show_upcoming_airings($variables['show']);
  if (!empty($airings)) {
    $variables['upcoming_airings'] = $airings;
  } 
}

function om_show_preprocess_om_show_upcoming_airings_all(&$variables) {
  $variables['airings'] = array();
  if (!empty($variables['user'])) {
    $airings =  om_show_upcoming_airings_user($variables['user']);
    foreach ($airings AS $airing_date) {
      foreach($airing_date AS $airing) {
        $variables['airings'][] = array(
          'show' => l($airing['title'], 'node/' . $airing['nid']),
          'airing' => $airing['airing'],
          'channel' => $airing['channel']
        );
      }
    }
  }
}
