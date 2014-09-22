<?php
/**
 * Preprocess and Helper Functions for Views
 **/

/**
 * Implements hook_preprocess_HOOK
 */
function minim_preprocess_views_view_unformatted(&$variables) {
  $rows_rendered = array();
  if (!empty($variables['rows'])) {
    foreach ($variables['rows'] AS $id => $row) {
      $complete_row = "<div class='" . $variables['classes_array'][$id] . "'>";
      $complete_row .= $row;
      $complete_row .= "</div>";
      $rows_rendered[] = array('row' => $complete_row);
    }
  }
  $variables['rows_rendered'] = $rows_rendered;
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }
}

/**
 * Implements hook_preprocess_HOOK
 */
function minim_preprocess_views_view_fields(&$variables) {
  $fields_rendered = '';
  if (!empty($variables['fields'])) {
    foreach ($variables['fields'] AS $id => $field) {
      // Seperator
      if (!empty($field->separator)) {
        $fields_rendered .= $field->separator;
      }
      $fields_rendered .= $field->wrapper_prefix; 
      $fields_rendered .= $field->label_html; 
      $fields_rendered .= $field->content;
      $fields_rendered .= $field->wrapper_suffix;
    }
  }
  $variables['fields_rendered'] = $fields_rendered;
  // Allow for more granular preproces_functions
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }
}

function minim_preprocess_views_view_table(&$variables) {
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->name . '__' . $variables['view']->current_display;
  dsm($sub_functions);
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }

  if (!empty($variables['header'])) {
    $variables['headers_rendered'] = '';
    foreach ($variables['header'] as $field => $label) {
      $variables['headers_rendered'] .= "<th class='" . $variables['header_classes'][$field] . "'>" . $label . "</th>";
    }
  }
  if (!empty($variables['rows'])) {
    $row_zebra = 0;
    $variables['rows_rendered'] = '';
    foreach ($variables['rows'] as $row_count => $row) {
      $row_zebra_class = $row_zebra % 2 == 0 ? 'views-row-even' : 'views-row-odd pure-table-odd';
      $row_zebra ++;
      if (!empty($variables['row_classes'][$row_count])) {
        $variables['rows_rendered'] .= "<tr class='" . implode(' ', $variables['row_classes'][$row_count]) . " " . $row_zebra_class . "'>";
      }
      else {
        $variables['rows_rendered'] .= "<tr class='" . $row_zebra_class . "'>";
      }
      $zebra = 0;
      foreach ($row as $field => $content) {
        if (!empty($variables['field_classes'][$field][$row_count])) {
          $field_zebra_class = $zebra % 2 == 0 ? 'views-field-even' : 'views-field-odd pure-table-odd';
          $variables['field_classes'][$field][$row_count] .= ' ' . $field_zebra_class;
          $zebra ++;
          $variables['rows_rendered'] .= "<td class='" . $variables['field_classes'][$field][$row_count] . "'" . drupal_attributes($variables['field_attributes'][$field][$row_count]) .">" . $content . "</td>";
        }
        else {
          $variables['rows_rendered'] .= "<td " . drupal_attributes($variables['field_attributes'][$field][$row_count]) . ">" .  $content . "</td>";
        }
      }
      $variables['rows_rendered'] .= "</tr>";
    }
  }
}

function minim_preprocess_views_view_table__archived_sessions (&$vars) {
  foreach ($vars['rows'] as $row_key => $row_info) {
    foreach ($row_info as $field_key => $field_value) {
      if ($field_key == 'title') {
        if (!empty($_GET['iframe_mode'])) {
          $options = array();
          $options['absolute'] = TRUE;
          $options['attributes']['target'] = '_blank';
          $options['query']['iframe_mode'] = 'true';
        }
        else {
          $options = array('absolute' => TRUE); 
        }
        $link = l($vars['result'][$row_key]->node_title, $row_info['path'], $options);
        $vars['rows'][$row_key][$field_key] = $link;
      }
      elseif ($field_key == 'field_om_calendar') {
        $calendar_link = l('Download PDF', str_replace('/pub', '/export?format=pdf', $vars['result'][$row_key]->field_field_om_calendar[0]['raw']['url']));
        $vars['rows'][$row_key][$field_key] = $calendar_link;
      }
    } 
  }
  dsm ($vars);
  dsm($vars['result']);
}
function minim_preprocess_views_view_table__archived_sessions__page_2 (&$vars) {
  minim_preprocess_views_view_table__archived_sessions($vars);
}
