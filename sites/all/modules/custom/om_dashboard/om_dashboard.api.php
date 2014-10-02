<?php

/**
 * Describe hooks and functions provided by om_dashboard
 */

/**
 * hook_om_dashboard_panes
 * @returns array()
 *   An array of dashboard panes with keys as follows:
 *   theme: required array of theme characteristics for hook_theme.
 *   menu: optional array of additional menu items for hook_menu.
 *   dependencies: optional array of module dependencies for the pane.
 *   access: optional permission to check for pane.
 */
function hook_om_dashboard_panes() {
  return array();
}