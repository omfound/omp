<?php

function reservations_reports_preprocess_reservations_reports_usage_report(&$variables){
	$sorted_products = array();
	$count = 1;
	foreach ($variables['products'] as $product_id => $product_title){
			$sorted_products[$product_title]['product_ids'][] = $product_id;
	}
	$variables['products'] = $sorted_products;
	foreach($variables['line_items'] as $reservation){
	  $product_id = $reservation->commerce_product['und'][0]['product_id'];
	  foreach($variables['products'] as $product_title => $product_stats){
	    if (in_array($product_id, $product_stats['product_ids'])){
		    $variables['products'][$product_title]['total_reservations'] = $variables['products'][$product_title]['total_reservations'] + 1;
		    $startTime = strtotime($reservation->field_reservation_dates['und'][0]['value']);
	      $endTime = strtotime($reservation->field_reservation_dates['und'][0]['value2']);
	      $hours = floor(($endTime - $startTime)/3600);
	     	$variables['products'][$product_title]['total_hours'] = $variables['products'][$product_title]['total_hours'] + $hours;
	     	$total_amount = $reservation->commerce_total['und'][0]['amount'];
	    	$variables['products'][$product_title]['total_revenue']['amount'] = $variables['products'][$product_title]['total_revenue']['amount'] + $total_amount;
	    	$variables['products'][$product_title]['total_revenue']['formatted_amount'] = commerce_currency_format($variables['products'][$product_title]['total_revenue']['amount'], $reservation->commerce_total['und'][0]['currency_code']);
		    if ($reservation->field_commercial_reservation['und'][0]['value'] == 1){
			    $variables['products'][$product_title]['commercial_reservations'] = $variables['products'][$product_title]['commercial_reservations'] + 1;
			    $startTime = strtotime($reservation->field_reservation_dates['und'][0]['value']);
		      $endTime = strtotime($reservation->field_reservation_dates['und'][0]['value2']);
		      $hours = floor(($endTime - $startTime)/3600);
		      $variables['products'][$product_title]['commercial_hours'] = $variables['products'][$product_title]['commercial_hours'] + $hours;
		      $total_amount = $reservation->commerce_total['und'][0]['amount'];
	    	  $variables['products'][$product_title]['commercial_revenue']['amount'] = $variables['products'][$product_title]['commercial_revenue']['amount'] + $total_amount;
	      	$variables['products'][$product_title]['commercial_revenue']['formatted_amount'] = commerce_currency_format($variables['products'][$product_title]['commercial_revenue']['amount'], $reservation->commerce_total['und'][0]['currency_code']);
		    } else{
			    $variables['products'][$product_title]['member_reservations'] = $variables['products'][$product_title]['member_reservations'] + 1;
			    $startTime = strtotime($reservation->field_reservation_dates['und'][0]['value']);
		      $endTime = strtotime($reservation->field_reservation_dates['und'][0]['value2']);
		      $hours = floor(($endTime - $startTime)/3600);
		      $variables['products'][$product_title]['member_hours'] = $variables['products'][$product_title]['member_hours'] + $hours;
		      $total_amount = $reservation->commerce_total['und'][0]['amount'];
	    	  $variables['products'][$product_title]['member_revenue']['amount'] = $variables['products'][$product_title]['member_revenue']['amount'] + $total_amount;
	      	$variables['products'][$product_title]['member_revenue']['formatted_amount'] = commerce_currency_format($variables['products'][$product_title]['member_revenue']['amount'], $reservation->commerce_total['und'][0]['currency_code']);
		    }
	    }
	  }
	}
}