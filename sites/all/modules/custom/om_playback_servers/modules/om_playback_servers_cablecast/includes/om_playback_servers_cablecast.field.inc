<?php

/**
 * Implements hook_field_widget_info().
 */
function om_playback_servers_cablecast_field_widget_info() {
  return array(
    'file_cablecast' => array(
      'label' => t('Cablecast File Widget'),
      'field types' => array('file'),
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}

function om_playback_servers_cablecast_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $pbsid = variable_get('default_cablecast');
  if (!empty($pbsid)) {
    $element += array(
      '#type' => 'select',
      '#default_value' => '',
      '#options' => array('cablecast://1' => 'fileone.mp4')
    );
  }
  else {
    $element += array(
      '#markup' => t('No default Cablecast playback server has been selected.')
    );
  }
  return array('value' => $element);
}