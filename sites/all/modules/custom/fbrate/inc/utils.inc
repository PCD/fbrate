<?php
/**
 * Does the log in user has a FB Access Token.
 */
function field_fb_get_user_access_token($user) {
  if ( isset($user->field_fb_access_token[LANGUAGE_NONE][0]['value']) ) {
    return $user->field_fb_access_token[LANGUAGE_NONE][0]['value'];
  }
  return false;
}

/**
 * Gets the FB Story ID From a URL.
 */
function fbrate_api_get_story_id_from_url($url) {
  // Look for FB Id.
  $pattern = '/fbid=[^&]+/msi';
  if ( !preg_match($pattern, $url, $match) ) {
    // Try Last Argument Method
    $parts = parse_url($url);
    $path = explode('/', trim($parts['path'], '/ '));
    $fb_id = array_pop($path);
    return $fb_id;
  } else {
    // Try $_GET variable method.
    $parts = parse_url($url);
    parse_str($parts['query'], $query);
    if ( isset($query['story_fbid']) ) {
      return $query['story_fbid'];
    } else if ( isset($query['fbid']) ) {
      return $query['fbid'];
    }
  }
  
  drupal_set_message("No pudimos obtener el FB Id de la url {$url} proporcionada.", 'error');
  return false;
}
