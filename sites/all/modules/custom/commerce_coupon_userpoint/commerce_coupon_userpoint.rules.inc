<?php

/**
 * Implements hook_rules_action_info().
 */
function commerce_coupon_userpoint_rules_action_info() {
  $actions = array();

  $actions['commerce_coupon_action_create_up_coupon_line_item'] = array(
    'label' => t('Create user points coupon line item'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Commerce Coupon'),
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('commerce order'),
      ),
      'amount' => array(
        'type' => 'decimal',
        'label' => t('coupon amount'),
      ),
      'component_name' => array(
        'type' => 'text',
        'label' => t('Price component type'),
        'description' => t('Price components track changes to prices made during the price calculation process, and they are carried over from the unit price to the total price of a line item. When an order total is calculated, it combines all the components of every line item on the order. When the unit price is altered by this action, the selected type of price component will be added to its data array and reflected in the order total display when it is formatted with components showing. Defaults to base price, which displays as the order Subtotal.'),
        'options list' => 'commerce_price_component_titles',
        'default value' => 'base_price',
      ),
      'currency_code' => array(
        'type' => 'text',
        'label' => t('coupon amount currency code'),
      ),
    ),
    'provides' => array(
      'commerce_coupon_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('commerce coupon line item'),
      ),
    ),
    'group' => t('Commerce Coupon'),
    'base' => 'commerce_coupon_action_create_up_coupon_line_item',
    'callbacks' => array(
      'execute' => 'commerce_coupon_action_create_up_coupon_line_item',
    ),
  );
  
  return $actions;
}

function commerce_coupon_action_create_up_coupon_line_item($coupon, $commerce_order, $amount, $component_name, $currency_code) {
  if ($coupon->type == 'commerce_coupon_userpoint') {
    dsm('coupon firing...');
    dsm($coupon);
    if (!($commerce_order instanceof EntityMetadataWrapper)) {
      $commerce_order = entity_metadata_wrapper('commerce_order', $commerce_order);
    }

    $line_item = commerce_coupon_line_item_new($coupon, $commerce_order->order_id->raw());
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);

    // Set the unit price on the line item object.
    $line_item_wrapper->commerce_unit_price->amount = $amount * -1;
    $line_item_wrapper->commerce_unit_price->currency_code = $currency_code;

    // Add the base price to the components array.
    if ($coupon->is_active && !commerce_price_component_load($line_item_wrapper->commerce_unit_price->value(), $component_name)) {
      $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add(
        $line_item_wrapper->commerce_unit_price->value(), $component_name, $line_item_wrapper->commerce_unit_price->value(), TRUE, FALSE
      );
    }

    commerce_line_item_save($line_item);
    dsm($line_item);

    $commerce_order->commerce_line_items[] = $line_item;

    return array('commerce_coupon_line_item' => $line_item);
  }
}

