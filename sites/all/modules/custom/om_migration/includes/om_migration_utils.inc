<?php

// create new membership for user
function om_migration_create_new_member($product_id, $uid, $start_date) {
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
  om_migration_grant_user_role($uid, $role);
}

/**
 * @params: $uid, $role is the rid of the role
 */
function om_migration_grant_user_role($uid, $role) {
  // Save the user object with the new role.
  user_multiple_role_edit(array($uid), 'add_role', $role);
}
