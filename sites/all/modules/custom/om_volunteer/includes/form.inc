<?php

function om_volunteer_log_form($form, $form_state, $user) {
  $total = 0;
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
    $form['log_hours_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#submit' => 'om_volunteer_log_form_update_hours_submit'
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
    '#submit' => 'om_volunteer_log_form_log_hours_submit'
  ); 
  return $form;
}

function om_volunteer_log_form_log_hours_submit($form, $form_state) {
  dsm('log hours');
}

function om_volunteer_log_form_update_hours_submit($form, $form_state) {
  dsm('update hours');
}
