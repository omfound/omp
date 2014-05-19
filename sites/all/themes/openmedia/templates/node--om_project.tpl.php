<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if (isset($video)):?>
  <div class="clearfix">
    <div class="project-video">
      <?php print $video; ?>
   </div>
    <?php endif; ?>
    <div id="project-top" class="clearfix project-top">
      <?php if (isset($project_title)): ?> 
      <?php print $project_title; ?>
      <?php endif; ?>
        <?php if (isset($description)): ?>
          <div id="project-description">
            <?php print $description; ?>
          </div>
        <?php endif; ?>
        <div id="project-metadata">
          <div id="project-date-author">
-           <span class="bold">Producer: <?php print $name; ?></span>
-         </div>
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
          <?php if (isset($theme)): ?>
            <div id="project-theme">
              <div class="bold label">Theme:</div>
              <div class="value"><?php print $theme; ?></div>
            </div>
          <?php endif; ?>
        </div>
      </div>
  </div>
    <div class="featured-video-area">
      <?php if (isset($video_title)): ?>
      <div class="featured-video-title">
        <?php print $video_title; ?>
      </div>
      <?php endif; ?>
      <?php if (isset($video_description)): ?>
      <div class="featured-video-description">
        <?php print $video_description; ?>
      </div>
      <?php endif; ?>
      <?php if (isset($video_published)): ?>
      <div class="featured-video-date">
        <?php print $video_published; ?>
      </div>
      <?php endif; ?>
    </div>
  <div class="middle-project">
    <div class="project-line">
    <?php if (isset($project_title)): ?>
    <div class="project-lower-title">
      <h2 class="more-from">MORE FROM <?php print $project_title; ?></h2>
    </div>
    </div>
    <?php endif; ?>
  </div>
</article><!-- /.node -->
