<?php
/**
 * Creates a Node FB Post.
 */
function fbrate_fb_post_node_save($url, $graphNode) {
  global $user;
  $node = new stdClass();
  $node->type = "fb_post";
  node_object_prepare($node);
  $node->language = LANGUAGE_NONE;
  $node->uid = $user->uid;
  $node->status = 1;
  $node->promote = 0;
  $node->title = substr($graphNode['name'], 0, 32);
  //$node->field_publication_date[LANGUAGE_NONE][0]['value'] = date('Y-m-d', $raw['date']);
  $node->body[LANGUAGE_NONE][0]['value'] = $graphNode['name'];
  $node->body[LANGUAGE_NONE][0]['format'] = 'filtered_html';
  $node->body[LANGUAGE_NONE][0]['safe_value'] = check_markup($graphNode['name'], 'filtered_html');
  
  $node->field_fb_post_url[LANGUAGE_NONE][0]['url'] = $url;
  $node->field_fb_graph_node[LANGUAGE_NONE][0]['value'] = serialize($graphNode);
  $node->field_fb_graph_node[LANGUAGE_NONE][0]['format'] = 'filtered_html';
  $node->field_fb_graph_node[LANGUAGE_NONE][0]['safe_value'] = check_markup(serialize($graphNode), 'filtered_html');
  
  try{
    $node = node_submit($node);
    node_save($node);
  } catch(Exception $e) {
    drupal_set_message("Error on creating node:\n  - " . $e->getMessage(), 'error');
    drupal_goto('admin/fbrate/import/post');
    exit;
  }
  
  drupal_set_message("Se ha importado el post exitosamente.");
  drupal_goto("node/{$node->nid}");
  exit;
}
