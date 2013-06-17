<?php
class newestEpisodeInProjectSchedulingRule extends timeslotSchedulingRule {
  public function executeRule($timeslot) {
    $shows = array();
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'));
    $query->condition('type', 'om_show', '=');
    // These two lines specific to Local Show Rule.
    $query->join('field_data_field_om_show_project', 'project', 'project.entity_id=n.nid');
    $query->condition('field_om_show_project_nid', $timeslot->nid, '=');
    $resource = $query->execute();
    // Form a list ranked by field_om_show_episode_number
    $shows = array();
    while ($result = $resource->fetchAssoc()) {
      $episode_query = db_select('field_data_field_om_show_episode_number', 'episode');
      $episode_query->fields('episode', array('entity_id', 'field_om_show_episode_number_value'));
      $episode_query->condition('entity_id', $result['nid'], '=');
      $resource_episode = $episode_query->execute();
      $episodes = $resource_episode->fetchAll();
      if (!empty($episodes)) {
        $shows[$result['nid']] = $episodes[0]->field_om_show_episode_number_value;
      }
      else {
        $shows[$result['nid']] = 0;
      }
    }
    krsort($shows);
    return array_values($shows);
  }
}
