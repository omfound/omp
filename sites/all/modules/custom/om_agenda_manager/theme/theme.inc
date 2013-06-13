<?php

/**
 * Implements hook_preprocess_hook
 */
function om_agenda_manager_preprocess_om_show_live_block(&$variables) {
  dsm($variables);
  if (!empty($variables['livestream_info'])) {
    //
  }
}
