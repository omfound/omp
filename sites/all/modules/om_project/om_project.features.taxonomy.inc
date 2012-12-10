<?php
/**
 * @file
 * om_project.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function om_project_taxonomy_default_vocabularies() {
  return array(
    'genres' => array(
      'name' => 'Genres',
      'machine_name' => 'genres',
      'description' => 'Customizable ratings vocabulary to be mapped with PB Core Genres',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '-6',
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
    'languages' => array(
      'name' => 'Languages',
      'machine_name' => 'languages',
      'description' => 'Customizable language vocabulary to be mapped with PB Core Languages',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '-5',
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
    'om_project_types' => array(
      'name' => 'OM Project Types',
      'machine_name' => 'om_project_types',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '-4',
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
    'pbcore_fcc_ratings' => array(
      'name' => 'PBCore FCC Ratings',
      'machine_name' => 'pbcore_fcc_ratings',
      'description' => '',
      'hierarchy' => '1',
      'module' => 'pbcore',
      'weight' => '-10',
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
    'pbcore_genres' => array(
      'name' => 'PBCore Genres',
      'machine_name' => 'pbcore_genres',
      'description' => 'Customizable genres vocabulary to be mapped with PB Core Genres',
      'hierarchy' => '0',
      'module' => 'pbcore',
      'weight' => '-9',
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
    'pbcore_languages' => array(
      'name' => 'PBCore Languages',
      'machine_name' => 'pbcore_languages',
      'description' => '',
      'hierarchy' => '1',
      'module' => 'pbcore',
      'weight' => '-8',
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
    'ratings' => array(
      'name' => 'Ratings',
      'machine_name' => 'ratings',
      'description' => 'Customizable ratings vocabulary to be mapped with PB Core FCC Ratings',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '-7',
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
