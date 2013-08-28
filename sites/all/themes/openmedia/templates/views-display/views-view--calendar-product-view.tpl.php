<?php global $user;?>
<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>
    <div id = "top-area">
    <div class = "res-title-number">1</div>
    <div class = "res-title">Choose Equipment</div>
    <?php if ($exposed): ?>
      <div class="view-filters">
        <?php print $exposed; ?>
      </div>
    <?php endif; ?>

    <?php if ($attachment_before): ?>
      <div class="attachment attachment-before">
        <?php print $attachment_before; ?>
      </div>
    <?php endif; ?>
    <div class = "item-area">
      <?php if ($rows): ?>
        <div class="view-content">
          <?php print $rows; ?>
        </div>
      <?php elseif ($empty): ?>
        <div class="view-empty">
          <?php print $empty; ?>
        </div>
      <?php endif; ?>
   	  
      <?php if ($pager): ?>
        <?php print $pager; ?>
      <?php endif; ?>
    </div>
  </div>
  <div id = reservations-header>
      <div class = "res-title-number">2</div>
      <div class = "res-title">Review</div>
    <div id = "left-side">
      <img id = "equipment_img" src = "/sites/all/modules/custom/commerce_reservations/theme/images/equipment.jpg" width = "150" height="100">
    </div>
    <div id = "right-side">
      <p></p>
  </div>
  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>
