<?php

/**
 * Main administration form builder
 */
function om_timeslot_scheduler_admin_form($form, &$form_state) {
  $form = array();
  
  if (isset($_GET['tab'])) {
    $default_tab = $_GET['tab'];
  }
  else {
    $default_tab = 'edit-basic_config';
  }
  
  $form['om_timeslot_scheduler_admin'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => $default_tab,
  );

  $elements = array();
  $elements += _om_timeslot_scheduler_basic_config_form();
  $elements += _om_timeslot_scheduler_themes();
  $elements += _om_timeslot_scheduler_rules();

  $form['om_timeslot_scheduler_admin'] += $elements;

  return system_settings_form($form);
}

/**
 * Configuration tab form
 */
function _om_timeslot_scheduler_basic_config_form() {

  $form = array();

  $form['basic_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Scheduling Configuration'),
    '#weight' => 0,
  );

  $form['basic_config']['om_timeslot_scheduler_time_between_shows'] = array(
    '#type' => 'textfield',
    '#title' => t('Time Between Airings'),
    '#description' => t('Time in seconds between scheduled airings.'),
    '#default_value' => variable_get('om_timeslot_scheduler_time_between_shows', 30),
    '#element_validate' => array('_om_timeslot_admin_validate_numeric'),
    '#weight' => 0,
  );

  $form['basic_config']['om_timeslot_scheduler_adult_hours_start'] = array(
    '#type' => 'textfield',
    '#title' => t('Adult Hours Start'),
    '#description' => t('Enter when adult programming should be allowed to start. Value should be 24 hour format i.e. 22.'),
    '#default_value' => variable_get('om_timeslot_scheduler_adult_hours_start', 22),
    '#element_validate' => array('_om_timeslot_admin_validate_numeric'),
    '#weight' => 1,
  );

  $form['basic_config']['om_timeslot_scheduler_adult_hours_end'] = array(
    '#type' => 'textfield',
    '#title' => t('Adult Hours End'),
    '#description' => t('Enter when adult programming should end. Value should be 24 hour format i.e. 22.'),
    '#default_value' => variable_get('om_timeslot_scheduler_adult_hours_end', 5),
    '#element_validate' => array('_om_timeslot_admin_validate_numeric'),
    '#weight' => 2,
  );

  $form['basic_config']['om_timeslot_scheduler_branding'] = array(
    '#type' => 'radios',
    '#title' => t('Favor Station Branding'),
    '#description' => t('Favor station branding when gaps in the schedule are smaller than immediate shows the scheduling rule has returned.'),
    '#options' => array('Disabled', 'Enabled'),
    '#default_value' => variable_get('om_timeslot_scheduler_branding', 1),
    '#weight' => 3,
  );

  $rules = om_timeslot_scheduler_entity_get_rules();
  $options = array();
  foreach ($rules AS $rule) {
    $options[$rule['name']] = $rule['title'];
  }

  $form['basic_config']['om_timeslot_scheduler_branding_rule'] = array(
    '#type' => 'select',
    '#title' => t('Station Branding Rule'),
    '#description' => t('Select which rule should fill branding slots.'),
    '#options' => $options,
    '#default_value' => variable_get('om_timeslot_scheduler_branding_rule', 'station_branding_scheduling_rule'),
    '#weight' => 3,
  );

  return $form;
}

/**
 * Theme tab form
 */
function _om_timeslot_scheduler_themes() {

  $form = array();

  $form['themes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Themes'),
    '#weight' => 1,
  );

  $query = db_select('taxonomy_vocabulary', 'voc');
  $query->fields('voc', array('vid'));
  $query->condition('machine_name', 'themes', '=');
  $result = $query->execute();
  $vid = $result->fetchAssoc();

  if (!empty($vid['vid'])) {
    $markup = '<table><thead><th>Theme</th><th>Description</th></thead>';
    $voc = taxonomy_get_tree($vid['vid']);
    $options = array('query' => array('destination' => 'om_timeslot_scheduler/admin?tab=edit-themes'));
    foreach($voc AS $term) {
      $markup .= '<tr><td>' . l($term->name, 'taxonomy/term/' . $term->tid . '/edit', $options) . '</td><td>' . $term->description . '</td></tr>';
    }
    $add_link = l('Add a New Theme', 'admin/structure/taxonomy/themes/add', $options);
    $markup .= '</table>' . $add_link;
  }
  else {
    $markup = t('Your themes vocabulary is missing. Please reinstall Open Media Timeslot Scheduler or recreate the vocabulary.');
  }

  $form['themes']['om_timeslot_scheduler_time_between_shows'] = array(
    '#type' => 'item',
    '#title' => t('Available Themes'),
    '#markup' => $markup,
  );

  return $form;
}

