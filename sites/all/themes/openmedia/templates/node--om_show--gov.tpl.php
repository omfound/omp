<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <h2><?php print $node->title; ?></h2>
    <?php if (isset($video)): ?>
      <?php print $video['content']; ?>
    <?php else: ?>
      <div id="video-processing" style="clear: left;">This video is currently processing, please check back later.</div>
    <?php endif; ?>

    <?php if (isset($video['status'])): ?>
      <?php if ($video['status'] == 'live'): ?>
        <div id="video-status video-live"></div>
      <?php elseif ($video['status'] == 'ondemand'): ?>
        <div id="video-status video-ondemand"></div>
      <?php endif; ?>
    <?php endif; ?>

    <?php if (!empty($node->field_om_calendar)) { ?>
      <div id="documents">
        <br />
        <?php $edit_view = str_replace('/pub', '/edit?rm=minimal', $node->field_om_calendar[$node->language][0]['url']); ?>
        <iframe src="<?php print $edit_view; ?>" width="100%" height="500" ></iframe> 
      </div>
    <?php } ?>
</article><!-- /.node -->
