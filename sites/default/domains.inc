<?php

$domains = array();
// Denver Open Media #DOM
$domains['denveropenmedia.org'] = array(
  'ssl_enabled' => TRUE,
  'www_enabled' => TRUE
);

$aliases = array(
  // Denver Open Media #DOM
  'denveropenmedia.com' => 'denveropenmedia.org',
);

function _omp_perform_redirect() {
  $current_host = _omp_clean_host();
  $domain_info = _omp_return_current_domain_info($current_host);
  print "<pre>";
  print $current_host;
  print "\n";
  print_r($domain_info);
  print "</pre>";
  if (!empty($domain_info)) {
    if ((!isset($_SERVER['HTTP_X_SSL']) || $_SERVER['HTTP_X_SSL'] != 'ON') && $domain_info['ssl_enabled'] == TRUE) {
      $redirect = 'https://';
    }
    $request_contains_www = is_numeric(strpos($_SERVER['HTTP_HOST'], 'www')) ? TRUE : FALSE;
    if ($domain_info['www_enabled'] != $request_contains_www) {
      if (empty($redirect)) {
        $redirect = 'http://';
      }
      if ($domain_info['www_enabled'] == TRUE) {
        $redirect .= 'www.';
      }
    }
    print "MADE IT HERE: " . $redirect;
    if (!empty($redirect)) { 
      $redirect .= $current_host .  $_SERVER['REQUEST_URI'];
      header('HTTP/1.0 301 Moved Permanently');
      header('Location: ' . $redirect);
      exit(); 
    }
  }
}

/**
 * Use the above lookups to return information about the
 * current domain and if we need to perform any redirects.
 *
 * @param $key cleaned string of current url with no www, preceeding or trailing slashes.
 *
 * @returns array entry from above or boolean FALSE
 */
function _omp_return_current_domain_info($key) {
  global $domains, $aliases;
  print_r($domains);
  // See if we have a domain
  if (!empty($domains[$key])) {
    $domains[$key]['redirect'] = $key;
    return $domains[$key];
  }
  // See if we have an alias
  if (!empty($aliases[$key])) {
    // Include a convenience key 'redirect'.
    $domains[$aliases[$key]]['redirect'] = $aliases[$key]; 
    return $domains[$aliases[$key]];
  }
  return FALSE;
}

/**
 * Return a cleaned version of the $_SERVER['HTTP_HOST'] variable with no www, preceeding or trailing slashes.
 */
function _omp_clean_host() {
  return trim(str_replace('www.', '', $_SERVER['HTTP_HOST']), '/');
}
