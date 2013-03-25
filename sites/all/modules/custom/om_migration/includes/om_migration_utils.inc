<?php

// create new membership for user
function om_migration_create_new_member($uid, $product_id, $start_date) {
  // grab array of membership product_id => role_id mappings
  $om_memrole = om_migration_role_product_relationships();
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
  om_migration_grant_user_role($uid, $om_memrole[$product_id]);
}

/**
 * @params: $uid, $role_id is the rid of the role
 */
function om_migration_grant_user_role($uid, $role_id) {
  // Save the user object with the new role.
  user_multiple_role_edit(array($uid), 'add_role', $role_id);
}
