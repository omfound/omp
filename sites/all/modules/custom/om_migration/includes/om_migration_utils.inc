<?php

// create new membership for user
function om_migration_create_new_member($type, $user, $end_date) {
  global $user;
  $order = om_migration_create_new_order($user, $end_date);
  $line_iten = om_migration_create_line_item($type);
  om_migration_attach_line_item_order($order, $line_item);

  // TODO: do we need to save order??

  // now that the order is saved, we can grant the user this role
  om_migration_grant_user_role($user, $role);
}

function om_migration_create_new_order($user, $end_date) {
  global $user;
  $order = commerce_cart_order_new($user->uid);
  return $order;
}

function om_migration_create_line_item($type) {
  return $line_item;
}

function om_migration_attach_line_item_order($line_item, $order) {

}

/**
 * @params: global $user, $role is the rid of the role
 */
function om_migration_grant_user_role($user, $role) {
  global $user;
  // Save the user object with the new role.
  user_multiple_role_edit(array($user->uid), 'add_role', $role);
  // The following is if $role is the role name, eg Editor Membership
  //if ($role = user_role_load_by_name($role_name)) {
  //  user_multiple_role_edit(array($uid), 'add_role', $role->rid);
  //}
}