/**
 * Rule tab form
 */
function _om_timeslot_scheduler_rules() {

  $form = array();

  $form['rules'] = array(
    '#type' => 'fieldset',
    '#title' => t('Scheduling Rules'),
    '#weight' => 2,
  );

  $rules = om_timeslot_scheduler_entity_get_rules();

  $options = array('query' => array('destination' => 'om_timeslot_scheduler/admin?tab=edit-themes'));

  $markup = '<table><thead><th>Rule Title</th><th>Rule Description</th></thead>';

  foreach($rules AS $rule) {
    $markup .= '<tr><td>' . $rule['title'] . '</td><td>' . $rule['description'] . '</td></tr>';
  }

  $markup .= '</table>';

  $form['rules']['om_timeslot_scheduler_rules_table'] = array(
    '#type' => 'item',
    '#title' => t('Available Rules'),
    '#markup' => $markup,
  );

  return $form;
}

/**
 * Validation callback to determine if a field is numeric.
 */
function _om_timeslot_admin_validate_numeric(&$element, &$form_state, $form) {
  if (empty($element['#value']) || !is_numeric($element['#value'])) {
    form_error($element, t('This field must be numeric.'));
  }
}

/**
 * Bulk scheduling form builder
 */
function om_timeslot_scheduler_bulk_schedule_form($form, &$form_state) {

  $channels = array();
  $voc = om_playback_servers_get_channel_vocabulary();
  foreach ($voc AS $channel) {
    $channels[$channel->tid] = $channel->name;
  }

  $form['om_timeslot_scheduler_bulk_schedule_channel'] = array(
    '#title' => t('Channel'),
    '#type' => 'select',
    '#required' => TRUE,
    '#description' => t('Select a channel on which to run the bulk scheduler.'),
    '#options' => $channels,
    '#default_value' => variable_get('om_timeslot_scheduler_bulk_schedule_channel', '')
  );

  $form['om_timeslot_scheduler_bulk_schedule_start'] = array(
    '#title' => t('Start Date'),
    '#description' => t('Date and time to begin scheduling.'),
    '#required' => TRUE,
	  '#type' => 'date_popup',
	  '#default_value' => '',
	  '#date_format' => 'Y-m-d - H:i'
  );

  $form['om_timeslot_scheduler_bulk_schedule_end'] = array(
    '#title' => t('End Date'),
    '#description' => t('Date and time to end scheduling.'),
    '#required' => TRUE,
	  '#type' => 'date_popup',
	  '#default_value' => '',
	  '#date_format' => 'Y-m-d - H:i'
  );

  $form['om_timeslot_scheduler_bulk_schedule_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Preview Schedule',
  );

  $form['#validate'][] = '_om_timeslot_scheduler_bulk_schedule_form_validate';
  $form['#submit'][] = '_om_timeslot_scheduler_bulk_schedule_form_submit';

  return $form;
}

function _om_timeslot_scheduler_bulk_schedule_form_validate(&$form, &$form_state) {
  
  if (is_array($form_state['values']['om_timeslot_scheduler_bulk_schedule_start']) || is_array($form_state['values']['om_timeslot_scheduler_bulk_schedule_end'])) {
    return;
  }
  
  $start = strtotime($form_state['values']['om_timeslot_scheduler_bulk_schedule_start']);
  $end = strtotime($form_state['values']['om_timeslot_scheduler_bulk_schedule_end']);
  if ($start > $end) {
    $message = t('End time of scheduling run must be after start time.');
    form_set_error('om_timeslot_scheduler_bulk_schedule_start', $message);
  }
  if ($start < time()) {
    $message = t('You cannot schedule into the past.');
    form_set_error('om_timeslot_scheduler_bulk_schedule_start', $message);
  }
  if ($end < time()) {
    $message = t('You cannot schedule into the past.');
    form_set_error('om_timeslot_scheduler_bulk_schedule_end', $message);
  }
}

function _om_timeslot_scheduler_bulk_schedule_form_submit(&$form, &$form_state) {
  $channel_tid = $form_state['values']['om_timeslot_scheduler_bulk_schedule_channel'];
  $start = strtotime($form_state['values']['om_timeslot_scheduler_bulk_schedule_start']);
  $end = strtotime($form_state['values']['om_timeslot_scheduler_bulk_schedule_end']);
  om_timeslot_scheduler_schedule_window($channel_tid, $start, $end, TRUE);
}