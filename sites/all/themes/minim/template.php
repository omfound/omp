<?php
/**
 * Theme includes
 */
$theme_path = drupal_get_path('theme', 'minim');
require_once($theme_path . '/includes/base.inc');
require_once($theme_path . '/includes/blocks.inc');
require_once($theme_path . '/includes/views.inc');
require_once($theme_path . '/includes/components.inc');

function minim_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'om_show_node_form':
      $form['#attributes']['class'][] = 'pure-form';
      $form['#attributes']['class'][] = 'pure-form-stacked';
      break;
  }
}

if (file_exists('sites/default/files/theme_assets/om_theme_dynamic_css.css')) {
  $css_options = array('type' => 'file', 'group' => CSS_THEME);
  drupal_add_css('sites/default/files/theme_assets/om_theme_dynamic_css.css', $css_options);
}
