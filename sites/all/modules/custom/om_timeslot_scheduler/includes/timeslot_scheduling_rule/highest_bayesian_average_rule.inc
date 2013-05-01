<?php
class highestBayesianAverageRule extends timeslotSchedulingRule {
  public function executeRule($timeslot) {
    $shows = array();
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'));
    $query->condition('type', 'om_show', '=');
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
        if (isset($rating_value[0]->score)) {
          $vote_results[$nids['nid']] = $rating_value[0]->score;
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