<?php $start = $row->field_data_field_om_timeslot_date_field_om_timeslot_date_val; ?>
<?php $end = $row->field_data_field_om_timeslot_date_field_om_timeslot_date_val_1; ?>

<?php $schedule_link = l('Schedule', 'om_timeslot_scheduler/schedule/' . $row->nid . '/' . $start . '/' . $end); ?>

<?php $content = '<ul><li>' . date('g:i A', $start) . '</li><li>' . date('g:i A', $end) . '</li><li>' . $fields['title']->content . '</li><li>' . $schedule_link . '</li></ul>'; ?>

<?php
  $hex = om_timeslot_scheduler_get_theme_color_from_timeslot($row->nid);
  if (!empty($hex)) {
    $inline_style = "style='background-color: $hex;'";
    $theme_wrapper = "<div class='timeslot-theme-wrapper' $inline_style >$content</div>";
  }
  else {
    $theme_wrapper = "<div class='timeslot-theme-wrapper no-bg'>$content</div>";
  }
?>

<?php print $theme_wrapper; ?>
