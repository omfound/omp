<?php $checkedout = FALSE;?>
<?php if (!empty($row->field_field_checkout_status[0]['raw']['value']) && $row->field_field_checkout_status[0]['raw']['value'] == "Overdue"):?>
  <div class = "reservation-overdue">
<?php else:?>
  <div class = "reservation">
<?php endif;?>
  <table class="reservation-info-table">
  <tr>
  <th class = "item-title">Item</th>
  <th class="user-title">Username</th>
  <th class="order-title">Order</th>
  <th class="line-item-title">Item</th>
  <th class = "checkout-status-title">Status</th>
  <th class = "payment-status">Payment</th>
  <th class = "checkout-options">Options</th>
  </tr>
  <tr>
    <td class="item-name">
      <?php print $fields['line_item_title']->content . '</br>';?>
    </td>
    <td class = "user-info">
      <?php $user = user_load($fields['uid']->raw);?>
      <?php if ($user->uid > 0) { ?>
        <?php $contact_info = profile2_load_by_user($user, 'contact_info'); ?>
        <?php if (!empty($contact_info->field_first_name[LANGUAGE_NONE][0]['safe_value'])) { ?>
          <?php $first_name = $contact_info->field_first_name[LANGUAGE_NONE][0]['safe_value']; ?>
        <?php } ?>
        <?php if (!empty($contact_info->field_last_name[LANGUAGE_NONE][0]['safe_value'])) { ?>
          <?php $last_name = $contact_info->field_last_name[LANGUAGE_NONE][0]['safe_value']; ?>
        <?php } ?>
        <?php if(!empty($first_name) && !empty($last_name)) { ?>
          <?php $full_name = $first_name.' '.$last_name; ?>
          <?php print '<a href = "../user/' . $user->uid . '">' . $full_name . '</a></br>';?>
        <?php } ?>
      <?php } ?>
    </td>
    <td class = "order-link">
      <?php $link_options = array('query' => drupal_get_destination());?>
      <?php print $fields['view_order']->content; ?>
    </td>
    <td class = "line-item-link">
      <?php $link_options = array('query' => drupal_get_destination());?>
      <?php print l('view', 'administer_reservations/line-item/'.$fields['line_item_id']->raw, $link_options); ?>
    </td>
    <td class="checkout-status">
      <?php if (!empty($row->field_field_checkout_status[0]['raw']['value']) && $row->field_field_checkout_status[0]['raw']['value'] == "Overdue"){?>
        <div class = "checkout_status_bad">
        <?php print $fields['field_checkout_status']->content;?>
        </div>
      <?php } else{?>
        <div class = "checkout_status_good">
        <?php if(empty($fields['field_checkout_status']->content)) { ?>
          <?php print 'Order Complete, Awaiting Checkout'; ?>
        <?php } else { ?>
          <?php print $fields['field_checkout_status']->content;?>
        <?php } ?>
        </div>
      <?php }?>
      </td>
      <td class="payment-status">
        <?php print $cr['payment']; ?> 
      </td>
      <td class="checkout-options">
      <?php if ($checkedout) { ?>
        <?php print 'Checked Out Product: ' . $fields['commerce_product']->content; ?>
      <?php } elseif(!empty($row->field_field_checkout_status[0]['raw']['value']) && $row->field_field_checkout_status[0]['raw']['value'] == 'Checked In') {?>
        <?php print 'Checked In Product: ' . $fields['commerce_product']->content; ?>
      <?php } ?>
      <?php if (!empty($cr['buttons'])) { ?>
        <?php foreach ($cr['buttons'] as $key => $button) { ?>
          <?php print $button; ?>
        <?php } ?>
      <?php } ?>
    </td>
  </table>
</div>
