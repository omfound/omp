<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php if (isset($video)): ?>
      <?php print $video; ?>
    <?php endif; ?>
    <h2><?php print $node->title; ?></h2>
    <div class="edit-link-wrapper">
      <?php print $edit_link; ?>
    </div>
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
      </div>
    </div>
    <div class="divider">
      <div class="inner">
        <?php print render($content['comments']); ?>
      </div>
    </div>
    <?php if (!empty($node->field_om_calendar)) { ?>
      <div id="documents">
        <?php $edit_view = str_replace('/pub', '/edit', $node->field_om_calendar[$node->language][0]['url']); ?>
        <iframe src="<?php print $edit_view; ?>" width="100%" height="500" ></iframe> 
      </div>
    <?php } ?>
</article><!-- /.node -->
