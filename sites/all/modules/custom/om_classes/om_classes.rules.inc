<?php

/**
 * Implements hook_rules_condition_info
 */
function om_classes_rules_condition_info() {
  return array(
    'om_classes_order_contains_class_product' => array(
      'label' => t('Order contains a class'),
      'arguments' => array(
        'commerce_order' => array('label' => t('Commerce Order'), 'type' => 'commerce_order'),
      ),
      'help' => t('Does the order contain a class.'),
      'module' => 'om_classes',
      'group' => 'Open Media Classes'
    ),
  );
}

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
 * Condition handler that check to see if an order contains a class line item.
 */
function om_classes_order_contains_class_product($commerce_order) {
  if (!empty($commerce_order)) {
    $classes = om_classes_order_contains_class($commerce_order);
    if (!empty($classes)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Action handler to discount a class based on role or line item.
 */
function om_classes_discount($commerce_line_item) {
  if (!empty($commerce_line_item)) {
    $commerce_order = commerce_order_load($commerce_line_item->order_id);
    $line_item_meta = entity_metadata_wrapper('commerce_line_item', $commerce_line_item);
    $product = $line_item_meta->commerce_product->value();
    if ($product->type == 'membership_plan') {
      $unit_price = commerce_price_wrapper_value($line_item_meta, 'commerce_unit_price', TRUE);
      $current_membership_orders = om_membership_get_user_membership_orders($commerce_order);
      $current_membership_orders = $current_membership_orders[0];
      $current_memberships = om_membership_order_contains_membership($current_membership_orders);
      $current_memberships = array_pop($current_memberships);
      // Current membership
      $current_membership_metadata = entity_metadata_wrapper('commerce_product', $current_memberships);
      $current_membership_price = $current_membership_metadata->commerce_price->value();
      $exp = $current_membership_orders->created + ($current_membership_metadata->field_duration->value() * 31688800);
      $update_period = $exp - $current_membership_metadata->field_update_period->value() * 86400;
      $now = time();
      if ($now > $current_membership_orders->created && $now < $update_period) {
        // Membership in cart
        $product_metadata = entity_metadata_wrapper('commerce_product', $product);
        $product_price = $product_metadata->commerce_price->value();
        // Perform discount
        $difference = array(
          'amount' => -$current_membership_price['amount'],
          'currency_code' => $unit_price['currency_code'],
          'data' => array(),
        );
        $line_item_meta->commerce_unit_price->amount = $product_price['amount'] - $current_membership_price['amount'];;
        $line_item_meta->commerce_unit_price->data = commerce_price_component_add(
        $line_item_meta->commerce_unit_price->value(),
          'base_price',
          $difference,
          TRUE
        );
      }
    }
  }
}
