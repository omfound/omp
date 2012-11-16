<?php
// PRODUCT: membership plan product_type_name
/*
define('REGFORM_PRODUCT_TYPE', variable_get('regform_product_type', 'omp_membership_plan')); 
// User : User hash field name
define('REGFORM_USER_HASH', 'field_user_hash');
// User : User type field name
define('REGFORM_USER_TYPE', 'field_user_type');
// User : User status field name
define('REGFORM_USER_STATUS', 'field_user_status');
// User : membership plan field name (also defined in regform.pages.inc)
define('REGFORM_USER_PLAN_FIELD', 'field_user_membership');
// User : last plan field name (also defined in regform.pages.inc)
define('REGFORM_USER_LAST_PLAN_FIELD', 'field_user_last_plan');
// User : membership start field name
define('REGFORM_USER_FIELD_START', 'field_user_om_start');
// User : membership expire field name
define('REGFORM_USER_FIELD_EXPIRE', 'field_user_expire');
// User : membership expire notified field name
define('REGFORM_USER_FIELD_EXPIRE_NOTIFIED', 'field_user_expire_notified');
// User : contact info field name
define('REGFORM_USER_CONTACT_INFO', 'field_user_contact_info');
// User : Member of organization feild name
define('REGFORM_USER_ORGANIZATION', 'field_user_organization');
// Membership Plan : type
define('REGFORM_PLAN_TYPE', 'field_user_type'); // same as user type
// Membership Plan : Maximum accounts field name
define('REGFORM_PLAN_ACCOUNTS', 'field_om_accounts');
// Membership Plan : associated user role field name
define('REGFORM_PLAN_ROLE_FIELD', 'field_om_role');
*/

/**
 * Inplements hook_commerce_cart_product_prepare()
 * 
 * When membership plan added:
 * 1. Delete membership plans from cart (if any)
 */
/*
function hooks_commerce_cart_product_prepare($order, $product, $quantity) {
	if ($product->type == REGFORM_PRODUCT_TYPE) {
		if($order && !empty($order->commerce_line_items)) {
			foreach ($order->commerce_line_items['und'] as $key => $line) {
		    $line_item = commerce_line_item_load($line['line_item_id']);
		    $cart_product = commerce_product_load($line_item->commerce_product['und'][0]['product_id']);
		    if ($cart_product->type == REGFORM_PRODUCT_TYPE) {
		    	//commerce_cart_product_remove();
		    	unset($order->commerce_line_items['und'][$key]);
		    	//commerce_cart_order_refresh($order);
		    }
		  }
		  $result = commerce_order_save($order);
		  if ( empty($result) ) {
		  	drupal_set_message(t('Error #1 while adding product to cart.'), error);
				watchdog('hooks',  'Error #1 while adding product to cart.',
										array(),
										WATCHDOG_ERROR
									);
		  }
		}
	}
}*/

