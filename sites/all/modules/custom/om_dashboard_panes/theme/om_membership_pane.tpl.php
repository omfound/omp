<div id="membership-pane" class="pane">
  <h3 class="pane-title"><?php print $title; ?></h3>
  <div class="inner">
     <?php if (isset($message)): ?>
       <?php print $message; ?>
     <?php endif; ?>
     <?php if (isset($membership_type)): ?>
       <div class="label">Your Current Membership Plan:</div>
       <?php print $membership_type; ?>
     <?php endif; ?>
     <?php if (isset($membership_start)): ?>
       <div class="label">Start of Membership:</div>
       <?php print $membership_start; ?>
     <?php endif; ?>
     <?php if (isset($membership_end)): ?>
       <div class="label">End of Membership:</div>
       <?php print $membership_end; ?>
     <?php endif; ?>
     <?php if (isset($upgrade)): ?>
       <div class="divider">
         <?php print $upgrade; ?>
       </div>
     <?php endif; ?>
  </div>
</div>