<?php

if (function_exists('om_playback_servers_media_browser_form')) {
  return;
}

/**
 * Custom form builder for media browser plugin.
 */
function om_playback_servers_cablecast_media_browser_form($form, &$form_state) {
  $form = array();
  $options = array('' => '- select -');
  $channels = om_playback_servers_get_channel_vocabulary();
  foreach ($channels AS $channel) {
    $pbs = om_playback_servers_get_pbs_by_term($channel->tid);
    $pbs = array_shift($pbs);
    if ($pbs->ompbs_type == 'cablecast') {
      $controller = om_playback_servers_entity_get_controller($pbs);
      $parameters = array(
        //'isvalid' => 'false',
        'isorphan' => 'true'
      );
      $files = $controller->check_file_status($pbs, $parameters);
      foreach ($files AS $file) {
        $path = 'cablecast://'. $channel->tid .'/' . $file['FileName'];
        $options[$path] = $file['FileName'];
      }
    }
  }
  if (count($options) == 1) {
    $form['om_playback_servers_response'] = array(
      '#markup' => t('No playback server or file resource was found on your current configuration.'),
    );
  }
  else {
    $form['url'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Select a file'),
      '#description' => t('Select a file from your station\'s broadcast server.'),
      '#options' => $options
    );
    $form['#submit'][] = 'om_playback_servers_cablecast_media_browser_submit';
    
  }
  // @todo Validate against file field allowed types.
  $form['#validators'] = array();

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Custom submit handler for media browser plugin
 */
function om_playback_servers_cablecast_media_browser_submit($form, &$form_state) {
  $uri = $url = $form_state['values']['url'];

  try {
    $file = file_stream_wrapper_uri_normalize($uri);
    $files = entity_load('file', FALSE, array('uri' => $uri));
    if (!empty($files)) {
      $file = reset($files);
    }
    else {
      $file = new stdClass();
      $file->fid = NULL;
      $file->uri = $uri;
      $file->filename = basename(str_replace('cablecast://', '', $file->uri));
      $file->filemime = 'video/cablecast';
      $file->uid = $GLOBALS['user']->uid;
      $file->status = FILE_STATUS_PERMANENT;
      $saved = file_save($file);
    }
  }
  catch (Exception $e) {
    form_set_error('url', $e->getMessage());
    return;
  }
  if (empty($file->fid)) {
    form_set_error('url', t('Unable to add file from URL %file.', array('%file' => $url)));
    return;
  }
  else {
    $form_state['file'] = $file;
  }
}