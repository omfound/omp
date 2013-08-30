<?php if (!empty($airings)): ?>
  <table>
    <thead><th>Show</th><th>Airing Date</th><th>Channel</th></thead>
    <?php foreach ($airings AS $airing): ?>
      <tr><td><?php print $airing['show']; ?></td><td><?php print $airing['airing']; ?></td><td><?php print $airing['channel']; ?></td></tr>
    <?php endforeach; ?>
  </table>
<?php else: ?>
  <p>No upcoming airings.</p>
<?php endif; ?>
