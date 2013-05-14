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
  body #header a:focus,
  body #header a:hover {
    color: <?php print $main_nav_color_hover; ?>;
  }
<?php endif; ?>
<?php if (!empty($main_nav_background_hover)): ?>
  body #header a:focus,
  body #header a:hover {
    background-color: <?php print $main_nav_background_hover; ?>;
  }
<?php endif; ?>