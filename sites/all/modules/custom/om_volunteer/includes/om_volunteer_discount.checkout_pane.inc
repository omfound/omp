<?php

function om_volunteer_discount_checkout_form($form, &$form_state, $checkout_pane, $order) {
  dsm('test');
  $pane_form = array();
  $pane_form['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'om-volunteer-discount-pane',
    ),
  );
  $pane_form['info']['test'] = array(
    '#type' => 'item',
    '#markup' => 'TESTING'
  );
  return $pane_form; 
}


