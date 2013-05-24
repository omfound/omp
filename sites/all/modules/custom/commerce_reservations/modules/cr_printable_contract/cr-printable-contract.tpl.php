<?php 
global $base_path;
$logourl = theme_get_setting('logo_path', '');
?>
  <html>
    <head>
      <title>Contract</title>
      <link type="text/css" rel="stylesheet" href="<?php print $base_path ?><?php print drupal_get_path('module', 'cr_printable_contract'); ?>/contract.css" />
    </head>
    <body>
      <div id="page">
        <div id="header">
        <?php if ($logourl) { ?>
           <img src="<?php print $base_path ?><?php print $logourl ?>">
        <?php } ?>
        <h2><?php print variable_get('site_name', ''); ?> Equipment Rental Contract</h2>
<?php print variable_get('cr_contract_header','');
        ?>
        Order Date: <?php print date_format_date($order_date, "long") . '<br />'; ?>
        Name: <?php print $username ?><br />
        Email: <?php print $email ?><br />
        Phone: <?php print $phone ?><br />
        
        </div>
        <table id="cost">
          <thead>
            <tr>
              <th>Item</th>
              <th>Comcral Cost</th>
              <th>Member Cost</th>
            </tr>
          </thead>
          <tbody>
          <?php
  $discount = variable_get('cr_membership_discount', 1); 
  $comcral_cost_total = 0;
  $member_cost_total = 0;

  $even_odd = 'even';
  print '<pre>';
  print_r($items);
  print '</pre>';
  /**
  foreach ($items as $item) {

    $item_node = node_load($item['cr_placeholder_nid']);
    //$type            = cr_load_content_type_settings($item->type);
    //$type            = cr_load_item_settings($item,$item->type);
    $fee_hours       = $hours - ($item_node->cr_fee_free_hours);
    $comcral_cost = $item_node->cr_rate_per_hour * $hours;
    $member_cost     = ($fee_hours > 0) ? ($item_node->cr_rate_per_hour * $discount) * $fee_hours : 0;
    $day_rate     = ($item_node->cr_rate_per_hour * 24);
    
    $comcral_cost_total += $comcral_cost;
    $member_cost_total += $member_cost;

    if ($item['item_title']) {
      $ttitle = htmlspecialchars($item['item_title']);
    }
    else {
      $ttitle = '<b>SPECIFIC ITEM NOT SELECTED FROM BUCKET</b>';
    }
    ?>
            <tr class="<?php print $even_odd; ?>">
              <td>
                <div><?php print $ttitle; ?>(<?php print money_format('%(#10n', $day_rate); ?> per day)</div>
                <?php
    if (count($item_node->taxonomy) > 0) {

      ?>
                  <ul class="accessories">
                  <?php
      foreach ($item_node->taxonomy as $accessory) {

        ?>
                    <li><?php print $accessory->name; ?></li>
                    <?php
      }
      // foreach

      ?>
                  </ul>
                  <?php
    }
    // if

    ?>
              </td>
              <?php //print_r($item_node);?>
              <td><?php echo money_format('%(#10n', $comcral_cost); ?></td>
              <td><?php echo money_format('%(#10n', $member_cost); ?></td>
            </tr>
            <?php
    $even_odd = ($even_odd == 'even') ? 'odd' : 'even';
  }
  // foreach
  **/
  ?>
          </tbody>
          <tfoot>
            <tr class="<?php echo $even_odd; ?>">
              <th>Total</th>
              <td><?php //echo money_format('%(#10n', $comcral_cost_total) ?></td>
              <td><?php //echo money_format('%(#10n', $member_cost_total) ?></td>
            </tr>
          <tfoot>
        </table>
        <div id="boilerplate"><?php if (module_exists('token')) { echo token_replace(variable_get('cr_contract_boilerplate', ''), 'node', $node); }
  else  { echo variable_get('cr_contract_boilerplate',''); } ?></div>
        <div id="footer"><?php if (module_exists('token')) { echo token_replace(variable_get('cr_contract_footer', ''), 'node', $node); }
  else  { echo variable_get('cr_contract_footer',''); } ?></div>
      </div>
    </body>
