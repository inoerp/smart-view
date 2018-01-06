<?php

class so_forecast_shipment_weekly extends dbOraObject {

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
  'PLANNER_CODE',
  'ORGANIZATION_ID'
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
 public $fss_parameters = [
  'Organization' => 'search_org_name',
  'Planner Code' => 'search_planner_code',
  'Download in text mode' => 'search_download_as_text',
 ];
 public $fss_details = [
  'name' => 'Scheduling Report',
  'description' => 'Forecast , SO & Shipment Report',
 ];
 public $ITEM_NUMBER;
 public $DESCRIPTION;
 public $PLANNER_CODE;
 public $DOC_TYPE_QUANTITY;
 public $AUGUST_Forecast;
 public $AUGUST_Actual_Shipment;
 public $AUGUST_Sales_order;
 public $SEPTEMBER_Forecast;
 public $SEPTEMBER_Sales_order;
 public $SEPTEMBER_Actual_Shipment;
 public $OCTOBER_Forecast;
 public $OCTOBER_Actual_Shipment;
 public $OCTOBER_Sales_order;
 public $NOVEMBER_Forecast;
 public $NOVEMBER_Actual_Shipment;
 public $NOVEMBER_Sales_order;
 public $ORGANIZATION_ID;

 public function __set($name, $value) {
  switch ($value) {
   case $value:


    break;

   default:
    $this->$name = $value;
    break;
  }
 }

 public function getCHildFGI($item_number, $org_id = '2989', $planner_code = 'OBIS') {
  global $dbOra;
  $sql = "

SELECT DISTINCT( bbc.bill_item_name || '|' || bbc.component_item_name ),
bbc.bill_item_name as Assembly, msi.description as Parent_Description,
msi.ITEM_TYPE Parent_Item_Type, msi.PLANNER_CODE Parent_Planner_code,
bbc.component_item_id Component_Item_Id,bbc.component_item_name as Component_Number,
msi_c.description as Description , bbc.quantity_per_assembly as Quantity, 
msi_c.item_type, msi_c.planner_code, bbc.organization_code, bbc.end_effective_date as END_DATE,
bbc.organization_id, bbc.assembly_item_id
 
from apps.bomfg_bom_components  bbc,
apps.mtl_system_items_b msi,
apps.mtl_system_items_b msi_c
where bbc.organization_id = 63
and msi_c.inventory_item_id = bbc.component_item_id
and msi_c.organization_id = '{$org_id}'
and msi.organization_id = msi_c.organization_id
and msi.inventory_item_id = bbc.assembly_item_id
and msi.planner_code =  '{$planner_code}'
and msi.segment1 = '{$item_number}'
and msi.item_type IN ('FG','COM')
and msi_c.item_type IN ('FG','COM')

";

  $result = $dbOra->findBySql($sql);

  return !empty($result) ? $result : false;
  ;
 }

 public function getSOByDate($org_id, $item_number, $planner_code) {
  global $dbOra;
  $sql = " 
SELECT oela.ordered_item,msi.DESCRIPTION, msi.ITEM_TYPE, sum(oela.ordered_quantity) as Quantity, 'Scheduled_SO' as DOC_TYPE ,
msi.planner_code,  to_char(oela.schedule_ship_date) as SSD
FROM
apps.oe_order_lines_all oela,
apps.mtl_system_items_b msi
where oela.ship_from_org_id = '{$org_id}'
and schedule_ship_date >= TRUNC(SYSDATE,'IW')
and schedule_ship_date <= TRUNC(SYSDATE,'IW') + 14
and msi.segment1 = oela.ordered_item 
and msi.organization_id = oela.ship_from_org_id 
and msi.planner_code =  '{$planner_code}'
 and msi.segment1 =  '{$item_number}'
GROUP BY oela.ordered_item,msi.DESCRIPTION, msi.ITEM_TYPE, msi.planner_code, oela.schedule_ship_date";
  $result = $dbOra->findBySql($sql);

  return !empty($result) ? $result : false;
 }

