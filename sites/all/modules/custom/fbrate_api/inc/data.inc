<?php
// Funtion that request the comments to facebook.
function fbrate_api_request($post_id){
  if (!isset($post_id)) {
    $post_id = '10153225011647563';
  }
  $fb = new Facebook\Facebook([
    'app_id' => '932170426898750',
    'app_secret' => '35fe249a19d2e3da727da23551dc64d4',
    'default_graph_version' => 'v2.5',
  ]);

  /*
  $request = new FacebookRequest(
    $session,
    'GET',
    '/10153225011647563/comments'
    array(
      'limit' => '100'
    )
  );
  print_r($request); exit;
  $response = $request->execute();
  $graphObject = $response->getGraphObject();
  print_r($request); exit;*/

  $path = 'https://graph.facebook.com/v2.5/'.$post_id.'?fields=comments.limit(100)%7Bid%2Cmessage%2Clike_count%7D&access_token=932170426898750%7C1Lh-_FJf3v6RnscdBNMlRUqPGCI';

  // create curl resource 
  $ch = curl_init(); 

  // set url 
  curl_setopt($ch, CURLOPT_URL, $path); 

  //return the transfer as a string 
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); 

  // $output contains the output string 
  $output = curl_exec($ch); 

  // close curl resource to free up system resources 
  curl_close($ch); 

  //var_dump(html_entity_decode($output));
  $response = json_decode($output, true);

  print_r($response); exit;

}