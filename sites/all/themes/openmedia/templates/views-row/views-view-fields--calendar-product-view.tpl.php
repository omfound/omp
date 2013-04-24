<div class = "item">
  <div class = "small-image item-data">
    <?php print $fields['field_image']->content;?>
  </div>
  <div class  = "title item-data">
    <?php print $fields['title']-> content;?>
  </div>
  <div class = "body item-data">
    <?php print $fields['body']->content;?>
  </div>
  <?php if (!empty($fields['commerce_price']->content) && $fields['commerce_price']->content != '<div class="field-content"></div>'):?>
    <div class = "price item-data">
      <?php print '<span class="price-label">Price (per hour): </span>' . $fields['commerce_price']->content;?>
    </div>
  <?php endif;?>
  <?php if (!empty($fields['field_commercial_cost']->content) && $fields['field_commercial_cost']->content != '<div class="field-content"></div>'):?>
    <div class = "commercial-cost item-data">
      <?php print $fields['field_commercial_cost']->content;?>
      <label for = "commercial-cost">(Commercial)</label>
    </div>
  <?php endif;?>
  <div class="add-to-cart item-data">
    <?php print $fields['field_crp_product_reference']->content;?>
  </div>
  <div class="nid item-data">
    <?php print $fields['nid']->content;?>
  </div>
  <div class="large-image item-data">
    <?php print $fields['field_image_1']->content;?>
  </div>
</div>
