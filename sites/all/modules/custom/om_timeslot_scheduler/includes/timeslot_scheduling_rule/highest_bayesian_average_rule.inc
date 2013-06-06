<?php
class highestBayesianAverageRule extends timeslotSchedulingRule {
  public function executeRule($timeslot) {
    $shows = array();
    $last_two_months = time() - (3600 * 30 * 6);
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'));
    $query->condition('type', 'om_show', '=');
    $query->join('field_data_field_om_show_broadcast_file', 'file', 'file.entity_id=n.nid');
    // If the timeslot being scheduled has a theme make sure shows share the theme.
    if (isset($timeslot->field_om_timeslot_theme['und'][0]['tid'])) {
      $query->join('field_data_field_om_theme', 'theme', 'theme.entity_id=n.nid');
      $query->condition('field_om_theme_tid', $timeslot->field_om_timeslot_theme['und'][0]['tid'], '=');
    }
    $result = $query->execute();
    $vote_results = array();
    while($nids = $result->fetchAssoc()) {
      $rating_query = db_select('alternative_rating', 'votes');
      $rating_query->fields('votes', array('score'));
      $rating_query->condition('nid', $nids['nid'], '=');
      $rating_result = $rating_query->execute();
      $rating_value = $rating_result->fetchAll();
      $airing_query = db_select('field_data_field_om_show_id', 'airings');
      $airing_query->join('field_data_field_om_airing_dates', 'dates', 'airings.entity_id=dates.entity_id');
      $airing_query->fields('airings', array('entity_id'));
      $airing_query->condition('field_om_show_id_value', $nids['nid'], '=');
      $airing_query->condition('field_om_airing_dates_value', $last_two_months, '>=');
      $airing_resource = $airing_query->execute();
      $airing_count = $airing_resource->rowCount();
      if (!is_numeric($airing_count)) {
        $airing_count = 0;
      }
      if (isset($rating_value[0]->score)) {
        $vote_results[$nids['nid']] = $rating_value[0]->score - (.02 * $airing_count);
      }
      else {
        $vote_results[$nids['nid']] = 0;
      }
    }
    arsort($vote_results);
    foreach($vote_results AS $nid => $rating) {
      $shows[] = $nid;
    }
    return array_values($shows);
  }
}
