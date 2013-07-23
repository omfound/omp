<div id="classes-pane" class="pane pane-title-only">
  <h3 class="pane-title"><?php print $title; ?></h3>
  <div class="inner">
     <?php print $reservations_output; ?>
  </div>
  <?php if (isset($add_link)): ?>
  <div class="divider">
  <?php print $add_link; ?>
  </div>
  <?php endif; ?>
</div>
