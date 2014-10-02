<?php

function om_project_preprocess_project_member_list(&$variables) {
  $admin_list = '';
  $member_list = '';
  $node = menu_get_object();
  $user_is_admin = om_project_manage_access($node);
  if (!empty($variables['admins'])) {
    foreach ($variables['admins'] AS $admin) {
      $links = '';
      if ($user_is_admin == 'TRUE') {
        $links .= l('Remove', 'project/' . $node->nid . '/project-membership/remove/' . $admin);
      }
      $admin_list .= "<div class='project-admin'>$admin $links</div>";
    }
  }
  else {
     $admin_list .= "<div class='no-project-admins'>This project has no admins. There must be an error.</div>";
  }
  if (!empty($variables['members'])) {
    foreach ($variables['members'] AS $member) {
      $links = '';
      if ($user_is_admin == 'TRUE') {
        $links .= l('Remove', 'project/' . $node->nid . '/project-membership/remove/' . $member);
        $links .= ' | ' . l('Promote', 'project/' . $node->nid . '/project-membership/promote/' . $member);
      }
      $member_list .= "<div class='project-member'>$member $links</div>";
    }
  }
  else {
     $member_list .= "<div class='no-project-members'>This project has no members yet.</div>";
  }
  $variables['admin_list'] = $admin_list;
  $variables['member_list'] = $member_list;
  $variables['member_form'] = drupal_render(drupal_get_form('om_project_member_form'));
}