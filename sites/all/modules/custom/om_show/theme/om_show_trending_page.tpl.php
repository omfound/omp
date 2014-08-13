<div class = "filter">
  <?php print $filter; ?>
</div>

<div class = "show-grid">
  <?php foreach ($shows as $show) { ?>
    <div class="show-preview">
      <div class="show-image">
        <a href="<?php print $show['link']; ?>">
          <img src="<?php print $show['thumbnail_path']; ?>" />
        </a>
      </div>
      <div class="show-meta">
        <div class="show-title">
          <a href="<?php print $show['link']; ?>">
            <?php print $show['title']; ?>
          </a>
        </div>
        <div class="show-stats">
          <span class="show-label">Rating: </span><?php print $show['rating']; ?> | <span class="show-label">Views: </span><?php print $show['views']; ?>
        </div>
        <div class="voting-widget">
          <?php print $show['voting_widget']; ?>
        </div>
      </div>
    </div>
  <?php } ?>
</div>

<div class = "pager">
  <?php print $pager; ?>
</div>