/**
 * Implements hook_commerce_checkout_complete()
 
function hooks_commerce_checkout_complete($order) {
  // check order status
  if ($order->status == 'checkout_complete') {
  // 1. mark users as "enrolled" if class registration exists in order 
  if (isset($order->data['register_entities']) && !empty($order->data['register_entities'])) {
  	foreach ($order->data['register_entities'] as $k => $registration) {
  		$registration = $registration[0];
  		$registration->field_om_student_status['und'][0]['value'] = 2; // enrolled
  		if ( !registration_save($registration) ) {
  			watchdog('hooks',  'Error: can\'t change registration status for :user (:order).', array(
  									':user' => l('user', 'user/' . $registration['author_uid']), 
  									':order' => l('order', 'admin/commerce/orders/' . $order->order_id . '/view')
  						),	WATCHDOG_ERROR
  				);
  		}
  	}
  }
  // 2. ===== if membership plan is in the order, change user's role and user's membership expire date
 	$plan = NULL;
 	foreach ($order->commerce_line_items['und'] as $key => $line) {
	   $line_item = commerce_line_item_load($line['line_item_id']);
	   $product = commerce_product_load($line_item->commerce_product['und'][0]['product_id']);
	   if ($product->type == REGFORM_PRODUCT_TYPE) {
	   	$plan = $product;
	   	break;
	  }
	}
  if (!empty($plan)) {
  	// 3. === change plan and user type
  	$account = hooks_change_plan($order->uid, $plan, FALSE, TRUE);
  	if ($account) {
  		// 4. ==== if organization: send email, prolong organization users
  		if ($account->{REGFORM_USER_TYPE}['und'][0]['value'] == 1) {
  			// prolong users
  			hooks_prolong_org_users($account);
  			// send email to organization  			
	  		$letter_id = variable_get('hooks_org_registration_letter', '');
				if (!empty($letter_id)) {
					$letter = node_load($letter_id);
					if ($letter) {
						$letter_subject = $letter->title;
						$letter_content = $letter->body['und'][0]['safe_value'];
						$placeholders  = array(
								'{user_login}' => $account->name,
								'{user_first_name}' => $account->{REGFORM_USER_CONTACT_INFO}['und'][0]['first_name'],
								'{user_last_name}' => $account->{REGFORM_USER_CONTACT_INFO}['und'][0]['last_name'],
								'{plan_name}' => $plan->title,
								'{expire_date}' => format_date($account->{REGFORM_USER_FIELD_EXPIRE}['und'][0]['value'], 'short'),
								'{invite_link}' => url(variable_get('regform_join_uri') . '/' . $account->{REGFORM_USER_HASH}['und'][0]['value'], array('absolute' => TRUE)),
							);
							$letter_content = str_replace(array_keys($placeholders), array_values($placeholders), $letter_content);
							$sent = hooks_send_email($letter_subject, $letter_content, $account);
						}
						else {
							watchdog('hooks',  '"Organization registration letter" not sent: node ID of the letter not found (see Hooks and Tricks configuration).',
									array(':plan' => $user->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id']),
									WATCHDOG_ERROR
								);
						}
					}
					else {
						watchdog('hooks',  '"Organization registration letter" not defined. See Hooks and Tricks module setings.', array(),	WATCHDOG_ERROR);
					}
  			}
			}
			else {
				drupal_set_message(t('Error while updating your membership. Please, :contact administratior.', array(':contact' => l('contact', 'contact'))), 'error');
			}
  	}
  }
}
*/
/**
 * Implements hook_cron()
function hooks_cron() {
	// found expired members and assign User Only Membership to them
	$default_plan = hooks_get_plan_by_rid(2);
	if ($default_plan) {
		$query = new EntityFieldQuery();
		$results = $query->entityCondition('entity_type', 'user')//->entityCondition('bundle', 'lottery')
								//->propertyCondition('status', 1)
								->fieldCondition(REGFORM_USER_FIELD_EXPIRE, 'value', time() , '<')
								//->addMetaData('account', user_load(1)) // run the query as user 1
								->execute();
		foreach ($results as $records) {
			foreach ($records as $user) {
				$account = user_load($user->uid);
				$account = hooks_change_plan($account, $default_plan, FALSE, FALSE, 0); // do not change registration type, set "expired" status 
			}
		}
	}
	else {
		watchdog('cron',  'Hooks: Default Membership plan not found while searching expired members and assign User Only Membership to them.',
								array(),
								WATCHDOG_ERROR
							);
	}
	// ==== Send Membership expire notification ============
	$days = variable_get('hooks_expire_notice_days', 7);
	$days = 3600 * 24 * $days; // seconds
	$letter_id = variable_get('hooks_expire_notice_letter', '');
	if (!empty($letter_id)) {
		$letter = node_load($letter_id);
		if ($letter) {
			$letter_subject = $letter->title;
			$letter_content = $letter->body['und'][0]['safe_value'];
			$time1 = time();
			$time2 = $time1 + $days; // for production
			//$time2 = $time1 + $days + (3600 * 24 * 360); // for tests
			$query = new EntityFieldQuery();
			$results = $query->entityCondition('entity_type', 'user')//->entityCondition('bundle', 'lottery')
									->propertyCondition('status', 1)
									->fieldCondition(REGFORM_USER_FIELD_EXPIRE, 'value', $time1 , '>')
									->fieldCondition(REGFORM_USER_FIELD_EXPIRE, 'value', $time2 , '<')
									//->addMetaData('account', user_load(1)) // run the query as user 1
									->execute();
			$emails_sent = 0;
			foreach ($results as $records) {
				foreach ($records as $user) {
					$user = user_load($user->uid);
					$time1 = $user->{REGFORM_USER_FIELD_EXPIRE}['und'][0]['value'];
					$time2 = isset($user->{REGFORM_USER_FIELD_EXPIRE_NOTIFIED}['und']) ? $user->{REGFORM_USER_FIELD_EXPIRE_NOTIFIED}['und'][0]['value'] : FALSE;
					// if letter has not been send within $days
					if (!$time2 || ($time1 - $time2 > $days + 100)) { 
						$plan = commerce_product_load($user->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id']);
						if ($plan && floatval($plan->commerce_price['und'][0]['amount']) > 0) { // skip free members
							if (isset($user->{REGFORM_USER_CONTACT_INFO})) {
								$first_name = $user->{REGFORM_USER_CONTACT_INFO}['und'][0]['first_name'];
								$last_name = $user->{REGFORM_USER_CONTACT_INFO}['und'][0]['last_name'];
							}
							else {
								$first_name = $user->name; 
								$last_name = $user->name;  
							}
							$placeholders  = array(
									'{user_login}' => $user->name,
									'{user_first_name}' => $first_name,
									'{user_last_name}' => $last_name,
									'{plan_name}' => $plan->title,
									'{expire_date}' => format_date($user->{REGFORM_USER_FIELD_EXPIRE}['und'][0]['value'], 'short'),
							);
							$letter_content = str_replace(array_keys($placeholders), array_values($placeholders), $letter_content);
							$sent = hooks_send_email($letter_subject, $letter_content, $user);
							if ($sent) {
								$emails_sent++ ;
								// update user: set "field_expire_notified"
								$edit[REGFORM_USER_FIELD_EXPIRE_NOTIFIED]['und'][0]['value'] = time(); // for production
								//$edit[REGFORM_USER_FIELD_EXPIRE_NOTIFIED]['und'][0]['value'] = time() + (3600 * 24 * 360); // for tests
								$account = $user;
								user_save($account, $edit);
							}
						}
						else {
							watchdog('hooks',  '"Membership expire notification" letter not sent: plan not found (product_id = :plan).',
									array(':plan' => $user->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id']),
									WATCHDOG_ERROR
								);
						}
					}
				}
			}
			watchdog('hooks',  ':count membership expiration notices has been sent. "0" is not an error - just statistics.',
									array(':count' => $emails_sent),
									WATCHDOG_NOTICE
								);
		}
		else {
			watchdog('hooks',  '"Membership expire notification" letter (node ID :nid) not found.',
									array(':nid' => $letter_id),
									WATCHDOG_ERROR
								);
		}
	}
	else {
		watchdog('hooks',  '"Membership expire notification" letter not sent: letter is not defined in :hooks.',
								array(':hooks' => l('Hooks settings', 'admin/config/hooks')),
								WATCHDOG_ERROR
							);
	}
	// ==== END Send Membership expire notification ============
	//return '<p>CRON run expire notification simulation: ' . $emails_sent . ' emails has been sent.</p>';
}
*/
/*
function hooks_send_email($subject, $content, $user, $bcc = FALSE, $ishtml = TRUE) {
	require_once(drupal_get_path('module', 'hooks') . '/class.phpmailer.php');
	$mailer = new PHPMailer();
	
	$mailer->FromName = variable_get('site_mail'); 
	$mailer->From = variable_get('site_name'); 
	$mailer->Subject = $subject;
	
	$mailer->Body = $content;
	$mailer->AltBody = strip_tags($content);
	
	$mailer->isHTML($ishtml);
	$mailer->CharSet = 'utf-8';
	
	$user = is_object($user) ? $user : user_load($user);
	if (isset($user->{REGFORM_USER_CONTACT_INFO})) {
		$user_name = $user->{REGFORM_USER_CONTACT_INFO}['und'][0]['first_name'] . ' ' . $user->{REGFORM_USER_CONTACT_INFO}['und'][0]['last_name'];
	}
	else {
		$user_name = $user->name;
	}
	$mailer->AddAddress($user->mail, $user_name);
	
	if ($bcc) {
		$mailer->AddCC(trim($bcc), '');
	}

	if ($mailer->Send()) {
		$mailer->ClearAddresses();
		$mailer->ClearAttachments();
		return TRUE;
	}
	else {
		watchdog('hooks',  'E-mail ":subject" not send to :toaddress (:user)', array(
											':user' => l($user->name, 'user/' . $user->uid),
											':subject' => $subject,
											':toaddress' => $user->mail,
									),
									WATCHDOG_ERROR
							);
		return FALSE;
	}
}
*/

