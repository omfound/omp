<h1>Usage Report</h1>
<table class="quarterly-report">
  <th>Resource</th>
  <th>Resource Quantity</th>
  <th>Number of Member Rentals</th>
  <th>Hours of Member Rental Usage</th>
  <th>Number of Commercial Rentals</th>
  <th>Hours of Commercial Rental Usage</th>
  <th>Total Reservations</th>
  <th>Total Hours</th>
  <th>Member Revenue</th>
  <th>Commercial Revenue</th>
  <th>Total Revenue</th>
	<?php foreach($products as $product_title => $product_stats):?>
    <tr>
  	  <td class="first odd"><?php print ($product_title);?></td>
  	  <td class="even"><?php print sizeof($product_stats['product_ids']);?></td>
  	  <?php if ($product_stats['member_reservations']):?>
  	    <td class="odd"><?php print $product_stats['member_reservations'];?></td>
  	  <?php else:?>
  	    <td class="odd">0</td>
  	  <?php endif;?>
  	  <?php if ($product_stats['member_hours']):?>
  	    <td class="even"><?php print $product_stats['member_hours'];?></td>
  	  <?php else:?>
  	    <td class="even">0</td>
  	  <?php endif;?>
  	  <?php if ($product_stats['commercial_reservations']):?>
  	    <td class="odd"><?php print $product_stats['commercial_reservations'];?></td>
  	  <?php else:?>
  	    <td class="odd">0</td>
  	  <?php endif;?>
  	  <?php if ($product_stats['commercial_hours']):?>
  	    <td class="even"><?php print $product_stats['commercial_hours'];?></td>
  	  <?php else:?>
  	    <td class="even">0</td>
  	  <?php endif;?>
  	  <?php if ($product_stats['total_reservations']):?>
  	    <td class="odd"><?php print $product_stats['total_reservations'];?></td>
  	  <?php else:?>
  	    <td class="odd">0</td>
  	  <?php endif;?>
  	  <?php if ($product_stats['total_hours']):?>
   	    <td class="even"><?php print $product_stats['total_hours'];?></td>
   	  <?php else:?>
  	    <td class="even">0</td>
  	  <?php endif;?>
  	  <?php if ($product_stats['member_revenue']):?> 
   	    <td class="odd"><?php print $product_stats['member_revenue']['formatted_amount'];?></td>
   	  <?php else:?>
  	    <td class="odd">$0.00</td>
  	  <?php endif;?>
  	  <?php if ($product_stats['commercial_revenue']):?> 
   	    <td class="even"><?php print $product_stats['commercial_revenue']['formatted_amount'];?></td>
   	  <?php else:?>
  	    <td class="even">$0.00</td>
  	  <?php endif;?>
  	  <?php if ($product_stats['total_revenue']):?> 
   	    <td class="last odd"><?php print $product_stats['total_revenue']['formatted_amount'];?></td>
   	  <?php else:?>
  	    <td class="last odd">$0.00</td>
  	  <?php endif;?>
  <?php endforeach;?>
    </tr>
</table>