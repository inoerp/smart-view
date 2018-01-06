<?php

class fp_simple_board_v extends dbOraObject {

 public static $table_name = "fp_minmax_board_v";
 public static $primary_column = "onhand_id";
 public static $system_info = [
  'name' => 'Min Max Board',
  'number' => '8100',
  'description' => 'View Min Max Board',
  'version' => '1.1.1.3',
  'db_version' => '1001',
  'mod_version' => '1.1.x-1.1',
  'primary_entity_cb' => '',
  'module_name' => 'po',
  'weight' => 1
 ];
 public static $item_desc = [
  'Laser Diode' => 'Laser Diode',
  'Cold Block' => 'Cold Block',
  'FLEX BOARD ' => 'Flex Board',
  'LENS' => 'Lens',
  'Cleaned' => 'Cleaing',
  'Photodiode' => 'Photodiode'
 ];
 public static $order_by = [
  'ONHAND' => 'Onhand Availability',
 ];
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
 public $OPEN_PO_QTY;
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
 public $organization_id;
 public $SUBINVENTORY_CODE;
 public $SOURCE_SUBINVENTORY;
 public $PLANNER_CODE;
 public $PLANNING_MAKE_BUY_CODE;
 public $TOTAL_DELTA;
 public $DESCRIPTION;
 public $ITEM_NUMBER;
 public $ORDER_BY;
 public $SERIAL_VAL;
 public $LOT_VAL; 

