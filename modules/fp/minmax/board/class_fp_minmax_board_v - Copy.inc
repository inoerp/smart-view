<?php

class copy_fp_minmax_board_v extends dbOraObject {

 public static $table_name = "fp_minmax_board_v";
 public static $primary_column = "onhand_id";
 public $field_a = [
  'onhand_id',
  'item_number',
  'item_description',
  'org_name',
  'subinventory',
  'locator',
  'uom_id',
  'onhand',
  'minmax_min_quantity',
  'minmax_max_quantity',
  'item_id_m',
  'revision_name',
  'org_id',
  'subinventory_id',
  'locator_id',
  'lot_id',
  'serial_id',
  'reservable_onhand',
  'transactable_onhand',
  'lot_status',
  'serial_status',
  'secondary_uom_id',
  'onhand_status',
  'ef_id',
  'created_by',
  'creation_date',
  'last_update_by',
  'last_update_date',
 ];
 public $initial_search = [
  'onhand_id',
  'item_number',
  'item_description',
  'org_name',
  'subinventory',
  'locator',
  'uom_id',
  'onhand',
  'item_id_m',
  'org_id',
  'subinventory_id',
  'locator_id',
 ];
 public $dateField = [
 ];
 public $pageTitle = " Onhand - Find Inventory Onhand "; //page Title
 public $search = [
  '_view_path' => 'form.php?class_name=inv_onhand_serial',
  '_show_view_path' => 1,
  '_view_action_meassge' => 'Serial Numbers',
  '_extra_path' => array('form.php?class_name=inv_lot_onhand&mode=2' => 'Lot Numbers')
 ];
 public $search_groupBy = [
  'item_number' => 'Item Number'
//		 'locator' => 'Locator',
//		 'subinventory' => 'Sub Inventory',
//		 'org_id' => 'Inventory Org',
 ];
 public $search_groupBy_sum = 'onhand';
 public $ra_onhand_by_subinventoryType_parameters = [
  'Result Limit' => 'ra_result_limit',
  'Chart Type' => 'ra_chart_type',
 ];
 public $ra_onhand_by_subinventoryType_settings = [
  '_chart_name' => 'Onhand Quantity By Subinventory Type',
  '_x_axis_text' => 'Onhand Quantity',
 ];
 public $ra_onhand_value_by_subinventoryType_settings = [
  '_chart_name' => 'Onhand Value By Subinventory Type',
  '_x_axis_text' => 'Onhand Value',
 ];
 public $ra_onhand_by_productLine_settings = [
  '_chart_name' => 'Onhand Quantity By Product Line',
  '_x_axis_text' => 'Onhand Quantity',
 ];
 public $ra_onhand_value_by_productLine_settings = [
  '_chart_name' => 'Onhand Value By Product Line',
  '_x_axis_text' => 'Onhand Value',
 ];
 public $ra_onhand_by_productLine_subinventoryType_settings = [
  '_chart_name' => 'Onhand By Product Line Subinventory Type',
  '_chart_width' => '750',
  '_chart_height' => '450',
  '_x_axis_text' => 'Onhand Quantity',
  '_chart_type' => 'clustered_column',
  '_gap_between_xaxis_text' => '50',
  '_legend' => ''
 ];
 public $ra_report_set_onhand_by_subinventoryType_settings = [
  '_chart_name' => 'Onhand By Subinventory Type',
  '_chart_width' => '350',
  '_chart_height' => '350',
  '_x_axis_text' => 'Sub Invnetory Type',
  '_chart_type' => array('horizonatl_bar', 'vertical_column', 'pie'),
  '_legend' => ''
 ];
 public $ra_report_set_onhand_by_subinventoryType = [
  'ra_onhand_by_subinventoryType',
  'ra_onhand_value_by_subinventoryType',
  'ra_onhand_by_productLine',
  'ra_onhand_value_by_productLine',
  'ra_onhand_by_productLine_subinventoryType'
 ];
 public $onhand_id;
 public $item_number;
 public $item_description;
 public $product_line;
 public $org_name;
 public $subinventory;
 public $subinventory_type;
 public $locator;
 public $uom_id;
 public $onhand;
 public $minmax_min_quantity;
 public $minmax_max_quantity;
 public $open_po;
 public $item_id_m;
 public $revision_name;
 public $org_id;
 public $subinventory_id;
 public $locator_id;
 public $lot_id;
 public $serial_id;
 public $reservable_onhand;
 public $transactable_onhand;
 public $lot_status;
 public $serial_status;
 public $secondary_uom_id;
 public $onhand_status;
 public $ef_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;

