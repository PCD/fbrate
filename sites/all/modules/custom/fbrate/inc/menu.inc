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
  return $items;
}

/**
 *
 */
function fbrate_menu_import_post_form() {
  // Is the logged in user logged with fb.
  global $user;
  $luser = user_load($user->uid);
  if ( !($access_token = field_fb_get_user_access_token($luser)) ) {
    $login_link = l('Conectar con FaceBook', 'fbrate/login', array('attributes'=>array('class'=>array('fb_login'))));
    $message = "<p>Necesitas Conectar con Facebook para usar esta función.</p><p>{$login_link}</p>";
    return $message;
  }
  
  // 
  $form = drupal_get_form('fbrate_import_post_form');
  return drupal_render($form);
}