/**
 * Implements hook_theme()
function hooks_theme($existing, $type, $theme, $path) {
  return array(
    'membership_plans_personal' => array(
      'variables' => array(
        'plans' => NULL,
        'features' => NULL,
        'description' => '',
      ),
      'template' => 'membership-plans-personal',
    ),
    'membership_plans_org' => array(
      'variables' => array(
        'plans' => NULL,
        'features' => NULL,
        'description' => '',
      ),
      'template' => 'membership-plans-organization',
    ),
  );
}*/

/**
 * Found active Membership plan (product) by role ID
 * 
 * @param int $rid
 * @return object $plan or FALSE

function hooks_get_plan_by_rid($rid = '') {
	if (empty($rid)) {
		drupal_set_message(t('Plan not found: rid not provided.'));
		return FALSE;
	}
	if (module_exists('commerce')) {
		$plans = commerce_product_load_multiple(array(), array('type' => REGFORM_PRODUCT_TYPE, 'status' => 1));
		if (!empty($plans)) {
			foreach ($plans as $plan_id => $plan) {
				if ($plan->{REGFORM_PLAN_ROLE_FIELD}['und'][0]['rid'] == $rid) { // authenticated user
					return $plan;
				}
			}
		}
	}
	else {
		//drupal_set_message(t('Warning: default membership plan not assigned. Continue registration and choose plan on "Plan" step, please.'));
		watchdog('hooks',  'Commerce module not available. Membership plan not found.',
								array(),
								WATCHDOG_ERROR
							);
	}

	return FALSE;
}
*/
<?php

function om_membership_menu() {
  $items = array();
  /*
  @NB HORRIBLY FORMATTED CRAP FROM HOOKS TRY TO THIN THIS OUT
  // Personal membership plans
  $uri = variable_get('hooks_personal_plan_uri', 'personal-membership-plans');
  $items[$uri] = array(
    'title' => variable_get('hooks_personal_plan_title', 'Personal membership plans'),
    'page callback' => 'hooks_membership_plans',
    'access arguments' => array('access content'),
    'file' => 'hooks.pages.inc',
    'file path' => drupal_get_path('module', 'hooks'),
    'type' => MENU_CALLBACK,
  );
  $items[$uri . '/%'] = array(
    'title' => 'Membership Plans Sign Up',
    'page callback' => 'hooks_membership_plans_sign_up',
    'page arguments' => array(0, 1),
    'access arguments' => array('access content'),
    'file' => 'hooks.pages.inc',
    'file path' => drupal_get_path('module', 'hooks'),
    'type' => MENU_CALLBACK,
  );
  // Organization membership plans
  $uri = variable_get('hooks_org_plan_uri', 'organization-membership-plans');
  $items[$uri] = array(
    'title' => variable_get('hooks_org_plan_title', 'Organizational membership plans'),
    'page callback' => 'hooks_org_membership_plans',
    'access arguments' => array('access content'),
    'file' => 'hooks.pages.inc',
    'file path' => drupal_get_path('module', 'hooks'),
    'type' => MENU_CALLBACK,
  );
  $items[$uri . '/%'] = array(
    'title' => 'Organization Plans Sign Up',
    'page callback' => 'hooks_membership_plans_sign_up',
    'page arguments' => array(0, 1),
    'access arguments' => array('access content'),
    'file' => 'hooks.pages.inc',
    'file path' => drupal_get_path('module', 'hooks'),
    'type' => MENU_CALLBACK,
  );
  // MANAGE MEMBERS
  $items['admin/people/members'] = array(
     'title' => 'Members',
     'description' => 'Find and manage members.',
    'page callback' => 'hooks_manage_members_page',
    'page arguments' => array('all'),
     'access arguments' => array('administer users'),
     'type' => MENU_LOCAL_TASK,
     'file' => 'hooks.pages.inc',
   );
  $items['admin/people/members/%'] = array(
    'title' => 'Members',
    'description' => 'Find and manage members.',
    'page callback' => 'hooks_manage_members_page',
    'page arguments' => array(3),
    'access arguments' => array('administer users'),
    'type' => MENU_CALLBACK,
    'file' => 'hooks.pages.inc',
  );
  // Some commerce related membership route
  //checkout/34/complete
  $items['checkout/%commerce_order/complete'] = array(
    'title' => 'Checkout complete',
    'page callback' => 'hooks_checkout_complete_page',
    'page arguments' => array(1),
    'access arguments' => array('access checkout'),
    'type' => MENU_CALLBACK,
    'file' => 'hooks.pages.inc',
  );
/*  membership expiration notification test
 * 		uncomment return string in hooks_cron()
 * 	$items['cron_test'] = array(
		'title' => 'Send notifications (test)',
		'description' => 'Send notifications simulation',
		'page callback' => 'hooks_cron_test',
		'access arguments' => array('access content'),
	);*/
  return $items;
}

/**
 * Set user's membership plan according to its role
 * 
 * Plan may be changed while submit profile form or while registration
 * (that is why we need a separate role for every plan)
 * @param int or object $user
 * @return boolean

function hooks_reset_plan($user) {
	$account = is_object($user) ? $user : user_load($user);
	if (!$account) {
		drupal_set_message(t('Error while plan updating.'), error);
		watchdog('hooks',  'Error while plan updating: account not found.',
									array(),
									WATCHDOG_ERROR
								);
		return FALSE;
	}
	$plans = commerce_product_load_multiple(array(), array('type' => REGFORM_PRODUCT_TYPE, 'status' => 1));
	if (!empty($plans)) {
		foreach ($plans as $plan_id => $plan) {
			if (isset($account->roles[$plan->{REGFORM_PLAN_ROLE_FIELD}['und'][0]['rid']])) {
				$edit = array();
				$edit[REGFORM_USER_PLAN_FIELD]['und'][0]['product_id'] = $plan_id;
				$account = user_save($account, $edit);
				break;
			}
		}
	}
	else {
		watchdog('hooks',  'Error while plan updating: membership plan not changed.',
									array(),
									WATCHDOG_ERROR
								);
		return FALSE;
	}
	return TRUE;
}
*/

/**
 * Prolong organization users
 * @param object $org

function hooks_prolong_org_users($org) {
	$query = new EntityFieldQuery();
	$results = $query->entityCondition('entity_type', 'user')//->entityCondition('bundle', 'lottery')
							//->propertyCondition('status', 1)
							->fieldCondition(REGFORM_USER_ORGANIZATION, 'uid', $org->uid)
							//->addMetaData('account', user_load(1)) // run the query as user 1
							->execute();
	foreach ($results as $records) {
		foreach ($records as $user) {
			$account = hooks_change_plan($user->uid, $org->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id'], $org, FALSE, 1); // do not change registration type
		}
	}
} */

