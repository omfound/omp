<?php

/**
 * @file
 * Filter query extender and helper functions.
 * Heavily modified version of:
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
  public $filter = array();

  /**
   * Name of the used filter. This is used in the hooks and to load the data
   * in $_SESSION.
   */
  protected $name;

  /**
   * The defined form.
   *
   */
  public $form = array();


  /**
   * For active debugging
   */
  public $debug = false;

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
  public function filterForm($name) {
    $this->name = $name;
    $this->initialize();

    return $this;
  }

  protected function initialize() {
    if (empty($_GET['conditions'])) {
      $this->filter = array();
    }
    else {
      $this->filter = (array) json_decode(urldecode($_GET['conditions']), true);
    }
    $form_function = $this->name . '_form';
    $this->form = $form_function($this);
    $this->addTag('filter_' . $this->name);
    $this->addMetaData('filter', $this->filter);
    $this->addMetaData('form', $this->form);
  }

  public function execute() {
    $execute_function = $this->name . '_filter_conditions';
    $execute_function($this);
    if ($this->debug) {
      dpq($this->query);
    }
    return $this->query;
    //return $this->query->execute();
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
    if (empty($this->form)) {
      return array();
    }

    $form = $this->form;

    // Note: #query is a workaround becase we can't directly call a object
    // method for the form submit.
    $form['#query'] = $this;

    //Handle setting default values from prior submit
    foreach ($this->filter as $name => $values) {
      if (!empty($this->form[$name]['#multiple'])) {
        $form[$name]['#default_value'] = $values;
      }
      elseif (is_array($values) && !empty($values[0])) {
        $form[$name]['#default_value'] = $values[0]; 
      }
      elseif (!empty($values)) {
        $form[$name]['#default_value'] = $values; 
      }
    }

    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => (count($this->filter) ? t('Refine') : t('Filter')),
      '#submit' => array('filter_extender_form_submit'),
    );
    if (count($this->filter)) {
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
    $value_exists = false;
    switch ($form_state['values']['op']) {
      case t('Filter'):
      case t('Refine'):
        foreach ($form_state['values'] as $key => $value) {
          if (!empty($this->form[$key]) && !empty($value)) {
            $this->filter[$key] = $value;
            $value_exists = true;
          }
        }
        break;
      case t('Reset'):
        $this->filter = array();
        break;
    }
    
    if (!$value_exists) {
      $this->filter = array();
    }

    $path = current_path();
    if (!empty($this->filter)) {
      $form_state['redirect'] = array(
        $path,
        array(
          'query' => array(
            'conditions' => json_encode($this->filter),
          ),
        ),
      );
    }
    else {
      $form_state['redirect'] = $path;
    }
  }
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
function filter_extender_form($form, &$form_state, $query) {
  return $query->getForm();
}

/**
 * Helper function for submitting the filter form.
 *
 * @see filter_extender_form()
 */
function filter_extender_form_submit($form, &$form_state) {
  $form['#query']->submitForm($form, $form_state);
}