 public static function xx_find_by_orgId_subInventoryId($org_id, $subinventory_id = '') {
  if (empty($org_id)) {
   return false;
  }

  $sql = " SELECT onhand.onhand_id, 
item.item_number, item.item_description, item.product_line,
org.org, subinventory.subinventory, locator.locator,
onhand.uom_id,onhand.onhand, item.minmax_min_quantity, item.minmax_max_quantity, 
(onhand.onhand - item.minmax_min_quantity) as onhand_delta, po_summary.open_quantity as open_po,
cic.standard_cost, (onhand.onhand * cic.standard_cost) as onhand_value,
onhand.item_id_m, onhand.revision_name, onhand.org_id, onhand.subinventory_id, subinventory.type,
onhand.locator_id, onhand.lot_id, onhand.serial_id, onhand.reservable_onhand, 
onhand.transactable_onhand, onhand.lot_status, onhand.serial_status,  
onhand.secondary_uom_id, onhand.onhand_status, onhand.ef_id, onhand.created_by, 
onhand.creation_date, onhand.last_update_by, onhand.last_update_date

FROM onhand  
LEFT JOIN org ON onhand.org_id = org.org_id
LEFT JOIN subinventory ON onhand.subinventory_id = subinventory.subinventory_id
LEFT JOIN locator ON onhand.locator_id = locator.locator_id
LEFT JOIN 
 ( 
 SELECT SUM(open_quantity) as open_quantity, receving_org_id, item_id_m
 FROM po_all_v pav 
  WHERE receving_org_id IS NOT NULL
 AND open_quantity > 0
 GROUP BY  item_id_m, receving_org_id
 ) po_summary 
ON onhand.item_id_m = po_summary.item_id_m AND po_summary.receving_org_id = onhand.org_id 
LEFT JOIN cst_item_cost_v cic ON cic.item_id_m = onhand.item_id_m AND cic.bom_cost_type='FROZEN'
AND cic.org_id = onhand.org_id,
item

WHERE onhand.item_id_m = item.item_id_m 
AND item.org_id = onhand.org_id
AND item.minmax_min_quantity IS NOT NULL 
AND onhand.org_id = '{$org_id}'";
  if (!empty($subinventory_id)) {
   $sql .= " AND onhand.subinventory_id = '{$subinventory_id}' ";
  }
  $sql .="  ORDER BY onhand_delta ASC ";

  $result = self::find_by_sql($sql);

  return !empty($result) ? $result : false;
 }

