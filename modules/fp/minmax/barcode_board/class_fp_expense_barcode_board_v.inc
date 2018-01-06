<?php

class fp_expense_barcode_board_v extends dbObject {

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

 public function findBy_Details() {
  $sql = " SELECT 
item_number as ITEM_NUMBER, item_description as DESCRIPTION, org_code as ORG_NAME, subinventory as SUBINVENTORY_CODE, 
locator as DESTINATION_LOCATOR, card_size as MIN_MINMAX_QUANTITY, card_size as MAX_MINMAX_QUANTITY,	 NULL as QUANTITY,
-(card_size) as TOTAL_DELTA,
from_subinventory as SOURCE, from_locator as FROM_LOCATOR, 
from_org_code as FROM_ORG, supplier, supplier_site, 'SUB' as SOURCE_TYPE , NULL as PLANNER_CODE,
NULL as MIN_DELTA, NULL as MAX_DELTA,  NULL as LOCATOR_ID,
'2989' as ORGANIZATION_ID, NULL as INVENTORY_ITEM_ID, 'Buy' as MAKE_BUY, NULL as OPEN_PO_QTY, NULL as SOURCE_ONHAND,
NULL as SERIAL_VAL, NULL as LOT_VAL
FROM fp_kanban_rfid_v

";

  if (!empty($this->ITEM_NUMBER)) {
   $sql .= " WHERE item_number LIKE '%{$this->ITEM_NUMBER}%' ";
  }

//           echo $sql;
  $result = self::find_by_sql($sql);
//pa($result);
  return !empty($result) ? ($result) : false;
 }

}

//end of po_detail class
?>