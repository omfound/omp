<?php

/**
 * @file
 * Coupon pct rules integration file.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_coupon_pct_order_rules_action_info() {
  $actions = array();
  $actions['commerce_coupon_pct_order_apply_to_product_line_item'] = array(
    'label' => t('Apply a percentage coupon to the cheapest product line item'),
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
    'base' => 'commerce_coupon_pct_order_apply_to_product_line_item',
    'group' => t('Commerce Coupon'),
  );

  return $actions;
}

function commerce_coupon_pct_order_apply_to_product_line_item($line_item, $order, $coupon, $component_name, $round_mode) {
  $coupon_wrapper = entity_metadata_wrapper('commerce_coupon', $coupon);
  $fields = $coupon_wrapper->getPropertyInfo();
  // Apply the coupon just if it's active, the type is of pct and it has the
  // field for percentage set.
  if ($coupon->is_active == TRUE && $coupon->type == 'commerce_coupon_pct_order'
      && isset($fields['commerce_coupon_percent_amount']) && $coupon_wrapper->commerce_coupon_percent_amount->value() > 0) {
    $rate = $coupon_wrapper->commerce_coupon_percent_amount->value();
    if ($rate > 1) {
      // Ensure that the rate is never bigger then 100%
      $rate = $rate / 100;
    }
    else {
      return;
    }

    //need to get the type of the current line item
    //check if it is the highest value of its type in the order
    //if it is, apply the discount
    $primary_product = commerce_product_load($line_item->data['context']['product_ids'][0]);
    if (is_object($order)) {
      $order_metadata = entity_metadata_wrapper('commerce_order', $order);
      $line_items = $order_metadata->commerce_line_items->value();

      $most_expensive_match = array();
      foreach ($line_items as $key => $info) {
        $line_item_product = commerce_product_load($info->data['context']['product_ids'][0]);
        if ($line_item_product->type == $primary_product->type) {
          if (empty($most_expensive_match)) {
            $most_expensive_match = $line_item_product;
          }elseif($most_expensive_match->commerce_price[LANGUAGE_NONE][0]['amount'] < $line_item_product->commerce_price[LANGUAGE_NONE][0]['amount']) {
            $most_expensive_match = $line_item_product;
          }
        }
      }

      if ($most_expensive_match->product_id == $primary_product->product_id) {
        //we have a winner
        // Get the price component to use in this price.
        $price_component_name = $coupon_wrapper->price_component_name->value();

        $wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
        $unit_price = commerce_price_wrapper_value($wrapper, 'commerce_unit_price', TRUE);
        $amount = commerce_round($round_mode, $unit_price['amount'] * $rate);

        // Calculate the updated amount and create a price array representing the
        // difference between it and the current amount.
        $current_amount = $unit_price['amount'];
        $updated_amount = commerce_round($round_mode, $current_amount - $amount);

        $difference = array(
          'amount' => $updated_amount - $current_amount,
          'currency_code' => $unit_price['currency_code'],
          'data' => array(),
        );

        // Set the amount of the unit price and add the difference as a component.
        $wrapper->commerce_unit_price->amount = $updated_amount;

        $wrapper->commerce_unit_price->data = commerce_price_component_add(
            $wrapper->commerce_unit_price->value(), $price_component_name, $difference, TRUE
        );
      }
    }
  }
}
