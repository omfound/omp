<?php

function minim_preprocess_block__nice_menus_1 (&$vars) {
  dsm($vars);
  $vars['classes_array'][] = 'pure-menu pure-menu-open pure-menu-horizontal';
}

