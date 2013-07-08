<?php

/**
 * Implements hook_preprocess_hook
 */
function om_agenda_manager_preprocess_om_show_live_block(&$variables) {
  drupal_add_css(drupal_get_path('module', 'om_agenda_manager') . '/theme/om-show-live-block.css');
  if (!empty($variables['live_themes'])) {
    $buttons = array();
    foreach ($variables['live_themes'] as $theme_tid => $details) {
      $button = '';
      if ($details['live_nid'] && $details['status']) {
        $button .= '<div class="om-live-button stream-online">';
        $live_node = node_load($details['live_nid']);
        $options = array('attributes' => array('class' => 'om-live-button-content'));
        $button .= l($details['theme'].' Currently In Session', 'node/'.$live_node->nid, $options);
        $button .= '</div>';
      }else{
        $button .= '<div class="om-live-button stream-offline">';
        $button .= '<div class="om-live-button-content">';
        $button .= $details['theme'].' Currently Not In Session';
        $button .= '</div>';
        $button .= '</div>';
      }
      $buttons[] = $button;
    }
  }

  if (count($buttons) > 0) {
    $variables['buttons'] = $buttons;
  }
}
