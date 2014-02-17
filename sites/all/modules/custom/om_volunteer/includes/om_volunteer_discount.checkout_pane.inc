<?php

function om_volunteer_discount_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $pane_form = array();
  $pane_form['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'om-volunteer-discount-pane',
    ),
  );
  _om_volunteer_discount_form($pane_form, 250);
  return $pane_form; 
}

function om_volunteer_discount_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  
}

function _om_volunteer_discount_form(&$form, $total_points) {
  $message_values = array(
    '!points' =>  100,
    '!point_type' => 'hours',
    '!value' => '$10.00'
  );
  $message = t('You have !points !point_type available for use. Each !point_type is worth !value.', $message_values);
  $form['message'] = array(
    '#markup' => $message 
  );
  $form['apply_points'] = array(
    '#type' => 'textfield',
    '#title' => t('Apply Points'),
    '#default_value' => $total_points,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Apply'
  );
}
