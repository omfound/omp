<?php $rating_5 = round(($row->votingapi_vote_node_percent_vote_value / 100) * 5); ?>
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
      <?php dsm($fields); ?>
      <?php $comment_count = om_social_fb_comment_count(); ?>
      <?php if ($comment_count != 0) { ?>
        <?php print $coment_count; ?> Comment(s)
      <?php } ?>
    </div>
    <div class="voting-result floated">
      Rating: 
      <?php print $rating_5; ?>/5
    </div>
  </div>
</div>
