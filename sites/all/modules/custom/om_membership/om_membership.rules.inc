<?php

/**
 * Implements hook_rules_event_info
 */
function om_membership_rules_event_info() {
  $items = array();
  // Provide an event for membership expiration.
  // Then any steps may be taken.
  $items['om_membership_on_expiration'] = array(
    'label' => t('When a Membership Expires'),
    'group' => 'Open Media Membership',
    'variables' => array(
      'user' => array(
        'label' => t('Expired User'),
        'type' => 'user',
        'skip save' => TRUE,
      ),
    )
  );
  $items['om_membership_new_org_sub_member'] = array(
    'label' => t('When Creating Org Sub-Members'),
    'group' => 'Open Media Membership',
    'variables' => array(
      'new_org_user' => array(
        'label' => t('New User granted org membership'),
        'type' => 'user',
        'skip save' => TRUE,
      ),
    )
  );
  $items['om_membership_add_org_membership_existing_user'] = array(
    'label' => t('When Adding an Org Membership to Existing Users'),
    'group' => 'Open Media Membership',
    'variables' => array(
      'existing_org_user' => array(
        'label' => t('Existing user granted org membership'),
        'type' => 'user',
        'skip save' => TRUE,
      ),
    )
  );
  return $items;
}

/**
 * Implements hook_rules_condition_info
 */
function om_membership_rules_condition_info() {
  return array(
    'om_membership_order_contains_membership_product' => array(
      'label' => t('Order contains a membership'),
      'arguments' => array(
        'commerce_order' => array('label' => t('Commerce Order'), 'type' => 'commerce_order'),
      ),
      'help' => t('Does the order contain a membership.'),
      'module' => 'om_membership',
      'group' => 'Open Media Membership'
    ),
    'om_membership_order_contains_upsell' => array(
      'label' => t('Order contains an upsold membership'),
      'arguments' => array(
        'commerce_order' => array('label' => t('Commerce Order'), 'type' => 'commerce_order'),
      ),
      'help' => t('Does the order trigger a membership upsell.'),
      'module' => 'om_membership',
      'group' => 'Open Media Membership'
    ),
    'om_membership_order_contains_paid_membership_product' => array(
      'label' => t('Order contains a paid membership'),
      'arguments' => array(
        'commerce_order' => array('label' => t('Commerce Order'), 'type' => 'commerce_order'),
      ),
      'help' => t('Does the order contain a paid membership.'),
      'module' => 'om_membership',
      'group' => 'Open Media Membership'
    ),
    'om_membership_user_has_membership' => array(
      'label' => t('Order user has a current membership'),
      'arguments' => array(
        'commerce_order' => array('label' => t('Commerce Order'), 'type' => 'commerce_order'),
      ),
      'help' => t('Does the user creating the order have a membership.'),
      'module' => 'om_membership',
      'group' => 'Open Media Membership'
    ),
    'om_membership_user_has_paid_membership' => array(
      'label' => t('Order user has a current paid membership'),
      'arguments' => array(
        'commerce_order' => array('label' => t('Commerce Order'), 'type' => 'commerce_order'),
      ),
      'help' => t('Does the user creating the order have a paid membership.'),
      'module' => 'om_membership',
      'group' => 'Open Media Membership'
    ),
  );
}

/**
 * Implements hook_rules_action_info
 */
function om_membership_rules_action_info() {
  $actions = array();
  $actions['om_membership_grant_user_role'] = array(
    'label' => t('Grant User Role From Product'),
    'group' => 'Open Media Membership',
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce Order'),
      )
    )
  );
  $actions['om_membership_remove_user_role'] = array(
    'label' => t('Remove Membership User Role'),
    'group' => 'Open Media Membership',
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User Object'),
      )
    )
  );
  $actions['om_membership_upsell_discount'] = array(
    'label' => t('Discount membership by current membership difference'),
    'group' => 'Open Media Membership',
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
 * Condition handler that check to see if an order contains a membership line item.
 */
function om_membership_order_contains_membership_product($commerce_order) {
  if (!empty($commerce_order)) {
    $membership = om_membership_order_contains_membership($commerce_order);
    if (!empty($membership)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Condition handler that check to see if an order contains a membership line item.
 */
function om_membership_order_contains_paid_membership_product($commerce_order) {
  if (!empty($commerce_order)) {
    $membership = om_membership_order_contains_membership($commerce_order, true);
    if (!empty($membership)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Condition handler that check to see if an order contains a membership line item.
 */
function om_membership_user_has_membership($commerce_order) {
  if (!empty($commerce_order)) {
    global $user;
    $membership = om_membership_user_memberships($user);
    if (!empty($membership)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Condition handler that check to see if an order contains a membership line item.
 */
function om_membership_user_has_paid_membership($commerce_order) {
  if (!empty($commerce_order)) {
    global $user;
    $membership = om_membership_user_memberships($user, true);
    if (!empty($membership)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Condition handler that checks to see if an order contains a membership upsell.
 */
function om_membership_order_contains_upsell($commerce_order) {
  if (!empty($commerce_order)) {
    // See if there is a membership in the order at all... if not don't go any further.
    $products = om_membership_order_contains_membership($commerce_order);
    if (!empty($products)) {
      // Get the user's current membership level
      $current_memberships = om_membership_get_user_membership_products($commerce_order);
      if (!empty($current_memberships)) {
        // NB not sure what end of this array we should take off of.
        $current_memberships = array_pop($current_memberships);
        $current_membership_metadata = entity_metadata_wrapper('commerce_product', $current_memberships);
        $current_membership_price = $current_membership_metadata->commerce_price->value();
        $product = array_shift($products);
        $product_metadata = entity_metadata_wrapper('commerce_product', $product);
        $product_price = $product_metadata->commerce_price->value();
        // If the user's current membership is cheaper than the one in the cart return TRUE
        if ($current_membership_price['amount'] <= $product_price['amount']) {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

/**
 * Action handler to discount a product in an upsell situation.
 */
function om_membership_upsell_discount($commerce_line_item) {
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
        $line_item_meta->commerce_unit_price->amount = $product_price['amount'] - $current_membership_price['amount'];
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
