<?php

class cst_bom_cost extends dbOraObject {

 public static $table_name = "cst_bom_cost";
 public static $primary_column = "cst_bom_cost_id";
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
  "include_all_items_in_cst_bom_cost",
  'validate_in_new_org'
 ];
 public $generate_bom_cost_parameters = [
  'Organization' => 'search_org_name',
  'List Of Items' => 'search_list_of_items',
  'Start Date' => 'search_start_date',
  'End Date' => 'search_end_date',
  'Include Purchsed FG' => 'search_include_purcehaseFG_cb',
  'Rate for PO' => 'search_exchange_rate',
 ];
 public $generate_bom_cost_details = [
  'name' => 'Generate BOM Cost',
  'description' => 'Generate BOM Cost',
 ];
 public $cst_bom_cost_id;
 public $PLANNER_CODE;
 public $ORGANIZATION_ID;
 public $include_all_items_in_cst_bom_cost;
 public $validate_in_new_org;
 public $exchange_rate;
 public $nclude_purcehaseFG_cb;

 public function __set($name, $value) {
  switch ($value) {
   case $value:


    break;

   default:
    $this->$name = $value;
    break;
  }
 }

 public function find_po_cost_details($organization_id, $inventory_item_id, $start_date, $end_date) {
  global $dbOra;
  $sql = "SELECT msi.segment1 as ITEM_NUMBER, SUM(cid.transaction_quantity) As Quantity, SUM(BASE_TRANSACTION_VALUE) As Value,
      ROUND(SUM(BASE_TRANSACTION_VALUE)/SUM(cid.transaction_quantity), 5) As PO_UNIT_PRICE, cic.material_cost,
      mtc.SEGMENT2 As COMMODITY

      FROM 
      apps.mtl_system_items_b msi,
      apps.CST_INV_DISTRIBUTION_V  cid,
      apps.CST_ITEM_COST_TYPE_V  cic,
      apps.MTL_ITEM_CATEGORIES_V mtc

      WHERE msi.organization_id = '{$organization_id}'
      and cid.TRANSACTION_TYPE_ID IN ('18', '61')
      and msi.organization_id = cid.organization_id
      and msi.inventory_item_id = cid.inventory_item_id
      and cid.transaction_date >= to_date('{$start_date}', 'YY-MM-DD') and cid.transaction_date <= to_date('{$end_date}', 'YY-MM-DD')
      AND cid.ACCOUNTING_LINE_TYPE IN ('14', '5')
      AND cic.inventory_item_id = msi.inventory_item_id 
      AND cic.organization_id = msi.organization_id 
      and cic.cost_type_id = 1
      AND msi.inventory_item_id = '{$inventory_item_id}'
       AND mtc.organization_id (+)= msi.organization_id 
      AND mtc.category_set_name (+)= 'Sourcing Commodity'
      AND mtc.inventory_item_id (+)= msi.inventory_item_id
      GROUP BY msi.segment1 ,  cic.material_cost ,mtc.SEGMENT2
";

  $result = $dbOra->findBySql($sql);

//        AND cid.ACCOUNTING_LINE_TYPE IN ('14', '5') is remove and replaced by AND cid.ACCOUNTING_LINE_TYPE = '5'
  if (empty($result)) {
   $sql1 = "     SELECT * FROM 
     (
      SELECT msi.segment1 as ITEM_NUMBER, (cid.transaction_quantity) As Quantity, (BASE_TRANSACTION_VALUE) As Value,
        ROUND((cid.BASE_TRANSACTION_VALUE)/(cid.transaction_quantity), 5) As PO_UNIT_PRICE, cic.material_cost,
        mtc.SEGMENT2 As COMMODITY

        FROM apps.mtl_system_items_b msi, 
        apps.CST_INV_DISTRIBUTION_V cid, 
        apps.CST_ITEM_COST_TYPE_V cic,
        apps.MTL_ITEM_CATEGORIES_V mtc

        WHERE msi.organization_id = '{$organization_id}'
        and cid.TRANSACTION_TYPE_ID IN ('18', '61') 
        and msi.organization_id = cid.organization_id 
        and msi.inventory_item_id = cid.inventory_item_id 
        AND cid.ACCOUNTING_LINE_TYPE IN('14', '5')
        AND cic.inventory_item_id = msi.inventory_item_id 
        AND cic.organization_id = msi.organization_id 
        and cic.cost_type_id = 1 
        AND msi.inventory_item_id =  '{$inventory_item_id}'
         AND mtc.organization_id (+)= msi.organization_id 
       AND mtc.category_set_name (+)= 'Sourcing Commodity'
       AND mtc.inventory_item_id (+)= msi.inventory_item_id
       ORDER BY cid.transaction_date DESC
       )
       WHERE ROWNUM = 1";
   $result = $dbOra->findBySql($sql1);
  }


  if (empty($result)) {
   $sql1 = "     SELECT * FROM 
     (
      SELECT msi.segment1 as ITEM_NUMBER, 0 As Quantity, 0 As Value, 0 As PO_UNIT_PRICE, cic.material_cost,
        mtc.SEGMENT2 As COMMODITY

        FROM apps.mtl_system_items_b msi, 
        apps.CST_ITEM_COST_TYPE_V cic,
        apps.MTL_ITEM_CATEGORIES_V mtc

        WHERE msi.organization_id = '{$organization_id}'
        AND cic.inventory_item_id = msi.inventory_item_id 
        AND cic.organization_id = msi.organization_id 
        and cic.cost_type_id = 1 
        AND msi.inventory_item_id =  '{$inventory_item_id}'
         AND mtc.organization_id (+)= msi.organization_id 
       AND mtc.category_set_name (+)= 'Sourcing Commodity'
       AND mtc.inventory_item_id (+)= msi.inventory_item_id
              )
       WHERE ROWNUM = 1";
   $result = $dbOra->findBySql($sql1);
  }

  //add one more sql to get only the cost details if there has been no PO receipts for that item
  return !empty($result) ? array_pop($result) : false;
 }

 public function generate_bom_cost($parameters) {
  global $dbOra;
  $organization_id = !empty($parameters['ORGANIZATION_ID']) ? $parameters['ORGANIZATION_ID'] : false;
  $planner_code = !empty($parameters['PLANNER_CODE']) ? $parameters['PLANNER_CODE'] : false;
  $item_number = !empty($parameters['ITEM_NUMBER']) ? $parameters['ITEM_NUMBER'] : false;
  $start_date = !empty($parameters['start_date'][0]) ? $parameters['start_date'][0] : current_time(1);
  $end_date = !empty($parameters['end_date'][0]) ? $parameters['end_date'][0] : current_time(1);
  $exchange_rate = !empty($parameters['exchange_rate'][0]) ? $parameters['exchange_rate'][0] : 1;
  $purchase_FG_cb = !empty($parameters['include_purcehaseFG_cb'][0]) ? $parameters['include_purcehaseFG_cb'][0] : 0;


  if ($purchase_FG_cb) {
   $item_type_a = ['P', 'INU', 'PFG'];
  } else {
   $item_type_a = ['P', 'INU'];
  }

  $bom = new bom();
  $bom->use_purchase_as_fg = 1;
  if (!empty($item_number)) {
   $item_number_a = explode(',', $item_number);
   $all_items = $bom->all_items_for_IB($organization_id, $item_number_a);
  }
  $bom->super_bom_details = 1;
  $result = $bom->superBOM($all_items, $organization_id);

  $supercst_bom_cost_a = [];

  $row_fgi = ['Component', 'Description', 'Type', 'Planner', 'COMMODITY',
   'QUANTITY', 'VALUE', 'UNIT_PO_PRICE', 'UNIT_PO_PRICE_LOC', 'UNIT_MATERIAL_COST'];

  $row_fgi_assembly_only = [];
  $row_fgi_assembly_header = [];
  foreach ($result as $data) {
   if (($data->PARENT_ITEM_TYPE == 'FG' || $data->PARENT_ITEM_TYPE == 'SA') && (!(in_array($data->ASSEMBLY, $row_fgi_assembly_only)))) {
    array_push($row_fgi_assembly_only, $data->ASSEMBLY);
    array_push($row_fgi_assembly_only, 'PO_PRICE');
    array_push($row_fgi_assembly_only, 'MATERIAL_COST');
   }
  }
  $row_fgi = array_merge($row_fgi, $row_fgi_assembly_only);
  array_push($supercst_bom_cost_a, $row_fgi);
//   array_push($supercst_bom_cost_a, $row_fgi_d);

  /* Data */
  $i = 0;
  $row_data_component = [];

  foreach ($result as $data_c) {
   $row_data = [];
   if (!in_array($data_c->COMPONENT_NUMBER, $row_fgi_assembly_only)) {
    if (!in_array($data_c->ITEM_TYPE, $item_type_a)) {
     continue;
    }
    $row_data = [];
//     pa($data_c);
    $key = array_search($data_c->COMPONENT_NUMBER, $row_data_component);
    if ($key) {
     $com_number = $row_data_component[$key];
     array_push($row_data, $data_c->COMPONENT_NUMBER);
     array_push($row_data, $data_c->DESCRIPTION);
     array_push($row_data, $data_c->ITEM_TYPE);
     array_push($row_data, $data_c->PLANNER_CODE);
     $element_num = 5;
     foreach ($row_fgi_assembly_only as $key => $val) {
      if ($val == $data_c->ASSEMBLY) {
       $po_cost_details = $this->find_po_cost_details($organization_id, $data_c->COMPONENT_ITEM_ID, $start_date, $end_date);
       if ($po_cost_details) {
        if (isset($po_cost_details->COMMODITY)) {
         array_push($row_data, $po_cost_details->COMMODITY);
        } else {
         array_push($row_data, null);
        }
        array_push($row_data, $data_c->QUANTITY + $supercst_bom_cost_a[$com_number][$element_num]);
        $element_num++;
        array_push($row_data, abs($po_cost_details->VALUE) + $supercst_bom_cost_a[$com_number][$element_num]);
        array_push($row_data, abs($po_cost_details->PO_UNIT_PRICE));
        array_push($row_data, abs($po_cost_details->PO_UNIT_PRICE) * $exchange_rate);
        array_push($row_data, $po_cost_details->MATERIAL_COST);
        $element_num += 4;
        $data_c->QUANTITY += $supercst_bom_cost_a[$com_number][$element_num];
        array_push($row_data, $data_c->QUANTITY);
       } else {
        for ($k1 = 0; $k1 <= 6; $k1++) {
         array_push($row_data, null);
        }
       }
      }
     }
//      echo "<br>com_number is  $com_number ";
//    pa($supercst_bom_cost_a[$com_number]);
     unset($supercst_bom_cost_a[$com_number]);
    } else {
     array_push($row_data_component, $data_c->COMPONENT_NUMBER);
     array_push($row_data, $data_c->COMPONENT_NUMBER);
     array_push($row_data, $data_c->DESCRIPTION);
     array_push($row_data, $data_c->ITEM_TYPE);
     array_push($row_data, $data_c->PLANNER_CODE);
     $po_cost_details = $this->find_po_cost_details($organization_id, $data_c->COMPONENT_ITEM_ID, $start_date, $end_date);
     if ($po_cost_details) {
      if (isset($po_cost_details->COMMODITY)) {
       array_push($row_data, $po_cost_details->COMMODITY);
      } else {
       array_push($row_data, null);
      }
      array_push($row_data, $po_cost_details->QUANTITY);
      array_push($row_data, abs($po_cost_details->VALUE));
      array_push($row_data, abs($po_cost_details->PO_UNIT_PRICE));
      array_push($row_data, abs($po_cost_details->PO_UNIT_PRICE) * $exchange_rate);
      array_push($row_data, $po_cost_details->MATERIAL_COST);
      array_push($row_data, $data_c->QUANTITY);
     } else {
      for ($i1 = 0; $i1 <= 6; $i1++) {
       array_push($row_data, null);
      }
     }
    }

    foreach ($row_fgi_assembly_only as $key => $val) {
     if ($val == $data_c->ASSEMBLY) {
      if (!empty($po_cost_details->PO_UNIT_PRICE)) {
       array_push($row_data, abs($po_cost_details->PO_UNIT_PRICE) * $exchange_rate * $data_c->QUANTITY);
      } else {
       array_push($row_data, 0);
      }
      if (!empty($po_cost_details->MATERIAL_COST)) {
       array_push($row_data, $po_cost_details->MATERIAL_COST * $data_c->QUANTITY);
      } else {
       array_push($row_data, 0);
      }
     }
    }
    $supercst_bom_cost_a[$data_c->COMPONENT_NUMBER] = $row_data;
   }
  }

  return $supercst_bom_cost_a;
 }

}

//end of cst_bom_cost class
?>