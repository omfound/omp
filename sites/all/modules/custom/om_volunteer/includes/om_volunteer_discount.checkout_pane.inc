<?php

function om_volunteer_discount_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $pane_form = array();
  $pane_form['test'] = array(
    '#markup' => 'TESTING'
  );
  return $pane_form; 
}
