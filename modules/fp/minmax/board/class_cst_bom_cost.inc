<?php

 class cst_bom_cost11 extends dbOraObject {

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
mtc.CATEGORY_CONCAT_SEGS As COMMODITY

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
GROUP BY msi.segment1 ,  cic.material_cost ,mtc.CATEGORY_CONCAT_SEGS
";
   $result = $dbOra->findBySql($sql);

   if (empty($result)) {
    $sql1 = "SELECT msi.segment1 as ITEM_NUMBER, SUM(cid.transaction_quantity) As Quantity, SUM(BASE_TRANSACTION_VALUE) As Value,
        ROUND(SUM(cid.BASE_TRANSACTION_VALUE)/SUM(cid.transaction_quantity), 5) As PO_UNIT_PRICE, cic.material_cost,
        mtc.CATEGORY_CONCAT_SEGS As COMMODITY

        FROM apps.mtl_system_items_b msi, 
        apps.CST_INV_DISTRIBUTION_V cid, 
        apps.CST_ITEM_COST_TYPE_V cic,
        apps.MTL_ITEM_CATEGORIES_V mtc

        WHERE msi.organization_id = '{$organization_id}'
        and cid.TRANSACTION_TYPE_ID IN ('18', '61') 
        and msi.organization_id = cid.organization_id 
        and msi.inventory_item_id = cid.inventory_item_id 
        AND cid.ACCOUNTING_LINE_TYPE IN ('14', '5')
        AND cic.inventory_item_id = msi.inventory_item_id 
        AND cic.organization_id = msi.organization_id 
        and cic.cost_type_id = 1 
        AND msi.inventory_item_id =  '{$inventory_item_id}'
         AND mtc.organization_id (+)= msi.organization_id 
       AND mtc.category_set_name (+)= 'Sourcing Commodity'
       AND mtc.inventory_item_id (+)= msi.inventory_item_id
        AND ROWNUM <= 1
        GROUP BY msi.segment1 , cic.material_cost ,mtc.CATEGORY_CONCAT_SEGS
";
    $result = $dbOra->findBySql($sql1);
   }
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

   $bom = new bom();
   $bom->use_purchase_as_fg = 1;
   if (!empty($item_number)) {
    $item_number_a = explode(',', $item_number);
//    pa($item_number_a);
    $all_items = $bom->all_items_for_IB($organization_id, $item_number_a);
   }
   $bom->super_bom_details = 1;
   $result = $bom->superBOM($all_items, $organization_id);

   $supercst_bom_cost_a = [];
   /* FGI Description */
//   $row_fgi_d = [];
//   for ($i = 0; $i <= 8; $i++) {
//    array_push($row_fgi_d, null);
//   }


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
   $row_data_component = [];
   $i = 0;

   foreach ($result as $data_c) {
    $row_data = [];
    if (!in_array($data_c->COMPONENT_NUMBER, $row_fgi_assembly_only)) {
     if (!in_array($data_c->ITEM_TYPE, array('P', 'INU'))) {
      continue;
     }
     $row_data = [];
     $key = array_search($data_c->COMPONENT_NUMBER, $row_data_component);
     echo "<br> Component is $data_c->COMPONENT_NUMBER & key is $key";
     if ($key) {
      $com_number = $row_data_component[$key];
      array_push($row_data, $data_c->COMPONENT_NUMBER);
      array_push($row_data, $data_c->DESCRIPTION);
      array_push($row_data, $data_c->ITEM_TYPE);
      array_push($row_data, $data_c->PLANNER_CODE);

      $element_num = 3;
      foreach ($row_fgi_assembly_only as $key => $val) {
       $element_num ++;
       if ($val == $data_c->ASSEMBLY) {
        $po_cost_details = $this->find_po_cost_details($organization_id, $data_c->COMPONENT_ITEM_ID, $start_date, $end_date);
        array_push($row_data, $po_cost_details->COMMODITY);
        $element_num ++;
        pa( $supercst_bom_cost_a[$com_number]); echo "<br> element_num is $element_num ". pa($data_c);
        array_push($row_data, $data_c->QUANTITY + $supercst_bom_cost_a[$com_number][$element_num]);
        array_push($row_data, abs($po_cost_details->PO_UNIT_PRICE) * $exchange_rate * $data_c->QUANTITY);
        array_push($row_data, $po_cost_details->MATERIAL_COST * $data_c->QUANTITY);
       } else {
        array_push($row_data, $supercst_bom_cost_a[$com_number][$element_num]);
       }
      }
      unset($supercst_bom_cost_a[$com_number]);
     } else {
      array_push($row_data_component, $data_c->COMPONENT_NUMBER);
      array_push($row_data, $data_c->COMPONENT_NUMBER);
      array_push($row_data, $data_c->DESCRIPTION);
      array_push($row_data, $data_c->ITEM_TYPE);
      array_push($row_data, $data_c->PLANNER_CODE);
      $po_cost_details = $this->find_po_cost_details($organization_id, $data_c->COMPONENT_ITEM_ID, $start_date, $end_date);
      if ($po_cost_details) {
       array_push($row_data, $po_cost_details->COMMODITY);
       array_push($row_data, $po_cost_details->QUANTITY);
       array_push($row_data, abs($po_cost_details->VALUE));
       array_push($row_data, abs($po_cost_details->PO_UNIT_PRICE));
       array_push($row_data, abs($po_cost_details->PO_UNIT_PRICE) * $exchange_rate);
       array_push($row_data, $po_cost_details->MATERIAL_COST);
      } else {
       for ($i1 = 0; $i1 <= 5; $i1++) {
        array_push($row_data, null);
       }
      }
//      if (!empty($this->validate_in_new_org)) {
//       $status_in_newOrg = $this->_item_type_in_new_org($data_c->COMPONENT_NUMBER, $this->validate_in_new_org);
//       array_push($row_data, $status_in_newOrg);
//      }
     }

     foreach ($row_fgi_assembly_only as $key => $val) {
      if ($val == $data_c->ASSEMBLY) {
       $key1 = array_search($data_c->COMPONENT_NUMBER, $row_data_component);
       array_push($row_data, $data_c->QUANTITY);
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
      } else {
       array_push($row_data, null);
      }
     }

     $supercst_bom_cost_a[$data_c->COMPONENT_NUMBER] = $row_data;
    }
   }
//pa($result);
//dssd();
   return $supercst_bom_cost_a;
  }

 }

//end of cst_bom_cost class
?>