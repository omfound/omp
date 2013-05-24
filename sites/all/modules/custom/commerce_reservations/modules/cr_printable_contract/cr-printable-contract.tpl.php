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
              <th>Cost</th>
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
  foreach ($items as $item) {

    $cost = money_format('%(#10n', $item->commerce_total['und'][0]['amount']/100);
    $rate = money_format('%(#10n', ($item->product->commerce_price['und'][0]['amount']/100)).' / '.$item->product->field_charge_by_the_['und'][0]['value'];
    $title = $item->product->title;

    ?>
            <tr class="<?php print $even_odd; ?>">
              <td>
                <div><?php print $title.$rate; ?> </div>
                  <?php
    }
    // if

    ?>
              </td>
              <?php //print_r($item_node);?>
              <td><?php echo $cost; ?></td>
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
              <td>99<?php //echo money_format('%(#10n', $comcral_cost_total) ?></td>
            </tr>
          <tfoot>
        </table>
        <div id="boilerplate"><?php if (module_exists('token')) { echo token_replace(variable_get('cr_contract_boilerplate', ''), 'node', $node); }
  else  { echo variable_get('cr_contract_boilerplate',''); } ?></div>
        <div id="footer"><?php if (module_exists('token')) { echo token_replace(variable_get('cr_contract_footer', ''), 'node', $node); }
  else  { echo variable_get('cr_contract_footer',''); } ?></div>
      </div>
    </body>
