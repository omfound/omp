<?php

/**
 * Implements hook_rules_event_info
 */
function commerce_reservations_rules_event_info() {
  $items = array();
  // Provide an event for membership expiration.
  // Then any steps may be taken.
  $items['om_membership_reserve_product'] = array(
    'label' => t('When a user attempts to reserve a product'),
    'group' => 'Commerce Reservations',
    'variables' => array(
      'user' => array(
        'label' => t('User'),
        'type' => 'user',
        'skip save' => TRUE,
      ),
      'product_display' => array(
        'label' => t('Product Display'),
        'type' => 'node',
        'skip save' => TRUE,
        'bundle' => 'reservable_product_display',
      ),
      'product' => array(
        'label' => t('Product'),
        'type' => 'commerce_product',
        'skip save' => TRUE,
      ),
    )
  );

  return $items;
}

/**
 * Implements hook_rules_action_info
 */
function commerce_reservations_rules_action_info() {
  $actions = array();

  // Prepare an array of arithmetical actions for altering prices.
  $action_types = array(
    'commerce_reservations_price_per_hour' => array(
      'label' => t('Multiply price by hour'),
    ),
    'commerce_reservations_price_per_day' => array(
      'label' => t('Multiply price by day'),
    ),
    'commerce_reservations_price_reduction' => array(
      'label' => t('Reduce price by days or hours specified on product'),
    ),
    'commerce_reservations_discount_by_day' => array(
      'label' => t('Remove days from reservations cost calculation'),
    ),
  );

  // Define the action using a common set of parameters.
  foreach ($action_types as $key => $value) {
    $actions[$key] = array(
      'label' => $value['label'],
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
        )
      ),
      'group' => t('Commerce Reservations Rules'),
    );
  }

  $actions['commerce_reservations_discount_by_day']['parameter']['day'] = array(
    'type' => 'text',
    'label' => t('Day'),
  ); 
  $actions['commerce_reservations_update_checkout_status'] = array(
    'label' => t('Set all reservable line items to specific status'),
    'group' => t('Commerce Reservations Rules'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce Order'),
        'description' => t('All reservations on this order will have their status changed.'),
      ),
      'reservation_state' => array(
        'type' => 'list<text>',
        'label' => t('Reservation Status'),
        'description' => t('Reservations will be set to this status.'),
        'options list' => 'commerce_reservations_status_options',
      ),
    ),
  );

  $actions['commerce_reservations_separate_quantity'] = array(
    'label' => t('Separate line items with quantity > 1 into multiple line items.'),
    'group' => t('Commerce Reservations Rules'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce Order'),
        'description' => t('All reservation line items with quantity > 1 will be separated into multiple line items.'),
      ),
    ),
  );

  $actions['commerce_reservations_deny_product_access'] = array(
    'label' => t('Deny access to a particular product'),
    'group' => t('Commerce Reservations Rules'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User'),
        'description' => t('User attempting to make the reservation'),
      ),
      'product_display' => array(
        'type' => 'node',
        'bundle' => 'reservable_product_display',
        'description' => t('Product display for the item being reserved'),
      ),
      'product' => array(
        'type' => 'commerce_product',
        'description' => t('Product being reserved'),
      ),
      'message' => array(
        'type' => 'text',
        'label' => t('Denial message'),
        'description' => t('This message will be displayed to the user to explain why they cannot access the product.'),
      ),
    ),
  );

  return $actions;
}

function commerce_reservations_separate_quantity($order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

  foreach ($order->commerce_line_items['und'] as $key => $info) {
    $line_item_ids[$info['line_item_id']] = $info['line_item_id'];
  } 
  $line_items = commerce_line_item_load_multiple($line_item_ids);

  foreach ($line_items as $line_item_id => $line_item) {
    if ($line_item->type == 'reservable_product') {
      if ($line_item->quantity > 1) {
        $clone_count = $line_item->quantity - 1;
        $counter = 1;
        while ($counter <= $clone_count) {
          //build a new line item by cloning existing and changing product
          $new_line_item = clone $line_item;
          $new_line_item->line_item_id = null;
          $new_line_item->is_new = TRUE; 
          $new_line_item->quantity = 1;

          commerce_line_item_save($new_line_item);
          $order_wrapper->commerce_line_items[] = $new_line_item;
          $counter++;
        }

        $line_item->quantity = 1;
        commerce_line_item_save($line_item);
        commerce_order_save($order);
      }
    }
  }
}

