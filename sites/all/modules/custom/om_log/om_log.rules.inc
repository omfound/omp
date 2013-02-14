<?php

/**
 * Implemnts hook_rules_event_info
 */
function om_log_rules_event_info() {
  $defaults = array(
    'group' => t('Open Media Log'),
    'module' => 'om_log',
    'access callback' => array('administer om log rules'),
  );
  return array(
    'om_log_created' => $defaults + array(
      'label' => t('After creating a new log entry'),
    ),
    'om_critical_log_created' => $defaults + array(
      'label' => t('After an emergency log entry is created'),
    ),
    'om_log_updated' => $defaults + array(
      'label' => t('After an log entry is updated'),
    ),
    'om_log_deleted' => $defaults + array(
      'label' => t('After an log entry is deleted'),
    ),
  );
}