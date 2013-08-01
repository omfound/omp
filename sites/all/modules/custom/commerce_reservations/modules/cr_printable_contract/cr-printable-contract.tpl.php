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
        Order Date: <?php print date("F j, Y, g:i a", $order->created) . '<br />'; ?>
        Name: <?php print $username ?><br />
        Email: <?php print $email ?><br />
        Phone: <?php print $phone ?><br />
        
        </div>
        <table id="cost">
          <thead>
            <tr>
              <th>Item</th>
              <th>Checkout Date</th>
              <th>Return Date</th>
              <th>Cost</th>
            </tr>
          </thead>
          <tbody>
  <?php
  $even_odd = 'even';
  foreach ($items as $item) {
    $cost = money_format('%(#10n', $item->commerce_total['und'][0]['amount']/100);
    $rate = money_format('%(#10n', ($item->product->commerce_price['und'][0]['amount']/100)).' / '.$item->product->field_charge_by_the_['und'][0]['value'];
    $title = $item->product->title;
    if (!empty($item->clean_accessories)) {
      $accessories = '<br /><span style="font-size: .7em;">'.$item->clean_accessories.'</span>';
    }
  ?>
  <tr class="<?php print $even_odd; ?>">
    <td><div><?php print $title.$rate.$accessories; ?></div></td>
    <td><?php print date("F j, Y, g:i a", strtotime($item->field_reservation_dates['und'][0]['value'].' UTC')); ?></td>
    <td><?php print date("F j, Y, g:i a", strtotime($item->field_reservation_dates['und'][0]['value2'].' UTC')); ?></td>
    <td><?php echo $cost; ?></td>
  </tr>
  <?php
    $even_odd = ($even_odd == 'even') ? 'odd' : 'even';
  }
  ?>
  </tbody>
  <tfoot>
    <tr class="<?php echo $even_odd; ?>">
      <th>Total</th>
      <td><td>
      <td><?php echo money_format('%(#10n', ($order->commerce_order_total['und'][0]['amount']/100)) ?></td>
    </tr>
  <tfoot>
</table>
<div id="boilerplate">
  <?php echo variable_get('cr_contract_boilerplate',''); ?> 
</div>

<div id="footer">
  <?php echo variable_get('cr_contract_footer',''); ?>
</div>
</div>
</body>
