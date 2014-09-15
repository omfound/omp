<?php

/**
 * Implements hook_preprocess_hook
 */
function om_agenda_manager_preprocess_om_show_live_block(&$variables) {
  drupal_add_css(drupal_get_path('module', 'om_agenda_manager') . '/theme/om-show-live-block.css');
  if (!empty($variables['live_themes'])) {
    $buttons = array();
    foreach ($variables['live_themes'] as $theme_tid => $details) {
      $button = om_agenda_manager_live_button($details);
      $buttons[] = $button;
    }
  }

  if (count($buttons) > 0) {
    $variables['buttons'] = $buttons;
  }
}
