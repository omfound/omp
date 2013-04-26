<?php
class stationBrandingSchedulingRule extends timeslotSchedulingRule {
  public function executeRule($timeslot) {
    $shows = array();
    $query = db_select('field_data_field_om_show_branding', 'branding');
    $query->fields('branding', array('entity_id'));
    $query->condition('field_om_show_branding_value', 1, '=');
    $result = $query->execute();
    
    while($row = $result->fetchAssoc()) {
      $shows[] = $row['entity_id'];
    }
    shuffle($shows);
    return array_values($shows);
  }
}