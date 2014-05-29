<?php

function om_volunteer_discount_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $form_state['checkout_pane'] = $checkout_pane;
  $form_state['order'] = $order;
  $pane_form = array();
  $pane_form['#attached'] = array(
    'js' => array(
      drupal_get_path('module', 'om_volunteer') . '/om_volunteer.js' => array(
        'type' => 'file',
      ),
    )
  );
  _om_volunteer_discount_form($pane_form, $form_state);
  return $pane_form; 
}

function _om_volunteer_discount_form(&$form, &$form_state) {
  global $user;
  $types = _commerce_coupon_userpoint_taxonomy_options();
  $active_term = key($types);
  if (!empty($form_state['values']['om_volunteer_discount']['info']['point_type'])) {
     $active_term = $form_state['values']['om_volunteer_discount']['info']['point_type'];
  }
  if (is_numeric($active_term)) {
    $active_term = taxonomy_term_load($active_term);
  }
  $total_points = userpoints_get_current_points($user->uid, $active_term->tid);
  $order_total = $form_state['order']->commerce_order_total[LANGUAGE_NONE][0]['amount'];
  $multiple = om_volunteer_get_multiple($active_term->tid);
  $required_points = intval($order_total / ($multiple * 100));
  $default_points = $required_points;
  if ($total_points < $required_points) {
    $default_points = $total_points;
  }
  $message_values = array(
    '!type' => $active_term->name,
    '!points' =>  om_volunteer_term_format_plural($active_term, $total_points, 'strtolower'),
    '!value' => '$' . $multiple,
    '!required' => om_volunteer_term_format_plural($active_term, $required_points, 'strtolower')
  );
  $message = "<div class='bold'>" . t('!term_plural Available:', array('!term_plural' => $active_term->field_type_label_plural[LANGUAGE_NONE][0]['value'])) . "</div>";
  $message .= t("You have !points available for use.", $message_values);
  $message .= "<div class='bold'>" . t('Exchange Rate:') . "</div>";
  $message .= t("1 hour = !value", $message_values);
  $message .= "<div class='bold'>" . t('Current Order:') . "</div>";
  $message .= t("!required hours required to pay for order in full.", $message_values);
  // Build the form
  $form['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'om-volunteer-discount-pane',
    ),
  );
  $form['info']['message'] = array(
    '#markup' => $message 
  );
  if (count($types) > 1) {
    $form['info']['point_type'] = array(
      '#type' => 'select',
      '#title' => t('Type of Credit:'),
      '#default_value' => $active_term->tid,
      '#options' => $types,
      '#ajax' => array(
        'wrapper' => 'om-volunteer-discount-pane',
        'method' => 'replace',
        'callback' => '_om_volunteer_discount_form_ajax'
      )
    );
  }
  else {
    $form['info']['point_type'] = array(
      '#type' => 'hidden',
      '#value' => $active_term->tid
    );
  }
  // NB: This unset is required for textfields (and other elements) to display new default values in ajax rebuild.
  if (!empty($form_state['input']['om_volunteer_discount'])) {
    unset($form_state['input']['om_volunteer_discount']['info']['apply_points']);
  }
  $form['info']['apply_points'] = array(
    '#type' => 'textfield',
    '#title' => t('Apply Hours:'),
    '#default_value' => $default_points,
    '#element_validate' => array('om_volunteer_validate_points')
  );
  $form['info']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Apply',
    '#submit' => array('om_volunteer_discount_pane_form_submit')
  );
}

function om_volunteer_validate_points($element, &$form_state, $form) {
  if ($form_state['triggering_element']['#value'] == 'Apply') {
    global $user;
    $term = taxonomy_term_load($form_state['values']['om_volunteer_discount']['info']['point_type']);
    $user_max_points = userpoints_get_current_points($user->uid, $term->tid);
    if ($element['#value'] > $user_max_points ) {
      $formatted = om_volunteer_term_format_plural($term, $user_max_points, 'strtolower');
      form_error($element, "You have $formatted available for redemption.");
    } 
  }
}

/**
 * This is NOT the commerce pane form submit handler. We only want ours
 * to execute if the user wants to apply points.
 */
function om_volunteer_discount_pane_form_submit($form, &$form_state) {
  global $user;
  $l = LANGUAGE_NONE;
  $term = taxonomy_term_load($form_state['values']['om_volunteer_discount']['info']['point_type']);
  $multiple = om_volunteer_get_multiple($term->tid) * 100;
  $order_total = $form_state['order']->commerce_order_total[$l][0]['amount'];
  $order_total_points = $order_total / $multiple;
  $user_max_points = userpoints_get_current_points($user->uid, $term->tid);
  $user_points_used = 0;
  if ($form_state['values']['om_volunteer_discount']['info']['apply_points'] > $order_total_points) {
    $user_points_used = $order_total_points;
  }
  else {
    $user_points_used = $form_state['values']['om_volunteer_discount']['info']['apply_points'];
  }
  $options = array(
    'uid' => $user->uid,
    'points' => -$user_points_used,
    'tid' => $term->tid,
    'display' => TRUE
  );
  userpoints_userpointsapi($options);
  om_volunteer_apply_points($form_state['order'], $user_points_used, $term->tid);
  $form_state['rebuild'] = TRUE;
}

/** 
 * Vanilla #ajax callback
 */
function _om_volunteer_discount_form_ajax($form, $form_state) {
  return $form['om_volunteer_discount']['info'];
}
