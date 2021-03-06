<?php
/**
 * Return a map of all domains to anticipate
 */
function _omp_return_domains() {
  $domains = array();
  // Denver Open Media
  $domains['denveropenmedia.org'] = array(
    'ssl_enabled' => TRUE,
    'www_enabled' => TRUE
  );
  // Berkely Community Media
  $domains['bcmtv.org'] = array(
    'ssl_enabled' => TRUE,
    'www_enabled' => TRUE
  );
  // CMA
  $domains['cmaportal.ompnetwork.org'] = array(
    'ssl_enabled' => TRUE,
    'www_enabled' => FALSE
  );
  return $domains;
}

/**
 * Return a map of all aliases to track. Relationship goes request => redirect. 
 */
function _omp_return_aliases() {
  $aliases = array(
    // Denver Open Media
    'denveropenmedia.com' => 'denveropenmedia.org',
    'betv.org' => 'bcmtv.org'
  );
  return $aliases;
}

/**
 * Determine if we need a redirect and then perform it.
 */
function _omp_perform_redirect() {
  // Get current host key
  $current_host = _omp_clean_host();
  $domain_info = _omp_return_current_domain_info($current_host);
  // If no domain info is available do nothing.
  if (!empty($domain_info)) {
    // If we are dealing with an alias redirect to the correct form of that alias.
    if (!empty($domain_info['redirect'])) {
      if ($domain_info['ssl_enabled'] == TRUE) {
        $redirect = 'https://';
      }
      else {
        $redirect = 'http://';
      }
      if ($domain_info['www_enabled'] == TRUE) {
        $redirect .= 'www.';
      }
      $redirect .= $domain_info['redirect'];
    }
    else {
      // Otherwise correct the current path if anything is wrong.
      $request_contains_www = is_numeric(strpos($_SERVER['HTTP_HOST'], 'www')) ? TRUE : FALSE;
      $request_is_secure = !empty($_SERVER['HTTP_X_SSL']) && $_SERVER['HTTP_X_SSL'] == 'ON' ? TRUE : FALSE;
      if ($request_is_secure == FALSE && $domain_info['ssl_enabled'] == TRUE) {
        if ($domain_info['www_enabled'] == TRUE) {
          $redirect = 'https://www.';
        }
        else {
          $redirect = 'https://';
        }
      }
      else if ($request_is_secure == TRUE && $domain_info['ssl_enabled'] == TRUE) {
        if ($request_contains_www == FALSE && $domain_info['www_enabled'] == TRUE) {
          $redirect = 'https://www.';
        }
        else if ($request_contains_www == TRUE && $domain_info['www_enabled'] == FALSE) {
          $redirect = 'https://';
        }
      }
      else if ($domain_info['ssl_enabled'] == FALSE) {
        if ($request_contains_www == FALSE && $domain_info['www_enabled'] == TRUE) {
          $redirect = 'http://www.';
        }
        else if ($request_contains_www == TRUE && $domain_info['www_enabled'] == FALSE) {
          $redirect = 'http://';
        }
      }
      if (!empty($redirect)) {
        $redirect .= $current_host;
      }
    }
    // Perform redirect
    if (!empty($redirect)) { 
      $redirect .=  $_SERVER['REQUEST_URI'];
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
  $domains = _omp_return_domains();
  $aliases = _omp_return_aliases();
  // See if we have a domain
  if (!empty($domains[$key])) {
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