 function getRecords($org_id = '2989', $planner_code = 'OBIS') {
  global $dbOra;
  $sql = "
    
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(wdj.QUANTITY_REMAINING) as Quantity, 'Scheduled_WO' as DOC_TYPE ,
msi.planner_code,  
(to_number(to_char(to_date(TRUNC (wdj.SCHEDULED_COMPLETION_DATE, 'IW')),'IW')) - to_number(to_char(to_date(TRUNC (SYSDATE, 'IW')),'IW'))) + 1 as WEEK
from 
apps.WIP_DISCRETE_JOBS_V wdj,
apps.mtl_system_items_b msi
where wdj.organization_id = '{$org_id}'
and wdj.status_type IN ( '3' )
and wdj.organization_id = msi.organization_id
and wdj.primary_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and wdj.SCHEDULED_COMPLETION_DATE >= TRUNC (SYSDATE,'IW') and wdj.SCHEDULED_COMPLETION_DATE <= TRUNC (SYSDATE + 84 ,'IW') 
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE,'Scheduled_WO', msi.planner_code,   TRUNC (wdj.SCHEDULED_COMPLETION_DATE, 'IW')

UNION
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(wdj.QUANTITY_REMAINING) as Quantity, 'Overdue_WO' as DOC_TYPE ,
msi.planner_code,  
1 as WEEK
from 
apps.WIP_DISCRETE_JOBS_V wdj,
apps.mtl_system_items_b msi
where wdj.organization_id = '{$org_id}'
and wdj.status_type IN ( '3' )
and wdj.organization_id = msi.organization_id
and wdj.primary_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and wdj.SCHEDULED_COMPLETION_DATE  < SYSDATE and wdj.SCHEDULED_COMPLETION_DATE  >= SYSDATE - 7
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE,'Scheduled_WO', msi.planner_code,   TRUNC (wdj.SCHEDULED_COMPLETION_DATE, 'IW')


UNION
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(wdj.QUANTITY_REMAINING) as Quantity, 'Overdue_WO' as DOC_TYPE ,
msi.planner_code,  
2 as WEEK
from 
apps.WIP_DISCRETE_JOBS_V wdj,
apps.mtl_system_items_b msi
where wdj.organization_id = '{$org_id}'
and wdj.status_type IN ( '3' )
and wdj.organization_id = msi.organization_id
and wdj.primary_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and wdj.SCHEDULED_COMPLETION_DATE  < SYSDATE - 7  and wdj.SCHEDULED_COMPLETION_DATE  >= SYSDATE - 14
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE,'Scheduled_WO', msi.planner_code,   TRUNC (wdj.SCHEDULED_COMPLETION_DATE, 'IW')

UNION
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(wdj.QUANTITY_REMAINING) as Quantity, 'Overdue_WO' as DOC_TYPE ,
msi.planner_code,  
3 as WEEK
from 
apps.WIP_DISCRETE_JOBS_V wdj,
apps.mtl_system_items_b msi
where wdj.organization_id = '{$org_id}'
and wdj.status_type IN ( '3' )
and wdj.organization_id = msi.organization_id
and wdj.primary_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and wdj.SCHEDULED_COMPLETION_DATE  < SYSDATE - 14 and wdj.SCHEDULED_COMPLETION_DATE  >= SYSDATE - 21
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE,'Scheduled_WO', msi.planner_code,   TRUNC (wdj.SCHEDULED_COMPLETION_DATE, 'IW')


UNION
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(wdj.QUANTITY_REMAINING) as Quantity, 'Overdue_WO' as DOC_TYPE ,
msi.planner_code,  
4 as WEEK
from 
apps.WIP_DISCRETE_JOBS_V wdj,
apps.mtl_system_items_b msi
where wdj.organization_id = '{$org_id}'
and wdj.status_type IN ( '3' )
and wdj.organization_id = msi.organization_id
and wdj.primary_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and wdj.SCHEDULED_COMPLETION_DATE  < SYSDATE - 21 and wdj.SCHEDULED_COMPLETION_DATE  >= SYSDATE - 28
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE,'Scheduled_WO', msi.planner_code,   TRUNC (wdj.SCHEDULED_COMPLETION_DATE, 'IW')


UNION
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(wdj.QUANTITY_REMAINING) as Quantity, 'L_Overdue_WO' as DOC_TYPE ,
msi.planner_code,  
5 as WEEK
from 
apps.WIP_DISCRETE_JOBS_V wdj,
apps.mtl_system_items_b msi
where wdj.organization_id = '{$org_id}'
and wdj.status_type IN ( '3' )
and wdj.organization_id = msi.organization_id
and wdj.primary_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and wdj.SCHEDULED_COMPLETION_DATE  >= SYSDATE - 29
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE,'Scheduled_WO', msi.planner_code,   TRUNC (wdj.SCHEDULED_COMPLETION_DATE, 'IW')

UNION

SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mmt.PRIMARY_QUANTITY) as Quantity, 'Production' as DOC_TYPE ,
msi.planner_code,  
(to_number(to_char(to_date(TRUNC (mmt.TRANSACTION_DATE, 'IW')),'IW')) - to_number(to_char(to_date(TRUNC (SYSDATE, 'IW')),'IW'))) + 1 as WEEK
from 
apps.MTL_MATERIAL_TRANSACTIONS mmt,
apps.mtl_system_items_b msi
where mmt.organization_id = '{$org_id}'
and mmt.TRANSACTION_TYPE_ID IN ( '44' )
and mmt.organization_id = msi.organization_id
and mmt.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and mmt.TRANSACTION_DATE >= TRUNC (SYSDATE,'IW') and mmt.TRANSACTION_DATE <= TRUNC (SYSDATE + 84,'IW') 
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION,msi.ITEM_TYPE, 'Production', msi.planner_code,    TRUNC (mmt.TRANSACTION_DATE, 'IW')

UNION

SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mmt.PRIMARY_QUANTITY) as Quantity, 'Actual_Shipment' as DOC_TYPE ,
msi.planner_code,  
(to_number(to_char(to_date(TRUNC (mmt.TRANSACTION_DATE + 1 , 'IW')),'IW')) - to_number(to_char(to_date(TRUNC (SYSDATE, 'IW')),'IW'))) + 1 as WEEK
from 
apps.MTL_MATERIAL_TRANSACTIONS mmt,
apps.mtl_system_items_b msi
where mmt.organization_id = '{$org_id}'
and mmt.TRANSACTION_TYPE_ID IN ( '33' , '62')
and mmt.organization_id = msi.organization_id
and mmt.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and msi.item_type IN ('SA','FG','COM')
and mmt.TRANSACTION_DATE >= TRUNC (SYSDATE,'IW')-1 and mmt.TRANSACTION_DATE <= TRUNC (SYSDATE + 84,'IW') 
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE, 'Actual_Shipment', msi.planner_code,  TRUNC (mmt.TRANSACTION_DATE + 1, 'IW')