 private function _getSQL_subInvCodeEmpty($item_number = '', $item_desc = '') {
  $sql = "
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.inventory_item_id, msi.DESCRIPTION, msi.planner_code, msi.item_type,msi.MIN_MINMAX_QUANTITY, 
           msi.MAX_MINMAX_QUANTITY, msi.FIXED_LOT_MULTIPLIER as FLM,
           msi.organization_id, onhand.Quantity, msi.SOURCE_TYPE, msi.WIP_SUPPLY_LOCATOR_ID locator_id,
           ( NVL(onhand.Quantity,0) +  NVL(open_po.Open_Quantity,0) - msi.MAX_MINMAX_QUANTITY ) as Total_Delta,
           ( NVL(onhand.Quantity,0) - msi.MIN_MINMAX_QUANTITY ) as Min_Delta,
           ( NVL(onhand.Quantity,0) - msi.MAX_MINMAX_QUANTITY ) as Max_Delta,
           DECODE(msi.PLANNING_MAKE_BUY_CODE, '1', 'Make', '2', 'Buy') as Make_Buy, msi.BUYER_ID, 'Org' as subinventory_code,
           DECODE(msi.SOURCE_TYPE, '1', 'INV', '2','SUPP', '3', 'SUB') as Source_Type,
           'NA' as Source, open_po.Open_Quantity as open_po_qty,
            onhand.Quantity as source_onhand, 1 as source_locator_id,
            CASE WHEN (msi.LOT_CONTROL_CODE > 1)  THEN '9'
                   ELSE '-9'
              END AS LOT_VAL,
              CASE WHEN (msi.SERIAL_NUMBER_CONTROL_CODE > 1)  THEN '9'
                   ELSE '-9'
              END AS SERIAL_VAL
           from 
           apps.mtl_system_items_b msi,
           (
           SELECT  
           moq.inventory_item_id, moq.organization_id, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL moq
           WHERE moq.subinventory_code != 'MRB'
           GROUP BY moq.inventory_item_id, moq.organization_id
           ) onhand,
           (
          SELECT pla.item_id, plla.SHIP_TO_ORGANIZATION_ID, (SUM(plla.QUANTITY) - SUM(plla.QUANTITY_RECEIVED)) as Open_Quantity
          FROM apps.PO_LINE_LOCATIONS_ALL plla,
          apps.po_lines_all pla
          WHERE SHIP_TO_ORGANIZATION_ID = '{$this->organization_id}'
          AND pla.po_line_id = plla.po_line_id
          GROUP BY pla.item_id, plla.SHIP_TO_ORGANIZATION_ID
          HAVING (SUM(plla.QUANTITY) - SUM(plla.QUANTITY_RECEIVED)) > 0 
           ) open_po
           where msi.organization_id = '{$this->organization_id}'
           and onhand.organization_id(+) = msi.organization_id
           and onhand.inventory_item_id(+) = msi.inventory_item_id
           and open_po.SHIP_TO_ORGANIZATION_ID(+) = msi.organization_id
           and open_po.item_id(+) = msi.inventory_item_id
           and msi.MIN_MINMAX_QUANTITY IS NOT NULL ";
  if (!empty($this->PLANNER_CODE)) {
   $sql .= "AND msi.planner_code LIKE '%{$this->PLANNER_CODE}%' ";
  }

  if (!empty($this->PLANNING_MAKE_BUY_CODE)) {
   $sql .= "AND msi.PLANNING_MAKE_BUY_CODE ='{$this->PLANNING_MAKE_BUY_CODE}' ";
  }

  if (!empty($this->DESCRIPTION)) {
   $sql .= "AND msi.DESCRIPTION LIKE '%{$this->DESCRIPTION}%' ";
  }

  if (!empty($this->ITEM_NUMBER)) {
   $sql .= "AND msi.SEGMENT1 LIKE '%{$this->ITEM_NUMBER}%' ";
  }

  $sql.="  UNION
           
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.inventory_item_id, msi.DESCRIPTION, msi.planner_code, msi.item_type,misi.MIN_MINMAX_QUANTITY,
           misi.MAX_MINMAX_QUANTITY,  misi.FIXED_LOT_MULTIPLE as FLM,
           msi.organization_id, onhand.Quantity, msi.SOURCE_TYPE, msi.WIP_SUPPLY_LOCATOR_ID locator_id,
           ( NVL(onhand.Quantity,0)+  NVL(open_po.Open_Quantity,0) - misi.MAX_MINMAX_QUANTITY ) as Total_Delta,
           ( NVL(onhand.Quantity,0) - misi.MIN_MINMAX_QUANTITY ) as Min_Delta,
           ( NVL(onhand.Quantity,0) - misi.MAX_MINMAX_QUANTITY ) as Max_Delta,
           DECODE(msi.PLANNING_MAKE_BUY_CODE, '1', 'Make', '2', 'Buy') as Make_Buy, msi.BUYER_ID, misi.SECONDARY_INVENTORY as subinventory_code,
           DECODE(misi.SOURCE_TYPE, '1', 'INV', '2','SUPP', '3', 'SUB') as Source_Type, misi.SOURCE_SUBINVENTORY as Source,
           open_po.Open_Quantity as open_po_qty,
            source_onhand.Quantity as source_onhand, source_onhand.locator_id as source_locator_id,
                        CASE WHEN (msi.LOT_CONTROL_CODE > 1)  THEN '9'
                   ELSE '-9'
              END AS LOT_VAL,
              CASE WHEN (msi.SERIAL_NUMBER_CONTROL_CODE > 1)  THEN '9'
                   ELSE '-9'
              END AS SERIAL_VAL
           from 
           apps.mtl_system_items_b msi,
           apps.MTL_ITEM_SUB_INVENTORIES_ALL_V misi,
           (
           SELECT  
           moq.inventory_item_id, moq.organization_id, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL moq
           WHERE moq.subinventory_code != 'MRB'
           GROUP BY moq.inventory_item_id, moq.organization_id
           ) onhand,
          (
           SELECT  
           source_moq.inventory_item_id, source_moq.organization_id, source_moq.subinventory_code, 
           sum(source_moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity, source_moq.locator_id
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL source_moq
         WHERE source_moq.organization_id = '{$this->organization_id}' 
          AND source_moq.subinventory_code != 'MRB'
         GROUP BY source_moq.inventory_item_id, source_moq.organization_id,source_moq.subinventory_code, source_moq.locator_id
           ) source_onhand,
          (
          SELECT pla.item_id, plla.SHIP_TO_ORGANIZATION_ID, (SUM(plla.QUANTITY) - SUM(plla.QUANTITY_RECEIVED)) as Open_Quantity
          FROM apps.PO_LINE_LOCATIONS_ALL plla,
          apps.po_lines_all pla
          WHERE SHIP_TO_ORGANIZATION_ID = '{$this->organization_id}'
          AND pla.po_line_id = plla.po_line_id
          GROUP BY pla.item_id, plla.SHIP_TO_ORGANIZATION_ID
          HAVING (SUM(plla.QUANTITY) - SUM(plla.QUANTITY_RECEIVED)) > 0 
           ) open_po
           where msi.organization_id = '{$this->organization_id}'
           AND msi.organization_id = misi.organization_id
           AND msi.inventory_item_id = misi.inventory_item_id
           and open_po.SHIP_TO_ORGANIZATION_ID(+) = msi.organization_id
           and open_po.item_id(+) = msi.inventory_item_id
           and onhand.organization_id(+) = msi.organization_id
           and onhand.inventory_item_id(+) = msi.inventory_item_id
           and misi.MIN_MINMAX_QUANTITY IS NOT NULL
           AND source_onhand.subinventory_code(+) = misi.SOURCE_SUBINVENTORY
                      and source_onhand.organization_id(+) = misi.organization_id
           and source_onhand.inventory_item_id(+) = misi.inventory_item_id
           ";
  if (!empty($this->PLANNER_CODE)) {
   $sql .= "AND msi.planner_code LIKE '%{$this->PLANNER_CODE}%' ";
  }
  if (!empty($this->PLANNING_MAKE_BUY_CODE)) {
   $sql .= "AND msi.PLANNING_MAKE_BUY_CODE='{$this->PLANNING_MAKE_BUY_CODE}' ";
  }

  if (!empty($this->DESCRIPTION)) {
   $sql .= "AND msi.DESCRIPTION LIKE '%{$this->DESCRIPTION}%' ";
  }

  if (!empty($this->ITEM_NUMBER)) {
   $sql .= "AND msi.SEGMENT1 LIKE '%{$this->ITEM_NUMBER}%' ";
  }
  
  
  if (!empty($this->ORDER_BY)) {
   $sql .=   $this->_get_orderBy() ;
  } else {
   $sql.="
           ORDER BY Min_Delta ASC
";
  }

//echo "<br><br><br><br><br><br><br>$sql";
  return $sql;
 }

 private function _getSQL_subInvCode() {
  $sql = "
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.inventory_item_id, msi.DESCRIPTION, msi.planner_code, msi.item_type,misi.MIN_MINMAX_QUANTITY,
           misi.MAX_MINMAX_QUANTITY, misi.FIXED_LOT_MULTIPLE as FLM,
           msi.organization_id, onhand.Quantity,onhand.subinventory_code, msi.SOURCE_TYPE, msi.WIP_SUPPLY_LOCATOR_ID locator_id,
           ( NVL(onhand.Quantity,0) +  NVL(open_po.Open_Quantity,0) - misi.MAX_MINMAX_QUANTITY ) as Total_Delta,
                      ( NVL(onhand.Quantity,0) - misi.MIN_MINMAX_QUANTITY ) as Min_Delta,
           ( NVL(onhand.Quantity,0) - misi.MAX_MINMAX_QUANTITY ) as Max_Delta,
           DECODE(msi.PLANNING_MAKE_BUY_CODE, '1', 'Make', '2', 'Buy') as Make_Buy, msi.BUYER_ID, misi.SECONDARY_INVENTORY as subinventory_code,
           DECODE(misi.SOURCE_TYPE, '1', 'INV', '2','SUPP', '3', 'SUB') as Source_Type, misi.SOURCE_SUBINVENTORY as Source,
           open_po.Open_Quantity as open_po_qty,
            source_onhand.Quantity as source_onhand, source_onhand.locator_id as source_locator_id,
                        CASE WHEN (msi.LOT_CONTROL_CODE > 1)  THEN '9'
                   ELSE '-9'
              END AS LOT_VAL,
              CASE WHEN (msi.SERIAL_NUMBER_CONTROL_CODE > 1)  THEN '9'
                   ELSE '-9'
              END AS SERIAL_VAL
           from 
           apps.mtl_system_items_b msi,
           apps.MTL_ITEM_SUB_INVENTORIES_ALL_V misi,
           (
           SELECT  
           moq.inventory_item_id, moq.organization_id, moq.subinventory_code,  sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL moq
           WHERE moq.subinventory_code = '{$this->SUBINVENTORY_CODE}'
            AND moq.organization_id = '{$this->organization_id}'
             AND moq.subinventory_code != 'MRB'
           GROUP BY moq.inventory_item_id, moq.organization_id,moq.subinventory_code
           ) onhand,
           (
           SELECT  
           source_moq.inventory_item_id, source_moq.organization_id, source_moq.subinventory_code, 
           sum(source_moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity, source_moq.locator_id
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL source_moq
         WHERE source_moq.organization_id = '{$this->organization_id}' 
          AND source_moq.subinventory_code != 'MRB'
         GROUP BY source_moq.inventory_item_id, source_moq.organization_id,source_moq.subinventory_code, source_moq.locator_id
           ) source_onhand,
          (
          SELECT pla.item_id, plla.SHIP_TO_ORGANIZATION_ID, (SUM(plla.QUANTITY) - SUM(plla.QUANTITY_RECEIVED)) as Open_Quantity
          FROM apps.PO_LINE_LOCATIONS_ALL plla,
          apps.po_lines_all pla
          WHERE SHIP_TO_ORGANIZATION_ID = '{$this->organization_id}'
          AND pla.po_line_id = plla.po_line_id
          GROUP BY pla.item_id, plla.SHIP_TO_ORGANIZATION_ID
          HAVING (SUM(plla.QUANTITY) - SUM(plla.QUANTITY_RECEIVED)) > 0 
           ) open_po
           where msi.organization_id = '{$this->organization_id}'
           AND msi.organization_id = misi.organization_id
           AND msi.inventory_item_id = misi.inventory_item_id
           AND misi.SECONDARY_INVENTORY = '{$this->SUBINVENTORY_CODE}'
           and onhand.organization_id(+) = msi.organization_id
           and onhand.inventory_item_id(+) = msi.inventory_item_id
           and open_po.SHIP_TO_ORGANIZATION_ID(+) = msi.organization_id
           and open_po.item_id(+) = msi.inventory_item_id
           and misi.MIN_MINMAX_QUANTITY IS NOT NULL
           AND source_onhand.subinventory_code(+) = misi.SOURCE_SUBINVENTORY
           and source_onhand.organization_id(+) = misi.organization_id
           and source_onhand.inventory_item_id(+) = misi.inventory_item_id
            ";
  if (!empty($this->PLANNER_CODE)) {
   $sql .= "AND msi.planner_code LIKE '%{$this->PLANNER_CODE}%' ";
  }
  if (!empty($this->PLANNING_MAKE_BUY_CODE)) {
   $sql .= "AND msi.PLANNING_MAKE_BUY_CODE='{$this->PLANNING_MAKE_BUY_CODE}' ";
  }
  if (!empty($this->ITEM_NUMBER)) {
   $sql .= "AND msi.SEGMENT1 LIKE '%{$this->ITEM_NUMBER}%' ";
  }

  if (!empty($this->ORDER_BY)) {
   $sql .=   $this->_get_orderBy() ;
  } else {
   $sql.="
           ORDER BY Min_Delta ASC
";
  }



//  echo $sql;
  return $sql;
 }

 private function _get_orderBy() {
  $stmt = "";
  switch ($this->ORDER_BY) {
   case 'ONHAND':
    $stmt = "  AND source_onhand.Quantity IS NOT NULL ORDER BY Min_Delta ASC  ";
    break;

   default :
    break;
  }
  return $stmt;
 }

 private function _getSQL_sourceSubInvCode() {
  $sql = "
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.inventory_item_id, msi.DESCRIPTION, msi.planner_code, msi.item_type,misi.MIN_MINMAX_QUANTITY,
           misi.MAX_MINMAX_QUANTITY, misi.FIXED_LOT_MULTIPLE as FLM,
           msi.organization_id, onhand.Quantity,onhand.subinventory_code, msi.SOURCE_TYPE,msi.WIP_SUPPLY_LOCATOR_ID locator_id,
           ( NVL(onhand.Quantity,0) +  NVL(open_po.Open_Quantity,0) - misi.MAX_MINMAX_QUANTITY ) as Total_Delta,
                      ( NVL(onhand.Quantity,0) - misi.MIN_MINMAX_QUANTITY ) as Min_Delta,
           ( NVL(onhand.Quantity,0) - misi.MAX_MINMAX_QUANTITY ) as Max_Delta,
           DECODE(msi.PLANNING_MAKE_BUY_CODE, '1', 'Make', '2', 'Buy') as Make_Buy, msi.BUYER_ID, misi.SECONDARY_INVENTORY as subinventory_code,
           DECODE(misi.SOURCE_TYPE, '1', 'INV', '2','SUPP', '3', 'SUB') as Source_Type, misi.SOURCE_SUBINVENTORY as Source,
           open_po.Open_Quantity as open_po_qty,
           source_onhand.Quantity as source_onhand, source_onhand.locator_id as source_locator_id,
                       CASE WHEN (msi.LOT_CONTROL_CODE > 1)  THEN '9'
                   ELSE '-9'
              END AS LOT_VAL,
              CASE WHEN (msi.SERIAL_NUMBER_CONTROL_CODE > 1)  THEN '9'
                   ELSE '-9'
              END AS SERIAL_VAL
           from 
           apps.mtl_system_items_b msi,
           apps.MTL_ITEM_SUB_INVENTORIES_ALL_V misi,
           (
           SELECT  
           moq.inventory_item_id, moq.organization_id, moq.locator_id, moq.subinventory_code, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL moq,
           apps.MTL_SECONDARY_INVENTORIES subinv
           ";
  $sql .= " WHERE moq.organization_id = '{$this->organization_id}' 
            AND subinv.organization_id = '{$this->organization_id}'  
            AND subinv.RESERVABLE_TYPE = '1' 
            AND moq.subinventory_code != 'MRB'
            AND subinv.SECONDARY_INVENTORY_NAME = moq.subinventory_code ";
  if (!empty($this->SUBINVENTORY_CODE)) {
   $sql .= " AND moq.subinventory_code = '{$this->SUBINVENTORY_CODE}' ";
  }
  $sql .=" GROUP BY moq.inventory_item_id, moq.organization_id,moq.subinventory_code, moq.locator_id
           ) onhand, (
           SELECT  
           source_moq.inventory_item_id, source_moq.organization_id, source_moq.subinventory_code, 
           sum(source_moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity, source_moq.locator_id
           from 
           apps.MTL_ONHAND_QUANTITIES_DETAIL source_moq
         WHERE source_moq.organization_id = '{$this->organization_id}' 
          AND source_moq.subinventory_code != 'MRB'
         GROUP BY source_moq.inventory_item_id, source_moq.organization_id,source_moq.subinventory_code, source_moq.locator_id
           ) source_onhand,
          (
          SELECT pla.item_id, plla.SHIP_TO_ORGANIZATION_ID, (SUM(plla.QUANTITY) - SUM(plla.QUANTITY_RECEIVED)) as Open_Quantity
          FROM apps.PO_LINE_LOCATIONS_ALL plla,
          apps.po_lines_all pla
          WHERE SHIP_TO_ORGANIZATION_ID = '{$this->organization_id}'
          AND pla.po_line_id = plla.po_line_id
          GROUP BY pla.item_id, plla.SHIP_TO_ORGANIZATION_ID
          HAVING (SUM(plla.QUANTITY) - SUM(plla.QUANTITY_RECEIVED)) > 0 
           ) open_po
           where msi.organization_id = '{$this->organization_id}'
           AND msi.organization_id = misi.organization_id
           AND msi.inventory_item_id = misi.inventory_item_id
            AND misi.SOURCE_SUBINVENTORY = '{$this->SOURCE_SUBINVENTORY}' 
           and onhand.organization_id(+) = misi.organization_id
           and onhand.inventory_item_id(+) = misi.inventory_item_id
           AND onhand.subinventory_code(+) = misi.SECONDARY_INVENTORY 
           and open_po.SHIP_TO_ORGANIZATION_ID(+) = msi.organization_id
           and open_po.item_id(+) = msi.inventory_item_id
           and misi.MIN_MINMAX_QUANTITY IS NOT NULL
           AND source_onhand.subinventory_code(+) = misi.SOURCE_SUBINVENTORY
           and source_onhand.organization_id(+) = misi.organization_id
           and source_onhand.inventory_item_id(+) = misi.inventory_item_id
           ";
  if (!empty($this->SUBINVENTORY_CODE)) {
   $sql .= "AND misi.SECONDARY_INVENTORY = '{$this->SUBINVENTORY_CODE}'";
  }
  if (!empty($this->PLANNER_CODE)) {
   $sql .= "AND msi.planner_code LIKE '%{$this->PLANNER_CODE}%' ";
  }
  if (!empty($this->PLANNING_MAKE_BUY_CODE)) {
   $sql .= "AND msi.PLANNING_MAKE_BUY_CODE='{$this->PLANNING_MAKE_BUY_CODE}' ";
  }

  if (!empty($this->ITEM_NUMBER)) {
   $sql .= "AND msi.SEGMENT1 LIKE '%{$this->ITEM_NUMBER}%' ";
  }
  
  
  if (!empty($this->ORDER_BY)) {
   $sql .=   $this->_get_orderBy() ;
  } else {
   $sql.="
           ORDER BY Min_Delta ASC
";
  }

  return $sql;
 }

 public function findBy_Details() {
  global $dbOra;

  if (!empty($this->SOURCE_SUBINVENTORY)) {
   $sql = $this->_getSQL_sourceSubInvCode();
  } else if (empty($this->SUBINVENTORY_CODE)) {
   $sql = $this->_getSQL_subInvCodeEmpty();
//   echo "<br><br><br><br><br>$sql";
  } else {
   $sql = $this->_getSQL_subInvCode();
  }


//           echo $sql; 
//           pa($this);
  $result = $dbOra->findBySql($sql);
//pa($result);
  return !empty($result) ? ($result) : false;
 }

 public static function xxfind_by_orgId_subInventoryId($organization_id, $PLANNER_CODE = '', $subinventory_code = '', $PLANNING_MAKE_BUY_CODE = '') {
  global $dbOra;

  if (empty($subinventory_code)) {
   $sql = "
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.inventory_item_id,  msi.DESCRIPTION, msi.planner_code, msi.item_type,msi.MIN_MINMAX_QUANTITY, msi.MAX_MINMAX_QUANTITY,
           msi.organization_id, onhand.Quantity, msi.SOURCE_TYPE, 
           ( NVL(onhand.Quantity,0) - msi.MAX_MINMAX_QUANTITY ) as Total_Delta,
           ( NVL(onhand.Quantity,0) - msi.MIN_MINMAX_QUANTITY ) as Min_Delta,
           ( NVL(onhand.Quantity,0) - msi.MAX_MINMAX_QUANTITY ) as Max_Delta,
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
           WHERE moq.subinventory_code != 'MRB'
           GROUP BY moq.inventory_item_id, moq.organization_id
           ) onhand
           where msi.organization_id = '{$organization_id}'
           AND msi.INVENTORY_PLANNING_CODE = 2
           and onhand.organization_id(+) = msi.organization_id
           and onhand.inventory_item_id(+) = msi.inventory_item_id
           and msi.MIN_MINMAX_QUANTITY IS NOT NULL  ";
   if (!empty($PLANNER_CODE)) {
    $sql .= "AND msi.planner_code LIKE '%{$this->PLANNER_CODE}%' ";
   }

   if (!empty($PLANNING_MAKE_BUY_CODE)) {
    $sql .= "AND msi.PLANNING_MAKE_BUY_CODE ='{$PLANNING_MAKE_BUY_CODE}' ";
   }

   $sql.="  UNION
           
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.inventory_item_id, msi.DESCRIPTION, msi.planner_code, msi.item_type,msi.MIN_MINMAX_QUANTITY, msi.MAX_MINMAX_QUANTITY,
           msi.organization_id, onhand.Quantity, msi.SOURCE_TYPE, 
           ( NVL(onhand.Quantity,0) - misi.MAX_MINMAX_QUANTITY ) as Total_Delta,
                      ( NVL(onhand.Quantity,0) - misi.MIN_MINMAX_QUANTITY ) as Min_Delta,
           ( NVL(onhand.Quantity,0) - misi.MAX_MINMAX_QUANTITY ) as Max_Delta,
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
           WHERE moq.subinventory_code != 'MRB'
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
    $sql .= "AND msi.planner_code LIKE '%{$this->PLANNER_CODE}%' ";
   }
   if (!empty($PLANNING_MAKE_BUY_CODE)) {
    $sql .= "AND msi.PLANNING_MAKE_BUY_CODE='{$PLANNING_MAKE_BUY_CODE}' ";
   }

   $sql.="
           ORDER BY Min_Delta ASC
";
  } else {
   $sql = "
           SELECT  
           msi.SEGMENT1 as ITEM_NUMBER, msi.inventory_item_id, msi.DESCRIPTION, msi.planner_code, msi.item_type,msi.MIN_MINMAX_QUANTITY, msi.MAX_MINMAX_QUANTITY,
           msi.organization_id, onhand.Quantity,onhand.subinventory_code, msi.SOURCE_TYPE, 
           ( NVL(onhand.Quantity,0) - msi.MAX_MINMAX_QUANTITY ) as Total_Delta,
                                 ( NVL(onhand.Quantity,0) - msi.MIN_MINMAX_QUANTITY ) as Min_Delta,
           ( NVL(onhand.Quantity,0) - msi.MAX_MINMAX_QUANTITY ) as Max_Delta,
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
            AND  moq.organization_id = '{$organization_id}'
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
    $sql .= "AND msi.planner_code LIKE '%{$this->PLANNER_CODE}%' ";
   }
   if (!empty($PLANNING_MAKE_BUY_CODE)) {
    $sql .= "AND msi.PLANNING_MAKE_BUY_CODE='{$PLANNING_MAKE_BUY_CODE}' ";
   }

   $sql.="
           ORDER BY Min_Delta ASC
";
  }


//           echo $sql;
  $result = $dbOra->findBySql($sql);

  return !empty($result) ? ($result) : false;
 }

}

//end of po_detail class
?>