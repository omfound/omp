<?php

function om_volunteer_log_form($form, &$form_state, $user) {
  $sum_entry = om_volunteer_get_sum_entry_by_uid($user->uid); 
  $form_state['sum_entry'] = $sum_entry;
  $form_state['tab_user'] = $user;
  $total = !empty($sum_entry) ? $sum_entry->hours : 0;
  $form = array();
  $help = variable_get('om_volunteer_log_form_help', FALSE);
  if (!empty($help)) {
    $form['optional_help_message'] = array(
      '#markup' => $help
    );
  }
  if (user_access('aminister open media volunteer')) {
    $form['total_hours'] = array(
      '#title' => t('Total Volunteer Hours'),
      '#description' => t('Total volunteer hours availale for use.'),
      '#type' => 'textfield',
      '#default_value' => $total
    );
    $form['total_hours_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#submit' => array('om_volunteer_log_form_update_hours_submit')
    );
  }
  else {
     $form['total'] = array(
       '#markup' => t('You have logged !total volunteer hours available.', array('!total' => $total))
     );
  }

  $form['log_hours'] = array(
    '#title' => t('Volunteer Hours'),
    '#description' => t('Enter hours as whole numbers or decimals i.e. .5 for 30 minutes'),
    '#type' => 'textfield',
    '#default_value' => 0
  );
  $form['log_hours_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Log Hours'),
    '#submit' => array('om_volunteer_log_form_log_hours_submit')
  ); 
  return $form;
}

function om_volunteer_log_form_update_hours_submit($form, $form_state) {
  if (!empty($form_state['values']['total_hours']) && is_numeric($form_state['values']['total_hours'])) {
    $change = $form_state['values']['total_hours'];
    if (!empty($form_state['sum_entry'])) {
      $change = $form_state['values']['total_hours'] - $form_state['sum_entry']->hours;
      if ($change == 0) {
        return;
      }
    }
    $sum_entry = !empty($form_state['sum_entry']) ? $form_state['sum_entry'] : new stdClass();
    $sum_entry->uid = $form_state['tab_user']->uid;
    $sum_entry->hours = $form_state['values']['total_hours']; 
    om_volunteer_write_sum_entry($sum_entry);
    global $user;
    $log_entry = new stdClass();
    $log_entry->uid = $form_state['tab_user']->uid;
    $log_entry->hours = $change;
    $log_entry->reported_by_uid = $user->uid;
    om_volunteer_write_log_entry($log_entry); 
  }
}

function om_volunteer_log_form_log_hours_submit($form, $form_state) {
  dsm($form_state['values']);
  if (!empty($form_state['values']['log_hours']) && is_numeric($form_state['values']['log_hours'])) {
    $sum = $form_state['values']['log_hours'];
    if (!empty($form_state['sum_entry'])) {
      $sum += $form_state['sum_entry']->hours;
    }
    $sum_entry = !empty($form_state['sum_entry']) ? $form_state['sum_entry'] : new stdClass();
    $sum_entry->uid = $form_state['tab_user']->uid;
    $sum_entry->hours = $form_state['values']['total_hours'];
    om_volunteer_write_sum_entry($sum_entry);
    global $user;
    $log_entry = new stdClass();
    $log_entry->uid = $form_state['tab_user']->uid;
    $log_entry->hours = $form_state['values']['log_hours'];
    $log_entry->reported_by_uid = $user->uid;
    om_volunteer_write_log_entry($log_entry);
  }
}
