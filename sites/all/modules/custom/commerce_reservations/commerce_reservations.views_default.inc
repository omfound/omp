<?php
/**
 * @file
 * commerce_reservations.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_reservations_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'calendar_product_view';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Calendar Product View';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Calendar Product View';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 1;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Hello';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'Where did reservations go?';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Content: Referenced product */
  $handler->display->display_options['relationships']['field_crp_product_reference_product_id']['id'] = 'field_crp_product_reference_product_id';
  $handler->display->display_options['relationships']['field_crp_product_reference_product_id']['table'] = 'field_data_field_crp_product_reference';
  $handler->display->display_options['relationships']['field_crp_product_reference_product_id']['field'] = 'field_crp_product_reference_product_id';
  $handler->display->display_options['relationships']['field_crp_product_reference_product_id']['required'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '20';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Product Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'product_image_view',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['body']['alter']['text'] = 'Item Description';
  $handler->display->display_options['fields']['body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '150';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = 1;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = 'Click here for a full description';
  $handler->display->display_options['fields']['body']['alter']['more_link_path'] = 'node/[nid]';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '600',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Field: Content: Reservable Product Reference */
  $handler->display->display_options['fields']['field_crp_product_reference']['id'] = 'field_crp_product_reference';
  $handler->display->display_options['fields']['field_crp_product_reference']['table'] = 'field_data_field_crp_product_reference';
  $handler->display->display_options['fields']['field_crp_product_reference']['field'] = 'field_crp_product_reference';
  $handler->display->display_options['fields']['field_crp_product_reference']['label'] = 'From';
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_crp_product_reference']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_crp_product_reference']['settings'] = array(
    'show_quantity' => 0,
    'default_quantity' => '1',
    'combine' => 1,
    'line_item_type' => 'reservable_product',
  );
  $handler->display->display_options['fields']['field_crp_product_reference']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_crp_product_reference']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_crp_product_reference']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_crp_product_reference']['field_api_classes'] = 0;
  /* Field: Content: Product Image */
  $handler->display->display_options['fields']['field_image_1']['id'] = 'field_image_1';
  $handler->display->display_options['fields']['field_image_1']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image_1']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_image_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_image_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_image_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image_1']['settings'] = array(
    'image_style' => '155x116',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image_1']['field_api_classes'] = 0;
  /* Field: Commerce Product: Commercial Cost */
  $handler->display->display_options['fields']['field_commercial_cost']['id'] = 'field_commercial_cost';
  $handler->display->display_options['fields']['field_commercial_cost']['table'] = 'field_data_field_commercial_cost';
  $handler->display->display_options['fields']['field_commercial_cost']['field'] = 'field_commercial_cost';
  $handler->display->display_options['fields']['field_commercial_cost']['relationship'] = 'field_crp_product_reference_product_id';
  $handler->display->display_options['fields']['field_commercial_cost']['label'] = 'Commercial Cost per Hour';
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_commercial_cost']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_commercial_cost']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_commercial_cost']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_commercial_cost']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['field_commercial_cost']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['field_commercial_cost']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['field_commercial_cost']['field_api_classes'] = 0;
  /* Field: Commerce Product: Member Cost */
  $handler->display->display_options['fields']['field_member_cost']['id'] = 'field_member_cost';
  $handler->display->display_options['fields']['field_member_cost']['table'] = 'field_data_field_member_cost';
  $handler->display->display_options['fields']['field_member_cost']['field'] = 'field_member_cost';
  $handler->display->display_options['fields']['field_member_cost']['relationship'] = 'field_crp_product_reference_product_id';
  $handler->display->display_options['fields']['field_member_cost']['label'] = 'Member Cost per Hour';
  $handler->display->display_options['fields']['field_member_cost']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_member_cost']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_member_cost']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_member_cost']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_member_cost']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_member_cost']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_member_cost']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['field_member_cost']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['field_member_cost']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['field_member_cost']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
    'reservable_product_display' => 'reservable_product_display',
  );
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = 'SORT BY CATEGORY';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['tid']['type'] = 'select';
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'product_categories';
  $handler->display->display_options['filters']['tid']['error_message'] = 1;
  /* Filter criterion: Content: Reservable Product Reference (field_crp_product_reference:delta) */
  $handler->display->display_options['filters']['delta']['id'] = 'delta';
  $handler->display->display_options['filters']['delta']['table'] = 'field_data_field_crp_product_reference';
  $handler->display->display_options['filters']['delta']['field'] = 'delta';
  $handler->display->display_options['filters']['delta']['value']['value'] = '0';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['calendar_product_view'] = $view;

  $view = new view;
  $view->name = 'reservation_calendar';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_line_item';
  $view->human_name = 'Reservation Calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'reserve equipment';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 1;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'fullcalendar';
  $handler->display->display_options['style_options']['defaultView'] = 'agendaWeek';
  $handler->display->display_options['style_options']['right'] = 'agendaWeek month';
  $handler->display->display_options['style_options']['theme'] = FALSE;
  $handler->display->display_options['style_options']['fullcalendar_options']['firstHour'] = 14;
  $handler->display->display_options['style_options']['fullcalendar_options']['minTime'] = 14;
  $handler->display->display_options['style_options']['fullcalendar_options']['maxTime'] = 22;
  $handler->display->display_options['style_options']['fullcalendar_options']['disableDragging'] = TRUE;
  $handler->display->display_options['style_options']['fullcalendar_options']['disableResizing'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  $handler->display->display_options['header']['area']['content'] = '<div class = "res-title-number">3</div>
    <div class = "res-title">Choose Your Dates</div>
<p><b>Calendar:</b>The calendar shows when items are NOT available to rent.  To make a reservation, click and drag on the calendar.  To make a reservation for multiple days, select your start date and time from the calendar, and fill end the end date and time on the date form.</p>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  /* Relationship: Commerce Line item: Referenced product */
  $handler->display->display_options['relationships']['commerce_product_product_id']['id'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['table'] = 'field_data_commerce_product';
  $handler->display->display_options['relationships']['commerce_product_product_id']['field'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['required'] = 0;
  /* Field: Commerce Line Item: Line item ID */
  $handler->display->display_options['fields']['line_item_id']['id'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_id']['field'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_id']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['line_item_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_id']['hide_empty'] = 1;
  $handler->display->display_options['fields']['line_item_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['line_item_id']['hide_alter_empty'] = 1;
  /* Field: Commerce Line item: Reservation Dates */
  $handler->display->display_options['fields']['field_reservation_dates']['id'] = 'field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['table'] = 'field_data_field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['field'] = 'field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['label'] = '';
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_reservation_dates']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['settings'] = array(
    'format_type' => 'full',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_reservation_dates']['field_api_classes'] = 0;
  /* Contextual filter: Commerce Product: Product ID */
  $handler->display->display_options['arguments']['product_id']['id'] = 'product_id';
  $handler->display->display_options['arguments']['product_id']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['product_id']['field'] = 'product_id';
  $handler->display->display_options['arguments']['product_id']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['arguments']['product_id']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['product_id']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['product_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['product_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['product_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['product_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['product_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['product_id']['not'] = 0;
  /* Filter criterion: Commerce Line Item: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'commerce_line_item';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'reservable_product' => 'reservable_product',
  );

  /* Display: Reservation Calendar Page */
  $handler = $view->new_display('page', 'Reservation Calendar Page', 'page_1');
  $handler->display->display_options['path'] = 'reservations';
  $export['reservation_calendar'] = $view;

  $view = new view;
  $view->name = 'reservation_orders';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_line_item';
  $view->human_name = 'Administer Reservations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Administer Reservations';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    16 => '16',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Reset Filters';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 0;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There are either no reservations, or no reservations that match the filter criteria.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Commerce Line Item: Order ID */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = 0;
  /* Relationship: Commerce Order: Referenced customer profile */
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['id'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['table'] = 'field_data_commerce_customer_billing';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['field'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['relationship'] = 'order_id';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['required'] = 0;
  /* Field: Commerce Line Item: Title */
  $handler->display->display_options['fields']['line_item_title']['id'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_title']['field'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['label'] = '';
  $handler->display->display_options['fields']['line_item_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['line_item_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['line_item_title']['hide_alter_empty'] = 1;
  /* Field: Commerce Line Item: Line item ID */
  $handler->display->display_options['fields']['line_item_id']['id'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_id']['field'] = 'line_item_id';
  /* Field: Commerce Line item: Reservation Dates */
  $handler->display->display_options['fields']['field_reservation_dates']['id'] = 'field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['table'] = 'field_data_field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['field'] = 'field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['settings'] = array(
    'format_type' => 'full',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_reservation_dates']['field_api_classes'] = 0;
  /* Field: Commerce Order: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['uid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['uid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['uid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['uid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['uid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['uid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uid']['link_to_user'] = 1;
  /* Field: Commerce Order: Link */
  $handler->display->display_options['fields']['view_order']['id'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['view_order']['field'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['view_order']['label'] = 'Order Information';
  $handler->display->display_options['fields']['view_order']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['external'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_order']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_order']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_order']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_order']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['view_order']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_order']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_order']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_order']['hide_alter_empty'] = 1;
  /* Field: Commerce Line item: Checkout Status */
  $handler->display->display_options['fields']['field_checkout_status']['id'] = 'field_checkout_status';
  $handler->display->display_options['fields']['field_checkout_status']['table'] = 'field_data_field_checkout_status';
  $handler->display->display_options['fields']['field_checkout_status']['field'] = 'field_checkout_status';
  $handler->display->display_options['fields']['field_checkout_status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_checkout_status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_checkout_status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_checkout_status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_checkout_status']['field_api_classes'] = 0;
  /* Field: Commerce Line item: Product */
  $handler->display->display_options['fields']['commerce_product']['id'] = 'commerce_product';
  $handler->display->display_options['fields']['commerce_product']['table'] = 'field_data_commerce_product';
  $handler->display->display_options['fields']['commerce_product']['field'] = 'commerce_product';
  $handler->display->display_options['fields']['commerce_product']['label'] = 'Assigned Product';
  $handler->display->display_options['fields']['commerce_product']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_product']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_product']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_product']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_product']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_product']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_product']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_product']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_product']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['commerce_product']['type'] = 'commerce_product_reference_sku_link';
  $handler->display->display_options['fields']['commerce_product']['settings'] = array(
    'show_quantity' => 0,
    'default_quantity' => '1',
    'combine' => 1,
    'line_item_type' => 'product',
  );
  $handler->display->display_options['fields']['commerce_product']['field_api_classes'] = 0;
  /* Contextual filter: Commerce Order: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['relationship'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['order_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['order_id']['not'] = 0;
  /* Filter criterion: Commerce Line Item: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'commerce_line_item';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'reservable_product' => 'reservable_product',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Commerce Customer profile: Address (commerce_customer_address:last_name) */
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['id'] = 'commerce_customer_address_last_name';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['table'] = 'field_data_commerce_customer_address';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['field'] = 'commerce_customer_address_last_name';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['relationship'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['operator'] = 'word';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['group'] = 1;
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['expose']['operator_id'] = 'commerce_customer_address_last_name_op';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['expose']['label'] = 'Member Last Name';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['expose']['operator'] = 'commerce_customer_address_last_name_op';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['expose']['identifier'] = 'commerce_customer_address_last_name';
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['expose']['required'] = 0;
  $handler->display->display_options['filters']['commerce_customer_address_last_name']['expose']['multiple'] = FALSE;
  /* Filter criterion: Commerce Line item: Reservation Dates -  start date (field_reservation_dates) */
  $handler->display->display_options['filters']['field_reservation_dates_value']['id'] = 'field_reservation_dates_value';
  $handler->display->display_options['filters']['field_reservation_dates_value']['table'] = 'field_data_field_reservation_dates';
  $handler->display->display_options['filters']['field_reservation_dates_value']['field'] = 'field_reservation_dates_value';
  $handler->display->display_options['filters']['field_reservation_dates_value']['group'] = 1;
  $handler->display->display_options['filters']['field_reservation_dates_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_reservation_dates_value']['expose']['operator_id'] = 'field_reservation_dates_value_op';
  $handler->display->display_options['filters']['field_reservation_dates_value']['expose']['label'] = 'Reservation Start Date';
  $handler->display->display_options['filters']['field_reservation_dates_value']['expose']['operator'] = 'field_reservation_dates_value_op';
  $handler->display->display_options['filters']['field_reservation_dates_value']['expose']['identifier'] = 'field_reservation_dates_value';
  $handler->display->display_options['filters']['field_reservation_dates_value']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['field_reservation_dates_value']['form_type'] = 'date_popup';
  /* Filter criterion: Commerce Line item: Reservation Dates - end date (field_reservation_dates:value2) */
  $handler->display->display_options['filters']['field_reservation_dates_value2']['id'] = 'field_reservation_dates_value2';
  $handler->display->display_options['filters']['field_reservation_dates_value2']['table'] = 'field_data_field_reservation_dates';
  $handler->display->display_options['filters']['field_reservation_dates_value2']['field'] = 'field_reservation_dates_value2';
  $handler->display->display_options['filters']['field_reservation_dates_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_reservation_dates_value2']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_reservation_dates_value2']['expose']['operator_id'] = 'field_reservation_dates_value2_op';
  $handler->display->display_options['filters']['field_reservation_dates_value2']['expose']['label'] = 'Reservation End Date';
  $handler->display->display_options['filters']['field_reservation_dates_value2']['expose']['operator'] = 'field_reservation_dates_value2_op';
  $handler->display->display_options['filters']['field_reservation_dates_value2']['expose']['identifier'] = 'field_reservation_dates_value2';
  $handler->display->display_options['filters']['field_reservation_dates_value2']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['field_reservation_dates_value2']['form_type'] = 'date_popup';
  /* Filter criterion: Commerce Order: Order status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_order';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'order_id';
  $handler->display->display_options['filters']['status']['value'] = array(
    'completed' => 'completed',
    'pending' => 'pending',
  );
  $handler->display->display_options['filters']['status']['group'] = 1;
  /* Filter criterion: Commerce Line item: Checkout Status (field_checkout_status) */
  $handler->display->display_options['filters']['field_checkout_status_value']['id'] = 'field_checkout_status_value';
  $handler->display->display_options['filters']['field_checkout_status_value']['table'] = 'field_data_field_checkout_status';
  $handler->display->display_options['filters']['field_checkout_status_value']['field'] = 'field_checkout_status_value';
  $handler->display->display_options['filters']['field_checkout_status_value']['group'] = 1;
  $handler->display->display_options['filters']['field_checkout_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_checkout_status_value']['expose']['operator_id'] = 'field_checkout_status_value_op';
  $handler->display->display_options['filters']['field_checkout_status_value']['expose']['label'] = 'Checkout Status';
  $handler->display->display_options['filters']['field_checkout_status_value']['expose']['operator'] = 'field_checkout_status_value_op';
  $handler->display->display_options['filters']['field_checkout_status_value']['expose']['identifier'] = 'field_checkout_status_value';
  $handler->display->display_options['filters']['field_checkout_status_value']['expose']['reduce'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'administer_reservations';
  $handler->display->display_options['menu']['title'] = 'Reservation Monitor';
  $handler->display->display_options['menu']['description'] = 'Admin Reservation Section';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $export['reservation_orders'] = $view;

  $view = new view;
  $view->name = 'reservations_cart';
  $view->description = 'Display a list of line items added to cart.';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_order';
  $view->human_name = 'Reservations Cart';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Reservations Cart';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'quantity' => 'quantity',
    'commerce_display_path' => 'commerce_display_path',
    'line_item_title' => 'line_item_title',
    'commerce_total' => 'commerce_total',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'quantity' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'commerce_display_path' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'line_item_title' => array(
      'align' => '',
      'separator' => '',
    ),
    'commerce_total' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-right',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Footer: Commerce Line Item: Line item summary */
  $handler->display->display_options['footer']['line_item_summary']['id'] = 'line_item_summary';
  $handler->display->display_options['footer']['line_item_summary']['table'] = 'commerce_line_item';
  $handler->display->display_options['footer']['line_item_summary']['field'] = 'line_item_summary';
  $handler->display->display_options['footer']['line_item_summary']['links'] = array(
    'view_cart' => 'view_cart',
    'checkout' => 'checkout',
  );
  $handler->display->display_options['footer']['line_item_summary']['info'] = array(
    'quantity' => 'quantity',
    'total' => 'total',
  );
  /* Relationship: Commerce Order: Referenced line item */
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['id'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['table'] = 'field_data_commerce_line_items';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['field'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['required'] = 1;
  /* Field: Commerce Line Item: Quantity */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['quantity']['label'] = 'Qty';
  $handler->display->display_options['fields']['quantity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['quantity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['quantity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['quantity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['quantity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['quantity']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['quantity']['set_precision'] = 0;
  $handler->display->display_options['fields']['quantity']['precision'] = '0';
  $handler->display->display_options['fields']['quantity']['format_plural'] = 0;
  $handler->display->display_options['fields']['quantity']['suffix'] = ' × ';
  /* Field: Commerce Line item: Display path */
  $handler->display->display_options['fields']['commerce_display_path']['id'] = 'commerce_display_path';
  $handler->display->display_options['fields']['commerce_display_path']['table'] = 'field_data_commerce_display_path';
  $handler->display->display_options['fields']['commerce_display_path']['field'] = 'commerce_display_path';
  $handler->display->display_options['fields']['commerce_display_path']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['commerce_display_path']['label'] = '';
  $handler->display->display_options['fields']['commerce_display_path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_display_path']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_display_path']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_display_path']['field_api_classes'] = 0;
  /* Field: Commerce Line Item: Title */
  $handler->display->display_options['fields']['line_item_title']['id'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_title']['field'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['line_item_title']['label'] = 'Item';
  $handler->display->display_options['fields']['line_item_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['path'] = '[commerce_display_path]';
  $handler->display->display_options['fields']['line_item_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['line_item_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['line_item_title']['hide_alter_empty'] = 1;
  /* Field: Commerce Line item: Total */
  $handler->display->display_options['fields']['commerce_total']['id'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['table'] = 'field_data_commerce_total';
  $handler->display->display_options['fields']['commerce_total']['field'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['commerce_total']['label'] = '';
  $handler->display->display_options['fields']['commerce_total']['exclude'] = TRUE;
  $handler->display->display_options['fields']['commerce_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_total']['element_class'] = 'price';
  $handler->display->display_options['fields']['commerce_total']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['commerce_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_total']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['commerce_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_total']['field_api_classes'] = 0;
  /* Field: Commerce Line item: Reservation Dates */
  $handler->display->display_options['fields']['field_reservation_dates']['id'] = 'field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['table'] = 'field_data_field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['field'] = 'field_reservation_dates';
  $handler->display->display_options['fields']['field_reservation_dates']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['field_reservation_dates']['label'] = 'Res Dates';
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_reservation_dates']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_reservation_dates']['settings'] = array(
    'format_type' => 'reservation_cart',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_reservation_dates']['field_api_classes'] = 0;
  /* Sort criterion: Commerce Line Item: Line item ID */
  $handler->display->display_options['sorts']['line_item_id']['id'] = 'line_item_id';
  $handler->display->display_options['sorts']['line_item_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['sorts']['line_item_id']['field'] = 'line_item_id';
  $handler->display->display_options['sorts']['line_item_id']['relationship'] = 'commerce_line_items_line_item_id';
  /* Contextual filter: Commerce Order: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'commerce_cart_current_cart_order_id';
  $handler->display->display_options['arguments']['order_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['order_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['order_id']['not'] = 0;
  /* Filter criterion: Commerce Line Item: Line item is of a product line item type */
  $handler->display->display_options['filters']['product_line_item_type']['id'] = 'product_line_item_type';
  $handler->display->display_options['filters']['product_line_item_type']['table'] = 'commerce_line_item';
  $handler->display->display_options['filters']['product_line_item_type']['field'] = 'product_line_item_type';
  $handler->display->display_options['filters']['product_line_item_type']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['filters']['product_line_item_type']['value'] = '1';
  /* Filter criterion: Commerce Line Item: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'commerce_line_item';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['filters']['type']['value'] = array(
    'reservable_product' => 'reservable_product',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['block_description'] = 'Reservations Cart';
  $export['reservations_cart'] = $view;

  return $export;
}
