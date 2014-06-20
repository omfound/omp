<?php

function om_membership_drush_command() {
  $items = array();
  $items['dom-membership-update'] = array(
    'description' => "Run membership update",
    'aliases' => array('dmu'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );
  return $items;
}

function drush_om_membership_dom_membership_update() {
  $users = om_membership_get_expired_memberships_enhanced();
  if (module_exists('rules')) {
    // Get expirees
    foreach ($users AS $user) {
      rules_invoke_event('om_membership_on_expiration', $user);
    }
    // Adjust any incorrect or outdated membership records.

    om_membership_expire_membership_roles($users);
    om_membership_add_membership_roles();
  }

  // Ensure that relationships between org member admins and subs are correct.
  om_membership_validate_all_org_sub_members();
  drush_log('Updating membership complete.', 'success');
}
