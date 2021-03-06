<?php

/**
 * @file
 * Coupon pct rules integration file.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_coupon_class_membership_combo_rules_action_info() {
  $actions = array();
  $actions['commerce_coupon_class_membership_combo_apply_discount'] = array(
    'label' => t('Apply a member discount to applicable line items'),
    'parameter' => array(
      'line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce Order'),
      ),
      'coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
      ),
      'component_name' => array(
        'type' => 'text',
        'label' => t('Price component type'),
        'description' => t('Price components track changes to prices made during the price calculation process, and they are carried over from the unit price to the total price of a line item. When an order total is calculated, it combines all the components of every line item on the order. When the unit price is altered by this action, the selected type of price component will be added to its data array and reflected in the order total display when it is formatted with components showing. Defaults to base price, which displays as the order Subtotal.'),
        'options list' => 'commerce_price_component_titles',
        'default value' => 'base_price',
      ),
      'round_mode' => array(
        'type' => 'integer',
        'label' => t('Price rounding mode'),
        'description' => t('Round the resulting price amount after performing this operation.'),
        'options list' => 'commerce_round_mode_options_list',
        'default value' => COMMERCE_ROUND_HALF_UP,
      ),
    ),
    'base' => 'commerce_coupon_class_membership_combo_apply_discount',
    'group' => t('Commerce Coupon'),
  );

  return $actions;
}

function commerce_coupon_class_membership_combo_apply_discount($line_item, $order, $coupon, $component_name, $round_mode) {
  $coupon_wrapper = entity_metadata_wrapper('commerce_coupon', $coupon);
  $fields = $coupon_wrapper->getPropertyInfo();
  // If coupon is type commerce_coupon_combo
  if ($coupon->is_active == TRUE && $coupon->type == 'commerce_coupon_combo' && is_object($line_item)) {
    $primary_product = commerce_product_load($line_item->commerce_product[LANGUAGE_NONE][0]['product_id']);
    $is_maxed = _commerce_coupon_class_membership_combo_order_is_maxed($coupon);
    // If the line item is a membership and matches the type designated by commerce_coupon_combo
    // or the line item is a class.
    if ($is_maxed == FALSE
    && (($primary_product->type == 'membership_plan' && $primary_product->product_id  == $coupon->field_coupon_membership[LANGUAGE_NONE][0]['value']) 
    || $primary_product->type == 'class')) {
      $wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
      $unit_price = commerce_price_wrapper_value($wrapper, 'commerce_unit_price', TRUE);
      $new_price = -1 * $unit_price['amount'];
      // Get the price component to use in this price.
      $price_component_name = $coupon_wrapper->price_component_name->value();
      $difference = array(
        'amount' => $new_price,
        'currency_code' => $unit_price['currency_code'],
        'data' => array(),
      );
      // Set the amount of the unit price and add the difference as a component.
      $wrapper->commerce_unit_price->amount = 0;

      $wrapper->commerce_unit_price->data = commerce_price_component_add(
        $wrapper->commerce_unit_price->value(), $price_component_name, $difference, TRUE
      );
      _commerce_coupon_class_membership_combo_static_cache_discount($primary_product->type);
    }  
  }
}

function _commerce_coupon_class_membership_combo_order_is_maxed($coupon) {
  $order_cache = _commerce_coupon_class_membership_combo_static_cache_discount();
  if (!empty($order_cache['membership_plan']) && !empty($order_cache['class']) && $order_cache['class'] >= $coupon->coupon_class_count[LANGUAGE_NONE][0]['value']) {
    return TRUE;
  }
  return FALSE;
}

function _commerce_coupon_class_membership_combo_static_cache_discount($discount = '') {
  $static_cache = &drupal_static(__FUNCTION__);
  if (!isset($static_cache)) {
    $static_cache = array();
  }
  if (!empty($discount)) {
    $static_cache[$discount] = !empty($static_cache[$discount]) ? $static_cache[$discount] : 0;
    $static_cache[$discount] ++;
  }
  return $static_cache;
}
