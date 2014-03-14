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
  if ($options = commerce_order_project_user_project_options($order->uid)) {
    if (!empty($order->field_commerce_order_project[LANGUAGE_NONE][0]['target_id'])) {
      $default = $order->field_commerce_order_project[LANGUAGE_NONE][0]['target_id'];
    }
    else {
      $default = '';
    }
    $checkout_form['commerce_order_project_reference'] = array(
      '#type' => 'select',
      '#title' => t('Please associate your order with a project:'),
      '#options' => commerce_order_project_user_project_options($order->uid),
      '#default' => $default,
    );
    return $checkout_form;
  }
  else {
    return false;
  }
}

function commerce_order_project_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  if (!empty($form_state['values']['commerce_order_project']['commerce_order_project_reference'])) {
    $order->field_commerce_order_project[LANGUAGE_NONE][0]['target_id'] = $form_state['values']['commerce_order_project']['commerce_order_project_reference'];
    commerce_order_save($order);
  }
}
