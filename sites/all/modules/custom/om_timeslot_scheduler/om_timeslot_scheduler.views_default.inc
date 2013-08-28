<?php
/**
 * @file
 * om_timeslot_scheduler.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function om_timeslot_scheduler_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'om_timeslot_scheduler_calendar';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'OM Timeslot Scheduler Calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access scheduling calendar';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['style_options']['track_date'] = '0';
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_om_timeslot_date']['id'] = 'field_om_timeslot_date';
  $handler->display->display_options['fields']['field_om_timeslot_date']['table'] = 'field_data_field_om_timeslot_date';
  $handler->display->display_options['fields']['field_om_timeslot_date']['field'] = 'field_om_timeslot_date';
  $handler->display->display_options['fields']['field_om_timeslot_date']['label'] = '';
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_om_timeslot_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_om_timeslot_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_om_timeslot_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '0',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'hide',
  );
  $handler->display->display_options['fields']['field_om_timeslot_date']['group_rows'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_om_timeslot_date']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_om_timeslot_date']['field_api_classes'] = 0;
  /* Contextual filter: Content: Date -  start date (field_om_timeslot_date) */
  $handler->display->display_options['arguments']['field_om_timeslot_date_value']['id'] = 'field_om_timeslot_date_value';
  $handler->display->display_options['arguments']['field_om_timeslot_date_value']['table'] = 'field_data_field_om_timeslot_date';
  $handler->display->display_options['arguments']['field_om_timeslot_date_value']['field'] = 'field_om_timeslot_date_value';
  $handler->display->display_options['arguments']['field_om_timeslot_date_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_om_timeslot_date_value']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_om_timeslot_date_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_om_timeslot_date_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_om_timeslot_date_value']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'om_timeslot_event' => 'om_timeslot_event',
  );
  /* Filter criterion: Content: Channel (field_om_timeslot_channel) */
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['id'] = 'field_om_timeslot_channel_tid';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['table'] = 'field_data_field_om_timeslot_channel';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['field'] = 'field_om_timeslot_channel_tid';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['expose']['operator_id'] = 'field_om_timeslot_channel_tid_op';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['expose']['label'] = 'Channel';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['expose']['operator'] = 'field_om_timeslot_channel_tid_op';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['expose']['identifier'] = 'field_om_timeslot_channel_tid';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['vocabulary'] = 'channels';
  $handler->display->display_options['filters']['field_om_timeslot_channel_tid']['error_message'] = 1;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['om_timeslot_scheduler_calendar'] = $view;

  return $export;
}
