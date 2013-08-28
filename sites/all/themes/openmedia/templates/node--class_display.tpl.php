<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div id="class-node-left">
    <?php print render($content['product:field_class_image']); ?>
    <?php if (isset($instructor) && isset($instructor_bio)): ?>
    <div id="instructor-profile">
      <div class="label">About the instructor</div>
      <div id="instructor-name">
      <?php print $instructor; ?>
      </div>
      <div id="instructor-bio">
        <?php print $instructor_bio; ?>
      </div>
      <div id="instructor-email">
        <div class="label">Email the Instructor</div>
        <?php print $instructor_email; ?>
      </div>
    </div>
    <?php endif; ?>
  </div>
  <div id="class-node-right">
    <?php if (!empty($registration_box)): ?>
      <?php print $registration_box; ?>
    <?php endif; ?>
    <div id="description">
      <div class="label">Description:</div>
      <?php print render($content['product:field_class_description']); ?>
    </div>
    <?php if (isset($materials_provided)): ?>
      <div id="materials-provided">
        <div class="label">Materials provided:</div>
        <?php print $materials_provided; ?>
      </div>
    <?php endif; ?>
    <?php if (isset($what_to_bring)): ?>
      <div id="what-to-bring">
        <div class="label">What to bring:</div>
        <?php print $what_to_bring; ?>
      </div>
    <?php endif; ?>
    <?php if (isset($certs_required)): ?>
      <div id="required-certs">
        <div class="label">Certifications required for this class: </div>
        <?php print $certs_required; ?>
      </div>
    <?php endif; ?>
    <?php if (isset($certs_earned)): ?>
      <div id="earned-certs">
        <div class="label">Certifications earned by this class: </div>
        <?php print $certs_earned; ?>
      </div>
    <?php endif; ?>
  </div>
</article>