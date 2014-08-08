<?php

/**
 * @file
 * Filter query extender and helper functions.
 * https://www.drupal.org/files/issues/filter_extender8.patch
 */

/**
 * Query extender for filter queries.
 *
 * This creates a filter form and filters the query based on this form.
 */
class Filter extends SelectQueryExtender {
  /**
   * Currently active filters, loaded based on $name.
   */
  protected $filter = array();

  /**
   * Name of the used filter. This is used in the hooks and to load the data
   * in $_SESSION.
   */
  protected $name;

  /**
   * The defined filter elements of that filter, loaded with the hook.
   *
   * @see hook_filter_elements_FILTERNAME().
   */
  protected $elements = array();

  /**
   * Set the name of the filter.
   *
   * Load the saved filter data in $_SESSION, execute the hook to load the
   * filter elements. Then add a tag to the query object and store the loaded
   * data as metadata in the query object.
   *
   * After that, the defined filters are applied to the object, as far as
   * possible.
   *
   * @param $name
   *   Name of the filter query. This should be a unique string to identify the
   *   site/listing that should be filtered.
   * 
   * @return
   *   The query object to allow fluent method calls.
   */
  public function filterName($name) {
    $this->name = $name;
    $this->initialize();

    return $this;
  }

  protected function initialize() {
    if (!isset($_SESSION['filter'][$this->name])) {
      $_SESSION['filter'][$this->name] = array();
    }
    $this->filter =& $_SESSION['filter'][$this->name];
    $this->elements = module_invoke_all('filter_elements_' . $this->name, $this);
    $this->addTag('filter_' . $this->name);
    $this->addMetaData('filter', $this->filter);
    $this->addMetaData('elements', $this->elements);
  }

  public function execute() {
    // Add simple conditions of the currently active filters to the query.
    // @todo: Implement additional simple filter configurations.
    foreach ($this->filter as $name => $values) {
      foreach ($values as $value) {
        if (isset($this->elements[$name]['field'])) {
          // Check if we need to do a LIKE comparison.
          if (preg_match('/([\*%]+)/', $value)) {
            // Replace wildcards with PDO wildcards.
            $this->condition($this->elements[$name]['field'], preg_replace('!\*+!', '%', $value), 'LIKE');
          }
          else {
            $this->condition($this->elements[$name]['field'], $value);
          }
        }
      }
    }

    return $this->query->execute();
  }

  /**
   * Return the defined filter name.
   *
   * @return
   *   The previously defined filter.
   */
  public function getFilterName() {
    return $this->name;
  }

  /**
   * Return the loaded, currently active filters for that query.
   *
   * @return
   *   Array with active filters.
   */
  public function getFilter() {
    return $this->filter;
  }

