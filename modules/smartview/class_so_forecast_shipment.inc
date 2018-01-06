<?php

class so_forecast_shipment extends dbOraObject {

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
  'Period Name' => 'search_period_type_m',
  'Download in text mode' => 'search_download_as_text',
 ];
 public $fss_details = [
  'name' => 'Forecast , SO & Shipment Report ',
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

 public $created_by;
 public $creation_date;

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

 function getRecords($org_id = '2989', $planner_code = 'OBIS', $period_name) {
  global $dbOra;
  $sql = "
    
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(wdj.QUANTITY_REMAINING) as Quantity, 'Scheduled_WO' as DOC_TYPE ,msi.planner_code,  gp.period_name  as MONTH
from 
apps.WIP_DISCRETE_JOBS_V wdj,
apps.mtl_system_items_b msi,
apps.GL_PERIODS_v gp
where wdj.organization_id = '{$org_id}'
and wdj.status_type IN ( '3' )
and wdj.organization_id = msi.organization_id
and wdj.primary_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and wdj.SCHEDULED_COMPLETION_DATE >= gp.START_DATE and wdj.SCHEDULED_COMPLETION_DATE <= gp.END_DATE 
and gp.period_name = '{$period_name}'
and gp.period_set_name = 'COHR Calendar'
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE,'Scheduled_WO', msi.planner_code,  gp.period_name
 
UNION
 
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mmt.PRIMARY_QUANTITY) as Quantity, 'Return' as DOC_TYPE ,msi.planner_code,  gp.period_name  as MONTH
from 
apps.MTL_MATERIAL_TRANSACTIONS mmt,
apps.mtl_system_items_b msi,
apps.GL_PERIODS_v gp
where mmt.organization_id = '{$org_id}'
and mmt.TRANSACTION_TYPE_ID IN ( '15' )
and mmt.organization_id = msi.organization_id
and mmt.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and mmt.TRANSACTION_DATE >= gp.START_DATE and mmt.TRANSACTION_DATE <= gp.END_DATE 
and gp.period_name = '{$period_name}'
 and gp.period_set_name = 'COHR Calendar'
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE,'Return', msi.planner_code,  gp.period_name

UNION
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mmt.PRIMARY_QUANTITY) as Quantity, 'Production' as DOC_TYPE ,msi.planner_code,  gp.period_name  as MONTH
from 
apps.MTL_MATERIAL_TRANSACTIONS mmt,
apps.mtl_system_items_b msi,
apps.GL_PERIODS_v gp
where mmt.organization_id = '{$org_id}'
and mmt.TRANSACTION_TYPE_ID IN ( '44' )
and mmt.organization_id = msi.organization_id
and mmt.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and mmt.TRANSACTION_DATE >= gp.START_DATE and mmt.TRANSACTION_DATE <= gp.END_DATE 
and gp.period_name = '{$period_name}'
 and gp.period_set_name = 'COHR Calendar'
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION,msi.ITEM_TYPE, 'Production', msi.planner_code,   gp.period_name

UNION

SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mmt.PRIMARY_QUANTITY) as Quantity, 'Actual_Shipment' as DOC_TYPE ,msi.planner_code,  gp.period_name  as MONTH
from 
apps.MTL_MATERIAL_TRANSACTIONS mmt,
apps.mtl_system_items_b msi,
apps.GL_PERIODS_v gp
where mmt.organization_id = '{$org_id}'
and mmt.TRANSACTION_TYPE_ID IN ( '33' , '62')
and mmt.organization_id = msi.organization_id
and mmt.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and msi.item_type IN ('SA','FG','COM')
and mmt.TRANSACTION_DATE >= gp.START_DATE and mmt.TRANSACTION_DATE <= gp.END_DATE 
and gp.period_name = '{$period_name}'
 and gp.period_set_name = 'COHR Calendar'
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE, 'Actual_Shipment', msi.planner_code,  gp.period_name

UNION


SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mst.schedule_quantity) as current_quantity, replace(mst.SCHEDULE_ORIGINATION_TEXT,' ','_') as DOC_TYPE, msi.planner_code,   gp.period_name  as MONTH
from 
apps.MRP_SCHEDULE_ITEM_DATES_V  mst,
apps.mtl_system_items_b msi,
apps.GL_PERIODS_v gp
where mst.organization_id = '{$org_id}'
and mst.organization_id = msi.organization_id
and mst.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and msi.item_type IN ('SA','FG','COM')
and mst.schedule_date >= gp.START_DATE and mst.schedule_date <= gp.END_DATE 
and gp.period_name = '{$period_name}'
 and gp.period_set_name = 'COHR Calendar'
 and mst.SCHEDULE_DESIGNATOR = 'SPG_MDS'
 and mst.SCHEDULE_LEVEL = '2'
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE, replace(mst.SCHEDULE_ORIGINATION_TEXT,' ','_') , msi.planner_code,  gp.period_name

