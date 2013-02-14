<?php

/**
 * Implements hook_fullcalendar_options_info().
 */
function commerce_reservations_fullcalendar_options_info() {
  return array(
    'commerce_reservations' => array(
      'name' => 'Commerce Reservations',
      'js' => TRUE,
      'css' => TRUE,
    ),
  );
}

/**
 * Implements hook_fullcalendar_options_definition().
 */
function commerce_reservations_fullcalendar_options_definition() {
  $options['commerce_reservations']['contains'] = array(
    'click' => array(
      'default' => FALSE,
      'bool' => TRUE,
    ),
    'select' => array(
      'default' => FALSE,
      'bool' => TRUE,
    ),
    'node_type' => array('default' => ''),
    'date_field' => array('default' => array()),
  );
  return $options;
}