UNION

SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mst.schedule_quantity) as current_quantity, replace(mst.SCHEDULE_ORIGINATION_TEXT,' ','_') as DOC_TYPE, 
msi.planner_code, 
(to_number(to_char(to_date(TRUNC (mst.schedule_date, 'IW')),'IW')) - to_number(to_char(to_date(TRUNC (SYSDATE, 'IW')),'IW'))) + 1 as WEEK
from 
apps.MRP_SCHEDULE_ITEM_DATES_V  mst,
apps.mtl_system_items_b msi
where mst.organization_id = '{$org_id}'
and mst.organization_id = msi.organization_id
and mst.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and msi.item_type IN ('SA','FG','COM')
and mst.schedule_date >= TRUNC (SYSDATE,'IW') and mst.schedule_date <= TRUNC (SYSDATE + 84,'IW') 
 and mst.SCHEDULE_DESIGNATOR = 'SPG_MDS'
 and mst.SCHEDULE_LEVEL = '2'
 and mst.SCHEDULE_ORIGINATION_TEXT LIKE '%Sales%order%'
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE, replace(mst.SCHEDULE_ORIGINATION_TEXT,' ','_') , msi.planner_code, TRUNC (mst.schedule_date, 'IW')

UNION

SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mst.schedule_quantity) as current_quantity, replace(mst.SCHEDULE_ORIGINATION_TEXT,' ','_') as DOC_TYPE, 
msi.planner_code, 1 as WEEK
from 
apps.MRP_SCHEDULE_ITEM_DATES_V  mst,
apps.mtl_system_items_b msi
where mst.organization_id = '{$org_id}'
and mst.organization_id = msi.organization_id
and mst.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and msi.item_type IN ('SA','FG','COM')
and mst.schedule_date >= TRUNC (SYSDATE,'IW') and mst.schedule_date <= TRUNC (SYSDATE + 84,'IW') 
 and mst.SCHEDULE_DESIGNATOR = 'SPG_MDS'
 and mst.SCHEDULE_LEVEL = '2'
 and mst.SCHEDULE_ORIGINATION_TEXT LIKE '%Forecast%'
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE, replace(mst.SCHEDULE_ORIGINATION_TEXT,' ','_') , msi.planner_code



