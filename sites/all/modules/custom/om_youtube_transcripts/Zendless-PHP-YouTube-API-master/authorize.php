<?php

    require 'api/google_oauth.php';
    require 'api/youtube.php';

    $key = 'AI39si7DiBRGrrLFePflzAs2ZAr9LJvYASOXk-lVcgHGxQIX-ROr0zpz5oSC6sHHU4BkewMIvMGxqnOMt4QXb0vKLvNxc-H9lA'; //TODO: This should be the key given to you by google
    $secret = '6h03d9WznAVxJ4Gg7I6Daqdr'; //TODO: This should be the secret given to you by google

    $auth = new \API\google_oauth($key, $secret);
    $oauth_token = $auth->get_access_token($_GET['oauth_token'], $_SESSION['token_secret'], $_GET['oauth_verifier']);

    //Make sure you urlencode the values of $oauth_token before passing it to the youtube api
    foreach($oauth_token as $key => $value)
        $oauth_token[$key] = urlencode($value);

    $youtube_api_key = '6h03d9WznAVxJ4Gg7I6Daqdr'; //TODO: This should be the api key give to you by youtube

    $youtube = new \API\youtube();

    echo $youtube->getUserProfile('default', array('alt'=>'json'));