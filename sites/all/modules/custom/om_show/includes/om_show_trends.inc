<?php

function om_show_trends() {
  $query = om_show_trends_base_query();
  $display = om_show_trends_display($query);
  drupal_set_title('Currently Trending Shows');
  return $display;
}

function om_show_trends_base_query() {
  module_load_include('inc', 'query_extender_filter', 'includes/filter');
  $query = db_select('node')->extend('PagerDefault')->extend('Filter');
  $query->join('users', 'users', 'users.uid = node.uid');
  $query->join('field_data_field_om_theme', 'theme', 'node.nid = theme.entity_id');
  $query->join('alternative_rating', 'rating', 'node.nid = rating.nid');
  $query->join('field_data_field_show_thumbnail', 'thumbnail', 'node.nid = thumbnail.entity_id');
  $query->join('file_managed', 'file', 'thumbnail.field_show_thumbnail_fid = file.fid');
  $query->join('node_counter', 'counter', 'node.nid = counter.nid');
  $query->condition('node.status', 1)
    ->condition('node.type', 'om_show')
    ->condition('num_votes.vote_count', 1, '>=')
    ->fields('node', array('title', 'nid', 'created'))
    ->fields('users', array('name'))
    ->fields('theme', array('field_om_theme_tid'))
    ->fields('rating', array('bayesian'))
    ->fields('num_votes', array('vote_count'))
    ->fields('file', array('uri'))
    ->fields('counter', array('totalcount'))
    ->limit(24)
    ->filterForm('om_show_trends')
    ->orderBy('rating.bayesian', 'DESC')
    ->orderBy('num_votes.vote_count', 'DESC')
    ->orderBy('counter.totalcount', 'DESC');
  return $query;
}

function om_show_trends_filter_conditions(&$query) {
  $subquery = db_select('votingapi_vote', 'votes');
  $subquery->fields('votes', array('entity_id'));
  $subquery->addExpression('COUNT(entity_id)', 'vote_count');
  $subquery->groupBy('entity_id');
  if (empty($query->filter['period']) || $query->filter['period'] == 'month') {
    $query->condition('rating.period', 'month');
    $time_limit = strtotime("-30 days");
    $subquery->condition('votes.timestamp', $time_limit, '>='); 
  }
  elseif ($query->filter['period'] == 'alltime') {
    $query->condition('rating.period', 'alltime');
  }
  elseif ($query->filter['period'] == 'week') {
    $query->condition('rating.period', 'week');
    $time_limit = strtotime("-7 days");
    $subquery->condition('votes.timestamp', $time_limit, '>='); 
  }
  $query->addJoin('LEFT', $subquery, 'num_votes', 'node.nid = num_votes.entity_id');

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
    '#title' => t('Time Period'),
    '#type' => 'select',
    '#options' => array('alltime' => 'All Time', 'month' => 'Last 30 Days', 'week' => 'Last 7 Days'),
    '#default_value' => 'month',
  );

  return $form;
}

function om_show_trends_display($query) {
  $result = $query->execute();
  $filters = drupal_get_form('filter_extender_form', $query);
  $pager = array('#theme' => 'pager');
  return theme('om_show_trending_page', array('filter' => $filters, 'results' => $result, 'pager' => $pager));

  $header = array(
    array('data' => t('Title')),
    array('data' => t('Nid')),
    array('data' => t('Created')),
    array('data' => t('Username')),
    array('data' => t('Tid')),
    array('data' => t('Bayesian')),
    array('data' => t('# Votes')),
  );

  $rows = array();
  foreach ($result as $row) {
    $rows[] = array(
      $row->title,
      $row->nid,
      date("Y-m-d H:i:s", $row->created),
      $row->name,
      $row->field_om_theme_tid,
      $row->bayesian,
      $row->vote_count,
    );
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
