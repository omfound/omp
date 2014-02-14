<?php

function om_volunteer_discount_checkout_form($form, &$form_state, $checkout_pane, $order) {
  require_once('sites/all/modules/custom/om_volunteer/includes/form.inc');
  $pane_form = array();
  $pane_form['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'om-volunteer-discount-pane',
    ),
  );
  om_volunteer_use_hours_form($pane_form);
  return $pane_form; 
}

function om_volunteer_discount_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  
}

