<?php

function om_timeslot_scheduler_automation_drush_command() {
  $items = array();
  $items['dom-automation-run'] = array(
    'description' => "Run automated scheduling.",
    'aliases' => array('dar'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );
  return $items;
}

function drush_dom_automation_run() {
  om_timeslot_scheduler_automation_run_scheduling_jobs();
  drush_log('Automation ran successfully.', 'success');
}

