<?php

function commerce_login_commerce_checkout_router($order, $checkout_page) {
  if(user_is_anonymous()) {
    dsm('Intercepting checkout and sending to login');
  }
  //drupal_goto('join-fstv/store-checkout');
}
