<?php
/**
 * @file
 * These functions enable the Open Media System Reports for the commerce_reservations module.
 *
 * These reports uses theme(table) to output the reports
 */
 
 /**
  * Implement hook_help.
  *
  * Displays help and module information.
  *
  * @param path
  *    Which path of the site we're using to display help
  * @param arg
  *    Array that holds the current path as returned from arg() function
  */
 
function commerce_reservations_om_reports_inventory_help($path, $arg) {
  switch($path) {
    case "admin/help#om_reports_reservations_inventory":
      $help_text = '<p>'. t("This modules provides the inventory report for the Open Media System").'</p>';
      break;
    case "admin/help#om_reports_reservations_reservations":
      $help_text = '<p>'. t("This modules provides the resevations usage report for the Open Media System").'</p>';
  }
  return $help_text;
}


/**
 * Implements hook_om_reports().
 */
function commerce_reservations_om_get_reports() {
  //Equipment Inventory
  $reports['admin/om/reports/reservations/inventory'] = array(
    'title' => 'Inventory Report',
    'page callback' => 'commerce_reservations_om_reports_inventory',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK);
  $reports['admin/om/reports/reservations/reservations'] = array(
    'title' => 'Equipment Reservations Report 2',
    'page callback' => 'commerce_reservations_om_reservationreport_page',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK);
  return $reports;
}
/**
 * Inventory Report Begins
 * /
/**
 * Function commerce_reservations_om_reports_inventory().
 */
function commerce_reservations_om_reports_inventory() {
//Build Header
  $header = array('<b>ITEM</b>', '<b>ON HAND</b>', '<b>CHECKED OUT</b>','<b>UNAVAILABLE</b>', '<b>TOTAL</b>');
  $no_yes = array('No', 'Yes');
  /* Build complete list of items that are checked out
    Get all the items from the commerce_line_item table with field_checkout_status = Checked Out -> use the resulting
    values to calculate number of items per reservable_product_display that are checked out
   */
  $checked_out = array();
  $checked_out_query = "Select commerce_line_item.line_item_id, commerce_line_item.line_item_label from commerce_line_item where commerce_line_item.type = 'reservable_product'  order by commerce_line_item.line_item_label";
  $checked_out_results = db_query($checked_out_query);

  foreach($checked_out_results as $checked_out_record) {
    $checked_out_wrapper = entity_metadata_wrapper('commerce_line_item', $checked_out_record->line_item_id);
     if ($checked_out_wrapper->field_checkout_status->value() == 'Checked Out') {
       $checked_out[$checked_out_wrapper->line_item_label->value()] = $checked_out_wrapper->field_checkout_status->value();
     }
  }

  //Get Reservable Product Display Nodes

  $query = new EntityFieldQuery();
  $entities = $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'reservable_product_display')
        ->propertyOrderBy('title', 'ASC')
        //->propertyCondition('status', 1)
        ->execute();

  // Get RP node IDs

  $product_nids = array_keys($entities['node']);

  //Build Rows - Loop through rpd nodes and populate Item, On Hand, Checked Out, Unavailable and Total Columns

  foreach ($product_nids as $values) {
    //Generate Data for Each Row
    //initialize onhand, checked out, unavailable counts
    $onhand_count = 0;
    $unavailable_count = 0;
    $checkout_count = 0;

    // Get Wrapper for each Reservable Product to access title, product ids, and to loop through individual
    //   products to get total product counts associated with product display node
    $reservable_product_wrapper = entity_metadata_wrapper('node', $values);

    // Process each Reservable Product Node calculate the total on hand, total unavailable, the total checked out
    //   and the overall total
    foreach ($reservable_product_wrapper->field_crp_product_reference->raw() as $key2 =>$prod_id) {
      //Get Commerce Product Info to access title
      $prod_wrapper = entity_metadata_wrapper('commerce_product', $prod_id);
      //Get Commerce Line Item Info
      $chkoutstat_wrapper = entity_metadata_wrapper('commerce_line_item', $prod_id);
      //calculate onhand and unavailable
      if ($prod_wrapper->status->value() == 1) {
        //calculate number of items on hand for reservable product display
        $onhand_count = ++$onhand_count;
      }
      else {
        //calculate number of items unavailable for reservable product display
        $unavailable_count = ++ $unavailable_count;
      }
      //calculate number of items unavailable for reservable product display
      //determine number checked out count
      $item = $prod_wrapper->sku->value();
      foreach ($checked_out as $key => $status) {
        if ($key == $item) {
          $checkout_count = ++$checkout_count;
        }
      }
    }

    $rows[] = array(
            array('data' => t($reservable_product_wrapper->title->value())),
            array('data' => t($onhand_count - $checkout_count - $unavailable_count)),
            array('data' => t($checkout_count)),
            array('data' => t($unavailable_count)),
            array('data' => t(count($reservable_product_wrapper->field_crp_product_reference->raw())))
        );
}


/*
 *
 return theme('table', $header, $rows);
 */

   return theme('table', array('header' => $header, 'rows' => $rows));

}
/** Inventory Report Ends
 */

 /**
  * Equipment Reservations Usage Reportt Begins
  */
 /**
 * Show Report Form - Gets date and displays table results as part of form...
 */
