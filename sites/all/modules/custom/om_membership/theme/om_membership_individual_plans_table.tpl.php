<section id="membership-table">
  <?php if (!empty($header)): ?>
    <div id="membership-header-links">
      <?php print $header; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($table_rows) && !empty($table_header)): ?>
    <table id="individual-membership-table">
      <thead>
        <?php print $table_header; ?>
      </thead>
      <?php print $table_rows; ?>
      <?php print $cost_row; ?>
      <?php print $link_row; ?>
    </table>
  <?php endif; ?>
</section>