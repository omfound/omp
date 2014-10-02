<div class="section upcoming-airings">
  <h3>Upcoming Airings</h3>
  <?php if (!empty($upcoming_airings)): ?>
    <?php foreach ($upcoming_airings AS $airing): ?>
      <div class="airing">
        <?php print $airing['airing']; ?> on <?php print $airing['channel']; ?>
      </div>
    <?php endforeach; ?>
  <?php else: ?>
    No upcoming airings.
  <?php endif; ?>
</div>

