<?php

/**
 * Form builder function for add/edit forms.
 *
 * @param $form
 *   standard form var
 * @param $form_state 
 *   standard form_state var
 * @parm $pbs
 *   the pbs to be added/edited
 * @returns $form
 *   the built form
 */
function om_playback_servers_admin_form($form, &$form_state, $pbs = NULL) {
  
  $form = array();
  
  $options = array();
  $types = om_playback_servers_get_types();
  foreach ($types AS $name => $plugin) {
    $options[$name] = $plugin['title'];
  }
  if (!empty($pbs)) {
    $pbsid = arg(1);
    $form_state['storage']['pbs'] = $pbs[$pbsid];
    $type = $pbs[$pbsid]->ompbs_type;
  }
  else {
    $pbsid = 0;
    $pbs = array(0 => new StdClass());
    $pbs[$pbsid]->is_new = TRUE;
  }

  $pbs[$pbsid]->om_playback_server = 'om_playback_server';

  $form['pbs_channel']['#weight'] = 2;

  if (isset($type)) {
    $pbs[$pbsid]->ompbs_type = $type;
  }

  $form['ompbs_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('Human readable name of the playback server'),
    '#required' => TRUE,
    '#default_value' => empty($pbs[$pbsid]->is_new) ? $pbs[$pbsid]->name : '',
    '#weight' => 0,
  );

  $form['ompbs_type'] = array(
    '#type' => 'select',
    '#title' => t('Playback Server Type'),
    '#description' => t('Type of playback server'),
    '#options' => $options,
    '#required' => TRUE,
    '#default_value' => empty($pbs[$pbsid]->is_new) ? $pbs[$pbsid]->ompbs_type : '',
    '#weight' => 1,
  );
  
  $options = array();
  $channels = om_playback_servers_get_channel_vocabulary();
  foreach ($channels AS $term) {
    $options[$term->tid] = $term->name;
  }
  
  $form['ompbs_channel'] = array(
    '#type' => 'select',
    '#title' => t('Channel'),
    '#options' => $options,
    '#description' => t('Channel to associate the playback server with.'),
    '#default_value' => empty($pbs[$pbsid]->is_new) ? $pbs[$pbsid]->channel : '',
    '#weight' => 2,
  );

  $form['ompbs_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Server Uri'),
    '#description' => t('URL or IP address of the server'),
    '#required' => TRUE,
    '#default_value' => empty($pbs[$pbsid]->is_new) ? $pbs[$pbsid]->uri : '',
    '#weight' => 3,
  );

  $form['ompbs_mount'] = array(
    '#type' => 'textfield',
    '#title' => t('Mount Path'),
    '#description' => t('Mount path to servers hot folder'),
    '#default_value' => empty($pbs[$pbsid]->is_new) ? $pbs[$pbsid]->mount : '',
    '#weight' => 4,
  );

  $form['ompbs_location_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Location ID'),
    '#description' => t('Location ID field for servers that allow more than one location per server'),
    '#default_value' => empty($pbs[$pbsid]->is_new) ? $pbs[$pbsid]->location_id : '',
    '#weight' => 5,
  );

  $form['ompbs_output'] = array(
    '#type' => 'textfield',
    '#title' => t('Output'),
    '#description' => t('Output for servers that can handle more than one channel'),
    '#default_value' => empty($pbs[$pbsid]->is_new) ? $pbs[$pbsid]->output : '',
    '#weight' => 6,
  );

  $form['ompbs_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('Server username'),
    '#required' => TRUE,
    '#default_value' => empty($pbs[$pbsid]->is_new) ? $pbs[$pbsid]->user : '',
    '#weight' => 7,
  );

  $form['ompbs_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#description' => t('Server password. This field is always presented as empty on this form.'),
    '#required' => TRUE,
    '#default_value' =>  '',
    '#weight' => 8,
  );

  $form['ompbs_submit'] = array(
    '#type' => 'submit',
    '#value' => !empty($pbs) ? t('Save') : t('Add'),
    '#weight' => 9,
  );

  $form['#submit'][] = 'om_playback_servers_admin_form_submit';

  return $form;
}

/**
 * Submit handler for add/edit forms.
 *
 * @param $form
 *   standard form var
 * @param $form_state
 *    standard form_state var
 * @returns
 *   render array.
 */
function om_playback_servers_admin_form_submit($form, &$form_state) {
  if (empty($form_state['storage']['pbs'])) {
    $values = array();
    foreach ($form AS $key => $form_element) {
      if (is_numeric(stripos($key, 'ompbs')) && $key != 'ompbs_submit' && $key != 'ompbs_type') {
        $values[str_replace('ompbs_', '', $key)] = $form_element['#value'];
      }
      else if ($key == 'ompbs_type') {
        $values['ompbs_type'] = $form_element['#value'];
      }
    }
    $new_pbs = entity_get_controller('om_playback_server')->create($values);
  }
  else {
    foreach ($form AS $key => $form_element) {
      if (is_numeric(stripos($key, 'ompbs')) && $key != 'ompbs_submit' && $key != 'ompbs_type') {
        $values[str_replace('ompbs_', '', $key)] = $form_element['#value'];
      }
      else if ($key == 'ompbs_type') {
        $values[$key] = $form_element['#value'];
      }
    }
    $new_pbs = array_merge((array)$form_state['storage']['pbs'], $values);
    $new_pbs = (object)$new_pbs;
  }
  entity_get_controller('om_playback_server')->save($new_pbs);
  drupal_goto('om_playback_servers/list');
}

