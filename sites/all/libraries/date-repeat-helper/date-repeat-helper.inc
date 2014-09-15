<?php

/**
 * Theme level functions to make dealing with date repeat fields ez.
 * Requires date api. Please check for module while including this file!
 */

/**
 * Fetch date information for a given entity and field.
 *
 * @param $entity_type
 *   string type of entity
 * @param $entity
 *   int id or instance of entity
 * @param $field_name
 *   string field_name
 * @returns array
 */
function date_repeat_helper_fetch_all_date_formats($entity_type, $entity, $field_name) {
  if (is_numeric($entity)) {
    $entity = entity_load($entity_type, array($entity));
  }
  if (empty($entity->language)) {
    $entity->language = LANGUAGE_NONE;
  }
  $date = array();
  $date['entity'] = $entity;
  $date['field_name'] = $field_name;
  $date['entity_type'] = $entity_type;
  $full_html = drupal_render(field_view_field($entity_type, $entity, $field_name));
  $date['formatted']['full_html'] = $full_html;
  $date['formatted']['plain'] = strip_tags($full_html);
  
  //store raw & original dates
  foreach($entity->{$field_name}[$entity->language] AS $key => $value) {
    $start = strtotime($value['value'].' UTC');
    if (isset($value['value2'])) {
      $end = strtotime($value['value2'].' UTC');
    }
    $date['raw'][$key]['start'] = $start;
    $date['raw'][$key]['end'] = $end; 
    $date['original'][$key] = $value;
  }
  //store day type
  if (count($entity->{$field_name}[$entity->language]) > 1) {
    $date['day-type'] = 'repeating';
    if (isset($entity->{$field_name}[$entity->language][0]['rrule'])) {
      $date['repeat-desc'] = date_repeat_rrule_description($entity->{$field_name}[$entity->language][0]['rrule']);
      $date['repeat-desc'] = date_repeat_helper_cleanup_date_repeat_desc($date['repeat-desc']);
    }
  }
  else {
    if (date('d/m/Y', $date['raw'][0]['start']) == date('d/m/Y', $date['raw'][0]['end'])) {
      $date['day-type'] = 'oneday';
    }
    else {
      $date['day-type'] = 'multiday';
    }
  }
  //store time type
  if (date('h:i', $date['raw'][0]['start']) == '12:00' && date('h:i', $date['raw'][0]['start']) == '12:00') {
    $date['time-type'] = 'allday';
  }
  else {
    if (isset($date['raw'][0]['end']) && $date['raw'][0]['end'] == $date['raw'][0]['start']) {
      $date['time-type'] = 'startonly';
    }
    elseif (isset($date['raw'][0]['end']) && $date['raw'][0]['end'] != $date['raw'][0]['start']) {
      $date['time-type'] = 'startend';
    }
    else {
      $date['time-type'] = 'startonly';
    }
  }
  return $date;
}

/**
 * Given date info provided above (date_repeat_helper_fetch_all_date_formats) return
 *  a list of upcoming dates chronologically with formatting information.
 *
 * @param $date_info
 *   array from date_repeat_helper_fetch_all_date_formats
 * @returns array
 */
function date_repeat_helper_ordered_dates($date_info) {
  $all_dates = array();
  if (isset($date_info['raw'])) {
    $date_info = array($date_info);
  }
  foreach($date_info AS $key => $value) {
    foreach($value['raw'] AS $key2 => $value2) {
      $full_html = date_repeat_helper_format_date($date_info[$key], $value['original'][$key2]);
      $all_dates[] = array(
        'info_key' => $key,
        'start' => $value2['start'],
        'end' => $value2['end'],
        'formatted' => array(
          'full_html' => $full_html,
          'plain' => strip_tags($full_html),
        ),
      );
    }
  }
  usort($all_dates, "_date_repeat_helper_dates_cmp"); 
  return $all_dates;
}

/**
 * Usort helper function.
 */
function _date_repeat_helper_dates_cmp($a, $b) {
  if($a['start'] == $b['start']) {
    return 0;
  }
  return ($a['start'] < $b['start']) ? -1 : 1;
}


function date_repeat_helper_format_date($date_info, $date_item_array) {
  $field = field_info_field($date_info['field_name']);
  $field_instance = field_info_instance($date_info['entity_type'], $date_info['field_name'], $date_info['entity']->type);
  $display = $field_instance['display']['default'];

  $parameters = array(
    'entity' => $date_info['entity'],
    'entity_type' => $date_info['entity']->type,
    'field' => $field,
    'instance' => $field_instance,
    'langcode' => $date_info['entity']->language,
    'items' => array($date_item_array), 
    'display' => $display,
    'dates' => date_formatter_process($display['type'], $date_info['entity_type'], $date_info['entity'], $field, $field_instance, $date_info['entity']->language, $date_item_array, $display),
    'attributes' => array(),
    'rdf_mapping' => array(),
    'add_rdf' => TRUE,
    'delta' => 0,
    'item' => $date_item_array,
  );

  $output = theme('date_display_combination', $parameters); 
  $output = preg_replace('/<div>(.*?)<\/div>/s', "", $output);
  return $output;
}

/**
 * Utility function to clean up date repeat rule, making it more presentable on the front end.
 */
function date_repeat_helper_cleanup_date_repeat_desc($desc) {
  $desc = str_replace('   ', ', ', $desc);
  $desc = str_replace('  ', ', ', $desc);
  $desc = str_replace(' .', '.', $desc);
  $desc = str_replace('every week', 'weekly', $desc);
  $desc = str_replace('every month', 'monthly', $desc);
  $desc = str_replace('every year', 'yearly', $desc);
  return $desc;
}

function date_repeat_helper_date_info($node, $field_name) {
  if (is_numeric($node)) {
    $node = node_load($node);
  }
  $date_nids = date_repeat_helper_date_nids($node, $field_name);
  $date_info = array();
  if(!empty($date_nids)) {
    foreach($date_nids as $date_nid) {
      $date_info[] = date_repeat_helper_fetch_all_date_formats('node', $node, $field_name);
    }
    $date_info['ordered'] = date_repeat_helper_ordered_dates($date_info);
    return $date_info;
  }
  else {
    return false;
  }
}

function date_repeat_helper_date_nids($node, $field_name) {
  $field_info = field_info_field($field_name);
  $scheme = array();
  foreach ($field_info['storage']['details']['sql']['FIELD_LOAD_CURRENT'] AS $table => $values) {
    $scheme['table'] = $table;
    $scheme['field'] = $values['value'];
  }
  $date_nids = array();
  $query = db_select($scheme['table'], 'ai');
  $query->fields('ai', array('entity_id'));
  $query->condition('bundle', $node->type, '=');
  $query->condition($scheme['field'], $node_id, '=');
  $result = $query->execute();
  while($row = $result->fetchAssoc()) {
    $date_nids[] = $row['entity_id'];
  }
  if (!empty($date_nids)) {
    return $date_nids;
  }
  else{
    return FALSE;
  }
}