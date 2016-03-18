<?php
// Implements hook menu
function fbrate_api_menu() {
  $items['fbrate/api'] = array(
    'access arguments' => array('consultar comentarios'),
    'page callback' => 'fbrate_api_menu_process',
    'type' => MENU_CALLBACK,
  );
  $items['admin/config/fbrate/api'] = array(
    'access arguments' => array('consultar comentarios'),
    'page callback' => 'fbrate_api_menu_admin',
    'type' => MENU_CALLBACK,
  );

  return $items;
}

// Admin page.
function fbrate_api_menu_admin(){
  return 'hola aun no creo esta pagina :)';
}

// Read the data incoming and return an json with the data 
function fbrate_api_menu_process(){
  $post_id = NULL;
  //print_r($_GET['post_id']); exit;
  if ($_GET['post_id'] > 0) {
    $post_id = $_GET['post_id'];
  }

  $fb_response = fbrate_api_request($post_id);
  print_r($fb_response); exit;
}