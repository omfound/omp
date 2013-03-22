<?php

// this should be in the module file instead
// map membership product_id => role_id
$om_memrole_map = array();
// programming membership
$om_memrole_map[1] = 5;
// field membership
$om_memrole_map[3] = 6;
// studio membership
$om_memrole_map[4] = 8;
// unlimited membership
$om_memrole_map[5] = 9;
// organizational membership
$om_memrole_map[6] = 10;


// create new membership for user
function om_migration_create_new_member($product_id, $uid, $start_date) {
  global $om_memrole_map;
  $order = commerce_order_new($uid);
  commerce_order_save($order);
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $order->created = $start_date;
  $product = commerce_product_load($product_id);
  $line_item = commerce_product_line_item_new($product, 1, $order->order_id);
  commerce_line_item_save($line_item);
  $order_wrapper->commerce_line_items[] = $line_item;
  commerce_order_save($order);

  // Now grant the user the role
  om_migration_grant_user_role($uid, $om_memrole_map[$product_id]);
}

/**
 * @params: $uid, $role is the rid of the role
 */
function om_migration_grant_user_role($uid, $role_id) {
  // Save the user object with the new role.
  user_multiple_role_edit(array($uid), 'add_role', $role_id);
}
