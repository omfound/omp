<?php

function om_volunteer_discount_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $form_state['checkout_pane'] = $checkout_pane;
  $form_state['order'] = $order;
  $pane_form = array();
  _om_volunteer_discount_form($pane_form, $form_state);
  return $pane_form; 
}

function _om_volunteer_discount_form(&$form, &$form_state) {
  $form_state['storage'] = !empty($form_state['storage']) ? $form_state['storage'] : array();
  global $user;
  $types = _commerce_coupon_userpoint_taxonomy_options();
  $active_term = key($types);
  if (is_numeric($active_term)) {
    $active_term = taxonomy_term_load($active_term);
  }
  if (!empty($form_state['values']['om_volunteer_discount']['point_type'])) {
    $active_term = taxonomy_term_load($form_state['values']['om_volunteer_discount']['point_type']);
  }
  $form_state['storage']['active_term'] = $active_term;
  $total_points = userpoints_get_current_points($user->uid, $active_term->tid);
  $order_total = $form_state['order']->commerce_order_total[LANGUAGE_NONE][0]['amount'];
  $multiple = om_volunteer_get_multiple($active_term->tid);
  $required_points = intval($order_total / ($multiple * 100));
  $default_points = om_volunteer_get_default_points($total_points, $required_points);
  $message_values = array(
    '!type' => $active_term->name,
    '!points' =>  $total_points,
    '!point_type' => 'hours',
    '!value' => '$' . $multiple,
    '!required' => $required_points
  );
  $form_state['storage']['message_values'] = $message_values;
  _om_volunteer_pane_message($form, $form_state);
  if (count($types) > 1) {
    $form['point_type'] = array(
      '#type' => 'select',
      '#title' => t('Type of Credit'),
      '#default_value' => $active_term->tid,
      '#options' => $types,
      '#ajax' => array(
        'wrapper' => 'om-volunteer-discount-pane-message',
        'callback' => '_om_volunteer_discount_form_ajax',
        'method' => 'replace'
      )
    );
  }
  else {
    $form['point_type'] = array(
      '#type' => 'hidden',
      '#value' => $active_term->tid
    );
  }
  _om_volunteer_pane_apply_points($form, $form_state, $default_points);
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Apply',
    '#submit' => array('om_volunteer_discount_pane_form_submit')
  );
}

function _om_volunteer_pane_message(&$form, $form_state) {
  $message_values = !empty($form_state['storage']['message_values']) ? $form_state['storage']['message_values'] : array();
  $active_term = !empty($form_state['storage']['active_term']) ? $form_state['storage']['active_term'] : FALSE;
  if (!empty($message_values) && !empty($active_term)) {
    $message_values['!points'] = format_plural($message_values['!points'], '1 ' . strtolower($active_term->field_type_label_singular[LANGUAGE_NONE][0]['value']), '@count ' . strtolower($active_term->field_type_label_plural[LANGUAGE_NONE][0]['value']));
    $message_values['!required'] = format_plural($message_values['!required'], '1 ' . strtolower($active_term->field_type_label_singular[LANGUAGE_NONE][0]['value']), '@count ' . strtolower($active_term->field_type_label_plural[LANGUAGE_NONE][0]['value']));
    $message = "<div class='bold'>" . t('!term_name Available: ', array('!term_name' => $active_term->field_type_label_plural[LANGUAGE_NONE][0]['value'])) . "</div>";
    $message .= t("You have !points available for use.", $message_values);
    $message .= "<div class='bold'>" . t('Exchange Rate:') . "</div>";
    $message .= t("1 hour = !value", $message_values);
    $message .= "<div class='bold'>" . t('Current Order:') . "</div>";
    $message .= t("!required hours required to pay for order in full.", $message_values);
    $form['message_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => 'om-volunteer-discount-pane-message',
      ),
    );
    $form['message_wrapper']['message'] = array(
      '#markup' => $message 
    );
  }
}

function _om_volunteer_pane_apply_points(&$form, $form_state, $default_points) {
  $term = $form_state['storage']['active_term'];
  if (!empty($term)) {
    $form['apply_points_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => 'om-volunteer-discount-pane-apply',
      ),
    );
    $form['apply_points_wrapper']['apply_points'] = array(
      '#type' => 'textfield',
      '#title' => 'Apply ' . $term->field_type_label_plural[LANGUAGE_NONE][0]['value'],
      '#default_value' => $default_points,
      '#element_validate' => array('om_volunteer_validate_points'),
    );
  }
}

function om_volunteer_validate_points($element, &$form_state, $form) {
  if ($form_state['triggering_element']['#value'] == 'Apply') {
    global $user;
    $term = $form_state['storage']['active_term'];
    if (empty($term)) {
      form_error($element, "There has been an error. No volunteer term is active.");
    }
    $user_max_points = userpoints_get_current_points($user->uid, $term->tid);
    if ($element['#value'] > $user_max_points ) {
      // @TODO Abstract this.
      $points = format_plural($user_max_points, '1 ' . strtolower($term->field_type_label_singular[LANGUAGE_NONE][0]['value']), '@count ' . strtolower($term->field_type_label_plural[LANGUAGE_NONE][0]['value']));
      form_error($element, "You have $points available for redemption.");
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
  $multiple = om_volunteer_get_multiple($form_state['values']['om_volunteer_discount']['point_type']) * 100;
  $order_total = $form_state['order']->commerce_order_total[$l][0]['amount'];
  $order_total_points = $order_total / $multiple;
  $term = $form_state['storage']['active_term'];
  if (!empty($term)) {
    $user_max_points = userpoints_get_current_points($user->uid, $term->tid);
    $user_points_used = 0;
    if ($form_state['values']['om_volunteer_discount']['apply_points_wrapper']['apply_points'] > $order_total_points) {
      $user_points_used = $order_total_points;
    }
    else {
      $user_points_used = $form_state['values']['om_volunteer_discount']['apply_points_wrapper']['apply_points'];
    }
    $options = array(
      'uid' => $user->uid,
      'points' => -$user_points_used,
      'tid' => $term->tid,
      'display' => TRUE
    );
    userpoints_userpointsapi($options);
    om_volunteer_apply_points($form_state['order'], $user_points_used, $term->tid);
  }
  else {
    drupal_set_message("There has been an error. No volunteer term is active.");
  }
  $form_state['rebuild'] = TRUE;
}

function _om_volunteer_discount_form_ajax($form, $form_state) { 
  $message = array();
  _om_volunteer_pane_message($message, $form_state);
  $ret = array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace("#om-volunteer-discount-pane-message", render($message)),
    )
  );
  $active_term = $form_state['storage']['active_term'];
  $total_points = userpoints_get_current_points($user->uid, $active_term->tid);
  $order_total = $form_state['order']->commerce_order_total[LANGUAGE_NONE][0]['amount'];
  $multiple = om_volunteer_get_multiple($active_term->tid);
  $required_points = intval($order_total / ($multiple * 100));
  $default_points = om_volunteer_get_default_points($total_points, $required_points);
  $apply_points = array();
  _om_volunteer_pane_apply_points($apply_points, $form_state, $default_points);
  $ret['#commands'][] = ajax_command_replace("#om-volunteer-discount-pane-apply", render($apply_points));
  return $ret;
}
