<?php

function minim_preprocess_block__nice_menus_1 (&$vars) {
  $vars['classes_array'][] = 'pure-u-3-5';
  $vars['content_classes'] = 'pure-menu pure-menu-open pure-menu-horizontal';
  $menu_content = $vars['content'];
  $menu_content = str_replace('nice-menu ', '', $menu_content);
  $menu_content = str_replace('nice-menu-down ', '', $menu_content);
  $menu_content = str_replace('nice-menu-main-menu', '', $menu_content);
  $vars['content'] = $menu_content;
}

function minim_preprocess_block__om_theme_assets_om_round_social_media (&$vars) {
  $vars['content_classes'] = 'pure-menu pure-menu-open pure-menu-horizontal';
  $vars['classes_array'][] = 'pure-u-1-5';
}

function minim_preprocess_block__om_theme_assets_om_site_links (&$vars) {
  $vars['content_classes'] = 'pure-menu pure-menu-open';
  $menu_content = '';
  $menu_content .= '<a class="pure-menu-heading" href="/">OMP GOV DEMO</a>';
  $menu_content = $vars['content'];
  $menu_content = str_replace(' | ', '', $menu_content);
  $vars['content'] = $menu_content;
}

