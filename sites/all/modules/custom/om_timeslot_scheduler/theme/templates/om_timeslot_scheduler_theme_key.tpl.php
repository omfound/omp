<ul>
  <?php
  $voc = om_timeslot_scheduler_get_theme_vocabulary();
  foreach ($voc AS $term) {
    $hex = om_timeslot_scheduler_get_theme_color($term->tid);
    $swatch = "<div class='theme-swatch' style='background-color: $hex;'></div>";
    print "<li>$swatch $term->name</li>";
  }
  ?>
</ul>