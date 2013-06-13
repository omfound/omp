<?php

/**
 * Implements hook_preprocess_hook
 */
function om_agenda_manager_preprocess_om_show_live_block(&$variables) {
  dsm($variables);
  if (!empty($variables['live_themes'])) {
    $buttons = array();
    foreach ($variables['live_themes'] as $theme_tid => $details) {
      $button = '';
      if ($details['live_nid']) {
        $button .= '<div class="om-live-button stream-online">';
        $live_node = node_load($details['live_nid']);
        $options = array('attributes' => array('class' => 'button-live'));
        $button = l($details['theme'], 'node/'.$live_node->nid, $options);
      }else{
        $button .= '<div class="om-live-button stream-offline">';
        $button .= $details['theme'];
      }
      $button .= '</div>';
      $buttons[] = $button;
    }
  }

  if (count($buttons) > 0) {
    $variables['buttons'] = $buttons;
  }
}
