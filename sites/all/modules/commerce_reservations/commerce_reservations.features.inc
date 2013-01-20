<?php
/**
 * @file
 * commerce_reservations.features.inc
 */

/**
 * Implements hook_views_api().
 */
function commerce_reservations_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function commerce_reservations_node_info() {
  $items = array(
    'reservable_product_display' => array(
      'name' => t('Reservable Product Display'),
      'base' => 'node_content',
      'description' => t('A product display for a reservable item.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
