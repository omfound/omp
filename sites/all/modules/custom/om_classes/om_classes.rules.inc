<?php

/**
 * Implements hook_rules_action_info
 */
function om_classes_rules_action_info() {
  $actions = array();
  $actions['om_classes_discount'] = array(
    'label' => t('Discount class based on current role or membership line items'),
    'group' => 'Open Media Classes',
    'parameter' => array(
      'commerce_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Commerce Order'),
      )
    )
  );
  return $actions;
}

/**
 * Implements hook_rules_condition_info
 */
function om_classes_rules_condition_info() {
  return array(
    'om_classes_line_item_is_class' => array(
      'label' => t('Line item is a class'),
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_line_item',
          'label' => t('Commerce Line Item'),
          'description' => t('The Commerce Line Item that should be checked for a register enabled product.'),
        ),
      ),
      'help' => t('Is this line item a class.'),
      'module' => 'om_classes',
      'group' => 'Open Media Classes'
    ),
  );
}

/**
 * Condition handler to detect if a line item is a class
 */
function om_classes_line_item_is_class($commerce_line_item) {
  if (!empty($commerce_line_item)) {
    $line_item_meta = entity_metadata_wrapper('commerce_line_item', $commerce_line_item);
    $product = $line_item_meta->commerce_product->value();
    if($product->type == 'class') {
      return true;
    }
  }
  return false;
}

/**
 * Action handler to discount a class based on role or line item.
 */
function om_classes_discount($commerce_line_item) {
  if (!empty($commerce_line_item)) {
    $commerce_order = commerce_order_load($commerce_line_item->order_id);
    $line_item_meta = entity_metadata_wrapper('commerce_line_item', $commerce_line_item);
    $unit_price = commerce_price_wrapper_value($line_item_meta, 'commerce_unit_price', TRUE);
    $current_price = $unit_price['amount'];
    $product = $line_item_meta->commerce_product->value();
    print '<pre>';
    print_r($product);
    print '</pre>';
    $updated_price = '2222';

    $discounted_price = array(
      'amount' => $current_price - $updated_price,
      'currency_code' => $unit_price['currency_code'],
      'data' => array(), 
    );

    $line_item_meta->commerce_unit_price->amount = $updated_price;
    $line_item_meta->commerce_unit_price->data = commerce_price_component_add(
      $line_item_meta->commerce_unit_price->value(), 
      'base_price', 
      $discounted_price, 
      TRUE
    );

    //print '<pre>';
    //print_r($product);
    //print '</pre>';
  }
}
