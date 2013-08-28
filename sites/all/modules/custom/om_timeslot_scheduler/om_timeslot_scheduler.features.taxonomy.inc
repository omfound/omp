<?php
/**
 * @file
 * om_timeslot_scheduler.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function om_timeslot_scheduler_taxonomy_default_vocabularies() {
  return array(
    'channels' => array(
      'name' => 'Channels',
      'machine_name' => 'channels',
      'description' => 'A vocabulary to hold channel terms that connect playback servers to airings',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
