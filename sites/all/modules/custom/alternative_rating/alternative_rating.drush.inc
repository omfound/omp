<?php

function alternative_rating_drush_command() {
  $items = array();
  $items['dom-alternative-rating-calculate'] = array(
    'description' => "Calculate alternative rating scores.",
    'aliases' => array('darc'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
    'arguments' => array(
      'count' => t('How many times to run alternative_rating_populate which handles a batch of 500.')
    )
  );
  return $items;
}

function drush_alternative_rating_dom_alternative_rating_calculate($count = 1) {
  for ($i = 0; $i < $count; $i++) {
    alternative_rating_populate();
  }
  drush_log('Alternative rating scores calculation complete.', 'success');
}
