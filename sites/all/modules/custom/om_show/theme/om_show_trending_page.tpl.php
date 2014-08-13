<div class = "filter">
  <?php print $filter; ?>
</div>

<div class = "show-grid">
  <?php foreach ($shows as $show) { ?>
    <div class="show-preview">
      <div class="show-image">
        <img src="<?php print $show['thumbnail_path']; ?>" />
      </div>
      <div class="show-meta">
        <div class="show-title">
          <?php print $show['title']; ?>
        </div>
        <div class="show-votes">
          Rating: <?php print $show['rating']; ?>
        </div>
      </div>
    </div>
  <?php } ?>
</div>
