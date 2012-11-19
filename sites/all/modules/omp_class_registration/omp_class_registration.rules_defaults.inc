<?php
/**
 * @file
 * omp_class_registration.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function omp_class_registration_default_rules_configuration() {
  $items = array();
  $items['rules_assign_role_registrant_to_user'] = entity_import('rules_config', '{ "rules_assign_role_registrant_to_user" : {
      "LABEL" : "Assign Role \\u0022Registrant\\u0022 to user",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_conditions", "rules", "commerce_checkout" ],
      "ON" : [ "commerce_checkout_complete" ],
      "IF" : [
        { "commerce_conditions_compare_total_product_type_quantity" : {
            "commerce_order" : [ "commerce_order" ],
            "product_type" : "omp_class_session",
            "exclude" : 0,
            "operator" : "\\u003E=",
            "value" : "1"
          }
        }
      ],
      "DO" : [
        { "user_add_role" : {
            "account" : [ "commerce-order:owner" ],
            "roles" : { "value" : { "13" : "13" } }
          }
        }
      ]
    }
  }');
  $items['rules_class_registration_confirmation'] = entity_import('rules_config', '{ "rules_class_registration_confirmation" : {
      "LABEL" : "Class registration confirmation",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_conditions", "rules", "commerce_checkout" ],
      "ON" : [ "commerce_checkout_complete" ],
      "IF" : [
        { "commerce_conditions_compare_total_product_type_quantity" : {
            "commerce_order" : [ "commerce_order" ],
            "product_type" : "omp_class_session",
            "exclude" : 0,
            "operator" : "\\u003E=",
            "value" : "1"
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "commerce-order:owner:mail" ],
            "subject" : "Thank you for joining the class.",
            "message" : "Your have joined class session.\\r\\nTo review classes time-table, please follow this link:\\r\\n[site:url]\\/calendar-field-class-session-date\\/month\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_class_session_product_checkout'] = entity_import('rules_config', '{ "rules_class_session_product_checkout" : {
      "LABEL" : "Class Session Product Checkout",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "data_is" : { "data" : [ "commerce-product:type" ], "value" : "omp_class_session" } }
      ],
      "DO" : [ { "redirect" : { "url" : "checkout" } } ]
    }
  }');
  $items['rules_creating_class_display_after_class_session_is_added'] = entity_import('rules_config', '{ "rules_creating_class_display_after_class_session_is_added" : {
      "LABEL" : "Creating Class Display after Class Session is added",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : [ "commerce_product_insert", "commerce_product_update" ],
      "IF" : [
        { "data_is" : { "data" : [ "commerce-product:type" ], "value" : "omp_class_session" } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "omp_class_display",
              "param_title" : [ "commerce-product:title" ],
              "param_author" : [ "commerce-product:creator" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-create-new-like-this:url" ],
            "value" : "admin\\/commerce\\/products\\/add\\/omp-class-session\\/[commerce-product:product-id]"
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-product-reference" ],
            "value" : [ "commerce-product" ]
          }
        }
      ]
    }
  }');
  $items['rules_duplicate_class_session_products_check'] = entity_import('rules_config', '{ "rules_duplicate_class_session_products_check" : {
      "LABEL" : "Duplicate class session products check",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_conditions", "rules", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "commerce_conditions_compare_total_product_type_quantity" : {
            "commerce_order" : [ "commerce_order" ],
            "product_type" : "omp_class_session",
            "exclude" : 0,
            "operator" : "\\u003E",
            "value" : "1"
          }
        }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "commerce-line-item:quantity" ], "value" : "1" } },
        { "drupal_message" : {
            "message" : "There is already one Class Session in your cart.",
            "type" : "warning"
          }
        }
      ]
    }
  }');
  $items['rules_earned_certifications_check'] = entity_import('rules_config', '{ "rules_earned_certifications_check" : {
      "LABEL" : "Earned Certifications Check",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "AND" : [
            { "data_is" : { "data" : [ "commerce-product:type" ], "value" : "omp_class_session" } },
            { "OR" : [
                { "NOT list_contains" : {
                    "list" : [ "commerce-order:owner:field-cert-earned" ],
                    "item" : [ "commerce-product:field-cert-prerequisites:0" ]
                  }
                },
                { "NOT list_contains" : {
                    "list" : [ "commerce-order:owner:field-cert-earned" ],
                    "item" : [ "commerce-product:field-cert-prerequisites:1" ]
                  }
                },
                { "NOT list_contains" : {
                    "list" : [ "commerce-order:owner:field-cert-earned" ],
                    "item" : [ "commerce-product:field-cert-prerequisites:2" ]
                  }
                },
                { "NOT list_contains" : {
                    "list" : [ "commerce-order:owner:field-cert-earned" ],
                    "item" : [ "commerce-product:field-cert-prerequisites:3" ]
                  }
                }
              ]
            }
          ]
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "You do not have all the certifications required to enter this session.",
            "type" : "error"
          }
        },
        { "list_remove" : {
            "list" : [ "commerce-order:commerce-line-items" ],
            "item" : [ "commerce-line-item" ]
          }
        }
      ]
    }
  }');
  $items['rules_inform_admin_about_class_evaluation'] = entity_import('rules_config', '{ "rules_inform_admin_about_class_evaluation" : {
      "LABEL" : "Inform admin about class evaluation",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "webform_rules" ],
      "ON" : [ "webform_rules_submit" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "omp_class_display" : "omp_class_display" } }
          }
        }
      ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "14" : "14" } },
            "subject" : "Class session [node:title] is evaluated by user [user:name]",
            "message" : "To review this submission follow this link:\\r\\n[site:url]\\/node\\/[node:nid]\\/submission\\/[data:sid]\\r\\n\\r\\nTo review result submisions table of [node:title] class session follow this link:\\r\\n[site:url]\\/node\\/[node:nid]\\/webform-results\\/table"
          }
        }
      ]
    }
  }');
  $items['rules_inform_all_instructors_about_their_class_evaluation'] = entity_import('rules_config', '{ "rules_inform_all_instructors_about_their_class_evaluation" : {
      "LABEL" : "Inform all instructors about their class evaluation",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "webform_rules" ],
      "ON" : [ "webform_rules_submit" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "omp_class_display" : "omp_class_display" } }
          }
        },
        { "entity_has_field" : {
            "entity" : [ "node:field-product-reference" ],
            "field" : "field_class_session_instructor"
          }
        }
      ],
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "node:field-product-reference:field-class-session-instructor" ] },
            "ITEM" : { "class_session_instructor" : "Class session instructor" },
            "DO" : [
              { "mail" : {
                  "to" : [ "class-session-instructor:mail" ],
                  "subject" : "Incomming Class evaluation",
                  "message" : "Your class [node:title] has just got evaluation from student [user:name].\\r\\nTo review this evaluation visit following link:\\r\\n[site:url]\\/node\\/[node:nid]\\/submission\\/[data:sid]",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_inform_class_admins_about_incomming_message'] = entity_import('rules_config', '{ "rules_inform_class_admins_about_incomming_message" : {
      "LABEL" : "Inform class admins about incomming message from user",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "webform_rules", "rules" ],
      "ON" : [ "webform_rules_submit" ],
      "IF" : [
        { "webform_has_id" : {
            "form_id" : [ "form-id" ],
            "selected_webform" : { "value" : { "webform-client-form-30" : "webform-client-form-30" } }
          }
        }
      ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "14" : "14" } },
            "subject" : "User [user:name] has just sent message to Class Admin.",
            "message" : "User [user:name] has just sent message to Class Admin.\\r\\nTo read the message follow this link:\\r\\n[site:url]\\/node\\/[node:nid]\\/submission\\/[data:sid]"
          }
        }
      ]
    }
  }');
  $items['rules_inform_students_about_class_cancellation'] = entity_import('rules_config', '{ "rules_inform_students_about_class_cancellation" : {
      "LABEL" : "Inform students about class cancellation",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : [ "commerce_product_update" ],
      "IF" : [
        { "AND" : [
            { "data_is" : { "data" : [ "commerce-product:type" ], "value" : "omp_class_session" } },
            { "data_is" : { "data" : [ "commerce-product-unchanged:status" ], "value" : 1 } },
            { "data_is" : { "data" : [ "commerce-product:status" ], "value" : 0 } }
          ]
        }
      ],
      "DO" : [
        { "entity_query" : {
            "USING" : {
              "type" : "registration",
              "property" : "entity_id",
              "value" : [ "commerce-product:product-id" ],
              "limit" : "1000"
            },
            "PROVIDE" : { "entity_fetched" : { "registrations_fetched" : "Fetched registrations" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "registrations-fetched" ] },
            "ITEM" : { "registration_item" : "Current registration" },
            "DO" : [
              { "entity_fetch" : {
                  "USING" : { "type" : "user", "id" : [ "registration-item:author-uid" ] },
                  "PROVIDE" : { "entity_fetched" : { "user_fetched" : "Fetched user" } }
                }
              },
              { "mail" : {
                  "to" : [ "user-fetched:mail" ],
                  "subject" : "Class Session has been cancelled.",
                  "message" : "Class Session [commerce-product:title] has just been cancelled. Please contact your instructor for details.\\r\\n",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  return $items;
}
