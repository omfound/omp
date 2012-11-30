<?php

/**
 * Implements hook_preprocess_HOOK
 */
function om_membership_preprocess_om_membership_individual_plans_table(&$variables) {
  // Build the somewhat complex membership table and send related variables to the template for assembly
  global $user;
  // Header Section
  $login_link = l('Login', 'user', array('attributes' => array('class' => array('green')), 'query' => array('destination' => $_GET['q'])));
  $login = t('Already have an account ? {!login}', array('!login' => $login_link));
  $group_plans_link = l('Click Here', 'membership/org-plans', array('attributes' => array('class' => array('red'))));
  $group_plan = t('For A Group Membership {!click}', array('!click' => $group_plans_link));
  $header = "<ul id='membership-header'><li>$login</li><li>$group_plan</li></ul>";
  $membership = new StdClass();
  if ($user->uid > 0) {
    $membership = om_membership_get_user_memberships($user);
    $membership = array_shift($membership);
    $membership_wrapper = entity_metadata_wrapper('commerce_product', $membership);
  }
  $variables['header'] = $header;
  // Body Section
  // We build the table in four sections table header, table body, cost row and sign up links.
  $individual_header = t('Individual Membership Plans');
  $table_header = "<th>$individual_header</th>";
  $cost_row = "<tr><td></td>";
  $link_row = "<tr><td></td>";
  // Build header, cost row and links
  $table_rows = "";
  if ($variables['plans']) {
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
        $cost_row .= "<td>$price</td>";
        if (!empty($membership->product_id)) {
          if ($membership->product_id == $plan->product_id) {
            $link = 'You Current <br/> Membership Level';
          }
          else if ((int)$membership_wrapper->commerce_price->value() <= (int)$plan_meta_wrapper->commerce_price->value()) {
            $link = '-';
          }
          else if ((int)$membership_wrapper->commerce_price->value() >= (int)$plan_meta_wrapper->commerce_price->value()) {
            $link = l('Upgrade Membership', 'membership/add/' . $plan->product_id);
          }
        }
        else {
          $link = l('Sign Up', 'membership/add/' . $plan->product_id);
        }
        $link_row .= "<td>$link</td>";
      }
    }
    $cost_row .= "</tr>";
    $link_row .= "</tr>";
    $variables['cost_row'] = $cost_row;
    $variables['link_row'] = $link_row;
    // Build body
    $plan_features = om_membership_get_plan_features();
    foreach($plan_features AS $plan_term) {
      $table_rows .= '<tr><td>' . $plan_term->name . '</td>';
      foreach($variables['plans'] AS $plan) {
        $plan_meta_wrapper = entity_metadata_wrapper('commerce_product', $plan);
        if ($plan_meta_wrapper->field_user_type->value() == 0) {
          $features = $plan_meta_wrapper->field_membership_features->value();
          if (!empty($features)) {
            $match = FALSE;
            foreach ($features AS $feature) {
               if ($plan_term->tid == $feature->tid) {
                 $match = TRUE;
               }
            }
            if ($match == TRUE) {
              $table_rows .= "<td class='feature-yes'>Yes</td>";
            }
            else {
              $table_rows .= "<td class='feature-no'>No</td>";
            }
          }
          else {
            $table_rows .= "<td class='feature-no'>No</td>";
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
  $login = t('Already have an account ? {!login}', array('!login' => $login_link));
  $group_plans_link = l('Click Here', 'membership', array('attributes' => array('class' => array('red'))));
  $group_plan = t('For an Individual Membership {!click}', array('!click' => $group_plans_link));
  if ($user->uid > 0) {
    $membership = om_membership_get_user_memberships($user);
    $membership = array_shift($membership);
    $membership_wrapper = entity_metadata_wrapper('commerce_product', $membership);
  }
  $header = "<ul id='membership-header'><li>$login</li><li>$group_plan</li></ul>";
  $variables['header'] = $header;
  // Body Section
  // We build the table in four sections table header, table body, cost row and sign up links.
  $individual_header = t('Organizational Membership Plans');
  $table_header = "<th>$individual_header</th>";
  $cost_row = "<tr><td></td>";
  $link_row = "<tr><td></td>";
  $table_rows = "";
  // Build header, cost row and links
  if ($variables['plans']) {
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
        $cost_row .= "<td>$price</td>";
        if (!empty($membership->product_id)) {
          if ($membership->product_id == $plan->product_id) {
            $link = 'You Current <br/> Membership Level';
          }
          else if ((int)$membership_wrapper->commerce_price->value() <= (int)$plan_meta_wrapper->commerce_price->value()) {
            $link = '-';
          }
          else if ((int)$membership_wrapper->commerce_price->value() >= (int)$plan_meta_wrapper->commerce_price->value()) {
            $link = l('Upgrade Membership', 'membership/add/' . $plan->product_id);
          }
        }
        else {
          $link = l('Sign Up', 'membership/add/' . $plan->product_id);
        }
        $link_row .= "<td>$link</td>";
      }
    }
    $cost_row .= "</tr>";
    $link_row .= "</tr>";
    $variables['cost_row'] = $cost_row;
    $variables['link_row'] = $link_row;
    // Build body
    $plan_features = om_membership_get_plan_features();
    foreach($plan_features AS $plan_term) {
      $table_rows .= '<tr><td>' . $plan_term->name . '</td>';
      foreach($variables['plans'] AS $plan) {
        $plan_meta_wrapper = entity_metadata_wrapper('commerce_product', $plan);
        if ($plan_meta_wrapper->field_user_type->value() == 1) {
          $features = $plan_meta_wrapper->field_membership_features->value();
          if (!empty($features)) {
            $match = FALSE;
            foreach ($features AS $feature) {
               if ($plan_term->tid == $feature->tid) {
                 $match = TRUE;
               }
            }
            if ($match == TRUE) {
              $table_rows .= "<td class='feature-yes'>Yes</td>";
            }
            else {
              $table_rows .= "<td class='feature-no'>No</td>";
            }
          }
          else {
            $table_rows .= "<td class='feature-no'>No</td>";
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
function om_membership_preprocess_om_membership_renewal_table(&$variables) {
  global $user;
  $user_plan = om_membership_get_user_memberships($user);
  $user_plan = array_shift($user_plan);
  if ($variables['plans'][count($variables['plans']) - 1]->product_id != $user_plan->product_id) {
    $plan_metadata = entity_metadata_wrapper('commerce_product', $user_plan);
  }
}