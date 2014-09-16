<?php

function minim_preprocess_block__nice_menus_1 (&$vars) {
  dsm($vars);
  $vars['content_attributes_array']['class'][] = 'pure-menu pure-menu-open pure-menu-horizontal';
}