/**
 * Change user's membership plan
 * @param object or int(uid) $account
 * 		user object or user_id
 * @param object or int(product_id) $plan 
 * 		new plan object or plan_id
 * @param integer ($user->uid) or object $organization 
 * 		invoke hooks_check_organization() if set
 * @param boolean $change_type
 * 		to change user type to plan type or not
 * @param boolean $status
 * 		0 - Expired , 1 - Active , 2 - Cancelled
 * 		for example '0' goes from CRON : set user's status to expired (last membership plan expired)
 * @return $account or FALSE
 
function hooks_change_plan($account, $plan, $organization = FALSE, $change_type = FALSE, $status = 1) {
		
		if ($organization) {
			$organization = hooks_check_organization($organization);
			if (!$organization) {
				return FALSE;
			}
		}
		
		$edit = array();
		$account = is_object($account) ? $account : user_load($account);
		$plan = is_object($plan) ? $plan : commerce_product_load($plan);

	  if (!$account) {
	  		watchdog('hooks',  'Can\'t load user profile (<a href="/user/:user_id/edit">user ID :user_id</a>) to change membership plan to :plan. Order #:order (see regform_commerce_checkout_complete())',
	  					array(':user_id' => $order->uid, ':plan' => $plan->title),
	  					WATCHDOG_ERROR
	  				);
	  		return FALSE;
	  }
	  // CHANGE ROLE
	  $edit['roles'] = $account->roles;
		$prev_plan = isset($account->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id']) ? commerce_product_load($account->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id']) : FALSE;
		if ($prev_plan && $prev_plan->type == REGFORM_PRODUCT_TYPE) {
			$prev_rid = $prev_plan->{REGFORM_PLAN_ROLE_FIELD}['und'][0]['rid'];
			// delete previous role
			if (!empty($prev_rid) && $prev_rid != 2 && isset($account->roles[$prev_rid])) {
				$edit['roles'] = array_diff($edit['roles'], array($prev_rid => $account->roles[$prev_rid]));
				//user_multiple_role_edit(array($account->uid), 'remove_role', $prev_rid);
			}
		}
		// ADD NEW ROLE
		$role = user_role_load($plan->{REGFORM_PLAN_ROLE_FIELD}['und'][0]['rid']);
		$edit['roles'] = $edit['roles'] + array($role->rid => $role->name);
		//user_multiple_role_edit(array($account->uid), 'add_role', $role->rid);

		// set LAST PLAN
		if (isset($account->{REGFORM_USER_PLAN_FIELD})) {
			$edit[REGFORM_USER_LAST_PLAN_FIELD]['und'][0]['product_id'] = $account->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id'];
		}
		else {
			$edit[REGFORM_USER_PLAN_FIELD]['und'][0]['product_id'] = $plan->product_id;
		}
		
		// CHANGE MEMBERSHIP PLAN
		$edit[REGFORM_USER_PLAN_FIELD]['und'][0]['product_id'] = $plan->product_id;
		
		// CHANGE DATES
		//$timezone = $account->timezone;
		$timezone = variable_get('date_default_timezone', 'America/Denver');
		// expire
		$edit[REGFORM_USER_FIELD_EXPIRE]['und'][0]['value'] = strtotime('+ ' . $plan->field_om_validity['und'][0]['value'] . ' months', time());
		$edit[REGFORM_USER_FIELD_EXPIRE]['und'][0]['timezone'] = $timezone;//$account->timezone;
		$edit[REGFORM_USER_FIELD_EXPIRE]['und'][0]['timezone_db'] = $timezone;//$account->timezone;
		$edit[REGFORM_USER_FIELD_EXPIRE]['und'][0]['date_type'] = 'timestamp';
		// notified
		$edit[REGFORM_USER_FIELD_EXPIRE_NOTIFIED]['und'][0]['value'] = time() + 86400;
		$edit[REGFORM_USER_FIELD_EXPIRE_NOTIFIED]['und'][0]['timezone'] = $timezone;//$account->timezone;
		$edit[REGFORM_USER_FIELD_EXPIRE_NOTIFIED]['und'][0]['timezone_db'] = $timezone;//$account->timezone;
		$edit[REGFORM_USER_FIELD_EXPIRE_NOTIFIED]['und'][0]['date_type'] = 'timestamp';
		// start
		$edit[REGFORM_USER_FIELD_START]['und'][0]['value'] = time();
		$edit[REGFORM_USER_FIELD_START]['und'][0]['timezone'] = $timezone;//$account->timezone;
		$edit[REGFORM_USER_FIELD_START]['und'][0]['timezone_db'] = $timezone;//$account->timezone;
		$edit[REGFORM_USER_FIELD_START]['und'][0]['date_type'] = 'timestamp';
		
		// change STATUS
		$edit[REGFORM_USER_STATUS]['und'][0]['value'] = $status; 
		
		// change REGISTRATION TYPE
		if ($change_type) {
			$edit[REGFORM_USER_TYPE]['und'][0]['value'] = $plan->{REGFORM_PLAN_TYPE}['und'][0]['value'];
		}
		
		// set $edit[REGFORM_USER_FIELD_EXPIRE] from $organization
		// after $edit[REGFORM_USER_FIELD_EXPIRE]['und'][0]['value'] = strtotime('+ ' . $plan->field_om_validity['und'][0]['value'] . ' months', time());
		if ($organization) { 
				$edit[REGFORM_USER_ORGANIZATION]['und'][0]['uid'] = $organization->uid;
				$edit[REGFORM_USER_FIELD_EXPIRE]['und'][0]['value'] = $organization->{REGFORM_USER_FIELD_EXPIRE}['und'][0]['value'];
		}
		// unset organization
		// do not unset organization if plan expired (to make possible to restore organization users after expiration)
		else { 
			if ($status != 0) { 
				$edit[REGFORM_USER_ORGANIZATION]['und'][0]['uid'] = 0;
			}
		}

		$account = user_save($account, $edit);

  	if (!$account) {
	 		watchdog('hooks',  'Can\'t update :user_profile to change membership plan to :plan.',
	 					array(':user_profile' => l('user profile', 'user/' . $order->uid . '/edit'), ':plan' => $plan->title),
	 					WATCHDOG_ERROR
	 				);
		}
	return $account;
}
*/

