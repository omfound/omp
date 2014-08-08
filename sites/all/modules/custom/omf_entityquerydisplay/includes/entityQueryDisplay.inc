<?php

Class queryDisplay extends SelectQueryExtender {
  public function __construct(SelectQueryInterface $query, DatabaseConnection $connection) {
    parent::__construct($query, $connection);

    // Add convenience tag to mark that this is an extended query. We have to
    // do this in the constructor to ensure that it is set before preExecute()
    // gets called.
    $this->addTag('querydisplay');
  }

  public function createTable($variables = null) {
    if (empty($variables)) {
      $variables = array();
      dsm($this);
    }
  }
}
