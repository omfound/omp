<?php

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