UNION

SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(mst.original_quantity) as original_quantity,  'Original_Forecast' as DOC_TYPE , msi.planner_code,   gp.period_name  as MONTH
from 
apps.MRP_SCHEDULE_ITEM_DATES_V  mst,
apps.mtl_system_items_b msi,
apps.GL_PERIODS_v gp
where mst.organization_id = '{$org_id}'
and mst.organization_id = msi.organization_id
and mst.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and msi.item_type IN ('SA','FG','COM')
and mst.schedule_date >= gp.START_DATE and mst.schedule_date <= gp.END_DATE 
and gp.period_name = '{$period_name}'
 and gp.period_set_name = 'COHR Calendar'
 and mst.SCHEDULE_DESIGNATOR = 'SPG_MDS'
 and mst.SCHEDULE_LEVEL = '2'
 and mst.SCHEDULE_ORIGINATION_TEXT = 'Forecast'
GROUP BY msi.SEGMENT1, msi.DESCRIPTION,msi.ITEM_TYPE, replace(mst.SCHEDULE_ORIGINATION_TEXT,' ','_') , msi.planner_code,  gp.period_name

UNION


SELECT  
msi.SEGMENT1 as ITEM_NUMBER, msi.DESCRIPTION, msi.ITEM_TYPE, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity, 'Onhand' as DOC_TYPE ,msi.planner_code,  gp.period_name  as MONTH
from 
apps.MTL_ONHAND_QUANTITIES_DETAIL moq,
apps.mtl_system_items_b msi,
apps.GL_PERIODS_v gp
where moq.organization_id = '{$org_id}'
and moq.organization_id = msi.organization_id
and moq.inventory_item_id = msi.inventory_item_id
and msi.planner_code =  '{$planner_code}'
and gp.period_name = '{$period_name}'
 and gp.period_set_name = 'COHR Calendar'
and msi.item_type IN ('SA','FG','COM')
GROUP BY msi.SEGMENT1, msi.DESCRIPTION, msi.ITEM_TYPE, 'Production', msi.planner_code,  gp.period_name, msi.organization_id
";

  $result = $dbOra->findBySql($sql);
  return $result;
 }

 public function fss($parameters) {
  global $dbOra;

  $organization_id = !empty($parameters['ORGANIZATION_ID']) ? $parameters['ORGANIZATION_ID'] : false;
  $planner_code = !empty($parameters['PLANNER_CODE']) ? $parameters['PLANNER_CODE'] : false;
  $item_number = !empty($parameters['ITEM_NUMBER']) ? $parameters['ITEM_NUMBER'] : false;
  $period_names = !empty($parameters['PERIOD_NAME']) ? $parameters['PERIOD_NAME'] : array('AUG-14', 'SEP-14', 'OCT-15', 'NOV-15', 'DEC-15');

  $result = [];

  $headers = ['ITEM_NUMBER', 'DESCRIPTION', 'PLANNER_CODE', 'ITEM_TYPE', 'CHILD_FGI'];
  $onhand_count = 1;
  $no_of_periods = count($period_names);

  foreach ($period_names as $key => $period) {
   $result_period = $this->getRecords($organization_id, $planner_code, $period);
   $result = array_merge($result, $result_period);
   if ($onhand_count == 1) {
    array_push($headers, $period . '_Onhand');
   }
   $period_a = explode('-', $period);
   $period_n = $period_a[0];
   $period_y = $period_a[1];
   if (in_array($period_n, array('OCT', 'NOV', 'DEC'))) {
    $period_y = $period_y - 1;
   }
   $date = new DateTime();
   $period_date = new DateTime("01-$period_n-$period_y");
   $interval = $period_date->diff($date);

   array_push($headers, $period . '_Sales_order');
   if ($interval->invert == 0 && $interval->days < 30) {
    //period is current
    array_push($headers, $period . '_Forecast');
    array_push($headers, $period . '_Actual_Shipment');
    array_push($headers, $period . '_Production');
   } else if ($interval->invert == 1) {
    //period is future
    array_push($headers, $period . '_Forecast');
   } else {
    array_push($headers, $period . '_Actual_Shipment');
    array_push($headers, $period . '_Production');
   }


//    array_push($headers, $period . '_Original_Forecast');
   array_push($headers, $period . '_Scheduled_WO');
//    array_push($headers, $period . '_Return');

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
     $month_doc_type = trim($obj->MONTH) . '_' . trim($obj->DOC_TYPE);
     $row[$month_doc_type] = $obj->QUANTITY;
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
  return $final_formated_report;
 }

}

//end of bom class
?>