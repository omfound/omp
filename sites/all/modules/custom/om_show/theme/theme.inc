<?php

function om_show_preprocess_om_show_upcoming_airings(&$variables) {
  $airings = om_show_upcoming_airings($variables['show']);
  if (!empty($airings)) {
    $variables['upcoming_airings'] = $airings;
  } 
}
