<?php

function minim_preprocess_om_show_live_block (&$vars) {
  foreach ($vars['buttons'] as $key => $button) {
    $vars['buttons'][$key] = str_replace('om-live-button-content', 'pure-button', $button);
  }
}
