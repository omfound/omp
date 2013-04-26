<?php print $fields['field_news_image']->content; ?>
<div class="title">
  <?php print $fields['title']->content; ?>
</div>
<div class="created">
  <?php print date('Y-m-d g:ia', $row->node_created); ?>
</div>
<div class="body">
  <?php print $fields['body']->content; ?>
</div>
<div class="read-more">
  <?php print l('Read More >>', 'node/' . $row->nid); ?>
</div>
