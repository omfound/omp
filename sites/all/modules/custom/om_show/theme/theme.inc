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
  drupal_add_css(drupal_get_path('module', 'om_show') . '/css/om_show_trends.css');
  $shows = array();
  $param = array(
    'max_length' => 60,
    'word_boundary' => true,
    'ellipsis' => true,
  );
  foreach ($variables['results'] as $result) {
    $node = node_load($result->nid);

    $shows[$result->nid] = array(
      'title' => views_trim_text($param, $result->title),
      'nid' => $result->nid,
      'link' => url('node/'.$result->nid),
      'created' => date('F j, Y', $result->created),
      'username' => $result->name,
      'theme_tid' => $result->field_om_theme_tid,
      'rating' => $result->bayesian,
      'votes' => $result->vote_count,
      'voting_widget' => render(field_view_field('node', $node, 'field_om_voting_on_video')),
      'views' => $result->totalcount,
    );
    $shows[$result->nid]['thumbnail_path'] = om_show_video_image($node);
  }

  if (!empty($shows)) {
    $variables['shows'] = $shows;
  }
  $variables['filter'] = render($variables['filter']);
  $variables['pager'] = render($variables['pager']);
}
