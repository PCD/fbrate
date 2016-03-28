<?php
/**
 * Saves a Comment Rating Object.
 */
function fbrate_data_comment_rating_save($params) {
  if ( !($record = fbrate_data_comment_rating_load($params['fbrate_comment_id'])) ) {
    return fbrate_data_comment_rating_insert($params);
  }
  
  // Update
  return fbrate_data_comment_rating_update($params);
}

/**
 * Inserts a comment Object.
 */
function fbrate_data_comment_rating_insert($params) {
  return db_insert('fbrate_comment_rating')
  ->fields(array(
    'fbrate_comment_id' => $params['fbrate_comment_id'], 
    'uid' => $params['uid'], 
    'rate' => $params['rate'], 
    'timestamp' => $params['timestamp'], 
  ))
  ->execute();
}

/**
 * Updates a comment Rating Object.
 */
function fbrate_data_comment_rating_update($params) {
  $db_query = db_update('fbrate_comment_rating');
  if ( !isset($params['muid']) ) {
    $db_query->fields(array(
      'rate' => $params['rate'], 
      'timestamp' => $params['timestamp'], 
    ));
  } else {
    $db_query->fields(array(
      'rate' => $params['rate'], 
      'timestamp' => $params['timestamp'], 
      'muid' => $params['muid'], 
      'status' => $params['status'], 
      'mtimestamp' => $params['mtimestamp'], 
    ));
  }
  
  
  return $db_query->condition('fbrate_comment_id', $params['fbrate_comment_id'], '=')
  ->execute();
}

/**
 * Search for an Existing comment rating Record.
 */
function fbrate_data_comment_rating_load($fbrate_comment_id) {
  return db_select('fbrate_comment_rating', 'r')
  ->fields('r')
  ->condition('fbrate_comment_id', $fbrate_comment_id, '=')
  ->execute()
  ->fetchAssoc();
}

/**
 * Search for an Existing comment rating Record by Node ID.
 */
function fbrate_data_comment_rating_load_by_nid($nid) {
  return db_select('fbrate_comment_rating', 'r')
  ->join('fbrate_comment', 'c', 'c.fbrate_comment_id = r.fbrate_comment_id')
  ->join('fbrate_post', 'p', 'p.nid = c.nid')
  ->fields('r')
  ->condition('p.nid', $nid, '=')
  ->execute()
  ->fetchAllAssoc('fbrate_comment_id');
}
