<?php
/**
 * Implements hook_menu.
 */
function fbrate_menu() {
  $items = array();
  $items['admin/fbrate/import/post'] = array(
    'title' => 'Importar FB Post', 
    'page callback' => 'fbrate_menu_import_post_form', 
    'access arguments' => array('Use import post form'), 
    'type' => MENU_NORMAL_ITEM, 
    'menu_name' => 'main-menu', 
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
  $items['fbrate/comment/%'] = array(
    'page callback' => 'fbrate_menu_comment_load', 
    'page arguments' => array(2), 
    'access arguments' => array('Read Post Comments'), 
    'type' => MENU_CALLBACK, 
  );
  $items['fbrate/comment/%/good'] = array(
    'page callback' => 'fbrate_menu_comment_rating', 
    'page arguments' => array(2, '100'), 
    'access arguments' => array('Rate Comments'), 
    'type' => MENU_CALLBACK, 
  );
  $items['fbrate/comment/%/bad'] = array(
    'page callback' => 'fbrate_menu_comment_rating', 
    'page arguments' => array(2, '0'), 
    'access arguments' => array('Rate Comments'), 
    'type' => MENU_CALLBACK, 
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
  if ( !($graphNode = fbrate_fbapi_fetch_post($url)) ) {
    drupal_set_message("No fue posible obtener nuevos datos para refrescar el post.");
    drupal_goto("node/{$node->nid}");
    exit;
  }
  
  if ( !($node = fbrate_fb_post_node_save($graphNode)) ) {
    drupal_set_message("No fue posible guardar los datos al refrescar el post.");
    drupal_goto("node/{$node->nid}");
    exit;
  }
  
  // Save Comments
  if ( fbrate_fb_post_comments_save($node, $graphNode) ) {
    drupal_set_message("Se han importado todos los comentarios exitosamente.");
  }
  
  drupal_set_message("Se ha refrescado el post exitosamente.");
  drupal_goto("node/{$node->nid}");
  exit;
}

/**
 * Loads a Comment by its ID.
 */
function fbrate_menu_comment_load($cid) {
  require_once drupal_get_path('module', 'fbrate') . '/vendor/autoload.php';
  $data = fbrate_data_comment_load_by_cid($cid);
  $graphNode = unserialize($data['raw']);
  $return = array(
    'cid' => $data['fbrate_comment_id'], 
    'id' => $graphNode['id'], 
    'created' => $graphNode['created_time']->format('r'), 
    'from' => $graphNode['from']['name'], 
    'like_count' => $graphNode['like_count'], 
    'message' => $graphNode['message'], 
    'parent' => 0, 
    'rate_status' => (is_null($data['rate_uid'])?0:1), 
    'rate' => array(
      'uid' => $data['rate_uid'], 
      'value' => $data['rate_value'], 
      'timestamp' => $data['rate_timestamp'], 
      'muid' => $data['rate_muid'], 
      'status' => $data['rate_status'], 
      'mtimestamp' => $data['rate_mtimestamp'], 
    ), 
  );
  if ( isset($graphNode['parent']) ) {
    $return['parent'] = $graphNode['parent']['id'];
  }
  echo drupal_json_encode($return);
  exit;
}

/**
 * Rate Comments.
 */
function fbrate_menu_comment_rating($cid, $rating = '0') {
  global $user;
  $luser = user_load($user->uid);
  $params = array(
    'fbrate_comment_id' => $cid, 
    'uid' => $luser->uid, 
    'rate' => $rating, 
    'timestamp' => time(), 
  );
  fbrate_data_comment_rating_save($params);
  $return = array(
    'valid' => 1, 
  );
  echo drupal_json_encode($return);
  exit;
}