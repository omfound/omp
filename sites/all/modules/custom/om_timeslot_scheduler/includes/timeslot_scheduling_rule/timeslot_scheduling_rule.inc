<?php

function om_timeslot_scheduler_om_timeslot_scheduler_timeslot_scheduling_rule() {
  return array(
    'om_timeslot_scheduler_base_rule' => array(
      'title' => t('Base Scheduling Rule'),
      'description' => t('Template class for real rules.'),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'timeslot_scheduling_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'timeslotSchedulingRule',
      ),
    ),
    'fewest_aired_shows_scheduling_rule' => array(
      'title' => t('Fewest Aired Shows from Unique Project'),
      'description' => t("Selects the top 100 shows prioritizing content that has been aired the least from each project. Will only pick one show from each project. Show duration factors into prioritizing (i.e. if the top 75 shows don't fit a gap and #76 does it will get scheduled over 1-75) Includes theme integration. If theme is present shows will be limited by theme."),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'fewest_aired_shows_scheduling_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'fewestAiredShowsSchedulingRule',
        'parent' => 'timeslotSchedulingRule',
      ),
    ),
    'station_branding_scheduling_rule' => array(
      'title' => t('Newest Station Branding'),
      'description' => t("Selects only shows marked as station branding, newest first."),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'station_branding_scheduling_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'stationBrandingSchedulingRule',
        'parent' => 'timeslotSchedulingRule',
      ),
    ),
    'highest_bayesian_average_rule' => array(
      'title' => t('Highest Rated Station Content'),
      'description' => t("If the Bayesian ratinng module is availalbe select content with the highest rated Bayesian average for scheduling. If theme is present shows will be limited by theme."),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'highest_bayesian_average_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'highestBayesianAverageRule',
        'parent' => 'timeslotSchedulingRule',
      ),
    ),
  );
}

abstract class timeslotSchedulingRule {
  abstract function executeRule($timeslot);
  public function validateShow($show) {
    if (is_object($show)) {
      // if a show has a file
      if (empty($show->field_om_show_broadcast_file['und'][0]['uri'])) {
        return FALSE;
      }
      if (empty($show->field_om_show_duration['und'][0]['value'])) {
        return FALSE;
      }
      // has the right license
      return TRUE;
    }
  }
}