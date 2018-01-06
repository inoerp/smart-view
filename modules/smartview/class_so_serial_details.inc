<?php

class so_serial_details extends dbOraObject {

 public static $table_name = "bom";
 public static $primary_column = "bom_id";
 public static $system_info = [
  'name' => 'SO Forecast Shipment',
  'number' => '8101',
  'description' => 'SO Forecast Shipment',
  'version' => '1.1.1.3',
  'db_version' => '1001',
  'mod_version' => '1.1.x-1.1',
  'primary_entity_cb' => '',
  'module_name' => 'sd',
  'weight' => 1
 ];
 public $field_a = [
  'ITEM_NUMBER',
  'ORGANIZATION_ID',
  'TRANSACTION_DATE',
  'DESCRIPTION',
  'PLANNER_CODE',
  'SERIAL_NUMBER',
  'SHIP_DATE',
  'CHILD_SERIAL',
  'STATUS',
  'ORDER_NUMBER',
  'LINE_NUMBER',
  'PARTY_NAME',
  'PROMISE_DATE',
  'REQUEST_DATE',
  'SCHEDULE_SHIP_DATE'
 ];
 public $initial_search = [
 ];
 public $column = [
  'PLANNER_CODE'
 ];
 public $fields_inForm_notInDataBase = [
  "include_all_items_in_bom",
  'validate_in_new_org'
 ];
 public $so_serail_parameters = [
  'Organization' => 'search_org_name',
  'Planner Code' => 'search_planner_code',
  'Item Type' => 'search_item_type',
  'Start Date' => 'search_start_date',
  'End Date' => 'search_end_date',
  'Download in text mode' => 'search_download_as_text',
 ];
 public $so_serail_details = [
  'name' => 'Sales Order & Serial Details ',
  'description' => 'Sales Order & Serial Details',
 ];
 public $ITEM_NUMBER;
 public $DESCRIPTION;
 public $ITEM_TYPE;
 public $FROM_DATE;
 public $TO_DATE;
 public $PLANNER_CODE;
 public $SERIAL_NUMBER;
 public $SHIP_DATE;
 public $CHILD_SERIAL;
 public $STATUS;
 public $ORDER_NUMBER;
 public $LINE_NUMBER;
 public $PARTY_NAME;
 public $PROMISE_DATE;
 public $REQUEST_DATE;
 public $SCHEDULE_SHIP_DATE;
 public $TRANSACTION_DATE;
 public $ORGANIZATION_ID;

 public function so_serail($parameters) {
  global $dbOra;
   
  $organization_id = !empty($parameters['ORGANIZATION_ID']) ? $parameters['ORGANIZATION_ID'] : false;
  $planner_code = !empty($parameters['PLANNER_CODE']) ? $parameters['PLANNER_CODE'] : false;
  $start_date = !empty($parameters['start_date'][0]) ? $parameters['start_date'][0] : current_time(1);
  $end_date = !empty($parameters['end_date'][0]) ? $parameters['end_date'][0] : null;
  $item_number = !empty($parameters['ITEM_NUMBER']) ? $parameters['ITEM_NUMBER'] : false;

  
   $sql = " 
 SELECT  haou.name, msi.segment1 as item_number, msi.description, mmt.transaction_date as transaction_date,
  msi.planner_code, msn.serial_number, msnc.serial_number as child_serial, 
   DECODE(msn.current_status , '1' , 'Defined but not used', '2','Resides in stores', '4', 'Issued out of stores' , 'Resides in intransit',
  '6', 'Pending status' , '7','Resides in receiving' , '8' , 'Resides in WIP') as Status,
  a.order_number, ola.line_number, a.SOLD_TO_ORG_ID, d.account_number, e.party_name,
  mmt.TRANSACTION_REFERENCE, mmt.transaction_id,   ola.REQUEST_DATE,ola.PROMISE_DATE,ola.SCHEDULE_SHIP_DATE, ola.actual_shipment_date, a.booked_date, ola.creation_date,
    round((ola.actual_shipment_date - ola.PROMISE_DATE)) as promise_date_diff,round((ola.actual_shipment_date - ola.REQUEST_DATE)) as req_date_diff,
     round((ola.REQUEST_DATE - ola.creation_date) - 1) as order_lead_time
  from apps.MTL_SERIAL_NUMBERS msn, 
  apps.mtl_system_items_b msi, 
  apps.MTL_MATERIAL_TRANSACTIONS  mmt, 
  apps.MTL_UNIT_TRANSACTIONS_ALL_V mut,
  apps.MTL_SERIAL_NUMBERS msnc,
  apps.oe_order_headers_all a, 
  apps.OE_ORDER_LINES_ALL ola,
apps.hz_cust_site_uses_all b, 
apps.HZ_CUST_ACCT_SITES_ALL c,
apps.hz_cust_accounts d, 
apps.hz_parties e ,
apps.HR_ALL_ORGANIZATION_UNITS haou


  WHERE msi.inventory_item_id = msn.inventory_item_id 
  AND mmt.ORGANIZATION_ID = '{$organization_id}' 
  AND mmt.transaction_date > to_date('{$start_date}', 'YY-MM-DD')  
  AND mmt.inventory_item_id = msi.inventory_item_id 
  AND mmt.organization_id = msi.organization_id 
  AND msn.SERIAL_NUMBER = mut.SERIAL_NUMBER 
  AND mut.inventory_item_id = msi.inventory_item_id 
  AND mut.transaction_id = mmt.transaction_id 
  AND mmt.TRANSACTION_TYPE_ID IN ( '33', '62') 
  AND msi.planner_code like '{$planner_code}'  
  AND mut.organization_id = msi.organization_id 
  AND msnc.parent_serial_number (+) = msn.SERIAL_NUMBER 
  and a.header_id =   mmt.TRANSACTION_REFERENCE 
  AND a.ship_to_org_id = b.site_use_id 
  and b.cust_acct_site_id = c.cust_acct_site_id 
  and c.cust_account_id = d.cust_account_id 
  and d.party_id = e.party_id 
  AND ola.HEADER_ID = a.HEADER_ID
  AND ola.SHIP_FROM_ORG_ID =  msi.organization_id 
  AND ola.inventory_item_id = msi.inventory_item_id 
  and haou.organization_id = a.org_id
  AND mmt.trx_source_line_id = ola.line_id

";
  if(!empty($end_date)){
   $sql .= "AND mmt.transaction_date < to_date('{$end_date}', 'YY-MM-DD')  " ;
  }
  
  
  
 $result = $this->findBy_sql($sql);

  
 
  return $result;
 }

}

//end of bom class
?>