UNION

SELECT oela.ordered_item,msi.DESCRIPTION, msi.ITEM_TYPE, sum(oela.ordered_quantity) as Quantity, 'Unscheduled' as DOC_TYPE ,
msi.planner_code,  1 as WEEK
FROM
apps.oe_order_lines_all oela,
apps.mtl_system_items_b msi
where oela.ship_from_org_id = '{$org_id}'
and schedule_ship_date >= to_date('01-JAN-2020', 'DD-MON-YY')
and oela.FLOW_STATUS_CODE = 'AWAITING_SHIPPING'
and msi.segment1 = oela.ordered_item 
and msi.organization_id = oela.ship_from_org_id 
and msi.planner_code =  '{$planner_code}'
GROUP BY oela.ordered_item,msi.DESCRIPTION, msi.ITEM_TYPE, msi.planner_code

UNION

SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity, 'Onhand' as DOC_TYPE ,msi.planner_code,  
1 as WEEK
from 
apps.MTL_ONHAND_QUANTITIES_DETAIL moq,
apps.mtl_system_items_b msi
where moq.organization_id = '{$org_id}'
and moq.organization_id = msi.organization_id
and moq.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE, 'Production', msi.planner_code,  TRUNC (SYSDATE, 'IW'), msi.organization_id
";

  $result = $dbOra->findBySql($sql);

  return $result;
 }

 public function fss($parameters) {
  global $dbOra;

  $organization_id = !empty($parameters['ORGANIZATION_ID']) ? $parameters['ORGANIZATION_ID'] : false;
  $planner_code = !empty($parameters['PLANNER_CODE']) ? $parameters['PLANNER_CODE'] : false;
  $item_number = !empty($parameters['ITEM_NUMBER']) ? $parameters['ITEM_NUMBER'] : false;
  $period_names = [];

  $result = $this->getRecords($organization_id, $planner_code);


  $headers = ['ITEM_NUMBER', 'DESCRIPTION', 'PLANNER_CODE', 'ITEM_TYPE', 'CHILD_FGI'];
  $onhand_count = 1;

  $so_date_a = [];
  $first_monday = strtoupper(date("d-M-y", strtotime('monday this week')));
  $so_date = new DateTime($first_monday);
  for ($day = 0; $day <= 11; $day++) {
   $date_k = strtoupper($so_date->format("d-M-y"));
   $date_v = strtoupper($so_date->format("d-M"));
   $so_date_a[$date_k] = $date_v;
   $so_date->add(new DateInterval('P1D'));
  }

  for ($column_h = 1; $column_h <= 12; $column_h++) {
   array_push($period_names, 'Week_' . $column_h);
   if ($onhand_count == 1) {
    array_push($headers, 'L_Overdue_WO_5' );
    array_push($headers, 'Overdue_WO_4' );
    array_push($headers, 'Overdue_WO_3');
    array_push($headers, 'Overdue_WO_2');
    array_push($headers, 'Overdue_WO_1');
    array_push($headers, 'Quick Ship' . $column_h);
    array_push($headers, 'Onhand_' . $column_h);
    array_push($headers, 'Forecast_' . $column_h);
    array_push($headers, 'Unscheduled_' . $column_h);
    foreach ($so_date_a as $so_date_a_k => $so_date_a_v) {
     array_push($headers, $so_date_a_v);
    }
   }

   array_push($headers, 'Sales_order_' . $column_h);
   if ($column_h == 1) {
    //period is current
    array_push($headers, 'Actual_Shipment_' . $column_h);
    array_push($headers, 'Production_' . $column_h);
   }
   array_push($headers, 'Scheduled_WO_' . $column_h);
   if (in_array($column_h, [1, 2, 3, 4, 5, 6,  12])) {
    array_push($headers, 'Excess_' . $column_h);
   }


   $onhand_count++;
  }


  $headers_print = [];
  foreach ($headers as $key_h => $val_h) {
   if (strpos($val_h, 'Onhand') !== false) {
    $val_h = 'Onhand';
   } else if (strpos($val_h, 'Actual_Shipment') !== false) {
    $val_h = str_replace('Actual_Shipment', 'Shipped', $val_h);
   } else if (strpos($val_h, 'Sales_order') !== false) {
    $val_h = str_replace('Sales_order', 'SO', $val_h);
   } else if (strpos($val_h, 'Original_Forecast') !== false) {
    $val_h = str_replace('Original_Forecast', 'Orig FCST', $val_h);
   } else if (strpos($val_h, 'Forecast') !== false) {
    $val_h = str_replace('Forecast', 'FCST', $val_h);
   }if (strpos($val_h, 'Scheduled_WO') !== false) {
    $val_h = str_replace('Scheduled_WO', 'WIP', $val_h);
   }if (strpos($val_h, 'Production') !== false) {
    $val_h = str_replace('Production', 'Act_Prod', $val_h);
   }
   $val_h = ucwords(str_replace('_', ' ', $val_h));
   array_push($headers_print, $val_h);
  }


  $final_report = [];
  $all_assemblies = [];

  usort($result, "ino_sort_cmp_itemDescription");

  foreach ($result as &$obj) {
   if (!in_array($obj->ITEM_NUMBER, $all_assemblies)) {
    array_push($all_assemblies, $obj->ITEM_NUMBER);
   }
  }

  foreach ($result as $obj) {
   if (!in_array($obj->ITEM_NUMBER, $all_assemblies)) {
    array_push($all_assemblies, $obj->ITEM_NUMBER);
   }
  }
  array_push($final_report, $headers);
// pa($all_assemblies);
  foreach ($all_assemblies as $key => $item) {
   $count = 0;
   $row = [];

   foreach ($result as $obj) {
    if ($item == $obj->ITEM_NUMBER) {
     $count ++;
     if ($count == 1) {
      $row['ITEM_NUMBER'] = $obj->ITEM_NUMBER;
      $row['DESCRIPTION'] = $obj->DESCRIPTION;
      $row['ITEM_TYPE'] = $obj->ITEM_TYPE;
      $row['PLANNER_CODE'] = $obj->PLANNER_CODE;
      $child_fgi = $this->getCHildFGI($obj->ITEM_NUMBER, $organization_id, $planner_code);
      if ($child_fgi) {
       $con_component_numbers = '';
       $count_sep = 1;
       foreach ($child_fgi as $row_c) {
        if ($count_sep > 1) {
         $con_component_numbers .= ' | ';
        }
        $con_component_numbers .=!empty($row_c->COMPONENT_NUMBER) ? $row_c->COMPONENT_NUMBER : '';
        $count_sep++;
       }
       $row['CHILD_FGI'] = $con_component_numbers;
      } else {
       $row['CHILD_FGI'] = $obj->ITEM_NUMBER;
      }
     }
//           pa($obj);
     $week_doc_type = trim($obj->DOC_TYPE) . '_' . trim($obj->WEEK);
     $row[$week_doc_type] = $obj->QUANTITY;
    }
   }
   array_push($final_report, $row);
  }


  $final_formated_report = [];

  array_push($final_formated_report, $headers_print);
  foreach ($final_report as $key_a => $arr) {
   if ($key_a == 0) {
    continue;
   }
   $row = [];
   foreach ($headers as $h_k => $h_v) {
    if (empty($arr[$h_v])) {
     $row[$h_v] = null;
    } else {
     $row[$h_v] = $arr[$h_v];
    }
   }
   array_push($final_formated_report, $row);
  }

  foreach ($final_formated_report as $k => &$final_report_a) {
   $excess_1 = $excess_2 = $excess_3 = $excess_4 = $excess_5 = $excess_6 = 0;
   if ($k == 0) {
    continue;
   }
   $cumm_excess = 0;
   for ($excess_i = 1; $excess_i <= 6; $excess_i ++) {
    $cnt1_i = $excess_i;
    $excess_count = 'excess_' . $cnt1_i;
    $excess_i_Onhand = 'Onhand_' . $excess_i;
    $excess_i_Scheduled_WO = 'Scheduled_WO_' . $excess_i;
    $excess_i_sales_order = 'Sales_order_' . $excess_i;
    if (array_key_exists($excess_i_Onhand, $final_report_a)) {
     $$excess_count += $final_report_a[$excess_i_Onhand];
    }
    if (array_key_exists($excess_i_Scheduled_WO, $final_report_a)) {
     $$excess_count += $final_report_a[$excess_i_Scheduled_WO];
    }
    if (array_key_exists($excess_i_sales_order, $final_report_a)) {
     $$excess_count -= $final_report_a[$excess_i_sales_order];
    }
   }

   $excess_12 = $excess_6;
   for ($excess_i = 7; $excess_i <= 12; $excess_i ++) {
    $excess_i_Onhand = 'Onhand_' . $excess_i;
    $excess_i_Scheduled_WO = 'Scheduled_WO_' . $excess_i;
    $excess_i_sales_order = 'Sales_order_' . $excess_i;
    if (array_key_exists($excess_i_Onhand, $final_report_a)) {
     $excess_12 += $final_report_a[$excess_i_Onhand];
    }
    if (array_key_exists($excess_i_Scheduled_WO, $final_report_a)) {
     $excess_12 += $final_report_a[$excess_i_Scheduled_WO];
    }
    if (array_key_exists($excess_i_sales_order, $final_report_a)) {
     $excess_12 -= $final_report_a[$excess_i_sales_order];
    }
   }
   $cumm_excess += $excess_1;
   $final_report_a['Excess_1'] = $excess_1;
   $cumm_excess += $excess_2;
   $final_report_a['Excess_2'] = $cumm_excess;
   $cumm_excess += $excess_3;
   $final_report_a['Excess_3'] = $cumm_excess;
   $cumm_excess += $excess_4;
   $final_report_a['Excess_4'] = $cumm_excess;
   $cumm_excess += $excess_5;
   $final_report_a['Excess_5'] = $cumm_excess;
   $cumm_excess += $excess_6;
   $final_report_a['Excess_6'] = $cumm_excess;
//   $final_report_a['Excess_7'] = $excess_7;
   $final_report_a['Excess_12'] = $excess_12;

   //add the sales order
   $sales_demand = $this->getSOByDate($organization_id, $final_report_a['ITEM_NUMBER'], $planner_code);
   if ($sales_demand) {
//    pa($sales_demand);
//    pa($so_date_a);asada();
    foreach ($sales_demand as $sales_demand_k => $sales_demand_v) {
     foreach ($so_date_a as $so_date_a_k => $so_date_a_v) {
      if ($sales_demand_v->SSD == $so_date_a_k) {
       $final_report_a[$so_date_a_v] = $sales_demand_v->QUANTITY;
      }
     }
    }
   }
  }
//  pa($final_formated_report);
//  sdsd();
//  array_shift($final_formated_report);
  return $final_formated_report;
 }

}

//end of bom class
?>