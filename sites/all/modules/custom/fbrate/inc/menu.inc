<?php
/**
 * Implements hook_menu.
 */
function fbrate_menu() {
  $items = array();
  $items['admin/fbrate/import/post'] = array(
    'title' => 'Import Post', 
    'page callback' => 'fbrate_menu_import_post_form', 
    'access arguments' => array('Use import post form'), 
    'type' => MENU_CALLBACK, 
  );
  $items['fbrate/login'] = array(
    'title' => 'Login Callback', 
    'page callback' =>'fbrate_menu_login', 
    'access arguments' => array('Connect with Facebook'), 
    'type' => MENU_CALLBACK, 
  );
  $items['fbrate/login/process'] = array(
    'title' => 'Login Callback', 
    'page callback' =>'fbrate_menu_login_process', 
    'access arguments' => array('Connect with Facebook'), 
    'type' => MENU_CALLBACK, 
  );
  $items['node/%node/fbrefresh'] = array(
    'title' => 'Refrescar', 
    'page callback' => 'fbrate_menu_fb_refresh', 
    'page arguments' => array(1), 
    'access arguments' => array('Use import post form'), 
    'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE, 
    'type' => MENU_LOCAL_TASK, 
    'weight' => 2,
  );
  return $items;
}

/**
 * Presents a Facebook Login Link.
 */
function fbrate_menu_login() {
  // Is the logged in user logged with fb.
  global $user;
  $luser = user_load($user->uid);
  if ( !($access_token = field_fb_get_user_access_token($luser)) ) {
    $login_url = fbrate_get_fb_login_url();
    $login_link = "<a href=\"{$login_url}\" class=\"fb_login\">Conectar con FaceBook</a>";
    $message = "<p>Necesitas Conectar con Facebook para usar esta función.</p><p>{$login_link}</p>";
    return $message;
  } else {
    $message = "<p>Estas Conectado con Facebook.</p>";
    return $message;
  }
}

/**
 * Shows a Form to Import FB Post URL.
 */
function fbrate_menu_import_post_form() {
  fbrate_fb_connect();
  
  // 
  $form = drupal_get_form('fbrate_import_post_form');
  return drupal_render($form);
}

function fbrate_menu_fb_refresh($node) {
  $url = $node->field_fb_post_url[LANGUAGE_NONE][0]['url'];
  if ( ($graphNode = fbrate_fbapi_fetch_post($url)) ) {
    fbrate_fb_post_node_save($graphNode);
    drupal_set_message("Se ha refrescado el post exitosamente.");
    drupal_goto("node/{$node->nid}");
    exit;
  }
}
