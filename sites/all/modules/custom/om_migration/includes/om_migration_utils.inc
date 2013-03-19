<?php

// create new membership for user
function om_migration_create_new_member($type, $user, $start_date) {
  global $user;
  $order = om_migration_create_new_order($user, $start_date);
  $line_iten = om_migration_create_line_item($type);
  om_migration_attach_line_item_order($user, $line_item);

  // TODO: do we need to save order??

  // now that the order is saved, we can grant the user this role
  om_migration_grant_user_role($user, $role);
}

function om_migration_create_new_order($user, $start_date) {
  global $user;
  $order = commerce_order_new($user->uid);
  // not sure if you can do this or new a metadata_wrapper
  $order->created = $start_date;
  return $order;
}

function om_migration_create_line_item($type) {
  //$current_order = commerce_cart_order_load($user->uid);
  //$current_order_metadata = entity_metadata_wrapper('commerce_order', $current_order);
  //$current_line_items = $current_order_metadata->commerce_line_items->value();
  return $line_item;
}

function om_migrate_set_membership_dates($uid, $membership, $start_date, $end_date) {

}

function om_migration_attach_line_item_order($user, $line_item, $order) {
  global $user;
  // add line item to user's current order. If current order has line item
  // do not increment count of this line item.
  $line_item = commerce_cart_product_add($user->uid, $line_item, FALSE);
}

/**
 * @params: global $user, $role is the rid of the role
 */
function om_migration_grant_user_role($user, $role) {
  global $user;
  // Save the user object with the new role.
  user_multiple_role_edit(array($user->uid), 'add_role', $role);
}
