<div id="registration-box">
  <?php if (!empty($price)): ?>
    <div class="price clearfix">
      <div class="price-value">
        <?php print $price; ?>
      </div>
      <?php if (!empty($registration_button)): ?>
        <div class="registration-button">
          <?php print $registration_button; ?>
          <?php dsm($registration_button); ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($discount_message)): ?>
        <div class="discount-message">
          <?php print $discount_message; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($seats_left)): ?>
    <div class="seats-left">
      <?php print $seats_left; ?> seats left
    </div>
  <?php endif; ?>
  <?php if (!empty($dates)): ?>
    <div class="dates">
      <?php print $dates; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($location_list)): ?>
    <div class="location">
      <div class="label">Location</div>
      <?php print $location_list; ?>
    </div>
    <?php if (!empty($directions_link)): ?>
      <div class="direction-link">
        <?php print $directions_link; ?>
      </div>
    <?php endif; ?>
  <?php endif; ?>
</div>
