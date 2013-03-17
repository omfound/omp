<?php
/**
 * @file
 * commerce_reservations.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_reservations_default_rules_configuration() {
  $items = array();
  $items['rules_apply_reservation_price_by_day'] = entity_import('rules_config', '{ "rules_apply_reservation_price_by_day" : {
      "LABEL" : "Apply Reservation Price by Day",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_reservations", "commerce_product_reference" ],
      "ON" : [ "commerce_product_calculate_sell_price" ],
      "IF" : [
        { "commerce_reservations_charge_by_the_day_check" : { "lid" : [ "commerce-line-item:line-item-id" ] } }
      ],
      "DO" : [
        { "commerce_reservations_price_per_day" : {
            "commerce_line_item" : [ "commerce-line-item" ],
            "component_name" : "base_price",
            "round_mode" : "1"
          }
        }
      ]
    }
  }');
  return $items;
}
