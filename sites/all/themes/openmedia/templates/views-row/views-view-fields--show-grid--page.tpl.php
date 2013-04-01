<?php $rating_5 = round(($row->votingapi_cache_node_average_value / 100) * 5); ?>
<?php print $fields['field_show_thumbnail']->content; ?>
<div class="title">
  <?php print $fields['title']->content; ?>
</div>
<div class="counter-tray divider">
  <div class="inner clearfix">
    <div class="view-count floated">
      <?php print $fields['totalcount']->content; ?> View(s)
    </div>
    <div class="comment-count floated">
      <?php $options = array('absolute' => TRUE); ?>
      <?php $url = url('node/' . $row->nid, $options); ?>
      <?php $comment_count = om_social_fb_comment_count($url); ?>
      <?php if ($comment_count != 0) { ?>
        <?php print $comment_count; ?> Comment(s)
      <?php } ?>
    </div>
    <div class="voting-result floated">
      Rating: 
      <?php print $rating_5; ?>/5
    </div>
  </div>
</div>
