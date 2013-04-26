<?php
  $theme_info = openmedia_region_info();
  if (!empty($theme_info) && !empty($theme_info['sidebar_second'])) {
    $cols = 3;
  }
  else {
    $cols = 4;
  }
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php $row_count = 1; ?>
<?php foreach ($rows as $id => $row): ?>
  <?php
    if ($row_count % $cols == 0) {
      $classes_array[$id] .= ' views-row-end';
    }
    if (($row_count - 1) % $cols == 0) {
      $classes_array[$id] .= ' views-row-start';
    }
  ?>
  <div <?php if ($classes_array[$id]) { print 'class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
  <?php $row_count ++; ?>
<?php endforeach; ?>