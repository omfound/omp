<?php
/**
 * @file
 * Views integration functions.
 */

/**
 * Implements hook_views_data_alter().
 */
function commerce_registration_views_data_alter(&$data) {
  $data['registration']['order_id'] = array(
    'relationship' => array(
      'base' => 'commerce_order',
      'field' => 'order_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Commerce Order'),
    ),
    'title' => t('Commerce Order ID'),
    'help' => t('The Commerce Order ID Number.'),
    'field' => array(
      'handler' => 'views_handler_field_commerce_product',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $product_entity = entity_get_info('commerce_product');
  $data['registration']['entity_id'] = array(
    'relationship' => array(
      'base' => $product_entity['base table'],
      'field' => $product_entity['entity keys']['id'],
      'handler' => 'views_handler_relationship',
      'label' => t('Commerce Product'),
    ),
    'title' => t('Registration Commerce Product'),
    'help' => t('The Commerce Product associated with this registration.'),
  );
  $data['registration']['registration_attached_entity'] = array(
    'real field' => 'entity_id',
    'field' => array(
      'title' => t("Attached Commerce Product"),
      'help' => t('The commerce product this registration is associated to.'),
      'handler' => 'CommerceRegistrationHandlerFieldRegistrationEntity',
    ),
  );
}
