<?php

/**
 * Implemnts hook_rules_event_info
 */
function om_airing_rules_event_info() {
  $defaults = array(
    'group' => t('Open Media Airing'),
    'module' => 'om_airing',
    'access callback' => array('administer om airing'),
  );
  return array(
    'om_airing_created' => $defaults + array(
      'label' => t('After creating a new OM Airing node'),
    ),
    'om_airing_deleted' => $defaults + array(
      'label' => t('After deleting an OM Airing node.'),
    ),
    'om_airing_updated' => $defaults + array(
      'label' => t('After an OM Airing node is updated.'),
    ),
    'om_airing_cron' => $defaults + array(
      'label' => t('After an OM Airing cron job has run.'),
    ),
  );
}