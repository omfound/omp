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