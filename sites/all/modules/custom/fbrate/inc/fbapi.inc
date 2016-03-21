<?php
/**
 * Fetch All post data and comments from a given FB Post URL.
 */
function fbrate_fbapi_fetch_post($url) {
  // Get Post ID
  if ( !($fb_id = fbrate_api_get_story_id_from_url($url)) ) {
    drupal_set_message(t('La URL Proporcionada es incorrecta, no es una URL de un Post.'), 'error');
    return '';
  }
  
  // Get Credentials
  $app_id = variable_get('fbrate_app_id', '133228943514210');
  $app_secret = variable_get('fbrate_app_secret', '0f39ea261b13366934f35df9f4b9755b');
  $app_version = variable_get('fbrate_app_version', 'v2.5');
  require_once dirname(__DIR__) . '/vendor/autoload.php';
  
  
  // Get FB Object
  $fb = new Facebook\Facebook([
    'app_id' => $app_id,
    'app_secret' => $app_secret,
    'default_graph_version' => $app_version,
  ]);
  $helper = $fb->getRedirectLoginHelper();
  $permissions = ['email', 'user_likes'];
  $login_url = url('fbrate/login', array('absolute'=>true));
  $loginUrl = $helper->getLoginUrl($login_url, $permissions);
  return '<a href="' . $loginUrl . '">Log in with Facebook!</a>';
  


  // Get FB Access Token
  
  
  /*$request = new Facebook\FacebookRequest(
    $fbApp,
    'GET',
    "/{$fb_id}"
  );*/
  
  print_r($request);
  exit;  

  return 'ok';
}

/**
 * Process FB Login.
 */
function fbrate_api_menu_admin() {
  
}



















































