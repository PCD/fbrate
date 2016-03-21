<?php
/**
 * Saves a Post Object.
 */
function fbrate_data_post_save($node, $graphNode) {
  $fb_id = $graphNode['id'];
  if ( !($record = fbrate_data_post_load($fb_id)) ) {
    return fbrate_data_post_insert($node, $graphNode);
  }
  
  // Update
  $node = node_load($record['nid']);
  return fbrate_data_post_update($node, $graphNode);
}

/**
 * Updates a Post Object.
 */
function fbrate_data_post_update($node, $graphNode) {
  return db_update('fbrate_post')
  ->fields(array(
    'last_sync' => time(), 
    'raw' => serialize($graphNode), 
  ))
  ->condition('nid', $node->nid, '=')
  ->execute();
}

/**
 * Inserts a Post Object.
 */
function fbrate_data_post_insert($node, $graphNode) {
  return db_insert('fbrate_post')
  ->fields(array(
    'nid' => $node->nid, 
    'timestamp' => $node->created, 
    'status' => 1, 
    'fb_id' => $graphNode['id'], 
    'date' => strtotime($graphNode['created_time']->format('r')), 
    'url' => $graphNode['link'], 
    'last_sync' => $node->created, 
    'last_comment' => 0, 
    'last_update' => 0, 
    'raw' => serialize($graphNode), 
  ))
  ->execute();
}

/**
 * Search for an Existing Post Record.
 */
function fbrate_data_post_load($fb_id) {
  return db_select('fbrate_post', 'p')
  ->fields('p')
  ->condition('fb_id', $fb_id, '=')
  ->execute()
  ->fetchAssoc();
}

/**
 * Search All records for an Existing Post Record by Node ids.
 */
function fbrate_data_post_load_by_nids($nids) {
  return db_select('fbrate_post', 'p')
  ->fields('p')
  ->condition('nid', $nids, 'IN')
  ->execute()
  ->fetchAllAssoc('nid');
}

/**
 * Search for an Existing Post Record.
 */
function fbrate_data_post_load_by_url($url) {
  return db_select('field_data_field_fb_post_url', 'u')
  ->fields('u')
  ->condition('field_fb_post_url_url', $url, '=')
  ->condition('entity_type', 'node', '=')
  ->condition('bundle', 'fb_post', '=')
  ->execute()
  ->fetchAssoc();
}

/**
 * Deletes a Post record by its Nid.
 */
function fbrate_data_post_delete_by_nid($nid) {
  $result = db_delete('fbrate_post')
  ->condition('nid', $nid)
  ->execute();
  
  if ( $result ) {
    return fbrate_data_comment_delete_by_nid($nid);
  }
  
  return $result;
}