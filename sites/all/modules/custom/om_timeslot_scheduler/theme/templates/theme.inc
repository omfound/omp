<?php

function om_timeslot_scheduler_preprocess_timeslot_node_form(&$variables) {
  drupal_add_js(drupal_get_path('module', 'om_timeslot_scheduler') . '/theme/js/om_timeslot_scheduler_node_block.js');
  $variables['node_form'] = _om_timeslot_scheduler_node_form();
}
/**
 * Implements hook_preprocess_HOOK
 */
function om_timeslot_scheduler_preprocess_timeslot_schedule_completion(&$variables) {
  $dates = date('Y-m-d G:i', $variables['run_info']->start);
  $dates .= date(' \a\n\d Y-m-d G:i', $variables['run_info']->end);
  $voc = om_playback_servers_get_channel_vocabulary();
  foreach ($voc AS $term) {
    if ($term->tid == $variables['run_info']->channel_tid) {
      $channel = $term->name;
      break;
    }
  }
  if (!empty($variables['schedule_content'])) {
    $variables['message'] = t('The following schedule was generated for !dates on channel !channel.', array('!dates' => $dates, '!channel' => $channel));
    $variables['schedule_results'] = array();
    foreach ($variables['schedule_content'] AS $schedule_item) {
      if (empty($variables['schedule_results'][$schedule_item->timeslot_id])) {
        $timeslot = node_load($schedule_item->timeslot_id);
        $variables['schedule_results'][$schedule_item->timeslot_id] = array();
        $variables['schedule_results'][$schedule_item->timeslot_id]['timeslot'] = $timeslot;
        $variables['schedule_results'][$schedule_item->timeslot_id]['shows'] = array();
      }
      $item = node_load($schedule_item->show_id);
      if (empty($item->start)) {
        $item->start = $schedule_item->start;
        $item->end = $schedule_item->end;
        $variables['schedule_results'][$timeslot->nid]['shows'][$item->nid] = $item;
      }
    }
    $form = drupal_get_form('om_timeslot_scheduler_commit_schedule_form', arg(2));
    $form = drupal_render($form);
    $variables['commit_form'] = $form;
  }
  else {
    $return = l('Return', 'om_timeslot_scheduler');
    $variables['message'] = t('No scheduling results were generated for !dates on channel !channel. !return to scheduling.', array('!dates' => $dates, '!channel' => $channel, '!return' => $return));
  }
}

function _om_timeslot_scheduler_node_form() {
  global $user;
  // create a blank node
  $node = new StdClass();
  $node->uid = $user->uid;
  $node->name = (isset($user->name) ? $user->name : '');
  $node->type = 'om_timeslot_event';
  $node->language = '';
  module_load_include('inc', 'node', 'node.pages');
  $form = drupal_get_form("om_timeslot_event_node_form", $node);
  return $form;
}