  /**
   * Get the form definition of the active filter.
   *
   * @see filter_extender_form
   *
   * @param $title
   *   Fieldset title that should be used for that form.
   */
  public function getForm($title = NULL) {

    // Only display a form if filter elements were found.
    if (empty($this->elements)) {
      return array();
    }

    if ($title == NULL) {
      $title = t('Only display items where');
    }

    // Note: #query is a workaround becase we can't directly call a object
    // method for the form submit.
    $form = array(
      '#title'  => $title,
      '#type'   => 'fieldset',
      '#weight' => -50,
      '#theme'  => 'filter_selection_form',
      '#query'  => $this,
    );

    $i = 0;
    foreach ($this->filter as $name => $values) {
      $params = array(
        '%property' => $this->elements[$name]['title'],
        '%value' => join(t(' and '), $this->getFilterDescription($name, $values)
      ));
      if ($i++ > 0) {
        $form['current'][] = array('#markup' => t('<em>and</em> where <strong>%property</strong> is <strong>%value</strong>', $params));
      }
      else {
        $form['current'][] = array('#markup' => t('<strong>%property</strong> is <strong>%value</strong>', $params));
      }
    }

    // Create a select for each filter element.
    foreach ($this->elements as $name => $element) {
      $names[$name] = $element['title'];

      // Display a select if pre-defined options are available.
      if (isset($element['options'])) {
        $form['status'][$name] = array(
          '#type' => 'select',
          '#options' => $element['options'],
        );
      } else {
        // If not, use a textfield, optionally with an autocomplete path.
        $form['status'][$name] = array(
          '#type' => 'textfield',
          '#size' => 19,
        );
        if (isset($element['autocomplete_path'])) {
          $form['status'][$name]['#autocomplete_path'] = $element['autocomplete_path'];
        }
      }
    }

    // Create list of filter elements.
    $form['filter'] = array(
      '#type' => 'radios',
      '#options' => $names,
    );

    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => (count($this->filter) ? t('Refine') : t('Filter')),
      '#submit' => array('filter_extender_form_submit'),
    );
    if (count($this->filter)) {
      $form['buttons']['undo'] = array(
        '#type' => 'submit',
        '#value' => t('Undo'),
      '#submit' => array('filter_extender_form_submit'),
      );
      $form['buttons']['reset'] = array(
        '#type' => 'submit',
        '#value' => t('Reset'),
        '#submit' => array('filter_extender_form_submit'),
      );
    }
    return $form;
  }

  /**
   * Handle the filter form submit.
   *
   * Because this can't be called directly, it's called by the helper function
   * filter_extender_form_submit.
   *
   * @see filter_extender_form_submit()
   */
  public function submitForm($form, &$form_state) {
    switch ($form_state['values']['op']) {
      case t('Filter'):
      case t('Refine'):
        if (!empty($form_state['values']['filter'])) {
          $name = $form_state['values']['filter'];
          $value = $form_state['values'][$name];

          // Only add the new filter of multiple is enabled, override the
          // current value if not.
          if (isset($this->elements[$name]['multiple']) && $this->elements[$name]['multiple']) {
            $this->filter[$name][$value] = $value;
          }
          else {
            $this->filter[$name] = array($value => $value);
          }
        }
        break;
      case t('Undo'):
        array_pop($this->filter);
        break;
      case t('Reset'):
        $this->filter = array();
        break;
    }
  }

  /**
   * Return an array of filter values that should be displayed in the form.
   *
   * @param $name
   *   Name of the filter.
   * @param $values
   *   Array of values that should be displayed.
   * @return
   *   Array of filter values, either the values itself or the text of the
   *   selected options.
   */
  protected function getFilterDescription($name, $values) {
    if (isset($this->elements[$name]['options'])) {
      $options = $this->elements[$name]['options'];
      if (count(array_filter($this->elements[$name]['options'], 'is_array')) > 0) {
        $options = call_user_func_array('array_merge', $this->elements[$name]['options']);
      }
      return array_intersect_key($options, $values);
    } else {
      return $values;
    }
  }
}

/**
 * Theme filter selector form.
 *
 * @ingroup themeable
 */
function theme_filter_selection_form($form) {
  $output = '';
  if (!empty($form['current'])) {
    $output .= '<p>';
    foreach (element_children($form['current']) as $key) {
      $output .= '' . drupal_render($form['current'][$key]) . '<br />';
    }
    $output .= '</p>';
  }

  $output .= '<p><dl class="multiselect">' . (!empty($form['current']) ? '<dt><em>' . t('and') . '</em> ' . t('where') . '</dt>' : '') . '<dd class="a">';
  foreach (element_children($form['filter']) as $key) {
    $output .= drupal_render($form['filter'][$key]);
  }
  $output .= '</dd><dt>' . t('is') . '</dt><dd class="b">';

  foreach (element_children($form['status']) as $key) {
    $output .= drupal_render($form['status'][$key]);
  }
  $output .= '</dd></dl>';
  $output .= '<div class="container-inline" id="user-admin-buttons">' . drupal_render($form['buttons']) . '</div></p>';
  return $output;
}

/**
 * Form for the filter of the passed in $query object.
 *
 * This is a helper function because we can't directly call a object method with
 * drupal_get_form(). Only use this if you don't already have a $form object
 * that could be extended.
 *
 * @param $query
 *   SelectQuery object that is already extend with Filter.
 * @return <type>
 */
function filter_extender_form($query) {
  return $query->getForm();
}

/**
 * Helper function for submitting the filter form.
 *
 * @see filter_extender_form()
 */
function filter_extender_form_submit($form, &$form_state) {
  $form['filter']['#query']->submitForm($form, $form_state);
}
