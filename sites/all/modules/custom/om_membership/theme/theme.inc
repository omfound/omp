<?php

/**
 * A few constants for use with plan features
 */
define("FEATURE_ACTIVE", 1);
define("FEATURE_INACTIVE", 2);
define("FEATURE_INVALID", 3);


function om_membership_plans_by_weight($a, $b) {
  if ($a->field_weight[LANGUAGE_NONE][0]['value'] == $b->field_weight[LANGUAGE_NONE][0]['value'] ) {
    return 0;
  }
  return ($a->field_weight[LANGUAGE_NONE][0]['value']  < $b->field_weight[LANGUAGE_NONE][0]['value'] ) ? -1 : 1;
}

/**
 * Implements hook_preprocess_HOOK
 */
function om_membership_preprocess_om_membership_individual_plans_table(&$variables) {
  // Build the somewhat complex membership table and send related variables to the template for assembly
  global $user;
  // Header Section
  $login_link = l('Login', 'user', array('attributes' => array('class' => array('green')), 'query' => array('destination' => $_GET['q'])));
  $login = t('Already have an account ? !login', array('!login' => $login_link));
  $group_plans_link = l('Click Here', 'membership/org-plans', array('attributes' => array('class' => array('red'))));
  $group_plan = t('For A Group Membership !click', array('!click' => $group_plans_link));
  if (user_is_anonymous()) {
    $header = "<ul id='membership-header'><li>$login</li><li>$group_plan</li></ul>";
  }
  else {
    $header = "<ul id='membership-header'><li>$group_plan</li></ul>";
  }
  $membership = new StdClass();
  if ($user->uid > 0) {
    $membership = om_membership_get_user_membership_products($user);
    $membership = array_shift($membership);
    $membership_wrapper = entity_metadata_wrapper('commerce_product', $membership);
  }
  $variables['header'] = $header;
  // Body Section
  // We build the table in four sections table header, table body, cost row and sign up links.
  $break = "<br/>";
  $individual_header = t('Individual !break Membership Plans', array('!break' => $break));
  $table_header = "<th class='table-title'>$individual_header</th>";
  $cost_row = "<tr><td></td>";
  $link_row = "<tr><td></td>";
  // Build header, cost row and links
  $table_rows = "";
  if ($variables['plans']) {
    usort($variables['plans'], "om_membership_plans_by_weight");
    foreach ($variables['plans'] AS $plan) {
      $plan_meta_wrapper = entity_metadata_wrapper('commerce_product', $plan);
      if ($plan_meta_wrapper->field_user_type->value() == 0) {
        $table_header .= "<th>" . $plan->title . "</th>";
        $project = $plan_meta_wrapper->commerce_price->value();
        $price = ($project['amount']/100);
        if ($price == 0) {
          $price = 'Free';
        }
        else {
          $price = '$' . $price;
        }
        $cost_row .= "<td class='price'>$price</td>";
        if (!empty($membership->product_id)) {
          $membership_price = $membership_wrapper->commerce_price->value();
          $current_plan_price = $plan_meta_wrapper->commerce_price->value();
          if ($membership->product_id == $plan->product_id) {
            $link = 'Your Current <br/> Membership Level';
          }
          else if ($membership_price['amount'] >= $current_plan_price['amount']) {
            $link = '-';
          }
          else if ($membership_price['amount'] <= $current_plan_price['amount']) {
            $link = l('Upgrade Membership', 'membership/add/' . $plan->product_id);
          }
        }
        else {
          $link = l('Sign Up', 'membership/add/' . $plan->product_id);
        }
        $link_row .= "<td class='action'>$link</td>";
      }
    }
    $cost_row .= "</tr>";
    $link_row .= "</tr>";
    $variables['cost_row'] = $cost_row;
    $variables['link_row'] = $link_row;
    // Build body
    $plan_features = om_membership_get_plan_features();
    $feature_count = count($plan_features);
    foreach($plan_features AS $key => $plan_term) {
      if (om_membership_plans_feature_active($variables['plans'], $plan_term->tid)) {
        $last_class = '';
        if ($key + 1 == $feature_count) {
          $last_class = "last";
        }
        $table_rows .= '<tr><td class="plan-feature ' . $last_class . '">' . $plan_term->name . '</td>';
        foreach($variables['plans'] AS $plan) {
          $feature_status = om_membership_plan_feature_active($plan, $plan_term->tid);
          if ($feature_status == FEATURE_ACTIVE) {
            $table_rows .= "<td class='feature feature-yes'>Yes</td>";
          }
          elseif ($feature_status == FEATURE_INACTIVE) {
            $table_rows .= "<td class='feature feature-no'>No</td>";
          }
        }
      }
      $table_rows .= '</tr>';
    }
  }
  $variables['table_header'] = $table_header;
  $variables['table_rows'] = $table_rows;
}

