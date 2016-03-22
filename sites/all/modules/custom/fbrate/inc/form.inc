<?php
/**
 * Returns a Drupal Form to import FB Post.
 */
function fbrate_import_post_form($form, &$form_state) {
  $form = array();
  $form['fb_url'] = array(
    '#type' => 'textfield', 
    '#title' => t('FB Post URL'), 
    '#required' => TRUE, 
  );
  $form['actions'] = array(
    '#type' => 'actions', 
    'submit' => array(
      '#type' => 'submit', 
      '#value' => t('Import'), 
    ), 
  );
  return $form;
}

/**
 * Process the submission of the form fbrate_import_post_form.
 */
function fbrate_import_post_form_submit(&$form, &$form_state) {
  $val = $form_state['values'];
  $url = $val['fb_url'];
  if ( !($graphNode = fbrate_fbapi_fetch_post($url)) ) {
    return false;
  }
  
  // Save Node
  if ( !($node = fbrate_fb_post_node_save($graphNode)) ) {
    return false;
  }
  drupal_set_message("Se ha importado el post exitosamente.");
  
  // Save Comments
  if ( fbrate_fb_post_comments_save($node, $graphNode) ) {
    drupal_set_message("Se han importado todos los comentarios exitosamente.");
  }
  drupal_goto("node/{$node->nid}");
  exit;
}