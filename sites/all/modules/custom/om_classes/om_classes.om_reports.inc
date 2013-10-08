<?php
/**
 * @file
 * These functions enable the Open Media System usage reports for the om_class module.
 */

/**
 * Implement hook_help.
 *
 */
function om_classes_om_reports_classes_help($path, $arg) {
  switch($path) {
    case "admin/help#om_reports_clasess_classes":
      $help_text = '<p>'. t("This module provides a report on the number of classes sold for the Open Media System").'</p>';
      break;
    case "admin/help#om_reports_classesoffered":
      $help_text = '<p>'. t("This module provides a report on the number of classes offered from start date to end date for the Open Media System").'</p>';
      break;
    }
  return $help_text;
}

/**
 * Implements hook_om_get_reports().
 */
function om_classes_om_get_reports() {
  $reports['admin/om/reports/classes/classes_sold'] = array(
    'title' => 'Classes Sold Report',
    'page callback' => 'om_classes_om_classesreport_page',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK);
  $reports['admin/om/reports/classes/classes_offered'] = array(
    'title' => 'Classes Offered Report',
    'page callback' => 'om_classes_om_classesofferedreport_page',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK);
    return $reports;
}

/**
 *Start Class Sold Report
 */
/**
 * Display Report Form - Gets date and displays table results as part of form...
 */
function om_classes_om_classesreport_form($form, &$form_state) {
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
    '#markup' => t(om_classes_om_classesreportout($s_date, $e_date)),
    
    );
  }
  return $form;
}

/**
 * Generate Page to Display Form
 */
function om_classes_om_classesreport_page() {
  $build = array(
    'example_form' => drupal_get_form('om_classes_om_classesreport_form'),
  );
  return $build;
}

/**
 * Validate proper dates have been input
 */
function om_classes_om_classesreport_form_validate($form, &$form_state) {
  // Make sure the start date is before the end date
  if ($form_state['values']['start_date'] >= $form_state['values']['end_date']) {
    form_set_error('start_date', 'Sorry, your Start Date must be before your End Date.');
  }
}

// Submit Form and Set For to Rebuild to display the result
function om_classes_om_classesreport_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}




/**
 * Function om_classes_om_classesreportout().
 */
function om_classes_om_classesreportout($s_date, $e_date) {
// Form table header
  $header = array('<b>CLASS TYPE</b>', '<b>TOTAL STUDENTS REGISTERED</b>');

//Set start date and  end date
  $start_date = $s_date;
  $end_date = $e_date;
  $grand_total = 0;
// Query to retrieve data
  $query = "SELECT commerce_product.title, count(*) as 'quantity' FROM `commerce_line_item` join commerce_product on commerce_product.sku = commerce_line_item.line_item_label right join commerce_order on commerce_order.order_id = commerce_line_item.order_id where commerce_product.type = 'class' and commerce_order.status = 'completed' and commerce_line_item.created between unix_timestamp('$start_date') and unix_timestamp('$end_date') group by commerce_product.title order by commerce_product.title, commerce_order.order_id asc";
  $results = db_query($query);
// Loop through each record and build rows
  foreach ($results as $record) {

    $rows[] = array(array('data' => t($record->title)),
            array('data' => t($record->quantity))
        );
    $grand_total = $grand_total + $record->quantity;

  }

  // Write Summary Row
  $rows[] = array(array('data' => t('<b>GRAND TOTAL</b>')),
        array('data' => t('<b>'.$grand_total.'</b>'))
        );
  return theme('table', array('header' => $header, 'rows' => $rows));

}
/**
 * End Classes Sold Report
 */

/**
 * Start Classes Offered Report
 */
/**
 * Classes Offered Report Form - Gets date and displays table results as part of form...
 */
function om_classes_om_classesofferedreport_form($form, &$form_state) {
  
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
    '#markup' => t(om_classes_om_classesofferedreportout($s_date, $e_date)),
    
    );
  }
  return $form;
}

/**
 * Generate Page to Display Form
 */
function om_classes_om_classesofferedreport_page() {
  $build = array(
    'example_form' => drupal_get_form('om_classes_om_classesofferedreport_form'),
  );
  return $build;
}

/**
 * Validate proper dates have been input
 */
function om_classes_om_classesofferedreport_form_validate($form, &$form_state) {
  
  // Make sure the start date is before the end date
  if ($form_state['values']['start_date'] >= $form_state['values']['end_date']) {
    form_set_error('start_date', 'Sorry, your Start Date must be before your End Date.');
  }
}

// Submit Form and Set For to Rebuild to display the result
function om_classes_om_classesofferedreport_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}



/**
 * Function om_classes_om_classesofferedreportout().
 */
function om_classes_om_classesofferedreportout($s_date, $e_date) {
// Form table header
  $header = array('<b>CLASS NAME</b>', '<b>TOTAL TIMES OFFERED</b>');

//Set start date and  end date
  $start_date = $s_date;
  $end_date = $e_date;
  $grand_total = 0;
// Query to retrieve data
  $query = "SELECT commerce_product.title, count(*) as 'quantity' FROM `commerce_product` where commerce_product.type = 'class' and commerce_product.created between unix_timestamp('$start_date') and unix_timestamp('$end_date') group by commerce_product.title order by commerce_product.title";
  $results = db_query($query);
// Loop through each record and build rows
  foreach ($results as $record) {
    $rows[] = array(array('data' => t($record->title)),
            array('data' => t($record->quantity))
         );
    $grand_total = $grand_total + $record->quantity;

    }

    // Write Summary Row
  $rows[] = array(array('data' => t('<b>GRAND TOTAL</b>')),
          array('data' => t('<b>'.$grand_total.'</b>'))
        );
  return theme('table', array('header' => $header, 'rows' => $rows));

}
/**
 * End Classses Offered Report
 */