/**
 * Check organization
 * 
 * For status, membership expire date, max invitations
 * @param int or object $org
 * @return boolean TRUE or FALSE
  
function hooks_check_organization($org) {
	$org = is_object($org) ? $org : user_load($org);
	$error = 0;

	if ($org->status == 0) {
		$error = 1;
	}
	if (time() > (int)$org->{REGFORM_USER_FIELD_EXPIRE}['und'][0]['value']) {
		$error = 2;
	}
	if ($org->{REGFORM_USER_TYPE}['und'][0]['value'] != 1) { // not organization
		$error = 3;
	}
	if (!$error) {
			$count = hooks_count_invitations($org->uid);
			// get organization plan and compare with $count
			$plan = commerce_product_load($org->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id']);
			if ($count >= (int)$plan->{REGFORM_PLAN_ACCOUNTS}['und'][0]['value']) {
				$error = 4;
			}
	}
	
	switch($error) {
		case 0: {
			return $org;
			break;
		}
		case 1: {
			drupal_set_message(t(':organization is not active.', array(':organization' => $org->name)), 'error');
			break;
		}
		case 2: {
			drupal_set_message(t(':organization\'s membership plan has been expired.', array(':organization' => $org->name)), 'error');
			break;
		}
		case 3: {
			drupal_set_message(t(':organization has not organization user type.', array(':organization' => $org->name)), 'error');
			break;
		}
		case 4: {
			drupal_set_message(t('Sorry, no more invitations available.', array(':organization' => $org->name)), 'error');
			break;
		}
		default: ;
	}
	return FALSE;
}
*/
/**
 * Count organization's active invitations
 * @param int $uid
 * @return int number or active invitations
 */
function hooks_count_invitations($uid) {
	$query = new EntityFieldQuery();
	$count = $query->entityCondition('entity_type', 'user')//->entityCondition('bundle', 'lottery')
								//->propertyCondition('status', 1)
								->fieldCondition(REGFORM_USER_ORGANIZATION, 'uid', $uid, '=')
								->fieldCondition(REGFORM_USER_FIELD_EXPIRE, 'value', time(), '>')
								->count()
								->execute();
	return $count; //count($result['user'])
}

/**
 * Implements hook_view_alter()
 
function hooks_user_view_alter(&$build) {
	global $user;
	
	hooks_check_user_registration();
	
	$account = user_load($user->uid);

	// If Organization
	if (isset($account->{REGFORM_USER_TYPE}['und']) && $account->{REGFORM_USER_TYPE}['und'][0]['value'] == 1) { // organization
		// Invitation link
		$build['invitation_link'] = array(
			'#markup' => '<div class="user-invitation-link"><span>Invitation link: </span>' . url(variable_get('regform_join_uri', 'join-us') . '/' . $account->{REGFORM_USER_HASH}['und'][0]['value'], array('absolute' => TRUE)) . '</div>',
			'#weight' => 99,
		);
		// ACCOUNTS (for organizations)
	  $plan = commerce_product_load($account->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id']);
		$build['accounts'] = array(
		  '#markup' => '<div class="user-accounts"><span>Accounts: </span>' . hooks_count_invitations($account->uid) . '/' . $plan->{REGFORM_PLAN_ACCOUNTS}['und'][0]['value'] . '</div>',
		  '#weight' => 100,
	  );
	}
	// rewrite Membership expire and Membership expiration notified : they are show current time
	if (isset($build[REGFORM_USER_FIELD_EXPIRE])) {
		$weight = $build[REGFORM_USER_FIELD_EXPIRE]['#weight'];
		unset($build[REGFORM_USER_FIELD_EXPIRE]);
		$date = date('F j, Y', $account->{REGFORM_USER_FIELD_EXPIRE}['und'][0]['value']);
		$build[REGFORM_USER_FIELD_EXPIRE] = array(
			'#markup' => '<div class="user-profile-membership-expire"><span>' . t('Membership expire:') . ' </span>' . $date . '</div>',
			'#weight' => $weight,
		);
	}
	if (isset($build[REGFORM_USER_FIELD_EXPIRE_NOTIFIED])) {
		$weight = $build[REGFORM_USER_FIELD_EXPIRE_NOTIFIED]['#weight'];
		unset($build[REGFORM_USER_FIELD_EXPIRE_NOTIFIED]);
		$date = date('F j, Y', $account->{REGFORM_USER_FIELD_EXPIRE_NOTIFIED}['und'][0]['value']);
		$build[REGFORM_USER_FIELD_EXPIRE_NOTIFIED] = array(
			'#markup' => '<div class="user-profile-membership-expire2"><span>' . t('Membership expire notified:') . ' </span>' . $date . '</div>',
			'#weight' => $weight,
		);
	}
	// Cancel Membership text block
	$block = variable_get('hooks_cancel_membership');
	if (!empty($block)) {
		$block = module_invoke('block', 'block_view', $block);
		$build['cancel_block'] = array(
			'#markup' => $block['content'],
			'#weight' => 100,
		);
	}
	
	if ($user->uid > 1) {
		unset($build['field_user_hash']);
	}
}
*/
/**
 * Check if user have been passed all registration steps
 * if no, redirect to last registration step
 */
function hooks_check_user_registration() {
	global $user;
	if ($user->uid < 2) { // skip admin and anonymous
		return;
	}
	$account = user_load($user->uid);
	if (isset($account->data['regform']['all_steps_passed']) && $account->data['regform']['all_steps_passed'] == 1) {
		return;
	}
	else {
		// @TODO: delete  on production: temporary skip it for old users
			$edit['data']['regform']['all_steps_passed'] = 1;
			user_save($account, $edit);
		// ----------------------------------------------------------
		drupal_set_message('Please, pass all registration steps. Thank you.');
		if (!isset($_SESSION['regform_plan_id']) || empty($_SESSION['regform_plan_id'])) {
			$product = hooks_get_plan_by_rid(2);
			$plan_node = hooks_get_node_by_product_id($product->product_id);
			$_SESSION['regform_plan_id'] = $plan_node->nid;
		}
		drupal_goto(REGFORM_URI . '/' . $account->data['regform']['last_filled_step']); // last_filled_step important
	}
}

/**
 * Implements hook_form_FORM_ID_alter() 
 */
