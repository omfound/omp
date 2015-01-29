<div class = "item">
  <div class = "small-image item-data">
    <?php if (!empty($fields['field_image']->content)) { ?>
      <?php print $fields['field_image']->content;?>
    <?php } ?>
  </div>
  <div class  = "title item-data">
    <?php print $fields['title']-> content;?>
  </div>
  <div class = "body item-data">
    <?php if (!empty($fields['body']->content)) { ?>
      <?php print $fields['body']->content; ?>
    <?php } ?>
  </div>
  <?php if (!empty($fields['commerce_price']->content) && $fields['commerce_price']->content != '<div class="field-content"></div>'):?>
    <?php //watchdog('brian', '<pre>'.print_r($fields, TRUE).'</pre>'); ?>
    <?php if (!empty($fields['field_charge_by_the_']->content)) { ?>
      <?php $period = $fields['field_charge_by_the_']->content; ?>
    <?php } else { ?>
      <?php $period = 'Hourly'; ?>
    <?php } ?>
    <div class = "price item-data">
      <?php print '<span class="price-label">Commercial Rate ('.$period.'): </span>' . $fields['commerce_price']->content;?>
    </div>
  <?php endif;?>
  <?php if (!empty($fields['field_certifications_required']->content) && !variable_get('cr_hide_certs', 0)) { ?>
    <div class = "certifications item-data">
      <?php print '<span class="certifications-label">Certifications Required: </span>' . $fields['field_certifications_required']->content;?>
    </div>
  <?php } ?>
  <?php if (!empty($fields['field_commercial_cost']->content) && $fields['field_commercial_cost']->content != '<div class="field-content"></div>'):?>
    <div class = "commercial-cost item-data">
      <?php print $fields['field_commercial_cost']->content;?>
      <label for = "commercial-cost">(Commercial)</label>
    </div>
  <?php endif;?>
  <div class="nid item-data">
    <?php print $fields['nid']->content;?>
  </div>
  <div class="pid item-data">
    <?php print $fields['product_id']->content;?>
  </div>
  <div class="large-image item-data">
    <?php if (!empty($fields['field_image_1']->content)) { ?>
      <?php print $fields['field_image_1']->content;?>
    <?php } ?>
  </div>
</div>
