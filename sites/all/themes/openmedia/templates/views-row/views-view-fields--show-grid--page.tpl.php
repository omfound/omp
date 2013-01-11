<?php $rating_5 = round(($row->votingapi_vote_node_percent_vote_value / 100) * 5); ?>
<?php print $fields['field_show_thumbnail']->content; ?>
<?php print $fields['title']->content; ?>
<div class="counter-tray">
  <div class="view-count">
    <?php print $fields['totalcount']->content; ?> View(s)
  </div>
  <div class="comment-count">
    <?php print $fields['comment_count']->content; ?> Comment(s)
  </div>
  <div class="voting-result">
    <?php print $rating_5; ?>/5
  </div>
</div>
