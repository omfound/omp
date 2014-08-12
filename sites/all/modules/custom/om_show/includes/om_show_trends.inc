<?php

function om_show_trends() {
  $query = om_show_trends_base_query();
  $display = om_show_trends_display($query);
  return $display;
}

function om_show_trends_base_query() {
  module_load_include('inc', 'query_extender_filter', 'includes/filter');
  $query = db_select('node')->extend('PagerDefault')->extend('Filter');
  $query->join('users', 'users', 'users.uid = node.uid');
  $query->join('field_data_field_om_theme', 'theme', 'node.nid = theme.entity_id');
  $query->join('alternative_rating', 'rating', 'node.nid = rating.nid');
  $query->condition('node.status', 1)
    ->condition('node.type', 'om_show')
    ->fields('node', array('title', 'nid', 'created'))
    ->fields('users', array('name'))
    ->fields('theme', array('field_om_theme_tid'))
    ->fields('rating', array('bayesian'))
    ->limit(25)
    ->filterForm('om_show_trends')
    ->orderBy('rating.bayesian');
  return $query;
}

function om_show_trends_filter_conditions(&$query) {
  if (!empty($query->filter['period'])) {
    switch ($query->filter['period']) {
      case 'alltime':
          $query->condition('rating.period', 'alltime');
        break;
      case 'month':
          $query->condition('rating.period', 'month');
        break;
      case 'week':
          $query->condition('rating.period', 'week');
        break;
    }
  }
  if (!empty($query->filter['theme'])) {
    if (count($query->filter['theme']) > 1) {
      $or = db_or();
      foreach ($query->filter['theme'] as $key => $value) {
        $or->condition('theme.field_om_theme_tid', $value); 
      }
      $query->condition($or); 
    }
    else {
      $query->condition('theme.field_om_theme_tid', key($query->filter['theme'])); 
    }
  }
}

function om_show_trends_form() {
  $form = array();
  $form['theme'] = array(
    '#title' => t('Theme Block'),
    '#type' => 'select',
    '#options' => taxonomy_allowed_values(field_info_field('field_om_theme')),
    '#multiple' => true,
    '#required' => false,
    '#empty_value' => '',
  );
  $form['period'] = array(
    '#title' => t('Period'),
    '#type' => 'select',
    '#options' => array('alltime' => 'All Time', 'month' => 'Last 30 Days', 'week' => 'Last 7 Days'),
  );

  return $form;
}

function om_show_trends_display($query) {
  $result = $query->execute();
  $build['filters'] = drupal_get_form('filter_extender_form', $query);
  $header = array(
    array('data' => t('Title')),
    array('data' => t('Nid')),
    array('data' => t('Created')),
    array('data' => t('Username')),
    array('data' => t('Tid')),
    array('data' => t('Bayesian')),
  );

  $rows = array();
  foreach ($result as $row) {
    $rows[] = array('data' => (array) $row);
  }

  $build['node_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There was no data found matching your specifications.'),
  );

  $build['pager_pager'] = array('#theme' => 'pager');

  return $build;
}
