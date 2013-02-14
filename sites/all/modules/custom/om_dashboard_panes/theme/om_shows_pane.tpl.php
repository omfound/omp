<div id="membership-pane" class="pane">
  <h3 class="pane-title"><?php print $title; ?></h3>
  <div class="inner">
     <?php if (isset($message)): ?>
       <?php print $message; ?>
     <?php endif; ?>
     <?php if (isset($show_output)): ?>
       <?php print $show_output; ?>
     <?php endif; ?>
     <?php if (isset($add_link)): ?>
       <div class="divider">
         <?php print $add_link; ?>
       </div>
     <?php endif; ?>
  </div>
</div>