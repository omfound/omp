<?php
/**
 * @file
 * omp_class_registration.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function omp_class_registration_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'class_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Class List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Class List';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
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
  /* Sort criterion: Commerce Product: Date -  start date (field_class_session_date) */
  $handler->display->display_options['sorts']['field_class_session_date_value']['id'] = 'field_class_session_date_value';
  $handler->display->display_options['sorts']['field_class_session_date_value']['table'] = 'field_data_field_class_session_date';
  $handler->display->display_options['sorts']['field_class_session_date_value']['field'] = 'field_class_session_date_value';
  $handler->display->display_options['sorts']['field_class_session_date_value']['relationship'] = 'field_product_reference_product_id';
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
    'omp_class_display' => 'omp_class_display',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 1;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 0;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'field_subject_tid' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'bef_filter_description' => '',
      ),
    ),
    'title' => array(
      'more_options' => array(
        'bef_filter_description' => '',
      ),
    ),
  );
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'teaser';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Referenced product */
  $handler->display->display_options['relationships']['field_product_reference_product_id']['id'] = 'field_product_reference_product_id';
  $handler->display->display_options['relationships']['field_product_reference_product_id']['table'] = 'field_data_field_product_reference';
  $handler->display->display_options['relationships']['field_product_reference_product_id']['field'] = 'field_product_reference_product_id';
  $handler->display->display_options['relationships']['field_product_reference_product_id']['required'] = 1;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Product Reference Field */
  $handler->display->display_options['fields']['field_product_reference']['id'] = 'field_product_reference';
  $handler->display->display_options['fields']['field_product_reference']['table'] = 'field_data_field_product_reference';
  $handler->display->display_options['fields']['field_product_reference']['field'] = 'field_product_reference';
  $handler->display->display_options['fields']['field_product_reference']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_product_reference']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_product_reference']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_product_reference']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_product_reference']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_product_reference']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_product_reference']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_product_reference']['settings'] = array(
    'show_quantity' => 0,
    'default_quantity' => '1',
    'combine' => 1,
    'line_item_type' => 'product',
  );
  $handler->display->display_options['fields']['field_product_reference']['field_api_classes'] = 0;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
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
  $handler->display->display_options['fields']['nid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Class Image */
  $handler->display->display_options['fields']['field_class_image']['id'] = 'field_class_image';
  $handler->display->display_options['fields']['field_class_image']['table'] = 'field_data_field_class_image';
  $handler->display->display_options['fields']['field_class_image']['field'] = 'field_class_image';
  $handler->display->display_options['fields']['field_class_image']['label'] = '';
  $handler->display->display_options['fields']['field_class_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_class_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_class_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_class_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_class_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_class_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_class_image']['empty'] = '<img src="sites/all/themes/neptune/images/custom/no_image_mini.jpg">';
  $handler->display->display_options['fields']['field_class_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_class_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_class_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_class_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_class_image']['settings'] = array(
    'image_style' => '176x108',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_class_image']['field_api_classes'] = 0;
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
  /* Field: Commerce Product: Date */
  $handler->display->display_options['fields']['field_class_session_date']['id'] = 'field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['table'] = 'field_data_field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['field'] = 'field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['relationship'] = 'field_product_reference_product_id';
  $handler->display->display_options['fields']['field_class_session_date']['label'] = '';
  $handler->display->display_options['fields']['field_class_session_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_class_session_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['settings'] = array(
    'format_type' => 'full',
    'fromto' => 'both',
    'multiple_number' => '1',
    'multiple_from' => '1',
    'multiple_to' => '',
    'show_repeat_rule' => 'hide',
  );
  $handler->display->display_options['fields']['field_class_session_date']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_class_session_date']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'omp_class_display' => 'omp_class_display',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Field: Subject (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['relationship'] = 'field_product_reference_product_id';
  $handler->display->display_options['filters']['field_subject_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_subject_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator_id'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['label'] = 'Choose a Class Category';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['identifier'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['field_subject_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['field_subject_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'omp_subjects';
  $handler->display->display_options['filters']['field_subject_tid']['error_message'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Search Class by Keywords';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['required'] = 0;
  $handler->display->display_options['filters']['title']['expose']['multiple'] = FALSE;
  /* Filter criterion: Commerce Product: Certifications Required (field_certifications_required) */
  $handler->display->display_options['filters']['field_certifications_required_tid']['id'] = 'field_certifications_required_tid';
  $handler->display->display_options['filters']['field_certifications_required_tid']['table'] = 'field_data_field_certifications_required';
  $handler->display->display_options['filters']['field_certifications_required_tid']['field'] = 'field_certifications_required_tid';
  $handler->display->display_options['filters']['field_certifications_required_tid']['relationship'] = 'field_product_reference_product_id';
  $handler->display->display_options['filters']['field_certifications_required_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_certifications_required_tid']['expose']['operator_id'] = 'field_certifications_required_tid_op';
  $handler->display->display_options['filters']['field_certifications_required_tid']['expose']['label'] = 'Certifications Required';
  $handler->display->display_options['filters']['field_certifications_required_tid']['expose']['operator'] = 'field_certifications_required_tid_op';
  $handler->display->display_options['filters']['field_certifications_required_tid']['expose']['identifier'] = 'field_certifications_required_tid';
  $handler->display->display_options['filters']['field_certifications_required_tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['field_certifications_required_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['field_certifications_required_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_certifications_required_tid']['vocabulary'] = 'omp_certifications';
  $handler->display->display_options['filters']['field_certifications_required_tid']['error_message'] = 1;
  /* Filter criterion: Field: Certifications earned by taking this class (field_cert_earned) */
  $handler->display->display_options['filters']['field_cert_earned_tid']['id'] = 'field_cert_earned_tid';
  $handler->display->display_options['filters']['field_cert_earned_tid']['table'] = 'field_data_field_cert_earned';
  $handler->display->display_options['filters']['field_cert_earned_tid']['field'] = 'field_cert_earned_tid';
  $handler->display->display_options['filters']['field_cert_earned_tid']['relationship'] = 'field_product_reference_product_id';
  $handler->display->display_options['filters']['field_cert_earned_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cert_earned_tid']['expose']['operator_id'] = 'field_cert_earned_tid_op';
  $handler->display->display_options['filters']['field_cert_earned_tid']['expose']['label'] = 'Certifications Earned';
  $handler->display->display_options['filters']['field_cert_earned_tid']['expose']['operator'] = 'field_cert_earned_tid_op';
  $handler->display->display_options['filters']['field_cert_earned_tid']['expose']['identifier'] = 'field_cert_earned_tid';
  $handler->display->display_options['filters']['field_cert_earned_tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['field_cert_earned_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['field_cert_earned_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_cert_earned_tid']['vocabulary'] = 'omp_certifications';
  $handler->display->display_options['filters']['field_cert_earned_tid']['error_message'] = 1;
  $handler->display->display_options['path'] = 'class-list';
  $export['class_list'] = $view;

  $view = new view;
  $view->name = 'classes_calendar';
  $view->description = '';
  $view->tag = 'Calendar';
  $view->base_table = 'commerce_product';
  $view->human_name = 'Classes Calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['link_display'] = 'page_1';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  /* Relationship: Commerce Product: Node referencing products from field_product_reference */
  $handler->display->display_options['relationships']['field_product_reference']['id'] = 'field_product_reference';
  $handler->display->display_options['relationships']['field_product_reference']['table'] = 'commerce_product';
  $handler->display->display_options['relationships']['field_product_reference']['field'] = 'field_product_reference';
  $handler->display->display_options['relationships']['field_product_reference']['required'] = 0;
  /* Field: Commerce Product: Date */
  $handler->display->display_options['fields']['field_class_session_date']['id'] = 'field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['table'] = 'field_data_field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['field'] = 'field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['label'] = '';
  $handler->display->display_options['fields']['field_class_session_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_class_session_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_class_session_date']['group_rows'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_class_session_date']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['field_api_classes'] = 0;
  /* Field: Content: Rendered Node */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['relationship'] = 'field_product_reference';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'full';
  /* Sort criterion: Commerce Product: Date -  start date (field_class_session_date) */
  $handler->display->display_options['sorts']['field_class_session_date_value']['id'] = 'field_class_session_date_value';
  $handler->display->display_options['sorts']['field_class_session_date_value']['table'] = 'field_data_field_class_session_date';
  $handler->display->display_options['sorts']['field_class_session_date_value']['field'] = 'field_class_session_date_value';
  /* Filter criterion: Commerce Product: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_product';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Month */
  $handler = $view->new_display('page', 'Month', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $handler->display->display_options['path'] = 'om-classes-calendar';
  $handler->display->display_options['menu']['title'] = 'Month';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Month';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Week */
  $handler = $view->new_display('page', 'Week', 'page_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'week';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'week';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'week';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-field-class-session-date/week';
  $handler->display->display_options['menu']['title'] = 'Week';
  $handler->display->display_options['menu']['weight'] = '2';

  /* Display: Day */
  $handler = $view->new_display('page', 'Day', 'page_3');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'day';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'day';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'day';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-field-class-session-date/day';
  $handler->display->display_options['menu']['title'] = 'Day';
  $handler->display->display_options['menu']['weight'] = '3';

  /* Display: Year */
  $handler = $view->new_display('page', 'Year', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'year';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'year';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'year';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-field-class-session-date/year';
  $handler->display->display_options['menu']['title'] = 'Year';
  $handler->display->display_options['menu']['weight'] = '4';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'mini';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '1';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );

  /* Display: Upcoming */
  $handler = $view->new_display('block', 'Upcoming', 'block_2');
  $handler->display->display_options['display_description'] = 'Upcoming events block';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Date: Date (commerce_product) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'commerce_product';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $export['classes_calendar'] = $view;

  $view = new view;
  $view->name = 'manage_students';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'registration';
  $view->human_name = 'Manage students';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Students Currently Enrolled';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'registration_id' => 'registration_id',
    'field_address' => 'field_address',
  );
  $handler->display->display_options['style_options']['default'] = 'field_address';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'registration_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_address' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Registration: Commerce Order ID */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'registration';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = 0;
  /* Relationship: Commerce Order: Owner */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'commerce_order';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'order_id';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Relationship: Commerce Order: Referenced line item */
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['id'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['table'] = 'field_data_commerce_line_items';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['field'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['relationship'] = 'order_id';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['required'] = 0;
  /* Relationship: Commerce Line item: Referenced product */
  $handler->display->display_options['relationships']['commerce_product_product_id']['id'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['table'] = 'field_data_commerce_product';
  $handler->display->display_options['relationships']['commerce_product_product_id']['field'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['required'] = 0;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
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
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['uid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uid']['link_to_user'] = 0;
  /* Field: Commerce Product: Product ID */
  $handler->display->display_options['fields']['product_id']['id'] = 'product_id';
  $handler->display->display_options['fields']['product_id']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['product_id']['field'] = 'product_id';
  $handler->display->display_options['fields']['product_id']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['fields']['product_id']['label'] = '';
  $handler->display->display_options['fields']['product_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['product_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['product_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['product_id']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['product_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['product_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['product_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['product_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['product_id']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['product_id']['link_to_product'] = 0;
  /* Field: Bulk operations: Registration */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'registration';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['empty_zero'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo']['operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'use_queue' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_message_action' => array(
      'selected' => 0,
      'use_queue' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'use_queue' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::om_manage_students_mark_as_cancelled' => array(
      'selected' => 1,
      'use_queue' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::om_manage_students_mark_as_completed' => array(
      'selected' => 1,
      'use_queue' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::om_manage_students_mark_as_enrolled' => array(
      'selected' => 1,
      'use_queue' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::om_manage_students_mark_as_pending' => array(
      'selected' => 1,
      'use_queue' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'use_queue' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_goto_action' => array(
      'selected' => 0,
      'use_queue' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'use_queue' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  $handler->display->display_options['fields']['views_bulk_operations']['vbo']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo']['display_result'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo']['merge_single_action'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo']['force_single'] = 0;
  /* Field: Registration: Registration ID */
  $handler->display->display_options['fields']['registration_id']['id'] = 'registration_id';
  $handler->display->display_options['fields']['registration_id']['table'] = 'registration';
  $handler->display->display_options['fields']['registration_id']['field'] = 'registration_id';
  $handler->display->display_options['fields']['registration_id']['label'] = 'Reg. No.';
  $handler->display->display_options['fields']['registration_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['registration_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['registration_id']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['registration_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['registration_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['registration_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['registration_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['registration_id']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['registration_id']['separator'] = '';
  $handler->display->display_options['fields']['registration_id']['format_plural'] = 0;
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_user_contact_info_1']['id'] = 'field_user_contact_info_1';
  $handler->display->display_options['fields']['field_user_contact_info_1']['table'] = 'field_data_field_user_contact_info';
  $handler->display->display_options['fields']['field_user_contact_info_1']['field'] = 'field_user_contact_info';
  $handler->display->display_options['fields']['field_user_contact_info_1']['label'] = 'Student';
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_user_contact_info_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_user_contact_info_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_user_contact_info_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_user_contact_info_1']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_user_contact_info_1']['settings'] = array(
    'use_widget_handlers' => 0,
    'format_handlers' => array(
      'name-full' => 'name-full',
    ),
  );
  $handler->display->display_options['fields']['field_user_contact_info_1']['field_api_classes'] = 0;
  /* Field: Field: Certifications earned by taking this class */
  $handler->display->display_options['fields']['field_cert_earned']['id'] = 'field_cert_earned';
  $handler->display->display_options['fields']['field_cert_earned']['table'] = 'field_data_field_cert_earned';
  $handler->display->display_options['fields']['field_cert_earned']['field'] = 'field_cert_earned';
  $handler->display->display_options['fields']['field_cert_earned']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_cert_earned']['label'] = 'Certifications';
  $handler->display->display_options['fields']['field_cert_earned']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_cert_earned']['empty'] = '--';
  $handler->display->display_options['fields']['field_cert_earned']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_cert_earned']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_cert_earned']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_cert_earned']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_cert_earned']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_cert_earned']['field_api_classes'] = 0;
  /* Field: Registration: Status */
  $handler->display->display_options['fields']['field_om_student_status']['id'] = 'field_om_student_status';
  $handler->display->display_options['fields']['field_om_student_status']['table'] = 'field_data_field_om_student_status';
  $handler->display->display_options['fields']['field_om_student_status']['field'] = 'field_om_student_status';
  $handler->display->display_options['fields']['field_om_student_status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_om_student_status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_om_student_status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_om_student_status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_om_student_status']['field_api_classes'] = 0;
  /* Field: User: Membership Plan */
  $handler->display->display_options['fields']['field_user_membership']['id'] = 'field_user_membership';
  $handler->display->display_options['fields']['field_user_membership']['table'] = 'field_data_field_user_membership';
  $handler->display->display_options['fields']['field_user_membership']['field'] = 'field_user_membership';
  $handler->display->display_options['fields']['field_user_membership']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_user_membership']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_user_membership']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_user_membership']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_user_membership']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_user_membership']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_user_membership']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_user_membership']['type'] = 'commerce_product_reference_title_link';
  $handler->display->display_options['fields']['field_user_membership']['settings'] = array(
    'show_quantity' => 0,
    'default_quantity' => '1',
    'combine' => 1,
    'line_item_type' => 'product',
  );
  $handler->display->display_options['fields']['field_user_membership']['field_api_classes'] = 0;
  /* Contextual filter: Commerce Product: Product ID */
  $handler->display->display_options['arguments']['product_id']['id'] = 'product_id';
  $handler->display->display_options['arguments']['product_id']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['product_id']['field'] = 'product_id';
  $handler->display->display_options['arguments']['product_id']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['arguments']['product_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['product_id']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['product_id']['default_argument_options']['code'] = '$node = node_load(arg(1));
return $node->field_product_reference[\'und\'][0][\'product_id\'];';
  $handler->display->display_options['arguments']['product_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['product_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['product_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['product_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['product_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['product_id']['not'] = 0;
  /* Filter criterion: Commerce Order: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'commerce_order';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'order_id';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
  );

  /* Display: Manage Students */
  $handler = $view->new_display('block', 'Manage Students', 'block');
  $export['manage_students'] = $view;

  $view = new view;
  $view->name = 'saved_and_expired_classes_calendar';
  $view->description = '';
  $view->tag = 'Calendar';
  $view->base_table = 'commerce_product';
  $view->human_name = 'Saved and expired classes calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['link_display'] = 'page_1';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    14 => '14',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  /* Relationship: Commerce Product: Node referencing products from field_product_reference */
  $handler->display->display_options['relationships']['field_product_reference']['id'] = 'field_product_reference';
  $handler->display->display_options['relationships']['field_product_reference']['table'] = 'commerce_product';
  $handler->display->display_options['relationships']['field_product_reference']['field'] = 'field_product_reference';
  $handler->display->display_options['relationships']['field_product_reference']['required'] = 0;
  /* Field: Commerce Product: Product ID */
  $handler->display->display_options['fields']['product_id']['id'] = 'product_id';
  $handler->display->display_options['fields']['product_id']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['product_id']['field'] = 'product_id';
  $handler->display->display_options['fields']['product_id']['label'] = '';
  $handler->display->display_options['fields']['product_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['product_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['product_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['product_id']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['product_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['product_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['product_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['product_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['product_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['product_id']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['product_id']['link_to_product'] = 0;
  /* Field: Commerce Product: Date */
  $handler->display->display_options['fields']['field_class_session_date']['id'] = 'field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['table'] = 'field_data_field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['field'] = 'field_class_session_date';
  $handler->display->display_options['fields']['field_class_session_date']['label'] = '';
  $handler->display->display_options['fields']['field_class_session_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_class_session_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_class_session_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_class_session_date']['group_rows'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_class_session_date']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_class_session_date']['field_api_classes'] = 0;
  /* Field: Content: Rendered Node */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['relationship'] = 'field_product_reference';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['rendered_entity']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'full';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<p>Create new like this</p>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/commerce/products/add/omp-class-session/[product_id]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  /* Sort criterion: Commerce Product: Date -  start date (field_class_session_date) */
  $handler->display->display_options['sorts']['field_class_session_date_value']['id'] = 'field_class_session_date_value';
  $handler->display->display_options['sorts']['field_class_session_date_value']['table'] = 'field_data_field_class_session_date';
  $handler->display->display_options['sorts']['field_class_session_date_value']['field'] = 'field_class_session_date_value';

  /* Display: Month */
  $handler = $view->new_display('page', 'Month', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $handler->display->display_options['path'] = 'om-saved-classes-calendar';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Create new class like existing one';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-class-admin';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Month';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Week */
  $handler = $view->new_display('page', 'Week', 'page_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'week';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'week';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'week';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-field-class-session-date/week';
  $handler->display->display_options['menu']['title'] = 'Week';
  $handler->display->display_options['menu']['weight'] = '2';

  /* Display: Day */
  $handler = $view->new_display('page', 'Day', 'page_3');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'day';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'day';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'day';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-field-class-session-date/day';
  $handler->display->display_options['menu']['title'] = 'Day';
  $handler->display->display_options['menu']['weight'] = '3';

  /* Display: Year */
  $handler = $view->new_display('page', 'Year', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'year';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'year';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'year';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-field-class-session-date/year';
  $handler->display->display_options['menu']['title'] = 'Year';
  $handler->display->display_options['menu']['weight'] = '4';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'mini';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '1';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (commerce_product) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'commerce_product';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );

  /* Display: Upcoming */
  $handler = $view->new_display('block', 'Upcoming', 'block_2');
  $handler->display->display_options['display_description'] = 'Upcoming events block';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Date: Date (commerce_product) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'commerce_product';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_class_session_date.field_class_session_date_value' => 'field_data_field_class_session_date.field_class_session_date_value',
  );
  $export['saved_and_expired_classes_calendar'] = $view;

  return $export;
}
