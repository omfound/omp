<?php
class localShowsSchedulingRule extends timeslotSchedulingRule {
  public function executeRule($timeslot) {
    $shows = array();
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'));
    $query->condition('type', 'om_show', '=');
    // These two lines specific to Local Show Rule.
    $query->join('field_data_field_om_locally_produced', 'local', 'local.entity_id=n.nid');
    $query->condition('field_om_locally_produced_value', 1, '=');
    // If the timeslot being scheduled has a theme make sure shows share the theme.
    if (isset($timeslot->field_om_timeslot_theme['und'][0]['tid'])) {
      $query->join('field_data_field_om_theme', 'theme', 'theme.entity_id=n.nid');
      $query->condition('field_om_theme_tid', $timeslot->field_om_timeslot_theme['und'][0]['tid'], '=');
    }
    $result = $query->execute();
    $shows_by_airings = array();
    while($nids = $result->fetchAssoc()) {
      $airing_count_query = db_select('field_data_field_om_show_aired', 'aired');
      $airing_count_query->fields('aired', array('field_om_show_aired_value'));
      $airing_count_query->condition('entity_id', $nids['nid'], '=');
      $airing_count_query->orderBy('revision_id', 'DESC');
      $airing_count_query->range(0, 1);
      $airing_result = $airing_count_query->execute();
      $airings = $airing_result->fetchAll();
      if (isset($airings[0]->field_om_show_aired_value)) {
        $shows_by_airings[$nids['nid']] = $airings[0]->field_om_show_aired_value;
      }
      else {
        $shows_by_airings[$nids['nid']] = 0;
      }
    }
    asort($shows_by_airings);
    foreach($shows_by_airings AS $nid => $rank) {
      $shows[] = $nid;
    }
    return array_values($shows);
  }
}
