<?php

/**
 *  * @file
 *   * Template to display a view as a table.
 *    *
 *     * - $title : The title of this group of rows.  May be empty.
 *      * - $header: An array of header labels keyed by field id.
 *       * - $header_classes: An array of header classes keyed by field id.
 *        * - $fields: An array of CSS IDs to use for each field id.
 *         * - $classes: A class or classes to apply to the table, based on settings.
 *          * - $row_classes: An array of classes to apply to each row, indexed by row
 *           *   number. This matches the index in $rows.
 *            * - $rows: An array of row items. Each row is an array of content.
 *             *   $rows are keyed by row number, fields within rows are keyed by field ID.
 *              * - $field_classes: An array of classes to apply to each field, indexed by
 *               *   field id, then row number. This matches the index in $rows.
 *                * @ingroup views_templates
 *                 */
?>
<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
  <?php if (!empty($title)) : ?>
    <caption><?php print $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label): ?>
          <?php if ($field != 'path') { ?>
            <th <?php if ($header_classes[$field]) { print 'class="'. $header_classes[$field] . '" '; } ?>>
              <?php print $label; ?>
            </th>
          <?php } ?>
        <?php endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
    <?php foreach ($rows as $row_count => $row): ?>
      <tr <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>>
        <?php foreach ($row as $field => $content): ?>
          <?php if ($field != 'path' && $field != 'title' && $field != 'field_om_calendar') { ?>
            <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
              <?php print $content; ?>
            </td>
          <?php }elseif ($field == 'title') { ?>
            <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
              <?php if (!empty($_GET['iframe_mode'])) { ?>
              <?php 
                $options = array();
                $options['absolute'] = TRUE;
                $options['attributes']['target'] = '_blank';
                //$options['query']['iframe_mode'] = 'true';
              ?>      
              <?php }else{ ?>
                <?php $options = array('absolute' => TRUE); ?>
              <?php } ?>
              <?php $link = l($content, $rows[$row_count]['path'], $options); ?>
              <?php print $link; ?>
            </td>
          <?php }elseif ($field == 'field_om_calendar') { ?>
            <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
              <?php print l('Download PDF', str_replace('/pub', '/export?format=pdf', $content)); ?>
            </td>
          <?php } ?>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
