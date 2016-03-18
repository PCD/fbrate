<?php
/**
 * Fetch All post data and comments from a given FB Post URL.
 */
function fbrate_fbapi_fetch_post($url) {
  require_once dirname(__DIR__) . '/vendor/autoload.php';
  
  $fb = new Facebook\Facebook([
    'app_id' => '133228943514210',
    'app_secret' => '0f39ea261b13366934f35df9f4b9755b',
    'default_graph_version' => 'v2.5',
  ]);
  
  print_r($fb);exit;
  
  return 'ok';
  /* PHP SDK v5.0.0 */
  /* make the API call */
  $request = new FacebookRequest(
    $session,
    'GET',
    '/{post-id}'
  );
  $response = $request->execute();
  $graphObject = $response->getGraphObject();
  /* handle the result */
}