function commerce_reservations_update_checkout_status($order, $reservation_state) {
  $reservation_state = reset($reservation_state);
  $line_item_ids = array();
  foreach ($order->commerce_line_items['und'] as $key => $info) {
    $line_item_ids[$info['line_item_id']] = $info['line_item_id'];
  } 
  $line_items = commerce_line_item_load_multiple($line_item_ids);

  foreach ($line_items as $line_item_id => $line_item) {
    if ($line_item->type == 'reservable_product') {
      $line_item->field_checkout_status['und'][0]['value'] = $reservation_state;
      commerce_line_item_save($line_item);
    }
  }
}

function commerce_reservations_price_per_hour($line_item, $component_name, $round_mode){
  
  //First check to make sure the product is a reservable product
  $product = commerce_product_load($line_item->commerce_product['und'][0]['product_id']);
  if ($product->type != 'reservable_product') {
    return;
  }
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
  $unit_price = commerce_price_wrapper_value($line_item_wrapper, 'commerce_unit_price', TRUE);
  
  if (property_exists($line_item, "field_reservation_dates")){
    $start = strtotime($line_item->field_reservation_dates['und'][0]["value"]);
    $end = strtotime($line_item->field_reservation_dates['und'][0]["value2"]);
    $hours_days = commerce_reservations_hours_days($start, $end);
    $rate = $product->commerce_price['und'][0]['amount'];
    $updated_price = $hours_days['hours'] * $rate;
    $current_amount = $unit_price['amount'];
    $difference = array(
      'amount' => $updated_price - $current_amount,
      'currency_code' => $unit_price['currency_code'],
      'data' => array(),
    );
   
    // Set the amount of the unit price and add the difference as a component.
    $line_item_wrapper->commerce_unit_price->amount = $updated_price;
    
    $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add(
      $line_item_wrapper->commerce_unit_price->value(),
      $component_name,
      $difference,
      TRUE
    );
  }
}

function commerce_reservations_price_per_day($line_item, $component_name, $round_mode){
  
  //First check to make sure the product is a reservable product
  $product = commerce_product_load($line_item->commerce_product['und'][0]['product_id']);
  if ($product->type != 'reservable_product') {
    return;
  }
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
  $unit_price = commerce_price_wrapper_value($line_item_wrapper, 'commerce_unit_price', TRUE);
  
  if (property_exists($line_item, "field_reservation_dates")){
    $start = strtotime($line_item->field_reservation_dates['und'][0]["value"]);
    $end = strtotime($line_item->field_reservation_dates['und'][0]["value2"]);
    $hours_days = commerce_reservations_hours_days($start, $end);
    $hourly_rate = $product->commerce_price['und'][0]['amount'] / 8; 
    $day_rate = $product->commerce_price['und'][0]['amount'];
    
    $day_cost = $hours_days['days']*$day_rate;
    if ($hours_days['hours'] > 24) {
      if ($hours_days['remainder_hours'] < 8) {
        $hour_cost = $hours_days['remainder_hours']*$hourly_rate;
      }else{
        $hour_cost = $day_rate;
      }
    }

    if (!empty($hour_cost)) {
      $updated_price = $day_cost + $hour_cost;
    }else{
      $updated_price = $day_cost;
    }

    $current_amount = $unit_price['amount'];
    $difference = array(
      'amount' => $updated_price - $current_amount,
      'currency_code' => $unit_price['currency_code'],
      'data' => array(),
    );
   
    // Set the amount of the unit price and add the difference as a component.
    $line_item_wrapper->commerce_unit_price->amount = $updated_price;
    
    $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add(
      $line_item_wrapper->commerce_unit_price->value(),
      $component_name,
      $difference,
      TRUE
    );
  }
}