 public static function find_by_orgId_subInventoryId($organization_id, $PLANNER_CODE = '', $subinventory_code = '', $PLANNING_MAKE_BUY_CODE = '') {
  global $dbOra;

  if (empty($subinventory_code)) {
   $sql = "
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.planner_code, msi.item_type,msi.MIN_MINMAX_QUANTITY, msi.MAX_MINMAX_QUANTITY,
           msi.organization_id, onhand.Quantity, msi.SOURCE_TYPE, ( NVL(onhand.Quantity,0) - msi.MIN_MINMAX_QUANTITY ) as Onhand_Delta,
           DECODE(msi.PLANNING_MAKE_BUY_CODE, '1', 'Make', '2', 'Buy') as Make_Buy, msi.BUYER_ID, 'Org' as subinventory_code,
           DECODE(msi.SOURCE_TYPE, '1', 'INV', '2','SUPP', '3', 'SUB') as Source_Type,
           'NA' as Source
           from 
           apps.mtl_system_items_b msi,
           (
           SELECT  
           moq.inventory_item_id, moq.organization_id, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL moq
           GROUP BY moq.inventory_item_id, moq.organization_id
           ) onhand
           where msi.organization_id = '{$organization_id}'
           AND msi.INVENTORY_PLANNING_CODE = 2
           and onhand.organization_id(+) = msi.organization_id
           and onhand.inventory_item_id(+) = msi.inventory_item_id
           and msi.MIN_MINMAX_QUANTITY IS NOT NULL  ";
   if (!empty($PLANNER_CODE)) {
    $sql .= "AND msi.planner_code='{$PLANNER_CODE}' ";
   }

   if (!empty($PLANNING_MAKE_BUY_CODE)) {
    $sql .= "AND msi.PLANNING_MAKE_BUY_CODE ='{$PLANNING_MAKE_BUY_CODE}' ";
   }

   $sql.="  UNION
           
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.planner_code, msi.item_type,msi.MIN_MINMAX_QUANTITY, msi.MAX_MINMAX_QUANTITY,
           msi.organization_id, onhand.Quantity, msi.SOURCE_TYPE, ( NVL(onhand.Quantity,0) - msi.MIN_MINMAX_QUANTITY ) as Onhand_Delta,
           DECODE(msi.PLANNING_MAKE_BUY_CODE, '1', 'Make', '2', 'Buy') as Make_Buy, msi.BUYER_ID, misi.SECONDARY_INVENTORY as subinventory_code,
           DECODE(misi.SOURCE_TYPE, '1', 'INV', '2','SUPP', '3', 'SUB') as Source_Type, misi.SOURCE_SUBINVENTORY as Source
           from 
           apps.mtl_system_items_b msi,
           apps.MTL_ITEM_SUB_INVENTORIES_ALL_V misi,
           (
           SELECT  
           moq.inventory_item_id, moq.organization_id, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL moq
           GROUP BY moq.inventory_item_id, moq.organization_id
           ) onhand
           where msi.organization_id = '{$organization_id}'
           AND msi.organization_id = misi.organization_id
           AND msi.inventory_item_id = misi.inventory_item_id
           
           and onhand.organization_id(+) = msi.organization_id
           and onhand.inventory_item_id(+) = msi.inventory_item_id
           and misi.MIN_MINMAX_QUANTITY IS NOT NULL
           and misi.INVENTORY_PLANNING_CODE = '2' 
           ";
   if (!empty($PLANNER_CODE)) {
    $sql .= "AND msi.planner_code='{$PLANNER_CODE}' ";
   }
   if (!empty($PLANNING_MAKE_BUY_CODE)) {
    $sql .= "AND msi.PLANNING_MAKE_BUY_CODE='{$PLANNING_MAKE_BUY_CODE}' ";
   }

   $sql.="
           ORDER BY Onhand_Delta ASC
";
  } else {
   $sql = "
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.planner_code, msi.item_type,msi.MIN_MINMAX_QUANTITY, msi.MAX_MINMAX_QUANTITY,
           msi.organization_id, onhand.Quantity,onhand.subinventory_code, msi.SOURCE_TYPE, ( NVL(onhand.Quantity,0) - msi.MIN_MINMAX_QUANTITY ) as Onhand_Delta,
           DECODE(msi.PLANNING_MAKE_BUY_CODE, '1', 'Make', '2', 'Buy') as Make_Buy, msi.BUYER_ID, misi.SECONDARY_INVENTORY as subinventory_code,
           DECODE(misi.SOURCE_TYPE, '1', 'INV', '2','SUPP', '3', 'SUB') as Source_Type, misi.SOURCE_SUBINVENTORY as Source
           from 
           apps.mtl_system_items_b msi,
           apps.MTL_ITEM_SUB_INVENTORIES_ALL_V misi,
           (
           SELECT  
           moq.inventory_item_id, moq.organization_id, moq.subinventory_code, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL moq
           WHERE moq.subinventory_code = '{$subinventory_code}'
           GROUP BY moq.inventory_item_id, moq.organization_id,moq.subinventory_code
           ) onhand
           where msi.organization_id = '{$organization_id}'
           AND msi.organization_id = misi.organization_id
           AND msi.inventory_item_id = misi.inventory_item_id
           AND misi.SECONDARY_INVENTORY = '{$subinventory_code}'
           and onhand.organization_id(+) = msi.organization_id
           and onhand.inventory_item_id(+) = msi.inventory_item_id
           and misi.MIN_MINMAX_QUANTITY IS NOT NULL
           and misi.INVENTORY_PLANNING_CODE = '2'
           ";
   if (!empty($PLANNER_CODE)) {
    $sql .= "AND msi.planner_code='{$PLANNER_CODE}' ";
   }
   if (!empty($PLANNING_MAKE_BUY_CODE)) {
    $sql .= "AND msi.PLANNING_MAKE_BUY_CODE='{$PLANNING_MAKE_BUY_CODE}' ";
   }

   $sql.="
           ORDER BY Onhand_Delta ASC
";
  }


//           echo $sql;
  $result = $dbOra->findBySql($sql);

  return !empty($result) ? ($result) : false;
 }

}

//end of po_detail class
?>