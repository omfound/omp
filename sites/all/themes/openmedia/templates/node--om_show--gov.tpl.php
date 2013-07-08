<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php $show_status_images = om_theme_assets_show_status_images(); ?>
    <h2><?php print $node->title; ?></h2>
    <?php if (isset($video) && $video['status'] != 'processing'): ?>
      <?php print $video['content']; ?>
    <?php endif; ?>

    <?php if ($video_info['status'] == 'processing' && !empty($video_info['image'])) { ?>
      <div id="video-status video-processing"><?php print $video_info['image']; ?></div>
    <?php }elseif($video_info['status'] == 'processing') { ?>
      <div id="video-status video-processing">This video is currently processing, please check back later.</div>
    <?php } ?>

    <?php if ($video_info['status'] == 'live' && !empty($video_info['image'])) { ?>
      <div id="video-status video-live"><?php print $video_info['image']; ?></div>
    <?php } ?>

    <?php if ($video_info['status'] == 'ondemand' && !empty($video_info['image'])) { ?>
      <div id="video-status video-ondemand"><?php print $video_info['image']; ?></div>
    <?php } ?>
      
    <?php if (!empty($node->field_om_calendar)) { ?>
      <div id="documents">
        <br />
        <?php $edit_view = str_replace('/pub', '/edit?rm=minimal', $node->field_om_calendar[$node->language][0]['url']); ?>
        <iframe src="<?php print $edit_view; ?>" width="100%" height="500" ></iframe> 
      </div>
    <?php } ?>
</article><!-- /.node -->
