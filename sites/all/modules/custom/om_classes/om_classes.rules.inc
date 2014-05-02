<?php

/**
 * Implements hook_rules_action_info
 */
function om_classes_rules_action_info() {
  $action_types = array();
  $action_types['om_classes_discount'] = array(
    'label' => t('Discount class based on membership rate.'),
    'group' => 'Open Media Classes',
    'amount description' => t('Discount class line items to membership rate specified on class product.'),
  );

  // Define the action using a common set of parameters.
  foreach ($action_types as $key => $value) {
    $actions[$key] = array(
      'label' => $value['label'],
      'group' => $value['group'],
      'parameter' => array(
        'commerce_line_item' => array(
          'type' => 'commerce_line_item',
          'label' => t('Line item'),
        ),
        'component_name' => array(
          'type' => 'text',
          'label' => t('Price component type'),
          'description' => t('Price components track changes to prices made during the price calculation process, and they are carried over from the unit price to the total price of a line item. When an order total is calculated, it combines all the components of every line item on the order. When the unit price is altered by this action, the selected type of price component will be added to its data array and reflected in the order total display when it is formatted with components showing. Defaults to base price, which displays as the order Subtotal.'),
          'options list' => 'commerce_line_item_price_component_options_list',
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
    );
  }

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
 * Action handler to discount a class based on membership rate.
 */
function om_classes_discount($commerce_line_item, $component_name, $round_mode) {
  if (!empty($commerce_line_item)) {
    $commerce_order = commerce_order_load($commerce_line_item->order_id);
    $line_item_meta = entity_metadata_wrapper('commerce_line_item', $commerce_line_item);
    $unit_price = commerce_price_wrapper_value($line_item_meta, 'commerce_unit_price', TRUE);
    $current_price = $unit_price['amount'];

    $product = $line_item_meta->commerce_product->value();
    if ($product->field_class_member_price[LANGUAGE_NONE][0]['value']) {
      $updated_price = $product->field_class_member_price[LANGUAGE_NONE][0]['value'] * 100;
    }
    else {
      $updated_price = $current_price;
    }

    $discounted_price = array(
      'amount' => $updated_price - $current_price,
      'currency_code' => $unit_price['currency_code'],
      'data' => array(), 
    );

    $line_item_meta->commerce_unit_price->amount = $updated_price;
    $line_item_meta->commerce_unit_price->data = commerce_price_component_add(
      $line_item_meta->commerce_unit_price->value(), 
      $component_name,
      $discounted_price, 
      TRUE
    );
  }
}
