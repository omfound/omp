<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div id="show-left">
    <?php if (isset($video)): ?>
      <?php print $video; ?>
    <?php endif; ?>
    <h2><?php print $node->title; ?></h2>
    <?php if (!empty($edit_link)) { ?>
    <div class="edit-link-wrapper">
      <?php print $edit_link; ?>
    </div>
    <?php } ?>
    <div id="show-details" class="clearfix">
      <?php if (isset($picture_rendered)): ?>
        <div id="show-details-left">
          <?php print $picture_rendered; ?>
        </div>
      <?php endif; ?>
      <div id="show-details-right" <?php print !empty($picture_rendered) ? "class='with-photo'" : "class='without-photo'"; ?>>
        <div id="author">
          <?php print $name; ?>
        </div>
        <div id="created" class="bold">
          <?php print $created; ?> | 
        </div>
        <?php if (!empty($show_theme)): ?>
          <div id="theme" class="bold">
            <?php print $show_theme; ?> | 
          </div>
        <?php endif; ?>
        <?php if (!empty($locally_produced)): ?>
          <div id="locally-produced" class="bold">
            <?php print $locally_produced; ?> | 
          </div>
        <?php endif; ?>
        <div id="view-count" class="bold">
          <?php print $view_count; ?> |
        </div>
        <div id="comment-count" class="bold">
          <?php $comment_count = om_social_fb_comment_count(); ?>
          <?php print $comment_count; ?> Comments
        </div>
      </div>
    </div>
    <?php if (isset($description)): ?>
      <div id="description" class="divider show-hide">
        <div class="inner">
          <?php print $description; ?>
        </div>
      </div>
    <?php endif; ?>
    <?php print render($content['comments']); ?>
  </div>
  <?php if (isset($node_right)): ?>
    <div id="show-right">
      <?php print $node_right; ?>
      <div id="voting" class="clearfix">
        <div id="voting-widget">
          <?php if (!empty($vote_summary)) { ?>
            <?php print $vote_summary; ?>
          <?php } ?>
          <?php print $vote_widget; ?>
          <?php if (!empty($bayesian_score)): ?>
            <?php print $bayesian_score; ?>
          <?php endif; ?>
        </div>
      <div id="voting-msg">
        <?php print $vote_message; ?>
      </div>
      <?php if (!empty($upcoming_airings)): ?>
        <?php print $upcoming_airings; ?>
      <?php endif; ?>
      <?php if (!empty($archive_link)): ?>
        <a href="https://archive.org/details/<?php print $archive_link; ?>">File at Archive.org</a>
      <?php endif; ?>
    </div>
  <?php endif; ?>
</article><!-- /.node -->
