<?php print $fields['field_class_image']->content; ?>
<div class="title">
  <?php print $fields['title_1']->content; ?>
</div>
<div class="date">
  <?php print $fields['field_class_date']->content; ?>
</div>
<?php if (!empty($fields['field_class_required_certs']->content)): ?>
  <div class="divider">
    <div class="inner">
      <div class="certifications-required">
        <div class="label">Certifications Required:</div>
        <?php print $fields['field_class_required_certs']->content; ?>
      </div>
    </div>
  </div>
<?php endif; ?>
<?php if (!empty($fields['field_class_earned_certs']->content)): ?>
  <div class="divider">
    <div class="inner">
      <div class="certifications-earned">
        <div class="label">Certifications Earned:</div>
        <?php print $fields['field_class_earned_certs']->content; ?>
      </div>
    </div>
  </div>
<?php endif; ?>
