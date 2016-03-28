<?php
/**
 * Saves a Comment Object.
 */
function fbrate_data_comment_save($node, $graphNode) {
  if ( !($record = fbrate_data_comment_load($graphNode['id'])) ) {
    return fbrate_data_comment_insert($node->nid, $graphNode);
  }
  
  // Update
  return fbrate_data_comment_update($record['fbrate_comment_id'], $graphNode);
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
  $query = db_select('fbrate_comment', 'c');
  $query->leftJoin('fbrate_comment_rating', 'r', 'c.fbrate_comment_id = r.fbrate_comment_id');
  $query->addField('c', 'fbrate_comment_id');
  $query->addField('c', 'nid');
  $query->addField('c', 'timestamp');
  $query->addField('c', 'status');
  $query->addField('c', 'fb_id');
  $query->addField('c', 'date');
  $query->addField('c', 'updated');
  $query->addField('c', 'raw');
  // Rate fields
  $query->addField('r', 'uid', 'rate_uid');
  $query->addField('r', 'rate', 'rate_value');
  $query->addField('r', 'timestamp', 'rate_timestamp');
  $query->addField('r', 'muid', 'rate_muid');
  $query->addField('r', 'status', 'rate_status');
  $query->addField('r', 'mtimestamp', 'rate_mtimestamp');
  $query->condition('fb_id', $fb_id, '=');
  $results = $query->execute();
  return $results->fetchAssoc();
}

/**
 * Search for an Existing comment Record.
 */
function fbrate_data_comment_load_by_cid($cid) {
  $query = db_select('fbrate_comment', 'c');
  $query->leftJoin('fbrate_comment_rating', 'r', 'c.fbrate_comment_id = r.fbrate_comment_id');
  $query->addField('c', 'fbrate_comment_id');
  $query->addField('c', 'nid');
  $query->addField('c', 'timestamp');
  $query->addField('c', 'status');
  $query->addField('c', 'fb_id');
  $query->addField('c', 'date');
  $query->addField('c', 'updated');
  $query->addField('c', 'raw');
  // Rate fields
  $query->addField('r', 'uid', 'rate_uid');
  $query->addField('r', 'rate', 'rate_value');
  $query->addField('r', 'timestamp', 'rate_timestamp');
  $query->addField('r', 'muid', 'rate_muid');
  $query->addField('r', 'status', 'rate_status');
  $query->addField('r', 'mtimestamp', 'rate_mtimestamp');
  $query->condition('c.fbrate_comment_id', $cid, '=');
  $results = $query->execute();
  return $results->fetchAssoc();
}

/**
 * Search for an Existing comment Record.
 */
function fbrate_data_comment_load_all_id_by_nid($nid) {
  $query = db_select('fbrate_comment', 'c');
  $query->addField('c', 'fbrate_comment_id');
  $query->condition('nid', $nid, '=');
  $results = $query->execute();
  return $results->fetchAllAssoc('fbrate_comment_id');
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
    'date' => strtotime($graphNode['created_time']->format('r')), 
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
