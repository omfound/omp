<?php

function commerce_order_project_pane_settings_form($checkout_pane) {
  $form['commerce_order_project_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable project reference field on checkout?'),
    '#default_value' => variable_get('commerce_order_project_enabled'),
  );
  return $form;
}

function commerce_order_project_pane_checkout_form($form, $form_state, $checkout_pane, $order) {
  $checkout_form['commerce_order_project_reference'] = array(
    '#type' => 'select',
    '#title' => t('Project Reference'),
    '#options' => commerce_order_project_user_project_options($order->uid),
  );
  return $checkout_form;
}

function commerce_order_project_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  dsm($form_state['values']);
}
