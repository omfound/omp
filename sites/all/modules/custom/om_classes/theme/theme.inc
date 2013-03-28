<?php

/**
 * Implements hook_preprocess_HOOK
 */
function om_classes_preprocess_om_classes_user_registrations(&$variables) {
  if ($variables['registrations']) {
    $header = array(
      'Class',
      'Registration ID',
      'Order State',
      '# Registered',
      'Created',
      'Start Date',
      'Cost Paid',
    );
    $rows = array();
    foreach ($variables['registrations'] as $reg_id => $registration) {
      require_once(DRUPAL_ROOT . '/sites/all/libraries/date-repeat-helper/date-repeat-helper.inc');
      $date_info = date_repeat_helper_fetch_all_date_formats('commerce_product', $registration->product, 'field_class_date');
      $final_dates = date_repeat_helper_ordered_dates($date_info);
      $start_date = $final_dates[0]['start'];

      $order = commerce_order_load($registration->order_id);
      $wrapper = entity_metadata_wrapper('commerce_order', $order);
      $order_total = $wrapper->commerce_order_total->amount->value();

      $rows[] = array( 
        l($registration->product->title, 'node/'.commerce_autodisplay_entity_display_lookup($registration->entity_id)),
        l($registration->order_id, 'user/'.$registration->user_uid.'/orders/'.$registration->order_id),
        $registration->state,
        $registration->count,
        date("F j, Y, g:i a", $registration->created),
        $start_date,
        $order_total,
      );
    }

    $variables['registration_table'] = theme('table', array('header' => $header, 'rows' => $rows));
  }
  else {
    $variables['registration_table'] = '<div>'.t('You currently have no registrations.').'</div>';
  }
}
