<?php

function om_volunteer_discount_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $form_state['checkout_pane'] = $checkout_pane;
  $form_state['order'] = $order;
  $pane_form = array();
  $pane_form['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'om-volunteer-discount-pane',
    ),
  );
  _om_volunteer_discount_form($pane_form, $form_state);
  return $pane_form; 
}

function _om_volunteer_discount_form(&$form, $form_state) {
  global $user;
  $total_points = userpoints_get_current_points($user->uid);
  $order_total = $form_state['order']->commerce_order_total[LANGUAGE_NONE][0]['amount'];
  $multiple = om_volunteer_get_multiple() * 100;
  $required_points = intval($order_total / $multiple);
  $message_values = array(
    '!points' =>  $total_points,
    '!point_type' => 'hours',
    '!value' => '$10.00',
    '!required' => $required_points
  );
  $message = t('You have !points !point_type available for use. Each !point_type is worth !value.', $message_values);
  $message_values['!point_type'] = ucwords($message_values['!point_type']);
  $message .= "<br/>" . t('!point_type to completely fulfill this order: !required', $message_values);
  $form['message'] = array(
    '#markup' => $message 
  );
  $form['apply_points'] = array(
    '#type' => 'textfield',
    '#title' => t('Apply Points'),
    '#default_value' => $required_points,
    '#element_validate' => array('om_volunteer_validate_points')
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Apply',
    '#submit' => array('om_volunteer_discount_pane_form_submit')
  );
}

function om_volunteer_validate_points($element, &$form_state, $form) {
  if ($form_state['triggering_element']['#value'] == 'Apply') {
    global $user;
    $term = taxonomy_get_term_by_name('Volunteer Hours');
    $term = array_shift($term);
    $user_max_points = userpoints_get_current_points($user->uid, $term->tid);
    if ($element['#value'] > $user_max_points ) {
      form_error($element, "You have $user_max_points available for redemption.");
    } 
  }
}

/**
 * This is NOT the commerce pane form submit handler. We only want ours
 * to execute if the user wants to apply points.
 */
function om_volunteer_discount_pane_form_submit($form, &$form_state) {
  // @TODO Check to see if the order already has a points transaction and see 
  // if the user can apply more points.
  global $user;
  $l = LANGUAGE_NONE;
  $multiple = om_volunteer_get_multiple() * 100;
  $order_total = $form_state['order']->commerce_order_total[$l][0]['amount'];
  $order_total_points = $order_total / $multiple;
  $term = taxonomy_get_term_by_name('Volunteer Hours');
  $term = array_shift($term);
  $user_max_points = userpoints_get_current_points($user->uid, $term->tid);
  $user_points_used = 0;
  if ($form_state['values']['om_volunteer_discount']['apply_points'] > $order_total_points) {
    $user_points_used = $order_total_points;
  }
  else {
    $user_points_used = $form_state['values']['om_volunteer_discount']['apply_points'];
  }
  $options = array(
    'uid' => $user->uid,
    'points' => -$user_points_used,
    'tid' => $term->tid,
    'display' => TRUE
  );
  userpoints_userpointsapi($options);
  om_volunteer_apply_points();
}
