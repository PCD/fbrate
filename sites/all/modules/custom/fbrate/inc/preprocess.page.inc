<?php
/**
 * Implements hook_preprocess_page.
 */
function fbrate_preprocess_page(&$vars) {
  if ( arg(0) == 'node' && intval(arg(1)) > 1 && is_null(arg(2)) && ($node=node_load(arg(1))) ) {
    if ( $node->type = 'fb_post' ) {
      drupal_add_js(drupal_get_path('module', 'fbrate') . '/js/fbrate.commentsLoad.js');
    }
  }
}
