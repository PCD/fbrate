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
  $app_id = fbrate_get_fb_app_id();
  $app_secret = fbrate_get_fb_app_secret();
  $app_version = fbrate_get_fb_app_version();
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
 * Get FB Login URL.
 */
function fbrate_get_fb_login_url() {
  // Get Credentials
  $app_id = fbrate_get_fb_app_id();
  $app_secret = fbrate_get_fb_app_secret();
  $app_version = fbrate_get_fb_app_version();
  require_once dirname(__DIR__) . '/vendor/autoload.php';
  
  // Get FB Object
  $fb = new Facebook\Facebook([
    'app_id' => $app_id,
    'app_secret' => $app_secret,
    'default_graph_version' => $app_version,
  ]);
  
  $helper = $fb->getRedirectLoginHelper();
  $permissions = ['email', 'user_likes'];
  $base_url = url('fbrate/login', array('absolute'=>TRUE));
  return $helper->getLoginUrl($base_url, $permissions);
}


/**
 * Connects User with Facebook.
 */
function fbrate_menu_login() {
  // Get Credentials
  $app_id = fbrate_get_fb_app_id();
  $app_secret = fbrate_get_fb_app_secret();
  $app_version = fbrate_get_fb_app_version();
  require_once dirname(__DIR__) . '/vendor/autoload.php';
  
  // Get FB Object
  $fb = new Facebook\Facebook([
    'app_id' => $app_id,
    'app_secret' => $app_secret,
    'default_graph_version' => $app_version,
  ]);
  
  $helper = $fb->getRedirectLoginHelper();

  try {
    $accessToken = $helper->getAccessToken();
  } catch(Facebook\Exceptions\FacebookResponseException $e) {
    // When Graph returns an error
    drupal_set_message('Graph returned an error: ' . $e->getMessage(), 'error');
    return '';
  } catch(Facebook\Exceptions\FacebookSDKException $e) {
    // When validation fails or other local issues
    drupal_set_message('Facebook SDK returned an error: ' . $e->getMessage(), 'error');
    return '';
  }
  
  if ( !isset($accessToken)) {
    if ($helper->getError()) {
      header('HTTP/1.0 401 Unauthorized');
      echo "Error: " . $helper->getError() . "\n";
      echo "Error Code: " . $helper->getErrorCode() . "\n";
      echo "Error Reason: " . $helper->getErrorReason() . "\n";
      echo "Error Description: " . $helper->getErrorDescription() . "\n";
    } else {
      header('HTTP/1.0 400 Bad Request');
      echo 'Bad request';
    }
    exit;
  }
  
  //$accessToken
  // Save Access Token
  global $user;
  $luser = user_load($user->uid);
  $luser->field_fb_access_token[LANGUAGE_NONE][0]['value'] = $accessToken->getValue();
  user_save($luser);
  
  drupal_goto('admin/fbrate/import/post');
  exit;
}

/**
 * Gets FB App ID.
 */
function fbrate_get_fb_app_id() {
  return variable_get('fbrate_app_id', '1062595773813919');
}

/**
 * Gets FB App Secret.
 */
function fbrate_get_fb_app_secret() {
  return variable_get('fbrate_app_secret', '755ffc892303120f998b0d7ba9d0314a');
}

/**
 * Gets FB App Version.
 */
function fbrate_get_fb_app_version() {
  return variable_get('fbrate_app_version', 'v2.5');
}













































