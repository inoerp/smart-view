<?php
$f = new inoform();
$bc = new ino_barcode();
?>

<div id ="form_header" ><span class="heading">Barcoded Min Max Board </span>
 <div class="tabContainer">
  <ul class="inRow asperWidth headerBgColor">
   <li><lable>Inventory Org </lable>
   <?php echo $f->select_field_from_object('ORGANIZATION_ID', org::find_all_inventory(), 'ORGANIZATION_ID', 'ORGANIZATION_NAME', $fp_mmb->organization_id, 'ORGANIZATION_ID', 'medium', 1); ?>
   </li>
   <li><lable>Sub Inventory </lable>
   <?php echo $f->select_field_from_object('SUBINVENTORY_CODE', subinventory::find_all_subinventory_by_orgId($fp_mmb->organization_id), 'SECONDARY_INVENTORY_NAME', 'SECONDARY_INVENTORY_NAME', $fp_mmb->SUBINVENTORY_CODE, 'SUBINVENTORY_CODE', 'medium'); ?>
   </li>
   <li><lable>Planner </lable>
   <?php echo $f->select_field_from_object('PLANNER_CODE', fp_mrp_header::find_all_planner_code(), 'PLANNER_CODE', 'DESCRIPTION', $fp_mmb->PLANNER_CODE, 'PLANNER_CODE', 'medium'); ?>
   </li>
   <li><lable>Product Category</lable>
   <?php echo $f->select_field_from_array('DESCRIPTION', fp_minmax_barcode_board_v::$item_desc, $DESCRIPTION_val, 'DESCRIPTION'); ?>
   </li>
   <li><lable>Type </lable>
   <?php echo $f->select_field_from_array('PLANNING_MAKE_BUY_CODE', array('1' => 'Make', '2' => 'Buy'), $fp_mmb->PLANNING_MAKE_BUY_CODE, 'PLANNING_MAKE_BUY_CODE', 'small'); ?>
   </li>
   <li><lable>Source Sub </lable>
   <?php echo $f->select_field_from_object('SOURCE_SUBINVENTORY', subinventory::find_all_subinventory_by_orgId($fp_mmb->organization_id), 'SECONDARY_INVENTORY_NAME', 'SECONDARY_INVENTORY_NAME', $fp_mmb->SOURCE_SUBINVENTORY, 'SOURCE_SUBINVENTORY', 'medium SUBINVENTORY_CODE'); ?>
   </li>
   <li>              <a name="show3" href="form.php?class_name=fp_minmax_barcode_board_v" class="show3 onhand_id">	
     <i class="fa fa-refresh"></i></a> </li>
  </ul>
 </div>
 <div id="barcode_min_max_boardId">

  <?php
  if ($mm_details) {
   $download_data = [];
   $dbOraObject = new dbOraObject();
   $mm_details_ai = new ArrayIterator($mm_details);
   $mm_details_ai->seek($position);
   while ($mm_details_ai->valid()) {

    $recod = $mm_details_ai->current();

    if ($recod->SOURCE_TYPE == 'SUB' && !empty($recod->OPEN_PO_QTY)) {
     $recod->TOTAL_DELTA = $recod->TOTAL_DELTA - $recod->OPEN_PO_QTY;
    }
    $recod->TOTAL_DELTA_BY_ACTDEMAND = null;
    $recod->TOTAL_DELTA_A = $recod->TOTAL_DELTA;
    if (in_array($recod->PLANNER_CODE, array('OBIS', 'OBIS-WO', 'OBIS-WOL'))) {
     $sql = " SELECT mos.organization_id as organization_id,
       mos.inventory_item_id AS inventory_item_id,
       CEIL(abs(SUM(mos.quantity_rate))) AS actual_demand
  FROM apps.MRP_ORDERS_SC_V mos
  WHERE mos.organization_id = '{$fp_mmb->organization_id}'
  AND mos.creation_date     > (sysdate-5)
  AND mos.creation_date     < sysdate
     AND mos.new_due_date    < NEXT_DAY(sysdate, 'MONDAY') + 17
  AND mos.new_due_date    > sysdate
  AND mos.order_type IN ('3', '1' ,'6' ,'7')
  AND mos.inventory_item_id = '{$recod->INVENTORY_ITEM_ID}'
  GROUP BY mos.organization_id,    mos.inventory_item_id";

     $result_x1 = $dbOraObject->find_by_sql($sql);
     if ($result_x1) {
      $recod->ACTUAL_DEMAND = $result_x1[0]->ACTUAL_DEMAND;
      if ($recod->ACTUAL_DEMAND > $recod->MAX_MINMAX_QUANTITY) {
       $recod->TOTAL_DELTA_BY_ACTDEMAND =  $recod->OPEN_PO_QTY - $recod->ACTUAL_DEMAND;
       $recod->TOTAL_DELTA_A = $recod->TOTAL_DELTA_BY_ACTDEMAND;
      }
     } else {
      $recod->ACTUAL_DEMAND = null;
     }
    } else {
     $recod->ACTUAL_DEMAND = null;
    }


//           pa($recod);
    $onhand_min_delta = round($recod->MIN_DELTA);
    $onhand_max_delta = round($recod->MAX_DELTA);
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
    } else if ($recod->OPEN_PO_QTY >= 0 && ($recod->SOURCE_TYPE != 'SUB')) {
     $bgcolor = ($onhand_min_delta + $recod->OPEN_PO_QTY >= 0 ) ? 'bgPurple' : 'bgRed';
    } else {
     $bgcolor = ($onhand_min_delta >= 0 ) ? 'bgGreen' : 'bgRed';
    }

    if ($recod->TOTAL_DELTA_A < 0) {
     if (!empty($recod->FLM)) {
      $order_quantity = abs(roundUpToNextMultiplier(abs($recod->TOTAL_DELTA_A), $recod->FLM));
     } else {
      $order_quantity = abs($recod->TOTAL_DELTA_A);
     }
    } else {
     $order_quantity = 0;
    }

    if ($recod->LOCATOR_ID) {
     $desti_locator = findLocator_fromLocatorId_ora($recod->LOCATOR_ID);
    } else {
     $desti_locator = null;
    }
    $source_locator = null;
    if (!empty($recod->SUBINVENTORY_CODE)) {
     $source_locator = findDefault_RecevingLocator_ByItemSubInventory($recod->ORGANIZATION_ID, $recod->SOURCE, $recod->INVENTORY_ITEM_ID);
    }
    if (!empty($recod->SOURCE_LOCATOR_ID) & empty($source_locator)) {
     $source_locator = findLocator_fromLocatorId_ora($recod->SOURCE_LOCATOR_ID);
     ;
    }
    $recod->SOURCE_LOCATOR = $source_locator;
    echo "<div class='panel panel-default {$bgcolor} parent draggable_element medium'>";
    echo '<div class="panel-heading">
     <h3 class="panel-title">' . $recod->DESCRIPTION . '</h3>
      <div class="progress">
  <div class="progress-bar progress-bar-success progress-bar-striped active" role="progressbar" 
    aria-valuenow="' . $height_p . '" aria-valuemin="0" aria-valuemax="100" style="width: ' . $height_p . '%" title="' . $height_p . '">
    <span class="sr-only">' . $height_p . '% Available</span>
  </div>
</div>
    </div>';
    echo '<div class="panel-body">';
    echo "<ul class='child'  title='{$height_p} %' data-height='{$height_p}'>";
    echo '<li class="item_number">' . $recod->ITEM_NUMBER;
    echo ' : ' . $recod->PLANNER_CODE . '</li>';
    echo '<li>';
    if (!empty($recod->ITEM_NUMBER)) {
     $bc = new ino_barcode();
     $bc->setProperty('_text', $recod->ITEM_NUMBER);
     $bc->draw_barcode();
     unset($bc);
    }
    echo '</li>';
    echo '<li>Min : ' . $recod->MIN_MINMAX_QUANTITY . ' Max : ' . $recod->MAX_MINMAX_QUANTITY . ' </li>';
    echo '<li>Actual Demand(Net) : ' . $recod->ACTUAL_DEMAND . ' </li>';
    echo '<li>Min Delta :' . $onhand_min_delta . '</li><li>Max Delta :' . $onhand_max_delta . '</li>';
    echo '<li>Total Supp Delta :' . $recod->TOTAL_DELTA . '</li>';
    echo '<li>Actual Demand Delta :' . $recod->TOTAL_DELTA_BY_ACTDEMAND . '</li>';
    echo '<li>Onhand :' . $recod->QUANTITY . '</li>';
    echo '<li>Make/Buy :' . $recod->MAKE_BUY . '</li>';
    if (!empty($recod->SUBINVENTORY_CODE)) {
     echo '<li>Dest. SubInv :' . $recod->SUBINVENTORY_CODE . '</li>';
     echo '<li>';
     if (!empty($recod->SUBINVENTORY_CODE)) {
      $bc = new ino_barcode();
      $bc->setProperty('_text', $recod->SUBINVENTORY_CODE);
      $bc->draw_barcode();
      unset($bc);
     }
     echo '</li>';
     echo '<br>';
     $recod->DSTI_LOCATOR = $desti_locator;
     echo '<li>Dest. Loc :' . $desti_locator . '</li>';
     echo '<li>';
     if (!empty($desti_locator)) {
      $bc = new ino_barcode();
      $bc->setProperty('_text', $desti_locator);
      $bc->draw_barcode();
      unset($bc);
     }
     echo '</li>';
    }
    echo '<li>Source Type :' . $recod->SOURCE_TYPE . '</li>';
    echo '<li>OPO : ' . $recod->OPEN_PO_QTY . ' | SOH : ' . $recod->SOURCE_ONHAND . '</li>';
    echo '<li>Source :' . $recod->SOURCE . '</li>';
    echo '<li>';
    if (!empty($recod->SOURCE)) {
     $bc = new ino_barcode();
     $bc->setProperty('_text', $recod->SOURCE);
     $bc->draw_barcode();
     unset($bc);
    }
    echo '</li>';
    echo '<li>Source2 :' . $source_locator . '</li>';
    echo '<li>';
    if (!empty($source_locator)) {
     $bc = new ino_barcode();
     $bc->setProperty('_text', $source_locator);
     $bc->draw_barcode();
     unset($bc);
    }
    echo '</li>';
    echo '<li class="imp">Order Qty: ' . $order_quantity . '</li>';
    echo '<li>';
    if (!empty($order_quantity)) {
     $bc = new ino_barcode();
     $bc->setProperty('_text', $order_quantity);
     $bc->draw_barcode();
     unset($bc);
    }
    echo '</li>';
    echo '</ul></div>'; //end of panel body
    echo '</div>'; //end of panel
    $mm_details_ai->next();
    if ($mm_details_ai->key() == $position + $per_page) {
     break;
    }
    $recod->ORDER_QUANTITY = $order_quantity;
    array_push($download_data, $recod);
   }
  }
  ?>
  <div id="download_button"><?php echo!empty($download_data) ? show_download_button_simple($download_data) : '' ?></div>
 </div>
</div>
<?php echo $pagination->show_pagination(); ?>