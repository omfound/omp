<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if (isset($video)):?>
  <div class="project-video">
    <?php print $video; ?>
  </div>
  <?php endif; ?>
  <div id="project-top" class="clearfix project-top">
    <?php if (isset($project_title)): ?> 
    <?php print $project_title; ?>
    <?php endif; ?>
      <?php if (isset($logo)): ?>
        <div id="project-logo">
          <?php print $logo; ?>
        </div>
      <?php endif; ?>
      <div id="project-metadata">
        <?php if (isset($locally_produced)): ?>
          <div id="project-locally-produced">
            <div class="bold label">Production:</div>
            <div class="value"><?php print $locally_produced; ?></div>
          </div>
        <?php endif; ?>
        <?php if (isset($rating)): ?>
          <div id="project-rating">
            <div class="bold label">Rating:</div>
            <div class="value"><?php print $rating; ?></div>
          </div>
        <?php endif; ?>
        <?php if (isset($project_language)): ?>
          <div id="project-language">
            <div class="bold label">Language:</div>
            <div class="value"><?php print $project_language; ?></div>
          </div>
        <?php endif; ?>
        <?php if (isset($genre)): ?>
          <div id="project-genre">
            <div class="bold label">Genre:</div>
            <div class="value"><?php print $genre; ?></div>
          </div>
        <?php endif; ?>
        <?php if (isset($theme)): ?>
          <div id="project-theme">
            <div class="bold label">Theme:</div>
            <div class="value"><?php print $theme; ?></div>
          </div>
        <?php endif; ?>
      </div>
      <div id="project-date-author">
        <span class="bold"><?php print $created; ?> by <?php print $name; ?></span> - <?php print $view_count; ?>
      </div>
      <?php if (isset($description)): ?>
        <div id="project-description">
          <?php print $description; ?>
        </div>
      <?php endif; ?>
    </div>
    <?php if (isset($project_title)): ?>
   <h2>MORE FROM</h2><?php print $project_title; ?>
    <?php endif; ?> 
</article><!-- /.node -->