function hooks_form_commerce_checkout_form_registration_alter(&$form, &$form_state) {
	global $user;
	$account = user_load($user->uid);
	foreach ($form['registration_information']['register_entities'] as $sku => $value) {
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_phone']['und'][0]['value']['#default_value'])) && (isset($account->field_user_phone['und'][0]['safe_value']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_phone']['und'][0]['value']['#default_value'] = $account->field_user_phone['und'][0]['safe_value'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['first_name'])) && (isset($account->field_user_contact_info['und'][0]['first_name']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['first_name'] = $account->field_user_contact_info['und'][0]['first_name'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['last_name'])) && (isset($account->field_user_contact_info['und'][0]['last_name']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['last_name'] = $account->field_user_contact_info['und'][0]['last_name'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['country'])) && (isset($account->field_user_contact_info['und'][0]['country']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['country'] = $account->field_user_contact_info['und'][0]['country'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['administrative_area'])) && (isset($account->field_user_contact_info['und'][0]['administrative_area']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['administrative_area'] = $account->field_user_contact_info['und'][0]['administrative_area'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['locality'])) && (isset($account->field_user_contact_info['und'][0]['locality']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['locality'] = $account->field_user_contact_info['und'][0]['locality'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['dependent_locality'])) && (isset($account->field_user_contact_info['und'][0]['dependent_locality']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['dependent_locality'] = $account->field_user_contact_info['und'][0]['dependent_locality'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['postal_code'])) && (isset($account->field_user_contact_info['und'][0]['postal_code']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['postal_code'] = $account->field_user_contact_info['und'][0]['postal_code'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['thoroughfare'])) && (isset($account->field_user_contact_info['und'][0]['thoroughfare']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['thoroughfare'] = $account->field_user_contact_info['und'][0]['thoroughfare'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['premise'])) && (isset($account->field_user_contact_info['und'][0]['premise']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['premise'] = $account->field_user_contact_info['und'][0]['premise'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['sub_premise'])) && (isset($account->field_user_contact_info['und'][0]['sub_premise']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['sub_premise'] = $account->field_user_contact_info['und'][0]['sub_premise'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['organisation_name'])) && (isset($account->field_user_contact_info['und'][0]['organisation_name']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['organisation_name'] = $account->field_user_contact_info['und'][0]['organisation_name'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['name_line'])) && (isset($account->field_user_contact_info['und'][0]['name_line']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['name_line'] = $account->field_user_contact_info['und'][0]['name_line'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['data'])) && (isset($account->field_user_contact_info['und'][0]['data']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_contact_info']['und'][0]['#address']['data'] = $account->field_user_contact_info['und'][0]['data'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_gender']['und']['#default_value'])) && (isset($account->field_user_gender['und'][0]['value']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_gender']['und']['#default_value'] = $account->field_user_gender['und'][0]['value'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_orientation']['und']['#default_value'])) && (isset($account->field_user_orientation['und'][0]['value']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_orientation']['und']['#default_value'] = $account->field_user_orientation['und'][0]['value'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_age_range']['und']['#default_value'])) && (isset($account->field_age_range['und'][0]['value']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_age_range']['und']['#default_value'] = $account->field_age_range['und'][0]['value'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_income_level']['und']['#default_value'])) && (isset($account->field_income_level['und'][0]['value']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_income_level']['und']['#default_value'] = $account->field_income_level['und'][0]['value'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_internet_access']['und']['#default_value'])) && (isset($account->field_internet_access['und'][0]['value']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_internet_access']['und']['#default_value'] = $account->field_internet_access['und'][0]['value'];
		}
		if (isset($account->field_disability['und'][0]['value'])) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_disability']['und']['#default_value'] = $account->field_disability['und'][0]['value'];
		}
		if ((empty($form['registration_information'][$sku][$sku . '-reg-0']['field_user_ethnic']['und']['#default_value'])) && (isset($account->field_user_ethnic['und'][0]['value']))) {
			$form['registration_information'][$sku][$sku . '-reg-0']['field_user_ethnic']['und']['#default_value'] = $account->field_user_ethnic['und'][0]['value'];
		}
	}
}

/**
 * Menu callback
 */
function hooks_membership_plans() {
	global $user;
	// uset invitation code if any
	if (isset($_SESSION['invite_code'])) {
		unset($_SESSION['invite_code']);
	}
	// set plan type
	$_SESSION['regform_plan_type'] = 'personal';
	// get all allowed features from field
	$features = db_query('SELECT data FROM {field_config} WHERE field_name = :val LIMIT 1', array(':val' => 'field_om_member_features'))->fetchField();
	$features = unserialize($features);
	$taxonomy = taxonomy_vocabulary_load_multiple(FALSE, $conditions = array('machine_name' => $features['settings']['allowed_values'][0]['vocabulary']));
	foreach($taxonomy as $taxonomy){
	  $features = taxonomy_get_tree($taxonomy->vid, $features['settings']['allowed_values'][0]['parent']);
	  break;
	}
	// get plans
	$plans = array();
	$used_features = array();
	$iter = 0;
	$results = db_select('node', 'n')
									->fields('n', array('nid')) 
									->condition('n.type', 'membership_plan') 
									->condition('n.status', 1) 
									->execute(); 
	foreach ($results as $result) { 
	  $plan = node_load($result->nid);
		if (!isset($plan->field_plan['und'])) {
			drupal_set_message(t('Product for ":plan" not defined.', array(':plan' => $plan->title)), 'error');
			watchdog('hooks',  'Product for ":plan" not defined.',
									array(':plan' => $plan->title),
									WATCHDOG_ERROR
								);
			continue;
		}
		$product = commerce_product_load($plan->field_plan['und'][0]['product_id']);
		// is plan personal?
		if ( !isset($product->{REGFORM_PLAN_TYPE}) || $product->{REGFORM_PLAN_TYPE}['und'][0]['value'] != 0) {
		  continue;
		}
		$plan_features = array();
		if (isset($product->field_om_member_features['und'])) {
		  foreach ($product->field_om_member_features['und'] as $key => $val) {
		    $tid = $val['tid'];
		    foreach($features as $feature){
		      if ($feature->tid == $tid){
			      $plan_features[$feature->name] = check_plain($feature->name);
			      if (!in_array($feature, $used_features)){
			        $used_features[] = $feature;
			      }
			      break;
		      }
		    }
		  }
		}
	  $k = count($plan_features) . '_' . $iter;
	  $plans[$k]['nid'] = $plan->nid;
	  $plans[$k]['title'] = $plan->title;
	  $plans[$k]['features'] = $plan_features;
	  $plans[$k]['summary'] = $plan->body['und'][0]['safe_summary'];
	  $plans[$k]['product_id'] = $product->product_id; // used in regform_registration_form() (regform.pades.inc)
	  $plans[$k]['price'] = number_format($product->commerce_price['und'][0]['amount'] / 100, 0, ',', '\'');
	  $plans[$k]['currency'] = $product->commerce_price['und'][0]['currency_code'];
	  $plans[$k]['validity'] = $product->field_om_validity['und'][0]['value'];
	  //$plans[$k]['add_to_cart'] = hooks_get_add_to_cart($product);
	  if ($user->uid > 0) { 
	  	$account = user_load($user->uid);
	  	if (isset($account->{REGFORM_USER_PLAN_FIELD}['und']) && $account->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id'] == $product->product_id) {
	  		$plans[$k]['add_to_cart'] = '<div id = "current-plan">Current plan</div>';
	  	}
	  	else {
	  		$plans[$k]['add_to_cart'] = '<input type="button" onclick="document.location=\'' . variable_get('hooks_personal_plan_uri', 'personal-membership-plans') . '/' . $plan->nid . '\'" class="form-submit sign-up-button" value="Update">';
	  	}
	  }
	  else { // anonymous
	  	$plans[$k]['add_to_cart'] = '<input type="button" onclick="document.location=\'' . variable_get('hooks_personal_plan_uri', 'personal-membership-plans') . '/' . $plan->nid . '\'" class="form-submit sign-up-button" value="Sign Up">';
	  }
	  $iter++;
	}
	ksort($plans);
  // description
  $description = '';
  $block_id = variable_get('hooks_personal_plan', '');
  if (!empty($block_id)) {
  $description = module_invoke('block', 'block_view', $block_id);
  $description = render($description['content']);
  }
	//return theme('membership_plans', $plans, $features);
	$content = array(
	  'data' => array(
    '#theme' => 'membership_plans_personal',
    '#plans' => $plans,
    '#features' => $used_features,
    '#description' => $description,
	  ),
	);
	return $content;
}
/**
 * Menu callback
 * 
 * Add selected plan to cart and redirect to registration page
 */
