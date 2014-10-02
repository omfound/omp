<?php
/**
 * @file
 * XML for PBCore
 */

//to debug, comment out the text/xml header and enable the print_r.  
// dsm() does NOT work at this level
header("Content-type: text/xml");

//print '<pre>';
//print_r($node);
//print '</pre>';

//@TODO: Add licensing
//node->cc['name']
//node->cc['uri']
//node->cc['type']

//http://www.pbcore.org/PBCore/PBCore_SampleRecords/sample01.xml
?>
<xml version="1.0" encoding="UTF-8">
  
  <PBCoreDescriptionDocument xmlns="http://www.pbcore.org/PBCore/PBCoreNamespace.html"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xsi:schemaLocation="http://www.pbcore.org/PBCore/PBCoreNamespace.html http://www.pbcore.org/PBCore/PBCoreSchema.xsd">
   
   <pbcoreIdentifier>
     <identifier><?php print $node->title ?></identifier>
     <identifierSource><?php print variable_get('site_name', '') ?></identifierSource>
   </pbcoreIdentifier>

   <pbcoreTitle>
     <title><?php print $node->title ?></title>
     <titleType>Clip</titleType>
   </pbcoreTitle>

  <?php if (module_exists('cm_project')) { ?>
    <pbcoreTitle>
      <title><?php print $node->og ?></title>
      <titleType>Project</titleType>
    </pbcoreTitle>
  <?php } ?>

    <pbcoreDescription>
      <description><?php print $node->body[LANGUAGE_NONE][0]['safe_value'] ?></description>
      <descriptionType>Abstract</descriptionType>
    </pbcoreDescription>


  <?php foreach ($node->field_pbcore_genres[LANGUAGE_NONE] as $rating) { 
    $term = taxonomy_term_load($rating['tid']);  
  ?>  
    <pbcoreGenre>
      <genre><?php print $term->name ?></genre>
      <genreAuthorityUsed>PBMD Project</genreAuthorityUsed>
    </pbcoreGenre>
  <?php } ?>

  <?php foreach ($node->field_pbcore_fcc_ratings[LANGUAGE_NONE] as $rating) { 
    $term = taxonomy_term_load($rating['tid']);  
  ?> 
  
    <pbcoreAudienceRating>
      <audienceRating><?php print $term->name ?></audienceRating>
    </pbcoreAudienceRating>
    
  <?php } ?>
  
  <?php $term = taxonomy_term_load($node->field_pbcore_languages[LANGUAGE_NONE][0]['tid']); ?>
    <pbcoreInstantiation>
       <language><?php print $term->name ?></language>
       <dateCreated><?php print $node->published ?></dateCreated>
    </pbcoreInstantiation>

</PBCoreDescriptionDocument>
</xml>
