<?php
/**
 * Implements hook_node_load.
 */
function fbrate_node_load($nodes, $types) {
  if ( !in_array('fb_post', $types) ) {
    return;
  }
  
  $nids = array();
  foreach($nodes as $node) {
    if ( $node->type == 'fb_post' ) {
      $nids[$node->nid] = $node->nid;
    }
  }
  if ( !($records = fbrate_data_post_load_by_nids($nids)) ) {
    return;
  }
  
  require_once drupal_get_path('module', 'fbrate') . '/vendor/autoload.php';
  foreach($records as $record) {
    $nodes[$record->nid]->graphNode = unserialize($record->raw);
  }
}
