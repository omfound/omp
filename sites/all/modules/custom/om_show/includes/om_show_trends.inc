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
  $query->condition('node.status', 1)
    ->condition('node.type', 'om_show')
    ->fields('node', array('title', 'nid', 'status', 'created'))
    ->fields('users', array('name'))
    ->limit(25)
    ->filterForm('om_show_trends')
    ->orderBy('node.created');
  return $query;
}

function om_show_trends_filter_conditions(&$query) {
  //autocomplete textfield
  if (!empty($query->filter['username'])) {
    $query->condition('users.name', $query->filter['username']);
  } 

  //single select nid
  if (!empty($query->filter['nid'])) {
    $query->condition('node.nid', $query->filter['nid']);
  }

  //multiple select title
  if (!empty($query->filter['title'])) {
    if (count($query->filter['title']) > 1) {
      $or = db_or();
      foreach ($query->filter['title'] as $key => $title) {
        $or->condition('node.title', $title); 
      }
      $query->condition($or); 
    }
    else {
      $query->condition('node.title', key($query->filter['title'])); 
    }
  }
}

function om_show_trends_form() {
  $form = array();
  $form['theme'] = array(
    '#title' => t('Theme Block'),
    '#type' => 'select',
    '#options' => taxonomy_allowed_values(field_info_field('field_om_theme')),
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
    array('data' => t('Status')),
    array('data' => t('Created')),
    array('data' => t('Username')),
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
