<div id="classes-pane" class="pane">
  <h3 class="pane-title"><?php print $title; ?></h3>
  <div class="inner">
    <?php if (isset($message)): ?>
      <?php print $message; ?>
    <?php endif; ?>
    <?php if (isset($classes_output)): ?>
      <?php print $classes_output; ?>
    <?php endif; ?>
    <div class="divider">
      <?php print $links; ?>
    </div>
  </div>
</div>