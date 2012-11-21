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
  return $items;
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
  return $actions;
}

/**
 * Upon order completion check to see if the order contains a membership_plan product.
 *   if so grant the proper user role and set the duration of the membership appropriately.
 */
function om_membership_grant_user_role($commerce_order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $commerce_order);
  $line_items = $order_wrapper->commerce_line_items->value();
  foreach ($line_items AS $line_item) {
    $line_item_meta = entity_metadata_wrapper('commerce_line_item', $line_item);
    $product = $line_item_meta->commerce_product->value();
    if ($product->type == 'membership_plan') {
      $membership_dates = om_membership_determine_membership_dates($product);
      $role = user_role_load($product->field_associated_role[LANGUAGE_NONE][0]['rid']);
      $order_user = user_load($commerce_order->uid);
      $order_user->roles[$role->rid] = $role->name;
      user_save($order_user);
      $admin_profile = profile2_by_uid_load($order_user->uid, 'membership_administration');
      // Here we could use a metadata wrapper to save the conenent
      // This would be the most clean and correct way to handle saving date fields.
      // However the date module's field implementation does not allow for this
      // Instead we get the follwing kludge.
      $admin_profile->field_membership_start[LANGUAGE_NONE][0]['value'] = date('Y-m-d G:i:s', $membership_dates['start']);
      $admin_profile->field_membership_end[LANGUAGE_NONE][0]['value'] = date('Y-m-d G:i:s', $membership_dates['end']);
      $admin_proifle->field_membership_type[LANGUAGE_NONE][0]['value'] = $role->name;
      profile2_save($admin_profile);
    }
  }
}
/**
 * Remove all membership roles from a user.
 */
function om_membership_remove_user_role($user) {
  $user_modified = FALSE;
  $membership_roles = om_membership_return_membership_roles();
  foreach ($user->roles AS $rid => $role) {
    if (!empty($membership_roles[$rid])) {
      $user_modified = TRUE;
      unset($user->roles[$rid]);
    }
  }
  if ($user_modified == TRUE) {
    user_save($user);
  }
}