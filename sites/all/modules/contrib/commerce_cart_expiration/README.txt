Description
===========

This module provides a time-based cart expiration feature.


Requirements
============

- Drupal Commerce (http://drupal.org/project/commerce): 7.x-1.0 or newer
- Rules (http://drupal.org/project/rules): 7.x-2.0 or newer


Installation / Configuration
============================

The module provides a default rule that can be configured from the Rules
administration screen, located at: admin/config/workflow/rules
(rules_admin must be enabled)

If you want to change the default rule configuration, you need to implement the
hook_default_rules_configuration_alter() and override the current configuration.

Example:

/**
 * Implements hook_default_rules_configuration_alter().
 */
function HOOK_default_rules_configuration_alter(&$configs) {
  if (isset($configs['commerce_cart_expiration_delete_expired_carts'])) {
    foreach ($configs['commerce_cart_expiration_delete_expired_carts']->actions() as $action) {
      if ($action->getElementName() == 'commerce_cart_expiration_delete_orders') {
        $action->settings['interval'] = 3600;
      }
    }
  }
}


Drush integration
=================

This module provides a Drush (http://drupal.org/project/drush) command for
deleting expired cart orders.
Use 'drush help commerce-cart-expiration-clean-orders' for more information.


Maintainers
===========

Developed and maintained by Andrei Mateescu (amateescu) - http://drupal.org/user/729614


Credits
=======

jgalletta - http://drupal.org/user/1187850
Pedro Cambra (pcambra) - http://drupal.org/user/122101