function hooks_membership_plans_sign_up($url, $plan_id) {
  global $user;
  $plan_id = intval($plan_id);
  if (!$plan_id) {
    drupal_set_message(t('Membership plan not selected.'));
    drupal_goto($url);
  }
  else {
  	$plan = node_load($plan_id);
    if ($user->uid == 0) { // anonymous user
      $_SESSION['regform_plan_id'] = $plan_id;
      $_SESSION['regform_plan_name'] = $plan->title;
      drupal_goto(variable_get('regform_uri'));
    }
    // add plan to cart
    if ($plan->type = 'membership_plan' && $plan->status == 1) {
      $product = commerce_product_load($plan->field_plan['und'][0]['product_id']);
      if ($product && $product->commerce_price['und'][0]['amount'] > 0) {
        $added = commerce_cart_product_add_by_id($product->product_id, 1);
        if ( $added ) {
          drupal_set_message(t(':plan added to your shopcart and is waiting for checkout.', array(':plan' => $plan->title)));
          $order = commerce_cart_order_load($user->uid);
          drupal_goto('checkout/' . $order->order_id);
        }
        else {
          drupal_set_message(t('Error while adding membership plan to shopcart.'));
          drupal_goto($url);
        }
      }
      else { // free membership plan
        // @TODO what to do if  user already has not free plan? is there any free plans will be except "User only"?
        $rid = $plan->{REGFORM_PLAN_ROLE_FIELD}['und'][0]['rid'];
        if ($rid == 2) {
          drupal_set_message('All registered users already has this plan by default.');
          drupal_goto($url);
        }
      }
    }
    else {
      drupal_set_message(t('Membership plan not found.'));
      drupal_goto($url);
    }
  }
}
/**
 * Menu callback
 */
function hooks_org_membership_plans() {
  global $user;
  // uset invitation code if any
	if (isset($_SESSION['invite_code'])) {
		unset($_SESSION['invite_code']);
	}
	// set plan type
	$_SESSION['regform_plan_type'] = 'organizational';
  // get all allowed features from feild
  $features = db_query('SELECT data FROM {field_config} WHERE field_name = :val LIMIT 1', array(':val' => 'field_om_member_features'))->fetchField();
  $features = unserialize($features);
  $taxonomy = taxonomy_vocabulary_load_multiple(FALSE, $conditions = array('machine_name' => $features['settings']['allowed_values'][0]['vocabulary']));
	foreach($taxonomy as $taxonomy){
	  $features = taxonomy_get_tree($taxonomy->vid, $features['settings']['allowed_values'][0]['parent']);
	  break;
	}
  // get plans
  $plans = array();
	$used_features = array();
  $iter = 0;
  $results = db_select('node', 'n')
                  ->fields('n', array('nid')) 
                  ->condition('n.type', 'membership_plan') 
                  ->condition('n.status', 1) 
                  ->execute(); 
  foreach ($results as $result) { 
    $plan = node_load($result->nid);
    if (!isset($plan->field_plan['und'])) {
      drupal_set_message(t('Product for ":plan" not defined.', array(':plan' => $plan->title)), 'error');
      watchdog('hooks',  'Product for ":plan" not defined.',
                  array(':plan' => $plan->title),
                  WATCHDOG_ERROR
                );
      continue;
    }
    $product = commerce_product_load($plan->field_plan['und'][0]['product_id']);
    // is plan organization?
    if ( !isset($product->{REGFORM_PLAN_TYPE}) || $product->{REGFORM_PLAN_TYPE}['und'][0]['value'] != 1) {
     continue;
    }
    $plan_features = array();
		if (isset($product->field_om_member_features['und'])) {
		  foreach ($product->field_om_member_features['und'] as $key => $val) {
		    $tid = $val['tid'];
		    foreach($features as $feature){
		      if ($feature->tid == $tid){
			      $plan_features[$feature->name] = check_plain($feature->name);
			      if (!in_array($feature, $used_features)){
			        $used_features[] = $feature;
			      }
			      break;
		      }
		    }
		  }
		}
    $k = count($plan_features) . '_' . $iter;
    $plans[$k]['nid'] = $plan->nid;
    $plans[$k]['title'] = $plan->title;
    $plans[$k]['features'] = $plan_features;
    $plans[$k]['summary'] = isset($plan->body['und']) ? $plan->body['und'][0]['safe_summary'] : '';
    $plans[$k]['product_id'] = $product->product_id; // used in regform_registration_form() (regform.pades.inc)
    $plans[$k]['price'] = commerce_currency_format($product->commerce_price['und'][0]['amount'], $product->commerce_price['und'][0]['currency_code']);
    $plans[$k]['currency'] = $product->commerce_price['und'][0]['currency_code'];
    $plans[$k]['validity'] = $product->field_om_validity['und'][0]['value'];
    $plans[$k]['user_accounts'] = isset($product->field_om_accounts['und']) ? $product->field_om_accounts['und'][0]['value'] : 0;
    //$plans[$k]['add_to_cart'] = hooks_get_add_to_cart($product);
    if ($user->uid > 0) { 
    $account = user_load($user->uid);
    if (isset($account->{REGFORM_USER_PLAN_FIELD}['und']) && $account->{REGFORM_USER_PLAN_FIELD}['und'][0]['product_id'] == $product->product_id) {
      $plans[$k]['add_to_cart'] = '<div id = "current-plan">Current plan</div>';
    }
    else {
      $plans[$k]['add_to_cart'] = '<input type="button" onclick="document.location=\'' . variable_get('hooks_org_plan_uri', 'organization-membership-plans') . '/' . $plan->nid . '\'" class="form-submit sign-up-button" value="Update">';
    }
    }
    else { // anonymous
    $plans[$k]['add_to_cart'] = '<input type="button" onclick="document.location=\'' . variable_get('hooks_org_plan_uri', 'organization-membership-plans') . '/' . $plan->nid . '\'" class="form-submit sign-up-button" value="Sign Up">';
    }
    $iter++;
  }
  ksort($plans);
  // description
  $description = '';
  $block_id = variable_get('hooks_org_plan', '');
  if (!empty($block_id)) {
  $description = module_invoke('block', 'block_view', $block_id);
  $description = render($description['content']);
  }

  //return theme('membership_plans', $plans, $features);
  $content = array(
    'data' => array(
    '#theme' => 'membership_plans_org',
    '#plans' => $plans,
    '#features' => $used_features,
    '#description' => $description,
    ),
  );
  return $content;
}