function commerce_reservations_price_reduction($line_item, $component_name, $round_mode) {
  $product = commerce_product_load($line_item->commerce_product['und'][0]['product_id']);
  if (empty($product->field_charge_by_the_['und'][0]['value']) || $product->type != 'reservable_product' || empty($product->field_hours_days_free_for_member['und'][0]['value'])) {
    return;
  }

  if (empty($line_item->field_reservation_dates['und'][0]["value"]) || empty($line_item->field_reservation_dates['und'][0]["value2"])) {
    return;
  }
  $start = strtotime($line_item->field_reservation_dates['und'][0]["value"]);
  $end = strtotime($line_item->field_reservation_dates['und'][0]["value2"]);
  $hours_days = commerce_reservations_hours_days($start, $end);
  if ($hours_days['hours']) { 
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
    $unit_price = commerce_price_wrapper_value($line_item_wrapper, 'commerce_unit_price', TRUE);
    $free_hours = $product->field_hours_days_free_for_member['und'][0]['value'];

    if ($product->field_charge_by_the_['und'][0]['value'] == 'day') {
      $hourly_rate = $product->commerce_price['und'][0]['amount'] / 8; 
    }elseif ($product->field_charge_by_the_['und'][0]['value'] == 'hour') {
      $hourly_rate = $product->commerce_price['und'][0]['amount'];
    }else {
      return;
    }

    //if more than 1 day, discount by 1 day
    if ($free_hours >= $hours_days['hours']) {
      //reduce to zero cost if the hours provided are great than the order hours
      $new_price = 0; 
      $price_difference = $new_price - $unit_price['amount'];
    }
    else {
      if ($product->field_charge_by_the_['und'][0]['value'] == 'hour') {
        $new_price = $unit_price['amount'] - ($free_hours*$hourly_rate);
        $price_difference = $new_price - $unit_price['amount'];
      }elseif ($product->field_charge_by_the_['und'][0]['value'] == 'day') {
        if ($unit_price['amount'] <= $product->commerce_price['und'][0]['amount']) {
          $new_price = 0;
        }else{
          $new_price = $unit_price['amount'] - $product->commerce_price['und'][0]['amount'];
        }
        if ($new_price < 0) { $new_price = 0; }
        $price_difference = $new_price - $unit_price['amount'];
      }
    }
    $difference = array(
      'amount' => $price_difference,
      'currency_code' => $unit_price['currency_code'],
      'data' => array(),
    );

    // Set the amount of the unit price and add the difference as a component.
    $line_item_wrapper->commerce_unit_price->amount = $new_price;
    
    $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add(
      $line_item_wrapper->commerce_unit_price->value(),
      $component_name,
      $difference,
      TRUE
    );

  }
}

function commerce_reservations_discount_by_day($line_item, $component_name, $round_mode, $day){
  $day = strtolower($day);
  $product = commerce_product_load($line_item->commerce_product['und'][0]['product_id']);
  if (empty($product->field_charge_by_the_['und'][0]['value']) || $product->type != 'reservable_product' || empty($product->field_hours_days_free_for_member['und'][0]['value'])) {
    return;
  }

  if (empty($line_item->field_reservation_dates['und'][0]["value"]) || empty($line_item->field_reservation_dates['und'][0]["value2"])) {
    return;
  }
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
  $unit_price = commerce_price_wrapper_value($line_item_wrapper, 'commerce_unit_price', TRUE);
  $start = strtotime($line_item->field_reservation_dates['und'][0]["value"].' UTC');
  $end = strtotime($line_item->field_reservation_dates['und'][0]["value2"].' UTC');
  $current_date = $start;
  $deduct_hours = 0;
  $deduct_days = 0;
  while($current_date < $end) {
    $res_day = strtolower(date('l', $current_date)); 
    if ($res_day == $day) {
      $deduct_days = $deduct_days + 1;
    }
    $current_date = $current_date + (24*60*60);
  }
  if (!empty($deduct_days) && $deduct_days > 0) {
    if ($product->field_charge_by_the_['und'][0]['value'] == 'hour') {
      $new_price = $unit_price['amount'] - ($deduct_hours * 24 * $product->commerce_price['und'][0]['amount']);
    }
    elseif ($product->field_charge_by_the_['und'][0]['value'] == 'day') {
      $new_price = $unit_price['amount'] - ($product->commerce_price['und'][0]['amount']*$deduct_days);
    }
    if ($new_price < 0) { $new_price = 0; }
    $price_difference = $new_price - $unit_price['amount'];

    $difference = array(
      'amount' => $price_difference,
      'currency_code' => $unit_price['currency_code'],
      'data' => array(),
    );

    // Set the amount of the unit price and add the difference as a component.
    $line_item_wrapper->commerce_unit_price->amount = $new_price;
  
    $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add(
      $line_item_wrapper->commerce_unit_price->value(),
      $component_name,
      $difference,
      TRUE
    );
  }
}

function commerce_reservations_deny_product_access($user, $product_display, $product, $message) {
  dsm('setting denial message');
  watchdog('brian', 'setting denial message');
  $product_display->user_access = false;
  $product_display->user_access_message = $message;
}
