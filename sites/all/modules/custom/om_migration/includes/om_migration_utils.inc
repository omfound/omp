<?php

function om_migration_civi_product_relationships() {
  return array(
    // programming membership
    4 => 1,
    // field
    6 => 3,
    // studio
    7 => 4,
    // editor to unlimited
    8 => 5,
    // unlimited
    9 => 5,
    // organizational np
    10 => 6,
    // organiztional
    12 => 6,
  );
}
/**
 * Create new membership for user.
 *
 * @param $uid user id
 * @param $product_id product id of membership
 * @param $start_date start date of membership in seconds
 */
function om_migration_create_new_member_order($uid, $product_id, $start_date) {
  // grab array of membership product_id => role_id mappings
  $om_memrole = om_migration_role_product_relationships();
  $order = commerce_order_new($uid);
  // save order to generate order_id
  commerce_order_save($order);
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $order->created = $start_date;
  $product = commerce_product_load($product_id);
  $line_item = commerce_product_line_item_new($product, 1, $order->order_id);
  commerce_line_item_save($line_item);
  $order_wrapper->commerce_line_items[] = $line_item;
  commerce_order_save($order);
  //commerce_order_complete($order);
  //commerce_order_rules_update_state($order,"Completed");
  commerce_order_status_update($order,"completed");

  // Now grant the user the role
  om_migration_grant_user_role($uid, $om_memrole[$product_id]);
}

/**
 * Grant role for a user.
 * @param $uid
 * @param $role_id is the rid of the role
 */
function om_migration_grant_user_role($uid, $role_id) {
  // Save the user object with the new role.
  user_multiple_role_edit(array($uid), 'add_role', $role_id);
}
/**
 * Returns array of memberships.
 * @return each entry array with @uid, @start_date, @membership_type
 */
function om_migration_get_civi_memberships() {
  $results = array();
  $map_civi_prod = om_migration_civi_product_relationships();
  $query = Database::getConnection('default', 'civi')
  ->select('civicrm_membership','cm');
  $query->join('civicrm_uf_match', 'ccum', 'cm.contact_id=ccum.contact_id');
  $query->condition('membership_type_id', array_keys($map_civi_prod), 'IN');
  $query->fields('cm', array('membership_type_id','start_date','end_date'))
  ->addField('ccum','uf_id','uid');
  // only grab memberships that are still active.
  $query->where(" cm.end_date > NOW() ");
  //$query->range(0,30);
  //dpq($query);
  $res = $query->execute();
  $one_year = 365*24*3600;
  foreach ($res as $rec) {
    //print "uid: ". $rec->uid ." start_date:". $rec->start_date . " product: " . $rec->membership_type_id . "\n";
    $start = strtotime($rec->start_date);
    $end = strtotime($rec->end_date);
    // make start whichever is latest: start or (end - one_year)
    // because in commerce all memberships have duration 1 year, but in civi the
    // start date was never updated when memberships were renewed, just the end
    // date.
    if ($start < $end - $one_year) {
      $start = $end - $one_year;
    }
    om_migration_create_new_member_order($rec->uid,$map_civi_prod[$rec->membership_type_id],$start);
    $results[] = array($rec->uid, $start, $rec->membership_type_id);
  }
  return $results;
}