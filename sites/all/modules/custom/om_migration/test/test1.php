<?php
global $user;
$product_id = 1;

// Create the new order in checkout; you might also check first to
// see if your user already has an order to use instead of a new one.
$order = commerce_order_new($user->uid, 'checkout_checkout');

// Save the order to get its ID.
commerce_order_save($order);

// try to set created date of order that was one month ago
$order->created = time() - 3600*24*30;
// Load whatever product represents the item the customer will be
// paying for and create a line item for it.
$product = commerce_product_load($product_id);
$line_item = commerce_product_line_item_new($product, 1, $order->order_id);

// Save the line item to get its ID.
commerce_line_item_save($line_item);

// Add the line item to the order using fago's rockin' wrapper.
$order_wrapper = entity_metadata_wrapper('commerce_order', $order);
$order_wrapper->commerce_line_items[] = $line_item;

// Save the order again to update its line item reference field.
commerce_order_save($order);

// Redirect to the order's checkout form. Obviously, if this were a
// form submit handler, you'd just set $form_state['redirect'].
drupal_goto('checkout/' . $order->order_id);
?>
