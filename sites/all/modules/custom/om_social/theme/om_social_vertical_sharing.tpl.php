<?php if (!empty($services)): ?>
<div id="vertical-social-sharing">
  <?php foreach ($services AS $key => $service): ?>
     <div id="vertical-<?php print $key; ?>" class="social-service"><?php print $service; ?></div>
  <?php endforeach; ?>
</div>
<?php endif; ?>
