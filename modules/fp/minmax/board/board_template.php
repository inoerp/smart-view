<div id="content_left1">
<!-- <div id="block_for_system_transaction" class="block content_left urgent_cards block_100">
  <div class="headerBgColor title system_trnx"> <span  class="hideDiv"> </span>System Transaction </div>
  <div class="content system_trnx_cotent">
   <div class="system_trnx_block hideDiv_element">
    <span class="info"><label>Transaction Type</label>
     <?php
     $f = new inoform();
     $trnx_a = ['SUB_INV' => 'Subinventory Transfer', 'PUR_REQ' => 'Purchase Requisition'];
     echo $f->select_field_from_array('transaction_type', $trnx_a, '', 'transaction_type', 'medium');
     ?>
    </span>
    <span class="button" id="save_system_trnx">Save</span>
    <ul id="mmb_transaction_block"></ul>
   </div> 
  </div>
 </div>
 <div id="block_for_urgent_card" class="block content_left urgent_cards block_99">
  <div class="headerBgColor title urgent_cards_header"> <span  class="hideDiv"> </span>Urgent Cards </div>
  <div class="content urgent_card">
   <div class="urgent_card_block hideDiv_element">
    <span class="info">Drag the urgent cards to here<br>Double click to remove it</span>
    <span class="button" id="save_urgent_card">Save</span>
    <?php
    $existing_data = fp_urgent_card::find_current_cardList();
    if ($existing_data) {
     echo '<ul id="urgent_card_block">';
     echo $existing_data;
     echo '</ul>';
    } else {
     echo '<ul id="urgent_card_block">';
     echo '</ul>';
    }
    ?>
   </div> 
  </div>
 </div>-->
</div>
<div id="minmax_header_divId">
 <div id="form_top">
 </div>
 <!--    START OF FORM HEADER-->
 <div class="error"></div><div id="loading"></div>
 <div class="show_loading_small"></div>
 <?php echo (!empty($show_message)) ? $show_message : ""; ?>  
 <!--    End of place for showing error messages-->
 <div id ="form_header"><span class="heading">Min Max Board </span>
  <ul id="form_top_ul" class="inRow asperWidth headerBgColor">
   <li><lable>Inventory Org </lable>
   <?php echo $f->select_field_from_object('ORGANIZATION_ID', org::find_all_inventory(), 'ORGANIZATION_ID', 'ORGANIZATION_NAME', $fp_mmb->organization_id, 'ORGANIZATION_ID', 'medium', 1); ?>
   </li>
   <li><lable>Sub Inventory </lable>
   <?php echo $f->select_field_from_object('SUBINVENTORY_CODE', subinventory::find_all_subinventory_by_orgId($fp_mmb->organization_id), 'SECONDARY_INVENTORY_NAME', 'SECONDARY_INVENTORY_NAME', $fp_mmb->SUBINVENTORY_CODE, 'SUBINVENTORY_CODE', 'medium'); ?>
   </li>
   <li><lable>Planner </lable>
   <?php echo $f->select_field_from_object('PLANNER_CODE', fp_mrp_header::find_all_planner_code(), 'PLANNER_CODE', 'DESCRIPTION', $fp_mmb->PLANNER_CODE, 'PLANNER_CODE', 'medium'); ?>
   </li>
   <li><lable>Type </lable>
   <?php echo $f->select_field_from_array('PLANNING_MAKE_BUY_CODE', array('1' => 'Make', '2' => 'Buy'), $fp_mmb->PLANNING_MAKE_BUY_CODE, 'PLANNING_MAKE_BUY_CODE', 'small'); ?>
   </li>
   <li><lable>Source Sub </lable>
   <?php echo $f->select_field_from_object('SOURCE_SUBINVENTORY', subinventory::find_all_subinventory_by_orgId($fp_mmb->organization_id), 'SECONDARY_INVENTORY_NAME', 'SECONDARY_INVENTORY_NAME', $fp_mmb->SOURCE_SUBINVENTORY, 'SOURCE_SUBINVENTORY', 'medium SUBINVENTORY_CODE'); ?>
   </li>
   <li>              <a name="show" href="form.php?class_name=fp_minmax_board_v" class="show onhand_id">	
     <img src="<?php echo HOME_URL; ?>themes/images/refresh.png" class="clickable"></a> </li>
  </ul>
  <div id="min_max_boardId">
   <ul>
    <?php
