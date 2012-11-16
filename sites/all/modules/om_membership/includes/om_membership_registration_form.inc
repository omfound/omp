<?php
/** 
 * Kick off the multistep form
 *  this form loads the appropriate step through the menu (membership/signup/[step])
 **/
function om_membership_registration_form($form, &$form_state, $step) {
  global $user;
  $form = array();
  $steps = om_membership_list_steps();
  // If no step has been provided use the first step in the list.
  if (empty($step)) {
    $step = array_keys($steps);
    $step = key($steps);
  }
  $callback = $steps[$step]['form_builder'];
  if (function_exists($callback)) {
    $form = $callback($form, $from_state);
  }
  return $form;
}

/**
 * Given current registration step return the previous or next step of the form.
 * @param string $direction
 *   'next' or 'previous' values, which direction to step.
 * @param string $current_step
 *   optional string of current step.
 * @returns string
 *   next or previous step.
 */
function om_membership_get_step($direction, $current_step = '') {
  $steps = om_membership_list_steps(); 
  $step_keys = array_keys($steps);
  // Determine the current step if one is not provided
  // First try arg(2)
  if (empty($current_step)) {
    $current_step = arg(2);
  }
  // Next grab the first step.
  if (empty($current_step)) {
    $step = key($step_keys);
  }
  // @Todo would be great to clean this up. May have to change step list structure.
  $step_keys = array_flip($step_keys);
  $current_step_number = $step_keys[$current_step];
  $step_keys = array_flip($step_keys);
  if ($direction == 'next') {
    $current_step_number ++;
    return $step_keys[$current_step_number];
  }
  else {
    $current_step_number --;
    return $step_keys[$current_step_number];
  }
}

function om_membership_get_user_step_value() {
  
}

/**
 * Get a list of the registration form steps and provide callback formbuilder functions.
 * @returns array()
 *   list of form steps
 * @Todo these steps shoul be configurable via administration form
 *   and possibly extendable via hook.
 */
function om_membership_list_steps() {
  $steps = array();
  global $user;
  if ($user->uid == 0) {
    $steps['user-registration'] = array(
      'label' => t('Create Your User Account'),
      'form_builder' => 'om_membership_user_registration_form'
    );
  }
  $steps['user-registration'] = array(
    'label' => t('Edit Your User Account'),
    'form_builder' => 'om_membership_user_registration_form'
  );
  $steps['contact-info'] = array(
    'label' => t('Give Us You Contact Info'),
    'form_builder' => 'om_membership_contact_info_form'
  );
  $steps['demographic-info'] = array(
    'label' => t('Demographic Information'),
    'form_builder' => 'om_membership_demographic_form'
  );
  return $steps;
}

/**
 * Return user registration form catered for om_membership multi-step registration.
 */
function om_membership_user_registration_form($form, &$form_state) {
  // First step is not fully functional. Something is preventing this form from properly submitting.
  // Needs work!
  $form = drupal_get_form('user_register_form');
  $form['#submit'][] = 'om_membership_user_registration_form_submit';
  return $form;
}

/**
 * Submit handler for above step.
 */
function om_membership_user_registration_form_submit($form, &$form_state) {
  // Transfer user to next step.
  $next_step = om_membership_get_step('next');
  $form_state['redirect'] = array(
    'membership/signup/' . $next_step,
   );
}

function om_membership_contact_info_form() {
  
}

function om_membership_demographic_form() {
  
}