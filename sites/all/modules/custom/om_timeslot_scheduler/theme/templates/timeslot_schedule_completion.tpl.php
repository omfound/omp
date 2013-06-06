<div id="schedule-results">
  <p><?php print $variables['message']; ?></p>
  <?php if (isset($variables['schedule_results'])): ?>
    <?php foreach ($variables['schedule_results'] AS $result): ?>
      <table>
        <caption><?php print l($result['timeslot']->title, 'node/' . $result['timeslot']->nid); ?></caption>
        <thead>
          <th>Day</th>
          <th>Start Time</th>
          <th>End Time</th>
          <th>Duration</th>
          <th>Show Title</th>
        </thead>
        <?php foreach($result['shows'] AS $show): ?>
          <tr>
            <td>
              <?php print date('n-d (D)', $show->start); ?>
            </td>
            <td>
              <?php print date('H:i:s', $show->start); ?>
            </td>
            <td>
              <?php print date('H:i:s', $show->end); ?>
            </td>
            <td>
              <?php print $show->end - $show->start; ?>
            </td>
            <td>
              <?php print l($show->title, 'node/' . $show->nid); ?>
            </td>
          </tr>
        <?php endforeach; ?>
      </table>
    <?php endforeach; ?>
  <?php endif; ?>
</div>
<?php if (isset($variables['commit_form'])): ?>
  <?php print $variables['commit_form']; ?>
<?php endif; ?>