//         pa($mm_details[0]);
    if ($mm_details) {
     $mm_details_ai = new ArrayIterator($mm_details);
     $mm_details_ai->seek($position);
//          pa($mm_details_ai);
     while ($mm_details_ai->valid()) {
      $recod = $mm_details_ai->current();
      $onhand_min_delta = round($recod->QUANTITY - $recod->MIN_MINMAX_QUANTITY);
      $onhand_max_delta = round($recod->MAX_MINMAX_QUANTITY - $recod->QUANTITY);
      if ($recod->MIN_MINMAX_QUANTITY) {
       $height_p = round(($recod->QUANTITY / $recod->MIN_MINMAX_QUANTITY) * 100);
       $height_p = $height_p >= 100 ? 100 : $height_p;
      } else {
       $height_p = 0;
      }
      if (empty($recod->OPEN_PO_QTY)) {
       $bgcolor = ($onhand_min_delta >= 0 ) ? 'bgGreen' : 'bgRed';
      } else if ($onhand_min_delta >= 0) {
       $bgcolor = 'bgGreen';
      } else if ($recod->OPEN_PO_QTY >= 0) {
       $bgcolor = ($onhand_min_delta + $recod->OPEN_PO_QTY >= 0 ) ? 'bgPurple' : 'bgRed';
      } else {
       $bgcolor = ($onhand_min_delta >= 0 ) ? 'bgGreen' : 'bgRed';
      }

      if ($recod->TOTAL_DELTA < 0) {
       if (!empty($recod->FLM)) {
        $order_quantity = roundUpToNextMultiplier(abs($recod->TOTAL_DELTA), $recod->FLM);
       } else {
        $order_quantity = $recod->TOTAL_DELTA;
       }
      } else {
       $order_quantity = 0;
      }


      echo "<li class='{$bgcolor} parent draggable_element'><ul class='child'  title='{$height_p} %' data-height='{$height_p}'>";
      echo '<li class="item_number">' . $recod->ITEM_NUMBER;
      echo ' : ' . $recod->PLANNER_CODE . '</li>';
      echo '<li>Min : ' . $recod->MIN_MINMAX_QUANTITY . ' Max : ' . $recod->MAX_MINMAX_QUANTITY . ' </li>';
      echo '<li>Min Delta :' . $onhand_min_delta . '</li><li>Max Delta :' . $onhand_max_delta . '</li>';
      echo '<li>Total Supp Delta :' . $recod->TOTAL_DELTA . '</li>';
      echo '<li>Onhand :' . $recod->QUANTITY . '</li>';
      echo '<li>Make/Buy :' . $recod->MAKE_BUY . '</li>';
      if (!empty($recod->SUBINVENTORY_CODE)) {
       echo '<li>Location :' . $recod->SUBINVENTORY_CODE . '</li>';
      }
      echo '<li>Source Type :' . $recod->SOURCE_TYPE . '</li>';
      echo '<li>Source :' . $recod->SOURCE . '</li>';
      echo '<li>Open PO :' . $recod->OPEN_PO_QTY . '</li>';
      echo '<li class="imp">Order Qty: ' . $order_quantity . '</li>';
      echo '</ul></li>';
      $mm_details_ai->next();
      if ($mm_details_ai->key() == $position + $per_page) {
       break;
      }
     }
    }
    ?>
   </ul>
  </div>
 </div>
 <?php echo $pagination->show_pagination(); ?>
 <!--END OF FORM HEADER-->

</div>