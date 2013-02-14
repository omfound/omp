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
    drupal_set_title('Membership Registration');
    $callback($form, $form_state);
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
    $current_step = $step_keys[0];
  }
  $step_number = $steps[$current_step]['step'];
  if ($direction == 'next') {
    $step_number ++;
  }
  else if ($direction == 'previous') {
    $step_number --;
  }
  if ($step_number >= 0 && $step_number < count($steps)) {
    foreach($steps AS $key => $step) {
      if ($step['step'] == $step_number) {
        return $key;
      }
    }
  }
  else {
    return FALSE;
  }
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
      'form_builder' => 'om_membership_user_registration_form',
      'step' => 0
    );
  }
  else {
    $steps['user-registration'] = array(
      'label' => t('Edit Your User Account'),
      'form_builder' => 'om_membership_profile_edit_form',
      'step' => 0
    );
  }
  $hook_steps = &drupal_static(__FUNCTION__);
  if (empty($hook_steps)) {
    $hook_steps = array();
    $hook_steps = module_invoke_all('om_membership_registration_steps');
  }
  $steps = array_merge($steps, $hook_steps);
  module_invoke_all('om_membership_alter_steps', $steps);
  return $steps;
}
/**
 * Implements hook_om_membership_registration_steps
 */
function om_membership_om_membership_registration_steps() {
  global $user;
  $steps = array();
  $steps['contact-info'] = array(
    'label' => t('Give Us Your Contact Info'),
    'form_builder' => 'om_membership_contact_info_form',
    'step' => 1
  );
  $steps['demographic-info'] = array(
    'label' => t('Demographic Information'),
    'form_builder' => 'om_membership_demographic_form',
    'step' => 2
  );
  $steps['checkout'] = array(
    'label' => t('Pay for Your Membership'),
    'form_builder' => 'om_membership_commerce_transfer',
    'step' => 3
  );
  return $steps;
}

/**
 * Return user registration form catered for om_membership multi-step registration.
 */
function om_membership_user_registration_form(&$form, &$form_state) {
  // First step is not fully functional. Something is preventing this form from properly submitting.
  // Needs work!
  om_membership_add_form_helper($form, $form_state);
  $form = user_register_form($form, $form_state);
  $form['#submit'][] = 'om_membership_form_submit';
}

function om_membership_profile_edit_form(&$form, &$form_state) {
  global $user;
  om_membership_add_form_helper($form, $form_state);
  if (!function_exists('user_profile_form')) {
    require_once(drupal_get_path('module', 'user') . '/user.pages.inc');
  }
  $form = user_profile_form($form, $form_state, $user);
  $form['#submit'][] = 'om_membership_form_submit';
}

/**
 * Load contact info profile
 */
function om_membership_contact_info_form(&$form, &$form_state) {
  om_membership_add_form_helper($form, $form_state);
  om_membership_load_profile2_profile_form($form, $form_state, 'contact_info');
}

/**
 * Load demographic profile
 */
function om_membership_demographic_form(&$form, &$form_state) {
  om_membership_add_form_helper($form, $form_state);
  om_membership_load_profile2_profile_form($form, $form_state, 'demographics');
}

/**
 * Load manage org membership profile
 */
function om_membership_org_profile_form(&$form, &$form_state) {
  om_membership_add_form_helper($form, $form_state);
  om_membership_load_profile2_profile_form($form, $form_state, 'manage_organizational_membership');
}

/**
 * Transfer to commerce cart.
 */
function om_membership_commerce_transfer(&$form, &$form_state) {
  global $user;
  $order = commerce_cart_order_load($user->uid);
  drupal_goto('checkout/' . $order->order_id . '/checkout');
}

/**
 * Given references to a $form and $form_state load a profile2 profile of $type.
 */
function om_membership_load_profile2_profile_form(&$form, &$form_state, $type) {
  global $user;
  $form_state['profiles'] = array();
  $form_state['profiles'][$type] = profile2_by_uid_load($user->uid, $type);
  profile2_attach_form($form, $form_state);
  $form['submit'] = array('#type' => 'submit', '#value' => t('Next'));
  $form['#submit'][] = 'om_membership_form_submit';
}

/**
 *  Generic submit handler for all steps.
 */
function om_membership_form_submit($form, &$form_state) {
  global $user;
  // Transfer user to next step.
  $next_step = om_membership_get_step('next');
  $form_state['redirect'] = array(
    'membership/signup/' .  $next_step,
   );
}

/**
 * Create helper that displays steps with a prev/next button.
 */
function om_membership_add_form_helper(&$form, &$form_state) {
  global $user;
  $prev_step = om_membership_get_step('previous');
  $next_step = om_membership_get_step('next');
  $steps = om_membership_list_steps();
  $current_step = arg(2);
  if (empty($current_step)) {
    $current_step = key($steps);
  }
  $step_count = count($steps);
  $current_step_count = $steps[$current_step]['step'] + 1;
  $step_label = $steps[$current_step]['label'];
  
  $form['form_helper'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#weight' => -9999
  );
  if (!empty($prev_step)) {
    $form['form_helper']['form_helper_prev'] = array(
      '#prefix' => '<div id="form-helper-prev">',
      '#markup' => l('Back', 'membership/signup/' . $prev_step),
      '#suffix' => '</div>'
    );
  }
  $form['form_helper']['form_helper_text'] = array(
    '#prefix' => '<div id="form-helper-text">',
    '#markup' => t('!current of !total: !step', array('!current' => $current_step_count, '!total' => $step_count, '!step' => $step_label)),
    '#suffix' => '</div>'
  );
  if (!empty($next_step) && $user->uid > 0) {
    $form['form_helper']['form_helper_next'] = array(
      '#prefix' => '<div id="form-helper-next">',
      '#type' => 'submit',
      '#value' => t('Next'),
      '#suffix' => '</div>'
    );
  }
}