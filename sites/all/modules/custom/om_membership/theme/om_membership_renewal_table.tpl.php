<?php if ($membership_status == 'renew'): ?>
<div id="main-options">
  <div id="current-plan">
    <p>Your membership is about to expire. Continue enjoying all the benefits you receive from your membership in the future.</p>
    <?php print $renewal_link; ?>
  </div>
  <div id="upgrade-plan">
    <?php if (!empty($features)): ?>
    <p>Upgrade your membership today and enjoy all these added benefits:</p>
      <?php print $update_link; ?>
    <?php endif; ?>
    <?php print l('Upgrade Now!', 'membership/plans'); ?>
  </div>
</div>
<div id="downgrade">
  <p>Or contact station personnel to downgrade your plan.<p>
</div>
<?php else: ?>
<div id="main-options">
  <p><?php print $message; ?></p>
</div>
<?php endif; ?>