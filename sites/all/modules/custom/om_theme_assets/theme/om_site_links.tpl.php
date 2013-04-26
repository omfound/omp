<?php if (!empty($links)): ?>
<ul id="persistant-site-links">
  <?php foreach ($links AS $link): ?>
     <li><?php print $link; ?></li>
  <?php endforeach; ?>
</ul>
<?php endif; ?>