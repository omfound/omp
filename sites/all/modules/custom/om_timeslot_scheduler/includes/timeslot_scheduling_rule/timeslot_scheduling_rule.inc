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
    'locally_produced_shows_scheduling_rule' => array(
      'title' => t('Locally Produced Station Content'),
      'description' => t("Selects only shows marked as locally produced content. Prioritizes least aired content."),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'local_shows_scheduling_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'localShowsSchedulingRule',
        'parent' => 'timeslotSchedulingRule',
      ),
    ),
    'produced_at_station_scheduling_rule' => array(
      'title' => t('Shows Produced at Station'),
      'description' => t("Selects shows produced at your station. Prioritizes least aired content."),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'produced_at_station_scheduling_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'producedAtStationSchedulingRule',
        'parent' => 'timeslotSchedulingRule',
      ),
    ),
    'least_aired_show_in_project_scheduling_rule' => array(
      'title' => t('Least Aired Show in Project'),
      'description' => t("Selects least aired content, while constraining results to the current timeslot's project."),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'least_aired_show_in_project_scheduling_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'leastAiredShowInProjectSchedulingRule',
        'parent' => 'timeslotSchedulingRule',
      ),
    ),
    'newest_episode_in_project_scheduling_rule' => array(
      'title' => t('Newest Episode in Project'),
      'description' => t("Selects the newest episodes in a project using the episode field."),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'newest_episode_in_project_scheduling_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'newestEpisodeInProjectSchedulingRule',
        'parent' => 'timeslotSchedulingRule',
      ),
    ),
    'least_aired_shows_with_language_scheduling_rule' => array(
      'title' => t('Least Aired Shows from Language on Timeslot'),
      'description' => t("Selects the newest episodes in a project using the episode field."),
      'type' => 'timeslot_scheduling_rule',
      'path' => drupal_get_path('module', 'om_timeslot_scheduler') . '/includes/timeslot_scheduling_rule',
      'file' => 'least_aired_shows_with_language_scheduling_rule.inc',
      'timeslot_scheduling_rule' => array(
        'class' => 'leastAiredShowsWithLanguageSchedulingRule',
        'parent' => 'timeslotSchedulingRule',
      ),
    ),
  );
}

abstract class timeslotSchedulingRule {
  abstract function executeRule($timeslot);
}
