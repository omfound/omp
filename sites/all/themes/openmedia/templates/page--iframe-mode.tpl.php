<div id="page" class="iframe">
  <?php if(!isset($node) || $node->type != 'om_show') { ?>
    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <h1 class="title" id="page-title"><?php print $title; ?></h1>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
  <?php } ?>
  <?php print render($page['content']); ?>
</div>
