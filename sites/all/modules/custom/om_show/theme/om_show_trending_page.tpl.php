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
          <?php print $show['title']; ?>
        </div>
        <div class="show-votes">
          Rating: <?php print $show['rating']; ?>
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