/**
 * Implements hook_preprocess_HOOK
 */
function om_membership_preprocess_om_membership_org_plans_table(&$variables) {
  // Pretty much the same as above with a few key differences.
  // Product field_user_type = 1 && links are different.
  // Header Section
  global $user;
  $login_link = l('Login', 'user', array('attributes' => array('class' => array('green')), 'query' => array('destination' => $_GET['q'])));
  $login = t('Already have an account ? !login', array('!login' => $login_link));
  $group_plans_link = l('Click Here', 'membership', array('attributes' => array('class' => array('red'))));
  $group_plan = t('For an Individual Membership !click', array('!click' => $group_plans_link));
  if ($user->uid > 0) {
    $membership = om_membership_get_user_membership_products($user);
    $membership = array_shift($membership);
    $membership_wrapper = entity_metadata_wrapper('commerce_product', $membership);
  }
  if (user_is_anonymous()) {
    $header = "<ul id='membership-header'><li>$login</li><li>$group_plan</li></ul>";
  }
  else {
    $header = "<ul id='membership-header'><li>$group_plan</li></ul>";
  }
  $variables['header'] = $header;
  // Body Section
  // We build the table in four sections table header, table body, cost row and sign up links.
  $break = "<br/>";
  $individual_header = t('Organizational !break Membership Plans', array('!break' => $break));
  $table_header = "<th class='table-title'>$individual_header</th>";
  $cost_row = "<tr><td></td>";
  $link_row = "<tr><td></td>";
  $table_rows = "";
  // Build header, cost row and links
  if ($variables['plans']) {
    usort($variables['plans'], "om_membership_plans_by_weight");
    foreach ($variables['plans'] AS $plan) {
      $plan_meta_wrapper = entity_metadata_wrapper('commerce_product', $plan);
      if ($plan_meta_wrapper->field_user_type->value() == 1) {
        $table_header .= "<th>" . $plan->title . "</th>";
        $price = $plan_meta_wrapper->commerce_price->value();
        $price = $price['amount'] / 100;
        if ($price == 0) {
          $price = 'Free';
        }
        else {
          $price = '$' . $price;
        }
        $cost_row .= "<td class='price'>$price</td>";
        if (!empty($membership->product_id)) {
          $membership_price = $membership_wrapper->commerce_price->value();
          $current_plan_price = $plan_meta_wrapper->commerce_price->value();
          if ($membership->product_id == $plan->product_id) {
            $link = 'You Current <br/> Membership Level';
          }
          else if ($membership_price['amount'] >= $current_plan_price['amount']) {
            $link = '-';
          }
          else if ($membership_price['amount'] <= $current_plan_price['amount']) {
            $link = l('Upgrade Membership', 'membership/add/' . $plan->product_id);
          }
        }
        else {
          $link = l('Sign Up', 'membership/add/' . $plan->product_id);
        }
        $link_row .= "<td class='action'>$link</td>";
      }
    }
    $cost_row .= "</tr>";
    $link_row .= "</tr>";
    $variables['cost_row'] = $cost_row;
    $variables['link_row'] = $link_row;
    // Build body
    $plan_features = om_membership_get_plan_features();
    $feature_count = count($plan_features);
    foreach($plan_features AS $key => $plan_term) {
      if (om_membership_plans_feature_active($variables['plans'], $plan_term->tid, 'group')) {
        $last_class = '';
        if ($key + 1 == $feature_count) {
          $last_class = "last";
        }
        $feature_exists_in_plan = 0;
        $table_rows .= '<tr><td class="plan-feature ' . $last_class . '">' . $plan_term->name . '</td>';
        foreach($variables['plans'] AS $plan) {
          $feature_status = om_membership_plan_feature_active($plan, $plan_term->tid, 'group');
          if ($feature_status == FEATURE_ACTIVE) {
            $table_rows .= "<td class='feature feature-yes'>Yes</td>";
          }
          elseif ($feature_status == FEATURE_INACTIVE) {
            $table_rows .= "<td class='feature feature-no'>No</td>";
          }
        }
      }
      $table_rows .= '</tr>';
    }
  }
  $variables['table_header'] = $table_header;
  $variables['table_rows'] = $table_rows;
}

