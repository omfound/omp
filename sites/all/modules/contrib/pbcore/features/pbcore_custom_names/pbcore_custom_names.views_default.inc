<?php
/**
 * @file
 * pbcore_custom_names.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function pbcore_custom_names_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'pbcore_search_terms';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'PBCore: Search Terms';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'PBCore: Search Terms';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Filter';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = 1;
  $handler->display->display_options['fields']['name']['convert_spaces'] = 0;
  /* Field: Taxonomy term: Custom Name */
  $handler->display->display_options['fields']['field_pbcore_custom_name']['id'] = 'field_pbcore_custom_name';
  $handler->display->display_options['fields']['field_pbcore_custom_name']['table'] = 'field_data_field_pbcore_custom_name';
  $handler->display->display_options['fields']['field_pbcore_custom_name']['field'] = 'field_pbcore_custom_name';
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_pbcore_custom_name']['field_api_classes'] = 0;
  /* Field: Taxonomy vocabulary: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'Vocabulary';
  $handler->display->display_options['fields']['name_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name_1']['hide_alter_empty'] = 1;
  /* Field: Taxonomy term: Enable */
  $handler->display->display_options['fields']['field_term_enable']['id'] = 'field_term_enable';
  $handler->display->display_options['fields']['field_term_enable']['table'] = 'field_data_field_term_enable';
  $handler->display->display_options['fields']['field_term_enable']['field'] = 'field_term_enable';
  $handler->display->display_options['fields']['field_term_enable']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_term_enable']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_term_enable']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_term_enable']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_term_enable']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_term_enable']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_term_enable']['field_api_classes'] = 0;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'pbcore_fcc_ratings' => 'pbcore_fcc_ratings',
    'pbcore_genres' => 'pbcore_genres',
    'pbcore_languages' => 'pbcore_languages',
  );
  $handler->display->display_options['filters']['machine_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['machine_name']['expose']['operator_id'] = 'machine_name_op';
  $handler->display->display_options['filters']['machine_name']['expose']['label'] = 'Vocabulary';
  $handler->display->display_options['filters']['machine_name']['expose']['operator'] = 'machine_name_op';
  $handler->display->display_options['filters']['machine_name']['expose']['identifier'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['expose']['reduce'] = 0;
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['required'] = 0;
  $handler->display->display_options['filters']['name']['expose']['multiple'] = FALSE;
  /* Filter criterion: Taxonomy term: Custom Name (field_pbcore_custom_name) */
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['id'] = 'field_pbcore_custom_name_value';
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['table'] = 'field_data_field_pbcore_custom_name';
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['field'] = 'field_pbcore_custom_name_value';
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['expose']['operator_id'] = 'field_pbcore_custom_name_value_op';
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['expose']['label'] = 'Custom Name';
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['expose']['operator'] = 'field_pbcore_custom_name_value_op';
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['expose']['identifier'] = 'field_pbcore_custom_name_value';
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['expose']['required'] = 0;
  $handler->display->display_options['filters']['field_pbcore_custom_name_value']['expose']['multiple'] = FALSE;
  /* Filter criterion: Taxonomy term: Enable (field_term_enable) */
  $handler->display->display_options['filters']['field_term_enable_value']['id'] = 'field_term_enable_value';
  $handler->display->display_options['filters']['field_term_enable_value']['table'] = 'field_data_field_term_enable';
  $handler->display->display_options['filters']['field_term_enable_value']['field'] = 'field_term_enable_value';
  $handler->display->display_options['filters']['field_term_enable_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_term_enable_value']['expose']['operator_id'] = 'field_term_enable_value_op';
  $handler->display->display_options['filters']['field_term_enable_value']['expose']['label'] = 'Enabled';
  $handler->display->display_options['filters']['field_term_enable_value']['expose']['operator'] = 'field_term_enable_value_op';
  $handler->display->display_options['filters']['field_term_enable_value']['expose']['identifier'] = 'field_term_enable_value';
  $handler->display->display_options['filters']['field_term_enable_value']['expose']['reduce'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/config/search/pbcore/search';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Search';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $export['pbcore_search_terms'] = $view;

  return $export;
}
