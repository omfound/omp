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
  $items['rules_apply_commercial_reservation_pricing'] = entity_import('rules_config', '{ "rules_apply_commercial_reservation_pricing" : {
      "LABEL" : "Apply Commercial Reservation Pricing",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_reservations", "commerce_product_reference" ],
      "ON" : [ "commerce_product_calculate_sell_price" ],
      "IF" : [
        { "commerce_reservations_product_type_check" : { "order_id" : [ "commerce-line-item:order-id" ] } },
        { "commerce_reservations_commercial_check" : { "order_id" : [ "commerce-line-item:line-item-id" ] } }
      ],
      "DO" : [
        { "commerce_reservations_commercial_price_per_day" : {
            "commerce_line_item" : [ "commerce_line_item" ],
            "component_name" : "base_price",
            "round_mode" : "0"
          }
        }
      ]
    }
  }');
  $items['rules_apply_reservation_pricing'] = entity_import('rules_config', '{ "rules_apply_reservation_pricing" : {
      "LABEL" : "Apply Member Reservation Pricing",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_reservations", "commerce_product_reference" ],
      "ON" : [ "commerce_product_calculate_sell_price" ],
      "IF" : [
        { "commerce_reservations_product_type_check" : { "order_id" : [ "commerce-line-item:order-id" ] } }
      ],
      "DO" : [
        { "commerce_reservations_member_price_per_day" : {
            "commerce_line_item" : [ "commerce_line_item" ],
            "component_name" : "base_price",
            "round_mode" : "1"
          }
        }
      ]
    }
  }');
  $items['rules_send_reservation_confirmation_email'] = entity_import('rules_config', '{ "rules_send_reservation_confirmation_email" : {
      "LABEL" : "Send Reservation Confirmation Email",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_reservations", "commerce_checkout" ],
      "ON" : [ "commerce_checkout_complete" ],
      "IF" : [
        { "commerce_reservations_product_type_check" : { "order_id" : [ "commerce-order:order-id" ] } }
      ],
      "DO" : [
        { "commerce_reservations_email_confirmation" : {
            "commerce_line_item" : [ "commerce-order:commerce-line-items:0" ],
            "component_name" : "base_price",
            "round_mode" : "1"
          }
        }
      ]
    }
  }');
  return $items;
}