function om_membership_plans_feature_active($plans, $feature_tid, $type = 'individual') {
  foreach($plans as $plan) {
    $feature_status = om_membership_plan_feature_active($plan, $feature_tid, $type);
    if ($feature_status == FEATURE_ACTIVE) {
      return TRUE;
    }
  }

  return FALSE;
}

function om_membership_plan_feature_active($plan, $feature_tid, $type = 'individual') {
  if ($type == 'individual') {
    $user_type = 0;
  }elseif ($type == 'group') {
    $user_type = 1;
  }
  $plan_meta_wrapper = entity_metadata_wrapper('commerce_product', $plan);
  if ($plan_meta_wrapper->field_user_type->value() == $user_type) {
    $features = $plan_meta_wrapper->field_membership_features->value();
    if (!empty($features)) {
      foreach ($features AS $feature) {
        if ($feature_tid == $feature->tid) {
          return FEATURE_ACTIVE;
        }
      }
    }
    return FEATURE_INACTIVE;
  }

  return FEATURE_INVALID;
}

/**
 * Implements hook_preprocess_HOOK
 */
function om_membership_preprocess_om_membership_renewal_table(&$variables) {
  global $user;
  $user_plans = om_membership_get_user_membership_orders($user, FALSE);
  if (!empty($user_plans)) {
    // See if a renewal is needed.
    // Send features to template.
    foreach ($user_plans AS $user_plan) {
      $products = om_membership_order_contains_membership($user_plan);
      if (!empty($products)) {
        $product = $products[0];
        $product_metadata = entity_metadata_wrapper('commerce_product', $product);
        $exp = $user_plan->created + ($product_metadata->field_duration->value() * 31688800);
        $update_period = $product_metadata->field_update_period->value() * 86400;
        $now = time();
        if ($now >= ($exp - $update_period) && $now <= $exp) {
          // User is in renewal time.
          $status = 'renew';
          $variables['renewal_link'] = l('Renew Now!', 'membership/add/' . $product->product_id);
          $variables['update_link'] = l('Upgrade Now!', 'membership/plans');
          $all_features = om_membership_get_plan_features();
          $current_features = $product_metadata->field_membership_features->value();
          $unique_features = array_udiff($all_features, $current_features, '_om_membership_compare_vocs');
          if (!empty($unique_features)) {
            $variables['features'] = '<ul>';
              foreach ($unique_features AS $feature) {
                $variables['features'] .= '<li class="feature">' . $feature->name . '</li>';
              }
            $variables['features'] .= '</ul>';
          }
        }
        else if ($user_plan->created > $now) {
          $status = 'prepurchased';
        }
        else if ($now >= $exp) {
          $status = 'expired';
        }
        else if ($now >= $user_plan->created && $now <= $exp) {
          $status = 'current';
        }
      }
    }
  }
  else {
    $status = 'none';
  }
  $variables['membership_status'] = $status;
  switch ($status) {
    case 'current':
      $upgrade = l('upgrade', 'membership/plans');
      $variables['message'] = t('Your membership is not set to expire soon. However, you can !upgrade at any time.', array('!upgrade' => $upgrade));
      break;
    case 'prepurchased':
      $variables['message'] = t('Your memberships has already been renewed.');
      break;
    case 'expired':
      $sign_up = l('Sign up', 'membership/plans');
      $variables['message'] = t('Your membership has already expired. !signup for a new one now.', array('!signup' => $sign_up));
      break;
    case 'none':
      $sign_up = l('Sign Up Now!', 'membership/plans');
      $variables['message'] = t('You don\'t seem to have an active membership to renew. !signup', array('!signup' => $sign_up));
      break;
  }
}

/**
 * Implements hook_preprocess_HOOK
 */
function om_membership_preprocess_om_membership_checkout_completion(&$variables) {
  global $user;
  $orders = om_membership_get_user_membership_orders($user);
  if (!empty($orders)) {
    if (om_membership_validate_org_admin_member($user) == TRUE) {
      $account_link = l('account', 'user/' . $user->uid);
      $membership_admin = l('administer your organization', 'user/' . $user->uid . '/edit/manage_organizational_membership');
      $variables['message'] = t("Thanks! Your membership has been activated! Return to your !account or !admin. Please contact station personnel if you have any questions.", array('!account' => $account_link, '!admin' => $membership_admin));
    }
    else {
      $account_link = l('account', 'user/' . $user->uid);
      $variables['message'] = t("Thanks! Your membership has been activated! Return to your !account. Please contact station personnel if you have any questions.", array('!account' => $account_link));
    }
  }
  else {
    $home = l('home', '<front>');
    $variables['message'] = t("No memberships were found on this account. There must have been an error. Return !home.", array('!home' => $home));
  }
}