/**
 * Utility function to build list page.
 *
 *   @returns
 *     render array.
 */
function om_playback_servers_admin_list() {
  $term_query = $query = db_select('taxonomy_vocabulary', 'voc');
  $term_query->fields('voc', array('vid'));
  $term_query->condition('machine_name', 'channels', '=');
  $result = $query->execute();
  $record = $result->fetchAssoc();

  if (empty($record['vid'])) {
    $message = t('The Channels vocabulary seems to be missing. Please contact your site administrator.');
    drupal_set_message($message, 'warning');
  }
  else {
    $voc = taxonomy_get_tree($record['vid']);
    if (empty($voc)) {
      $options = array('query' => array('destination' => 'om_playback_servers/list'));
      $link = l('Add', 'admin/structure/taxonomy/channels/add', $options);
      $message = t('The Channels vocabulary doesn\'t have any channels yet. !add some now. The Channels vocabulary is responsible for connecting your playback servers, channels and scheduling information.', array('!add' => $link));
      drupal_set_message($message, 'status');
    }
  }
  
  $query = db_select('om_playback_servers', 'pbs');
  $query->fields('pbs');
  $result = $query->execute();
  $rows = array();
  $count = 0;

  while($record = $result->fetchAssoc()) {
    $rows[$record['pbsid']] = array(
      '#prefix' => '<tr>',
      'title_' . $count  => array(
        '#prefix' => '<td>',
        '#markup' => $record['name'],
        '#suffix' => '</td>',
      ),
      'type_' . $count  => array(
        '#prefix' => '<td>',
        '#markup' => $record['ompbs_type'],
        '#suffix' => '</td>',
      ),
      'links_' . $count => array(
        '#prefix' => '<td>',
        '#markup' => l('edit', 'om_playback_servers/' . $record['pbsid'] . '/edit') . ' | ' . l('delete', 'om_playback_servers/' . $record['pbsid'] . '/delete'),
        '#suffix' => '</td>',
      ),
      '#suffix' => '</tr>',
    );
    $count ++;
  }
  if (!empty($rows)) {
    $header = array(
      '#prefix' => '<thead>',
      'title_' . $count  => array(
        '#prefix' => '<th>',
        '#markup' => t('Name'),
        '#suffix' => '</th>',
      ),
      'type_' . $count  => array(
        '#prefix' => '<th>',
        '#markup' => t('Type'),
        '#suffix' => '</th>',
      ),
      'links_' . $count => array(
        '#prefix' => '<th>',
        '#markup' => t('Options'),
        '#suffix' => '</th>',
      ),
      '#suffix' => '</head>'
    );
    $render = array(
       '#prefix' => '<table>',
       'header' => $header,
       'content' => $rows,
       '#suffix' => '</table>',
    );
  }

  if (empty($render)) {
    $link = l('Add one', 'om_playback_servers/add');

    $content = array(
      'message' => array(
        '#prefix' => '<p>',
        '#markup' => t('You haven\'t created any playback servers yet. !add.', array('!add' => $link)),
        '#suffix' => '</p>'
      )
    );

    $render = array(
       '#prefix' => '<div>',
       'content' => $content,
       '#suffix' => '</div>',
    );
  }
  return $render;
}

/**
 * Formbuilder for delete confirmation page.
 *
 * @param
 *   $form standard form var
 * @param $form_state
 *   standard form_state var
 * @param pbs
 *   the pbs to be deleted
 * @returns form
 *   built form
 */
function om_playback_servers_delete_confirm($form, &$form_state, $pbs) {
  $pbsid = arg(1);
  $pbs = $pbs[$pbsid];
  $question = t('Are you sure you want to delete the playback server: !pbs?', array('!pbs' => $pbs->name));
  $path = 'om_playback_servers/list';
  $form['#submit'] = array('_om_playback_servers_delete_confirm');
  $form_state['storage']['pbs'] = $pbs;
  $form =  confirm_form($form, $question, $path, $description = NULL, $yes = NULL, $no = NULL, $name = 'confirm');
  return $form;
}

/**
 * Utility submit handler to actually delete the pbs.
 * 
 *  @parms
 *    form form from above
 *  @params $form_state 
 *    formstate from above
 */
function _om_playback_servers_delete_confirm($form, $form_state) {
  entity_get_controller('om_playback_server')->delete(array($form_state['storage']['pbs']->pbsid));
  drupal_goto('om_playback_servers/list');
}