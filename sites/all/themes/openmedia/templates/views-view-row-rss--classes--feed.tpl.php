   * @file views-view-row-rss.tpl.php
   * Default view template to display a item in an RSS feed.
   *
   * @ingroup views_templates
   */
  ?>
  <item>
    <title><?php print $title; ?></title>
    <link><?php print $link?></link>
    <description><?php print $description; ?></description>
    <summary><?php print $description; ?></summary>
    <content> <?php print $row->{$field->field_class_description} </content>
</item>
