<div id="page">
  <header id="header" role="banner">
    <div id="header-inner" class="clearfix">
      <?php print render($page['header']); ?>
    </div>
  </header>
  <div id="above-content" class="clearfix">
    <?php print render($page['above_content']); ?>
  </div>
  <div id="main">
    <div class="inner">
      <div id="main-inner" class="clearfix">
        <div id="content" class="column" role="main">
          <?php print render($page['highlighted']); ?>
          <?php print $breadcrumb; ?>
          <a id="main-content"></a>
          <?php print render($title_prefix); ?>
          <?php if ($title): ?>
            <h1 class="title" id="page-title"><?php print $title; ?></h1>
          <?php endif; ?>
          <?php print render($title_suffix); ?>
          <?php print $messages; ?>
          <?php print render($tabs); ?>
          <?php print render($page['help']); ?>
          <?php if ($action_links): ?>
            <ul class="action-links"><?php print render($action_links); ?></ul>
          <?php endif; ?>
          <?php print render($page['content']); ?>
          <?php print $feed_icons; ?>
          <?php if (!empty($page['iframe_embed'])) { ?>
            <div id="page-iframe-embed">
              <label>Embed this page:</label>
              <textarea class="iframe-embed"><?php print $page['iframe_embed']; ?></textarea>
            </div>
          <?php } ?>
        </div><!-- /#content -->
        <?php
          // Render the sidebars to see if there's anything in them.
          $sidebar_first  = render($page['sidebar_first']);
          $sidebar_second = render($page['sidebar_second']);
        ?>
        <?php if ($sidebar_first || $sidebar_second): ?>
          <aside class="sidebars clearfix">
            <?php print $sidebar_first; ?>
            <?php print $sidebar_second; ?>
          </aside><!-- /.sidebars -->
        <?php endif; ?>
      </div>
    </div>
  </div><!-- /#main -->
</div><!-- /#page -->
<?php if (!empty($page['action_items'])): ?>
<div id="action-item">
  <div class="wrapper">
    <div id="action-item-inner" class="clearfix">
      <?php print render($page['action_items']); ?>
    </div>
  </div>
</div>
<?php endif; ?>
<div id="footer-wrapper">
  <div class="inner">
    <?php print render($page['footer']); ?>
  </div>
</div>
