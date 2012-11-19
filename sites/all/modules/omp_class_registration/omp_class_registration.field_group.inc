<?php
/**
 * @file
 * omp_class_registration.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function omp_class_registration_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic|node|omp_class_display|form';
  $field_group->group_name = 'group_basic';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'omp_class_display';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Basic Info',
    'weight' => '0',
    'children' => array(
      0 => 'field_product_reference',
      1 => 'field_create_new_like_this',
      2 => 'field_om_withdraw_class',
      3 => 'field_class_image',
      4 => 'title',
      5 => 'path',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Basic Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_basic|node|omp_class_display|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cost_and_certifications|taxonomy_term|om_class|form';
  $field_group->group_name = 'group_cost_and_certifications';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'om_class';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Cost & Certifications',
    'weight' => '4',
    'children' => array(
      0 => 'field_cert_prerequisites',
      1 => 'field_cert_earned',
      2 => 'field_nonmember_price',
      3 => 'field_member_price',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_cost_and_certifications|taxonomy_term|om_class|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cost|node|omp_class_display|default';
  $field_group->group_name = 'group_cost';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'omp_class_display';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '8',
    'children' => array(
      0 => 'field_product_reference',
      1 => 'product:field_member_price',
      2 => 'product:field_nonmember_price',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_cost|node|omp_class_display|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_class_details|taxonomy_term|om_class|form';
  $field_group->group_name = 'group_om_class_details';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'om_class';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Class Details',
    'weight' => '0',
    'children' => array(
      0 => 'field_subject',
      1 => 'name',
      2 => 'description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_class_details|taxonomy_term|om_class|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_demographic|registration|om_class_registration|form';
  $field_group->group_name = 'group_om_demographic';
  $field_group->entity_type = 'registration';
  $field_group->bundle = 'om_class_registration';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Demographic',
    'weight' => '2',
    'children' => array(
      0 => 'field_user_gender',
      1 => 'field_user_orientation',
      2 => 'field_age_range',
      3 => 'field_income_level',
      4 => 'field_internet_access',
      5 => 'field_disability',
      6 => 'field_user_ethnic',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Demographic',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => 'OMF will never share your personal information with anyone for any reason. Our funders request that we report this demographic information to ensure that under-represented communities are being served.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_om_demographic|registration|om_class_registration|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_personal_info|registration|om_class_registration|form';
  $field_group->group_name = 'group_om_personal_info';
  $field_group->entity_type = 'registration';
  $field_group->bundle = 'om_class_registration';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal Info',
    'weight' => '0',
    'children' => array(
      0 => 'field_user_contact_info',
      1 => 'field_user_phone',
      2 => 'mail',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_personal_info|registration|om_class_registration|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_registration|commerce_product|omp_class_session|form';
  $field_group->group_name = 'group_om_registration';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'omp_class_session';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Registration',
    'weight' => '4',
    'children' => array(
      0 => 'field_om_class_registration',
      1 => 'status',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_registration|commerce_product|omp_class_session|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_session_details|commerce_product|omp_class_session|form';
  $field_group->group_name = 'group_om_session_details';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'omp_class_session';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Session Details',
    'weight' => '2',
    'children' => array(
      0 => 'commerce_price',
      1 => 'field_cert_earned',
      2 => 'field_cert_prerequisites',
      3 => 'field_class_description',
      4 => 'field_class_session_instructor',
      5 => 'field_member_price',
      6 => 'field_nonmember_price',
      7 => 'field_syllabus',
      8 => 'field_subject',
      9 => 'field_om_class',
      10 => 'title',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_session_details|commerce_product|omp_class_session|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_session_time_location|commerce_product|omp_class_session|form';
  $field_group->group_name = 'group_om_session_time_location';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'omp_class_session';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Session Date, Time & Location',
    'weight' => '3',
    'children' => array(
      0 => 'field_class_location',
      1 => 'field_class_session_date',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_session_time_location|commerce_product|omp_class_session|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_om_student|user|user|form';
  $field_group->group_name = 'group_om_student';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Student',
    'weight' => '4',
    'children' => array(
      0 => 'group_audience',
      1 => 'field_cert_earned',
      2 => 'field_om_classes_attended',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_om_student|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus_and_evaluation|node|omp_class_display|default';
  $field_group->group_name = 'group_syllabus_and_evaluation';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'omp_class_display';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '9',
    'children' => array(
      0 => 'webform',
      1 => 'product:field_syllabus',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_syllabus_and_evaluation|node|omp_class_display|default'] = $field_group;

  return $export;
}
