<?php if (!empty($main_nav_background)): ?>
  body #header {
    background-color: <?php print $main_nav_background; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_color)): ?>
  body #header a:link,
  body #header a:visited {
    color: <?php print $main_nav_color; ?>;
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
<?php if (!empty($main_nav_color_dropdown_color)): ?>
.block-nice-menus ul li.over li a,
.block-nice-menus ul li.active-trail li a {
  color: <?php print $main_nav_color_dropdown_color; ?>;
}
<?php endif; ?>
<?php if (!empty($main_nav_color_dropdown_background)): ?>
.block-nice-menus ul li.over li a,
.block-nice-menus ul li.active-trail li a {
  background-color: <?php print $main_nav_color_dropdown_background; ?>;
}
<?php endif; ?>