function commerce_reservations_om_reservationreport_form($form, &$form_state) {
  $form['start_date'] = array(
    '#title' => t('Start Date'),
    '#type' => 'date',
    '#required' => TRUE,
  );
  $form['end_date'] = array(
    '#title' => t('End Date'),
    '#type' => 'date',
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  if($form_state['submitted'] == TRUE){
  	$s_date = $form_state['values']['start_date']['year']."-".$form_state['values']['start_date']['month']."-".$form_state['values']['start_date']['day']." 00:00:00";
  	$e_date = $form_state['values']['end_date']['year']."-".$form_state['values']['end_date']['month']."-".$form_state['values']['end_date']['day']." 23:59:59";
  	$form['testing'] = array(
    '#markup' => t(commerce_reservations_om_reservationreportoutput($s_date, $e_date)),
    
    );
  }
  return $form;
}

/**
 * Generate Page to Display Form
 */
function commerce_reservations_om_reservationreport_page() {
  $build = array(
    'example_form' => drupal_get_form('commerce_reservations_om_reservationreport_form'),
  );
  return $build;
}

/**
 * Validate proper dates have been input
 */
function commerce_reservations_om_reservationreport_form_validate($form, &$form_state) {
  
  // Make sure the start date is before the end date
  if ($form_state['values']['start_date'] >= $form_state['values']['end_date']) {
    form_set_error('start_date', 'Sorry, your Start Date must be before your End Date.');
  }
}

// Submit Form and Set For to Rebuild to display the result
function commerce_reservations_om_reservationreport_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}


/**
 * Function om_reservationreportoutput().
 */
function commerce_reservations_om_reservationreportoutput($s_date, $e_date) {

  // Form table header
  $header = array('<b>ITEM</b>', '<b>NUMBER OF TIMES RESERVED</b>', '<b>TOTAL HOURS USED</b>');
    
  //Set start date and  end date
  $start_date = $s_date;
  $end_date = $e_date;
    
  // Set start and end time indexes to access those times in the start_end_hours array
  $start_time_index = 1;
  $end_time_index = 0;
  
  // Query to retrieve data
  $query = "SELECT commerce_line_item.line_item_id, commerce_line_item.line_item_label, commerce_product.title FROM `commerce_line_item` join commerce_order on commerce_order.order_id = commerce_line_item.order_id join commerce_product on commerce_product.sku = commerce_line_item.line_item_label where  commerce_line_item.type = 'reservable_product' order by commerce_product.title";
  $results = db_query($query);

  // Set initial title to NULL, usage count to 0, and initial item count "init" to 0, grand total hours = 0;
  $old_title="";
  $count = 0;
  $init = 0;
  $grand_total_hours = 0;
  $grand_total_count = 0;
  $get_reservations = array();
  // Loop through each record and get title, determine the number of reservations, and total hours used.
  foreach ($results as $record) {
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $record->line_item_id);
    $start_end_hours = array();
    //$get_reservations = array();
    $hours_used =0;
    $get_reservations = $line_item_wrapper->field_reservation_dates->value();
    if(isset($get_reservations)){
      foreach ($get_reservations as $hours) {
        $start_end_hours[] = $hours;
      }
      $hours_used = (strtotime($start_end_hours[$start_time_index]) - strtotime($start_end_hours[$end_time_index]))/3600;
    }
    //If reservation is between query start and end date add to report
    if (isset($start_end_hours[$start_time_index])){
      if (strtotime($start_end_hours[$start_time_index]) >= strtotime($start_date) && strtotime($start_end_hours[$end_time_index]) < strtotime($end_date)) {
        $title = $record->title;
        if ($old_title == $title) {
          $next =1;
          $total_hours_used = $total_hours_used + $hours_used;
          $count = ++$count;
        }
        else {
          if ($init != 0) {
            $grand_total_hours = $grand_total_hours + $total_hours_used;
            $grand_total_count = $grand_total_count + $count;
            $rows[] = array(
                 array('data' => t($old_title)),
                 array('data' => t($count)),
                 array('data' => t($total_hours_used))
                  );
          }
          $init = 1;
          $next = 0;
          $count = 1;
          $total_hours_used = $hours_used;
        }
        $old_title = $title;
      }
    }
  }
  //print_r($old_title.",".$count.",".$total_hours_used."\n");
  $grand_total_hours = $grand_total_hours + $total_hours_used;
  $grand_total_count = $grand_total_count + $count;
  $rows[] = array(
        array('data' => t($old_title)),
        array('data' => t($count)),
        array('data' => t($total_hours_used))
    );
    // Write Summary Row
  $rows[] = array(
        array('data' => t('<b>GRAND TOTAL</b>')),
        array('data' => t('<b>'.$grand_total_count.'</b>')),
        array('data' => t('<b>'.$grand_total_hours.'</b>'))
    );

  return theme('table', array('header' => $header, 'rows' => $rows));

}
/**
 * Equipment Reservation Usage Report Ends
 */