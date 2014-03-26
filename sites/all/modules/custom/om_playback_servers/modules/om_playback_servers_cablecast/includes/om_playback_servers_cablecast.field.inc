<?php

/**
 * Implements hook_field_info
 */
function om_playback_servers_cablecast_field_info() {
  return array(
    // We name our field as the associative name of the array.
    'cablecast_file_selector' => array(
      'label' => t('Cablecast File Selector'),
      'description' => t('Selects from orphaned files on the default cablecast.'),
      'default_widget' => 'cablecast_file_selector_widget',
      'default_formatter' => 'cablecast_file',
    ),
  );
}

/**
 * Implements hook_field_formatter_info
 */
function om_playback_servers_cablecast_field_formatter_info() {
  return array(
    'cablecast_file' => array(
      'label' => t('Cablecast file default formatter'),
      'field types' => array('cablecast_file_selector'),
    )
  );
}

/**
 * Implements hook_field_is_empty
 */
function om_playback_servers_cablecast_field_is_empty($item, $field) {
  if (!empty($item['uri']) && $item['uri'] != 'none') {
    return FALSE;
  }
  return TRUE;
}

/**
 * Implements hook_field_formatter_view
 */
function om_playback_servers_cablecast_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  if ($display['type'] == 'cablecast_file') {
    foreach ($items as $delta => $item) {
      $element[$delta] = array(
        '#type' => 'html_tag',
        '#tag' => 'p',
        '#value' => $item['uri'],
      );
    }
  }
  return $element;
}

/**
 * Implements hook_field_widget_info
 */
function om_playback_servers_cablecast_field_widget_info() {
  return array(
    'cablecast_file_selector_widget' => array(
      'label' => t('Cablecast File Widget'),
      'field types' => array('cablecast_file_selector'),
    )
  );
}

/**
 * Implements hook_field_widget_form
 */
function om_playback_servers_cablecast_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  if (user_access('use cablecast media browser')) {
    drupal_add_css(drupal_get_path('module', 'om_playback_servers_cablecast') . '/css/om_playback_servers_cablecast_file_selector.css');
    if (empty($items)) {
      $cablecast_file_interface = new cablecastFile();
      $files = $cablecast_file_interface->get_orphaned_files();
      /*$widget = array(
        '#title' => t('Select a File from Ingest:'),
        '#type' => 'select',
        '#options' => $files,
        '#empty_option' => '- Select a File -',
        '#empty_value' => 'none',
        '#required' => $element['#required'],
        '#description' => $element['#description'],
      );*/
    }
    else {
     /* $widget = array(
        '#markup' => '<label>' . t('Broadcast File') . '</label>' . om_playback_servers_cablecast_create_widget_table($items)
      );*/
    }
    $element['uri'] = $widget;
    return $element;
  }
}

/**
 * Implements hook_field_presave
 */
function om_playback_servers_cablecast_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  if ($field['type'] == 'cablecast_file_selector') {
    foreach($items AS $key => $item) {
      if ($item['uri'] != 'none') {
        $cablecast_file_interface = new cablecastFile();
        $uri = $cablecast_file_interface->build_uri($entity, $item['uri']);
        if (!empty($uri)) {
          $items[$key]['uri'] = $uri;
        }
      }
    }
  }
}

/**
 * Given a set of widget uri values return a table.
 */
function om_playback_servers_cablecast_create_widget_table($values) {
  $cablecast_file_interface = new cablecastFile();
  $header = '<thead><th>Filename</th><th>Uri</th><th>Internet Archive Status</th></head>';
  $body = '';
  foreach ($values AS $value) {
    $file_name = $cablecast_file_interface->get_original_file_name($value['uri']);
    if (empty($file_name)) {
      $file_name = 'N/A';
    }
    $ia_status = $cablecast_file_interface->get_ia_status($value['uri']);
    $body = '<tr><td>' . $file_name . '</td><td>' . $value['uri'] . '</td><td>' . $ia_status . '</td></tr>';
  }
  return "<table>$header $body</table>";
}
