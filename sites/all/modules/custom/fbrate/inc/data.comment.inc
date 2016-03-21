<?php
/**
 * Saves a Comment Object.
 */
function fbrate_data_comment_save($node, $graphNode) {
  $fb_id = $graphNode['id'];
  if ( !($record = fbrate_data_comment_load($fb_id)) ) {
    return fbrate_data_comment_insert($node->nid, $graphNode);
  }
  
  // Update
  $fbrate_comment_id = $record['fbrate_comment_id'];
  return fbrate_data_comment_update($fbrate_comment_id, $graphNode);
}

/**
 * Updates a comment Object.
 */
function fbrate_data_comment_update($fbrate_comment_id, $graphNode) {
  return db_update('fbrate_comment')
  ->fields(array(
    'raw' => serialize($graphNode), 
  ))
  ->condition('fbrate_comment_id', $fbrate_comment_id, '=')
  ->execute();
}

/**
 * Search for an Existing comment Record.
 */
function fbrate_data_comment_load($fb_id) {
  return db_select('fbrate_comment', 'c')
  ->fields('c')
  ->condition('fb_id', $fb_id, '=')
  ->execute()
  ->fetchAssoc();
}

/**
 * Inserts a comment Object.
 */
function fbrate_data_comment_insert($nid, $graphNode) {
  return db_insert('fbrate_comment')
  ->fields(array(
    'nid' => $nid, 
    'timestamp' => time(), 
    'status' => 1, 
    'fb_id' => $graphNode['id'], 
    'date' => strtotime($graphNode['created_time']->date), 
    'updated' => 0, 
    'raw' => serialize($graphNode), 
  ))
  ->execute();
}

/**
 * Deletes All Comment records by its Nid.
 */
function fbrate_data_comment_delete_by_nid($nid) {
  return db_delete('fbrate_comment')
  ->condition('nid', $nid)
  ->execute();
}