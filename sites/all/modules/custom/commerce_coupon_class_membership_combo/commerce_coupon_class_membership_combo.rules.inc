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
  drupal_set_message("<pre>" . print_r($order, true) . "</pre>", 'notice');
  /*if ($coupon->is_active == TRUE && $coupon->type == 'commerce_coupon_combo') {
    $primary_product = commerce_product_load($line_item->data['context']['product_ids'][0]);
    // If the line item is a membership and matches the type designated by commerce_coupon_combo
    // or the line item is a class.
    if (($primary_product->type == 'membership' && $primary_product->product_id  == $coupon->field_coupon_membership[LANG_NONE][0]['value']) 
    || $primary_product->type == 'class') {
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
      $wrapper->commerce_unit_price->amount = $new_price;

      $wrapper->commerce_unit_price->data = commerce_price_component_add(
        $wrapper->commerce_unit_price->value(), $price_component_name, $difference, TRUE
      );
    }  
  }*/
}
