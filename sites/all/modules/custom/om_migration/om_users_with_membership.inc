<?php
// User Migration class
class omUserWithMembershipMigration extends Migration {
  // class constructor
  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('om_users_with_membership_group'));
    $this->description = t('Migrate Drupal 6 users');

    // some field definitions; roles will be added later in prepareRow()
    $source_fields = array(
      'uid' => t('User ID'),
      'roles' => t('The set of roles assigned to a user.'),
    );

    $query = Database::getConnection('default', 'legacy')
      ->select('users','u');
    //$query = db_select(SOURCE_DATABASE .'.users', 'u');
    $query->join(CIVI_DATABASE .'.civicrm_uf_match', 'ccum', 'ccum.uf_id = u.uid'); //JOIN users with civi join table
    $query->join(CIVI_DATABASE .'.civicrm_membership', 'cm', 'cm.contact_id=ccum.contact_id'); //JOIN with membership
    $query = $query->fields('u', array('uid', 'name', 'pass', 'mail', 'created', 'access', 'login', 'status', 'init'))
      // set query to be distinct
      ->distinct()
      // user is active user
      ->condition('u.status', 1, '=')
      // grab users greater than UID 31, since there are that many created on the new site.
      ->condition('u.uid', 31, '>')
      // grab users who have accessed site since cutoff date
      // Don't limit this migration by date
      // ->condition('u.access',USER_MIGRATION_CUTOFF, '>')
      // TODO: also need to add users that have an active project. Perhaps in diff migation class.
      ->orderBy('u.uid', 'ASC');
     //select distinct uid from node join content_type_om_project using(nid);

    $this->source = new MigrateSourceSQL($query, $source_fields,NULL,
      array('map_joinable' => FALSE));
    // No need to force users to reset their passwords
    $this->destination = new MigrateDestinationUser(array('md5_passwords' => TRUE));

    // map source and destination keys
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'uid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'D6 Unique User ID',
          'alias' => 'u',
        )
      ),
      MigrateDestinationUser::getKeySchema()
    );

    // Create the field mappings
    // order: $destination, $source
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('field_legacy_uid', 'uid');
    $this->addFieldMapping('name', 'name')->dedupe('users', 'name');
    $this->addFieldMapping('pass', 'pass');
    $this->addFieldMapping('mail', 'mail')->dedupe('users', 'mail');
    $this->addFieldMapping('language')->defaultValue('');
    $this->addFieldMapping('theme')->defaultValue('');
    $this->addFieldMapping('signature')->defaultValue('');
    $this->addFieldMapping('signature_format')->defaultValue('filtered_html');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('access', 'access');
    $this->addFieldMapping('login', 'login');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('picture')->defaultValue(0);
    $this->addFieldMapping('init', 'init');
    $this->addFieldMapping('timezone')->defaultValue(NULL);
    $this->addFieldMapping('path')->issueGroup(t('DNM')); // DNM = Do Not Map
    $this->addFieldMapping('roles', 'roles');
  }
  // end omUserMigration class constructor

  // massage the user roles before saving
  // TODO: customize for DOM roles for D6 and D7
  public function prepareRow($current_row) {
    $source_id = $current_row->uid;
    $query = Database::getConnection('default', 'legacy')
      ->select('users_roles','r')
    //$query = db_select(SOURCE_DATABASE .'.users_roles', 'r')
      ->fields('r', array('uid', 'rid'))
      ->condition('r.uid', $source_id, '=');
    $results = $query->execute();
    // add the Authenticated role for everyone
    $roles = array('2' => '2');
    foreach ($results as $row) {
      // adjust the old to new role id's
      // Editors (rid 3) need role id 4
      if ($row->rid == 3) {
        $roles['4'] = '4';
      }
      // Admins (rid 4) need role id 3
      if ($row->rid == 4) {
        $roles['3'] = '3';
      }
      // Certifications
      // Edit role
      if ($row->rid == 26) {
        $roles['13'] = '13';
      }
      // Field role
      if ($row->rid == 10) {
        $roles['14'] = '14';
      }
      // Studio role
      if ($row->rid == 12) {
        $roles['15'] = '15';
      }

      // Collaboraters are role id 5 in both old and new dbs
      // skip roles greater than 4 for now
      if ($row->rid > 4) {
        continue;
      }
      $roles[$row->rid] = $row->rid;
    }
    $current_row->roles = $roles;
    return TRUE;
    // return FALSE if you wish to skip a particular row
  }
} // close the omUserMigration class
