<?php
/**
 * Loads an Existing Post Node.
 */
function fbrate_fb_post_node_load($graphNode) {
  // Try by Fb Id.
  $fb_id = $graphNode['id'];
  if ( ($record = fbrate_data_post_load($fb_id)) && ($node=node_load($record['nid'])) ) {
    return $node;
  }
  
  // Try by URL.
  $url = $graphNode['link'];
  if ( ($record = fbrate_data_post_load_by_url($url)) && ($node=node_load($record['entity_id'])) ) {
    return $node;
  }
  
  return false;
}

/**
 * Creates a Node FB Post.
 */
function fbrate_fb_post_node_save($graphNode) {
  $fb_id = $graphNode['id'];
  global $user;
  if ( !($node = fbrate_fb_post_node_load($graphNode)) ) {
    // New One
    $node = new stdClass();
    $node->type = "fb_post";
    node_object_prepare($node);
    $node->language = LANGUAGE_NONE;
    $node->uid = $user->uid;
    $node->status = 1;
    $node->promote = 0;
    $node->comments = 0;
    $node->last_comment_uid = $user->uid;
  } else {
    $node->changed = time();
  }
  
  
  $node->title = substr($graphNode['name'], 0, 32);
  $node->field_fb_post_url[LANGUAGE_NONE][0]['url'] = $graphNode['link'];
  $tz = $graphNode['created_time']->getTimezone();
  $node->field_date[LANGUAGE_NONE][0]['value'] = $graphNode['created_time']->getTimestamp();
  $node->field_date[LANGUAGE_NONE][0]['timezone'] = $tz->getName();
  $node->field_date[LANGUAGE_NONE][0]['offset'] = $graphNode['created_time']->getOffset();
  $node->field_date[LANGUAGE_NONE][0]['timezone_db'] = $tz->getName();
  $node->field_date[LANGUAGE_NONE][0]['date_type'] = 'datestamp';
  
  try{
    $node = node_submit($node);
    node_save($node);
  } catch(Exception $e) {
    drupal_set_message("Error on creating node:\n  - " . $e->getMessage(), 'error');
    drupal_goto('admin/fbrate/import/post');
    exit;
  }
  
  // Save Object
  fbrate_data_post_save($node, $graphNode);
  return $node;
}

/**
 * Implements hook_node_delete.
 */
function fbrate_node_delete($node) {
  switch($node->type) {
    case 'fb_post':
      fbrate_data_post_delete_by_nid($node->nid);
      break;
  }
}