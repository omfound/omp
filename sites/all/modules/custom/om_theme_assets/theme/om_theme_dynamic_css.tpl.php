<?php if (!empty($main_nav_bar_background)): ?>
  body #header {
    background-color: <?php print $main_nav_bar_background; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_color)): ?>
  body .block-nice-menus a:link,
  body .block-nice-menus a:visited {
    color: <?php print $main_nav_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_background)): ?>
  body .block-nice-menus a:link,
  body .block-nice-menus a:visited {
    background-color: <?php print $main_nav_background; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_color_hover)): ?>
  body .block-nice-menus a:focus,
  body .block-nice-menus a:hover {
    color: <?php print $main_nav_color_hover; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_background_hover)): ?>
  body .block-nice-menus a:focus,
  body .block-nice-menus a:hover,
  body .block-nice-menus a:focus,
  body .block-nice-menus a:hover,
  body .block-nice-menus li.over a,
  body .block-nice-menus li.active-trail a {
    background-color: <?php print $main_nav_background_hover; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_dropdown_color)): ?>
  body .block-nice-menus ul li.over li a:link,
  body .block-nice-menus ul li.over li a:visited,
  body .block-nice-menus ul li.active-trail li a:link,
  body .block-nice-menus ul li.active-trail li a:visited {
    color: <?php print $main_nav_dropdown_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_dropdown_background)): ?>
  body .block-nice-menus ul li.over li a:link,
  body .block-nice-menus ul li.over li a:visited,
  body .block-nice-menus ul li.active-trail li a:link,
  body .block-nice-menus ul li.active-trail li a:visited {
    background-color: <?php print $main_nav_dropdown_background; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_dropdown_color_hover)): ?>
  body .block-nice-menus ul li.over li a:focus,
  body .block-nice-menus ul li.over li a:hover,
  body .block-nice-menus ul li.active-trail li a:focus,
  body .block-nice-menus ul li.active-trail li a:hover {
    color: <?php print $main_nav_dropdown_color_hover; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_dropdown_background_hover)): ?>
  body .block-nice-menus ul li.over li a:focus,
  body .block-nice-menus ul li.over li a:hover,
  body .block-nice-menus ul li.active-trail li a:focus,
  body .block-nice-menus ul li.active-trail li a:hover {
    background-color: <?php print $main_nav_dropdown_background_hover; ?>;
  }
<?php endif; ?>
<?php if (!empty($header_shadow_color)): ?>
  #header {
    box-shadow: 3px 3px 3px <?php print $header_shadow_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($content_border_color)): ?>
  body.front #main .inner {
    border-top: 1px solid <?php print $content_border_color; ?>;
  }
  body.front #main {
    border-top: 1px solid <?php print $content_border_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($site_links_color)): ?>
  #block-om-theme-assets-om-site-links ul li,
  #block-om-theme-assets-om-site-links ul li a:link,
  #block-om-theme-assets-om-site-links ul li a:visited {
    text-shadow: none;
    color: <?php print $site_links_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($background_texture)): ?>
  html body {
    background: transparent url(<?php print $background_texture; ?>) top left repeat;
  }
<?php endif; ?>
<?php if (!empty($background_color)): ?>
  body.front #main {
    background-color: rgba(<?php print $background_color; ?>);
  }
<?php endif; ?>
<?php if (!empty($front_content_background_color)): ?>
  body.front #main #content {
    background-color: <?php print $front_content_background_color; ?>;
    padding: 10px;
    margin-bottom: 10px;
  }
<?php endif; ?>
<?php if (!empty($title_color)): ?>
  #page #content h1,
  #page #content h2,
  #page #content h3 {
    color: <?php print $title_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($om_dashboard_title_color)): ?>
  .section-dashboard #page #content h1,
  .section-dashboard #page #content h2,
  .section-dashboard #page #content h3 {
    color: <?php print $om_dashboard_title_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($om_dashboard_shadow_color)): ?>
  .section-dashboard #content {
    text-shadow: 1px 1px 1px <?php print $om_dashboard_shadow_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($info_tag_color)): ?>
  body .action-item .blue-bubble {
    background-color: <?php print $info_tag_color; ?>;
  }
  .action-item a:link .blue-text,
  .action-item a:visited .blue-text {
    color: <?php print $info_tag_color; ?>;
  }
<?php endif; ?>
<?php if (!empty($om_dashboard_pane_bg)): ?>
  .page-dashboard #content h3.pane-title {
    background-color: <?php print $om_dashboard_pane_bg; ?>;
  }
<?php endif; ?>
<?php if (!empty($show_page_left_width)): ?>
  .not-logged-in .node-om-show .node #show-left {
    width: <?php print $show_page_left_width; ?>;
  }
<?php endif; ?>
<?php if (!empty($show_page_right_width)): ?>
  .not-logged-in .node-om-show .node #show-right {
    width: <?php print $show_page_right_width; ?>;
  }
<?php endif; ?>
<?php if (!empty($show_page_left_width_user)): ?>
  .logged-in .node-om-show .node #show-left {
    width: <?php print $show_page_left_width_user; ?>;
  }
<?php endif; ?>
<?php if (!empty($show_page_right_width_user)): ?>
  .logged-in .node-om-show .node #show-right {
    width: <?php print $show_page_right_width_user; ?>;
  }
<?php endif; ?>

