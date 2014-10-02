<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php $row_count = 1; ?>
<?php foreach ($rows as $id => $row): ?>
  <?php
    if ($row_count % 4 == 0) {
      $classes_array[$id] .= ' views-row-end';
    }
    if (($row_count - 1) % 4 == 0) {
      $classes_array[$id] .= ' views-row-start';
    }
  ?>
  <div <?php if ($classes_array[$id]) { print 'class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
  <?php $row_count ++; ?>
<?php endforeach; ?>