<?php 
/**
 * @file
 * 
 * Hooks and Tricks settings. 
 */


function hooks_admin_settings() {
	
	$form['emails'] = array(
		'#type' => 'fieldset',
		'#title' => t('Notify E-mails'),
		'#weight' => 1,
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	$form['emails']['hooks_expire_notice_days'] = array(
		'#type' => 'textfield',
		'#title' => t('Days before membership expire to send notification letter'),
		'#default_value' => variable_get('hooks_expire_notice_days'),
		'#size' => 5,
		'#maxlengh' => 2,
		'#weight' => 5,
	);
	$form['emails']['hooks_expire_notice_letter'] = array(
		'#type' => 'textfield',
		'#title' => t('"Membership expire notice" letter'),
		'#description' => t('Node ID of "Membership expire notice" letter (see "Notification letter" content type).'),
		'#default_value' => variable_get('hooks_expire_notice_letter'),
		'#size' => 5,
		'#maxlengh' => 5,
		'#weight' => 10,
	);
	$form['emails']['hooks_org_registration_letter'] = array(
		'#type' => 'textfield',
		'#title' => t('"Organization registration letter"'),
		'#description' => t('Node ID of "Organization registration letter" (see "Notification letter" content type).'),
		'#default_value' => variable_get('hooks_org_registration_letter'),
		'#size' => 5,
		'#maxlengh' => 5,
		'#weight' => 15,
	);
	
	 $form['plans'] = array(
    '#type' => 'fieldset',
    '#title' => t('Membership plans'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['plans']['hooks_personal_plan_title'] = array(
    '#type' => 'textfield',
    '#title' => t('"Personal membership plans" page title'),
    //'#description' => t('"Personal membership plans" page title.'),
    '#default_value' => variable_get('hooks_personal_plan_title'),
    '#size' => 60,
    '#weight' => 5,
  );
  $form['plans']['hooks_personal_plan'] = array(
    '#type' => 'textfield',
    '#title' => t('Personal membership plans description'),
    '#description' => t('Block ID with personal membership plans description.'),
    '#default_value' => variable_get('hooks_personal_plan'),
    '#size' => 5,
    '#maxlengh' => 2,
    '#weight' => 5,
  );
  $form['plans']['hooks_personal_plan_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Personal membership plans URI'),
    '#description' => t('URI of "Personal membership plans" page.'),
    '#default_value' => variable_get('hooks_personal_plan_uri', 'personal-membership-plans'),
    '#size' => 60,
    '#weight' => 5,
  );
  $form['plans']['hooks_org_plan_title'] = array(
    '#type' => 'textfield',
    '#title' => t('"Organization membership plans" page title'),
    //'#description' => t('Block ID with organization membership plans description.'),
    '#default_value' => variable_get('hooks_org_plan_title'),
    '#size' => 60,
    '#weight' => 10,
  );
  $form['plans']['hooks_org_plan'] = array(
    '#type' => 'textfield',
    '#title' => t('Organization membership plans description'),
    '#description' => t('Block ID with organization membership plans description.'),
    '#default_value' => variable_get('hooks_org_plan'),
    '#size' => 5,
    '#maxlengh' => 5,
    '#weight' => 10,
  );
  $form['plans']['hooks_org_plan_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Organization membership plans URI'),
    '#description' => t('URI of "Organization membership plans" page.'),
    '#default_value' => variable_get('hooks_org_plan_uri', 'organization-membership-plans'),
    '#size' => 60,
    '#weight' => 10,
  );

$form['other'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other'),
    '#weight' => 4,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['other']['hooks_cancel_membership'] = array(
    '#type' => 'textfield',
    '#title' => t('Cancel Membership description'),
    '#description' => t('Block ID with Cancel Membership description.'),
    '#default_value' => variable_get('hooks_cancel_membership'),
    '#size' => 5,
    '#maxlengh' => 5,
    '#weight' => 10,
  );
  $form['other']['hooks_checkout_complete'] = array(
    '#type' => 'textfield',
    '#title' => t('Checkout Complete message (no plan)'),
    '#description' => t('Block ID with Checkout Complete message (whithout any membership plan).'),
    '#default_value' => variable_get('hooks_checkout_complete'),
    '#size' => 5,
    '#maxlengh' => 5,
    '#weight' => 15,
  );
  $form['other']['hooks_checkout_complete_personal'] = array(
    '#type' => 'textfield',
    '#title' => t('Checkout Complete message (personal plan)'),
    '#description' => t('Block ID with Checkout Complete message (with personal plan).'),
    '#default_value' => variable_get('hooks_checkout_complete_personal'),
    '#size' => 5,
    '#maxlengh' => 5,
    '#weight' => 20,
  );
  $form['other']['hooks_checkout_complete_org'] = array(
    '#type' => 'textfield',
    '#title' => t('Checkout Complete message (organizational plan)'),
    '#description' => t('Block ID with Checkout Complete message (with organizational plan).'),
    '#default_value' => variable_get('hooks_checkout_complete_org'),
    '#size' => 5,
    '#maxlengh' => 5,
    '#weight' => 25,
  );
	return system_settings_form($form);
}