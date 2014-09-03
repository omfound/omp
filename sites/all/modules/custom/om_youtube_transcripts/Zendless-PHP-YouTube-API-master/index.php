<?php

    require 'api/google_oauth.php';

    $key = '6h03d9WznAVxJ4Gg7I6Daqdr'; //TODO: This should be the key given to you by google
    $secret = '6h03d9WznAVxJ4Gg7I6Daqdr'; //TODO: This should be the secret given to you by google

    $auth = new \API\google_oauth($key, $secret);

    //TODO: Be sure to alter the callback url below to reflect your environment
    $data = $auth->get_request_token('http://dev-thornton.gotpantheon.com/sites/all/modules/custom/om_youtube_transcripts/Zendless-PHP-YouTube-API-master/authorize.php');
    // Store the returned token_secret in memory some where so
    // that it can be recalled during the authorization step.
    $_SESSION['token_secret'] = $data['token_secret'];
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>YouTube API Test</title>
</head>
<body>
    <h1>Authorize with YouTube</h1>
    <br/>
    <a href="<?php echo $data['redirect']; ?>">
        By Clicking This Link
    </a>
</body>
