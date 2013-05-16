<?php if (!empty($main_nav_background)): ?>
  body .block-nice-menus {
    background-color: <?php print $main_nav_background; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_color)): ?>
  body .block-nice-menus a:link,
  body .block-nice-menus a:visited {
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

<?php if (isset($background_texture)): ?>
  html body {
    background: transparent url(<?php print $background_texture; ?>) top left repeat;
  }
<?php $endif; ?>