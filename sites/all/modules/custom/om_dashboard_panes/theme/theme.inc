<?php

/**
 * Implements hook_preprocess_hook
 */
function om_dashboard_panes_preprocess_om_profile_pane(&$variables) {
  global $user;
  $options = array('attributes' => array('class' => array('blue-button')));
  $variables['title'] = t('Profile') . l('Edit Your Profile', 'user/' . $user->uid . '/edit', $options) .  l('View Your Profile', 'user/' . $user->uid, $options);
}

/**
 * Implements hook_preprocess_hook
 */
function om_dashboard_panes_preprocess_om_membership_pane(&$variables) {
  global $user;
  $variables['title'] = t('Membership');
  $memberships = om_membership_get_user_membership_orders($user);
  if (empty($memberships)) {
    $options = array('attributes' => array('class' => array('blue-button')));
    $learn_more = l('Learn More', 'membership', $options);
    $variables['message'] = t('You don\'t have a membership yet. !learnmore', array('!learnmore' => $learn_more));
  }
  else {
    $products = om_membership_get_user_membership_products($user);
    $products = array_shift($products);
    $product_meta = entity_metadata_wrapper('commerce_product', $products);
    $variables['membership_type'] = $products->title;
    $variables['membership_start'] = date('D j/n/Y', $memberships[0]->created);
    $year_seconds = 31688800;
    $end = $memberships[0]->created + ($year_seconds * $product_meta->field_duration->value());
    $variables['membership_end'] = date('D j/n/Y', $end);
    $options = array('attributes' => array('class' => array('blue-button')));
    $variables['upgrade'] = l('Upgrade Your Plan', 'membership', $options);
  }
}

/**
 * Implements hook_preprocess_hook
 */
function om_dashboard_panes_preprocess_om_classes_pane(&$variables) {
  $variables['title'] = t('Upcoming Classes');
  $options = array('attributes' => array('class' => array('red-button')));
  $variables['links'] = l('Take a Class!', 'classes', $options);
  $options = array('attributes' => array('class' => array('blue-button')));
  $variables['links'] .= l('See All Classes', 'classes', $options);
  $classes = om_dashboard_panes_upcoming_classes(5);
  if (!empty($classes)) {
    $class_output = '<table><tr><th>Date</th><th>Title</th></tr>';
    foreach ($classes AS $class) {
      $start = date('D n/j/y', $class['date']);
      $class_output .= '<tr><td>' . $start . '</td><td>' . $class['title'] . '</td></tr>';
    }
    $class_output .= "</table>";
    $variables['classes_output'] = $class_output;
  }
  else {
     $variables['message'] = t('There are no upcoming classes.');
  }
}

/**
  *  * Implements hook_preprocess_hook
  *   */
function om_dashboard_panes_preprocess_om_class_registration_pane(&$variables) {
  global $user;
  $registration_table = om_classes_user_registrations($user, 'simple');
  $variables['registration_table'] = $registration_table;
  $variables['title'] = t('Class Registrations');
}

/**
 * Implements hook_preprocess_hook
 */
function om_dashboard_panes_preprocess_om_reservations_pane(&$variables) {
  $options = array('attributes' => array('class' => array('blue-button')));
  $variables['title'] = t('Reservations') . l('Make a Reservation', 'reservations', $options);
}

/**
 * Implements hook_preprocess_hook
 */
function om_dashboard_panes_preprocess_om_shows_pane(&$variables) {
  $variables['title'] = t('Shows');
  $shows = om_dashboard_panes_get_users_shows();
  $options = array('attributes' => array('class' => array('blue-button')));
  if (!empty($shows)) {
    $show_output = '<table><tr><th>Title</th><th>Date Created</th></tr>';
    foreach ($shows AS $show) {
      $created = date('D n/j/y', $show->created);
      $title = l($show->title, 'node/' . $show->nid);
      $show_output .= '<tr><td>' . $created . '</td><td>' . $title . '</td></tr>';
    }
    $show_output .= "</table>";
    $variables['show_output'] = $show_output;
    $variables['add_link'] = l('Add a New Show', 'node/add/om_show', $options);
  }
  else {
    $link = l('Make One Now', 'node/add/om_show', $options);
    $variables['message'] = t('You haven\'t created any shows yet. !now', array('!now' => $link));
  }
}