<ul>
  <?php if (!empty($previous)): ?>
    <li><?php print $previous; ?></li>
  <?php endif; ?>
  <?php if (!empty($next)): ?>
    <li><?php print $next; ?></li>
  <?php endif; ?>
    <li>Step <?php print $current_step; ?> of <?php print $step_count; ?>: <?php print $step_label; ?></li>
</ul>
