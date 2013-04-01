<?php //dpm($fields);?>
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
  <div class="add-to-cart item-data">
    <?php print $fields['field_crp_product_reference']->content;?>
  </div>
  <div class="nid item-data">
    <?php print $fields['nid']->content;?>
  </div>
</div>