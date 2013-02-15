<?php
/**
 * Implementations of hook_preprocess_HOOK
 */
function om_social_preprocess_facebook_share(&$variables) {
  if (empty($variables['url'])) {
    $variables['url'] = 'http://' . $_SERVER['HTTP_HOST'] . '/' . $_GET['q'];
  }
  $js = "(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = \"//connect.facebook.net/en_US/all.js#xfbml=1\";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));";
  drupal_add_js($js, 'inline');
}

function om_social_preprocess_twitter_share(&$variables) {
  $js = '!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0];if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src="//platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");';
  drupal_add_js($js, 'inline');
}

function om_social_preprocess_pinterest_share(&$variables) {
  if (empty($variables['url'])) {
    $variables['url'] = 'http://' . $_SERVER['HTTP_HOST'] . '/' . $_GET['q'];
  }
  //drupal_add_js('//assets.pinterest.com/js/pinit.js', 'external');
}

function om_social_preprocess_google_share(&$variables) {
  $js = "(function() {
    var po = document.createElement('script'); po.type = 'text/javascript'; po.async = true;
    po.src = 'https://apis.google.com/js/plusone.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(po, s);
  })();";
  drupal_add_js($js, 'inline');
}
