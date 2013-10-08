<?php
/**
 * @file
 * These functions enable the Open Media System usage reports for the om_show module.
 */

/**
 * Implements hook_help().
 */
 

function om_show_om_reports_showreport_help($path, $arg) {
  switch($path) {
    case "admin/help#om_reports_shows_showsandthemes":
      $help_text = '<p>'. t("This modules provides a report on the submission of shows by themes (including number of hours) for the Open Media System").'</p>';
      break;
    }
    return $help_text;
}

/**
 * Implements hook_menu().
 */

function om_show_om_get_reports() {
  //Shows and Themes Submissions
  $reports['admin/om/reports/show/showsandthemes'] = array(
    'title' => 'Show and Theme Submission Report',
    'page callback' => 'om_show_om_showreport_page',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK);
  return $reports;
}


/**
 * Show Report Form - Gets date and displays table results as part of form...
 */
function om_show_om_showreport_form($form, &$form_state) {
  
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
    '#markup' => t(om_show_om_showreportout($s_date, $e_date)),
    
    );
  }
  return $form;
}

/**
 * Generate Page to Display Form
 */
function om_show_om_showreport_page() {
  $build = array(
    'example_form' => drupal_get_form('om_show_om_showreport_form'),
  );
  return $build;
}

/**
 * Validate proper dates have been input
 */
function om_show_om_showreport_form_validate($form, &$form_state) {
  
  // Make sure the start date is before the end date
  if ($form_state['values']['start_date'] >= $form_state['values']['end_date']) {
    form_set_error('start_date', 'Sorry, your Start Date must be before your End Date.');
  }
}

// Submit Form and Set For to Rebuild to display the result
function om_show_om_showreport_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}


function om_show_om_showreportout($s_date, $e_date) {

// Form table header
    $header = array('<b>PROGRAM THEME</b>', '<b>NUMBER OF SHOWS SUBMITTED</b>', '<b>TOTAL MINUTES OF PROGRAMMING</b>', '<b>AVG MINUTES/PROGRAM</b>');

//Set start date and  end date
    $start_date = $s_date;
    $end_date = $e_date;
    $grand_total = 0;

// Get Themes
$theme_items = array();
$program_themes = array();
$theme_query = "SELECT taxonomy_term_data.name FROM `taxonomy_term_data` where taxonomy_term_data.vid = 16";
$theme_results = db_query($theme_query);
foreach($theme_results as $theme_record) {
$program_themes[] = $theme_record->name;
}

// Get shows for period
$query ="Select node.nid from node where type = 'om_show' and node.created between unix_timestamp('$start_date') and unix_timestamp('$end_date')";
$results = db_query($query);
foreach ($results as $record) {
   $wrapper = entity_metadata_wrapper('node',$record->nid);
   if (!empty($wrapper->field_om_theme->value()->name) && $wrapper->field_om_show_duration->value() != 0) {
   $theme_items[] = $wrapper->field_om_theme->value()->name;
   $durations[] = array($wrapper->field_om_theme->value()->name, ($wrapper->field_om_show_duration->value()/60));
}
}

// Calculate Total Number of Shows Submitted for Period
$grand_total = count($theme_items);

// Build Rows 
if(isset($durations)){ 
array_multisort($durations);
}
$grand_total_duration = 0;
foreach ($program_themes as $theme) {
// Escape any forward slashes in strings
    if (strpos("/", $theme) == FALSE) {
    $theme = str_replace("/", "\/", $theme); 
    }
    $grep_string = "/$theme/";
// Count the number of occurrences of theme in array
    $item_count = count(preg_grep($grep_string,$theme_items));
// Reset string to original state
    if (strpos("/", $theme) == FALSE) {
    $theme = str_replace("\/", "/", $theme); 
    }
// Determine Total Hours in Theme
    $theme_duration = 0;
    if(isset($durations)) {  
    foreach ($durations as $value) {
        if ($value[0] == $theme) {
            $theme_duration = $theme_duration + $value[1];
            //print_r($theme_result." - ".$theme_duration."\n");
        }
    }
    }
    //$grand_total_duration = $grand_total_duration + $theme_duration;
    //Check for duration = 0 and avoid divide
    if ($item_count == 0){
    	$rows[] = array(
            array('data' => t($theme)),
            array('data' => t($item_count)),
            array('data' => t((int)$theme_duration)),
            array('data' => t(0))
        );
    	
    }
    else {
        $rows[] = array(
            array('data' => t($theme)),
            array('data' => t($item_count)),
            array('data' => t((int)$theme_duration)),
            array('data' => t((int)($theme_duration/$item_count)))
        );
        $grand_total_duration = $grand_total_duration + $theme_duration;
    }
}

// Grand Totals
// Calculate Total Number of Shows Submitted for Period
$grand_total = count($theme_items);
//Calcuate Grand Total Duration
//$grand_total_duration = $grand_total_duration;
//Check grand_total_duration = 0 and avoid divide by 0.
if($grand_total == 0) {
    $rows[] = array(
            array('data' => t('<b>Grand Totals</b>')),
            array('data' => t('<b>'.(int)$grand_total.'</b>')),
            array('data' => t('<b>'.(int)$grand_total_duration.'</b>')),
            array('data' => t('<b>'.(int)($grand_total_duration).'</b>'))
        );	
}
else {  
    $rows[] = array(
            array('data' => t('<b>Grand Totals</b>')),
            array('data' => t('<b>'.(int)$grand_total.'</b>')),
            array('data' => t('<b>'.(int)$grand_total_duration.'</b>')),
            array('data' => t('<b>'.(int)($grand_total_duration/$grand_total).'</b>'))
        );
}
return theme('table', array('header' => $header, 'rows' => $rows));
}