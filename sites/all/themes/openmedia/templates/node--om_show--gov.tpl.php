<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <h2><?php print $node->title; ?></h2>
    <?php if (isset($video)): ?>
      <?php print $video; ?>
    <?php endif; ?>

    <?php if ($video_info['status'] == 'processing' && !empty($video_info['image'])) { ?>
      <div class="video-status video-processing"><?php print $video_info['image']; ?></div>
    <?php }elseif($video_info['status'] == 'processing') { ?>
      <div class="video-status video-processing">This video is currently processing, please check back later.</div>
    <?php } ?>

    <?php if ($video_info['status'] == 'live' && !empty($video_info['image'])) { ?>
      <div class="video-status video-live"><?php print $video_info['image']; ?></div>
    <?php } ?>

    <?php if ($video_info['status'] == 'ondemand' && !empty($video_info['image'])) { ?>
      <div class="video-status video-ondemand"><?php print $video_info['image']; ?></div>
    <?php } ?>
      
    <?php if (isset($description)): ?>
      <div id="gov-description">
          <?php print $description; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($node->field_om_calendar)) { ?>
      <div id="documents">
        <br />
        <?php if(strpos($node->field_om_calendar[$node->language][0]['url'], '/pub') !== false) { ?>
          <?php $edit_view = str_replace('/pub', '/edit?rm=minimal', $node->field_om_calendar[$node->language][0]['url']); ?>
        <?php }elseif(strpos($node->field_om_calendar[$node->language][0]['url'], '/edit') !== false) { ?>
          <?php $edit_view = str_replace('/edit', '/edit?rm=minimal', $node->field_om_calendar[$node->language][0]['url']); ?>
        <?php } ?>
        <iframe src="<?php print $edit_view; ?>" width="100%" height="500" ></iframe> 
      </div>
    <?php } ?>
</article><!-- /.node -->
