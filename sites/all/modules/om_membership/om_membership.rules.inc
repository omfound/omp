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
      'user' => array(
        'label' => t('New User'),
        'type' => 'user',
        'skip save' => TRUE,
      ),
    )
  );
  $items['om_membership_add_org_membership_existing_user'] = array(
    'label' => t('When Adding an Org Membership to Existing Users'),
    'group' => 'Open Media Membership',
    'variables' => array(
      'user' => array(
        'label' => t('User'),
        'type' => 'user',
        'skip save' => TRUE,
      ),
    )
  );
  return $items;
}

function om_membership_rules_condition_info() {
  return array(
    'om_membership_order_contains_upsell' => array(
      'label' => t('Order is donation'),
      'arguments' => array(
        'order_id' => array('label' => t('Order Id'), 'type' => 'integer'),
      ),
      'help' => t('Does the order trigger a membership upsell.'),
      'module' => 'om_membership',
      'group' => 'Open Media Membership'
    )
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
    'label' => t('Discount membership by current membership difference.'),
    'group' => 'Open Media Membership',
    'parameter' => array(
      'commerce_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line Item'),
      ),
      'user' => array(
        'type' => 'user',
        'label' => t('Order User'),
      )
    )
  );
  return $actions;
}

function om_membership_order_contains_upsell($order) {
  
}

function om_membership_upsell_discount($line_item, $user) {
  
}