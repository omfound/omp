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
  _om_volunteer_discount_form($pane_form);
  return $pane_form; 
}

function _om_volunteer_discount_form(&$form) {
  global $user;
  $total_points = userpoints_get_max_points($user->uid);
  $order_total = $form_state['order']->commerce_order_total[$l][0]['amount'];
  $multiple = om_volunteer_get_multiple() * 100;
  $required_points = intval($order_total / $multiple);
  $message_values = array(
    '!points' =>  $total_points,
    '!point_type' => 'hours',
    '!value' => '$10.00',
    '!required' => $required_points
  );
  $message = t('You have !points !point_type available for use. Each !point_type is worth !value.', $message_values);
  $message .= "<br/>" . t('!point_type to completely fulfill this order: !required');
  $form['message'] = array(
    '#markup' => $message 
  );
  $form['apply_points'] = array(
    '#type' => 'textfield',
    '#title' => t('Apply Points'),
    '#default_value' => $required_points,
    '#element_validate' => 'om_volunteer_validate_points'
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Apply',
    '#submit' => array('om_volunteer_discount_checkout_form_submit')
  );
}
