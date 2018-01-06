<?php

 class bom extends dbOraObject {

  public static $table_name = "bom";
  public static $primary_column = "bom_id";
     public static $system_info = [
  'name' => 'Super BOM',
  'number' => '8105',
  'description' => 'Super BOM',
  'version' => '1.1.1.3',
  'db_version' => '1001',
  'mod_version' => '1.1.x-1.1',
  'primary_entity_cb' => '',
  'module_name' => 'bom',
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
  public $super_bom_parameters = [
   'Organization' => 'search_org_name',
   'Planner Code' => 'search_planner_code',
   'List Of Items' => 'search_list_of_items',
   'Use Sub Assembly as FG' => 'search_use_sa_as_fg',
   'Include Details' => 'search_include_details',
   'Item Number From' => 'search_item_number_from',
   'Item Number To' => 'search_item_number_to',
  ];
  public $super_bom_details = [
   'name' => 'Generate Super BOM',
   'description' => 'Roll up cost for pending or user defiled cost types',
  ];
  public $bom_id;
  public $PLANNER_CODE;
  public $ORGANIZATION_ID;
  public $include_all_items_in_bom;
  public $validate_in_new_org;
  public $_use_sa_as_fg;
  public $use_purchase_as_fg;

  public function __set($name, $value) {
   switch ($value) {
    case $value:


     break;

    default:
     $this->$name = $value;
     break;
   }
  }

  function getBOM($item_id, $org_id = '2989', $usage = '1') {
   global $dbOra;
   $sql = "
	SELECT DISTINCT( bbc.bill_item_name || '|' || bbc.component_item_name ),
 bbc.bill_item_name as Assembly, msi.description as Parent_Description,
msi.ITEM_TYPE Parent_Item_Type, msi.PLANNER_CODE Parent_Planner_code,
bbc.component_item_id Component_Item_Id,bbc.component_item_name as Component_Number,
msi_c.description as Description , bbc.quantity_per_assembly*$usage as Quantity, 
msi_c.item_type, msi_c.planner_code, bbc.organization_code,
 bbc.organization_id, bbc.assembly_item_id
from apps.bomfg_bom_components  bbc,
apps.mtl_system_items_b msi,
apps.mtl_system_items_b msi_c
where bbc.organization_id = 63
and bbc.assembly_item_id = '{$item_id}' ";
   if (!empty($this->include_all_items_in_bom) && ($this->include_all_items_in_bom == 1)) {
    $sql .= " ";
   } else {
    $sql .= " AND bbc.end_effective_date IS NULL ";
   }
   $sql .=" and msi_c.inventory_item_id = bbc.component_item_id
and msi_c.organization_id = '{$org_id}'
and msi.organization_id = '{$org_id}'
and msi.inventory_item_id = bbc.assembly_item_id

";

   $result = $dbOra->findBySql($sql);
   return $result;
  }

  function indentedBOM($item_id, $org_id, &$ib, $usage = 1, $assembly_number = '', $PARENT_DESCRIPTION = '') {
   $ib_i = $this->getBOM($item_id, $org_id, $usage);
   foreach ($ib_i as $records) {
    if (!empty($assembly_number)) {
     $records->ASSEMBLY = $assembly_number;
     $records->PARENT_DESCRIPTION = $PARENT_DESCRIPTION;
    }
    array_push($ib, $records);
    if (!empty($this->include_all_items_in_bom) && ($this->include_all_items_in_bom == 1)) {
     if ($records->ITEM_TYPE == 'SA' || $records->ITEM_TYPE == 'PF' ||
       $records->ITEM_TYPE == 'PH' || $records->ITEM_TYPE == 'FG' || $records->ITEM_TYPE == 'PFG') {
      $this->indentedBOM($records->COMPONENT_ITEM_ID, $org_id, $ib, $records->QUANTITY, $records->ASSEMBLY, $records->PARENT_DESCRIPTION);
     }
    } else {
     if ($records->ITEM_TYPE == 'SA' || $records->ITEM_TYPE == 'PF' ||
       $records->ITEM_TYPE == 'PH' || $records->ITEM_TYPE == 'FG') {
      $this->indentedBOM($records->COMPONENT_ITEM_ID, $org_id, $ib, $records->QUANTITY, $records->ASSEMBLY, $records->PARENT_DESCRIPTION);
     }
    }
//	 if ($records->ITEM_TYPE == 'SA' || $records->ITEM_TYPE == 'PF' ||
//					 $records->ITEM_TYPE == 'PH' || $records->ITEM_TYPE == 'FG') {
//		$this->indentedBOM($records->COMPONENT_ITEM_ID, $org_id, $ib, $records->QUANTITY, $records->ASSEMBLY, $records->PARENT_DESCRIPTION);
//	 }
   }
  }

  private function _item_type_in_new_org($segment1, $org_id) {
   $sql = " SELECT * FROM apps.mtl_system_items_b WHERE organization_id = '{$org_id}' AND segment1 = '{$segment1}' AND  ROWNUM < 2";
   $result = $this->findBySql($sql);
   return !empty($result) ? $result[0]->ITEM_TYPE : 'NOT ENLABLED';
  }

  function all_items_for_IB($org_id = '2989', $item_number_a = '', $planner_code = '') {
   global $dbOra;
   $sql = "
SELECT DISTINCT(segment1), inventory_item_id, description
from apps.mtl_system_items_b
WHERE organization_id = '{$org_id}' ";

   foreach ($item_number_a as $k1 => &$d1) {
    $d1 = trim($d1);
   }
   if (!empty($item_number_a)) {
    $in_array = '(\'' . implode('\', \'', $item_number_a) . '\')';
    $sql .= " AND SEGMENT1 IN $in_array ";
   } else {
    $sql .= " AND PLANNER_CODE = '{$planner_code}' ";
   }
   if ($this->use_purchase_as_fg) {
    $sql .= " AND ITEM_TYPE IN('FG' ,'SA' ,'P','PF') ";
   } else if ($this->_use_sa_as_fg) {
    $sql .= " AND ITEM_TYPE IN('FG' ,'SA') ";
   } else {
    $sql .= " AND ITEM_TYPE = 'FG' ";
   }
   $result = $dbOra->findBySql($sql);
   return $result;
  }

  function superBOM($all_items, $org_id) {
   $ib_final = [];

   foreach ($all_items as $items) {
    $ib = [];
    $this->indentedBOM($items->INVENTORY_ITEM_ID, $org_id, $ib, 1, $items->SEGMENT1, $items->DESCRIPTION);
    $ib_final = array_merge($ib, $ib_final);
   }
   return $ib_final;
  }

  public function find_other_details($organization_id, $inventory_item_id) {
   global $dbOra;
   $sql = "
SELECT  
msi.SEGMENT1 as ITEM_NUMBER, sum(moq.PRIMARY_TRANSACTION_QUANTITY) as Quantity, 'ONHAND' as DOC_TYPE , sourcing.vendor_name,
ascp.DATE_RUN, ascp.ORGANIZATION_ID, ascp.INVENTORY_ITEM_ID, ascp.PLANNING_METHOD,CURRENT_ABC_CLASS,
SOURCING_COMMODITY, ascp.ITEM_COST, ascp.OPEN_PO_QTY, ascp.WEEKLY_GROSS_REQS_WEEK_1 as GR_WK1 , ascp.WEEKLY_GROSS_REQS_WEEK_2 as GR_WK2,
ascp.WEEKLY_GROSS_REQS_WEEK_3 as GR_WK3 ,
TOTAL_GR_26_WEEKS as TOTAL_GR_WK26, ascp.PROJ_SPEND_NEXT_26_WEEKS_USD TOTAL_SPEND_WK26_USD , ascp.TOTAL_DAYS_OF_SUPPLY as DOS, 
ascp.ACTIVE_SUPPLIER_LT
from 
apps.MTL_ONHAND_QUANTITIES_DETAIL moq,
apps.mtl_system_items_b msi,
(
SELECT mtc.segment3 segment3, pv.vendor_name vendor_name, mtc.inventory_item_id inventory_item_id, mtc.organization_id organization_id
from 
apps.MTL_ITEM_CATEGORIES_V mtc,
apps.PO_VENDORS pv
WHERE organization_id = '{$organization_id}'
and category_set_name = 'Sourcing Rule'
and pv.vendor_id = mtc.segment3
)  sourcing,
(
SELECT DATE_RUN, ORGANIZATION_ID, INVENTORY_ITEM_ID, PLANNING_METHOD,CURRENT_ABC_CLASS,
SOURCING_COMMODITY, ITEM_COST, OPEN_PO_QTY, WEEKLY_GROSS_REQS_WEEK_1, WEEKLY_GROSS_REQS_WEEK_2, WEEKLY_GROSS_REQS_WEEK_3,
TOTAL_GR_26_WEEKS, PROJ_SPEND_NEXT_26_WEEKS_USD, TOTAL_DAYS_OF_SUPPLY, ACTIVE_SUPPLIER_LT
from apps.XX_INVASCP_FACT
WHERE organization_id = '{$organization_id}'
AND DATE_RUN > (sysdate-7)
) ascp
where moq.organization_id = '{$organization_id}'
and moq.organization_id = msi.organization_id
and moq.inventory_item_id = msi.inventory_item_id
and sourcing.organization_id(+) = msi.organization_id
and sourcing.inventory_item_id(+) = msi.inventory_item_id
and ascp.organization_id(+) = msi.organization_id
and ascp.inventory_item_id(+) = msi.inventory_item_id
and msi.inventory_item_id = '{$inventory_item_id}'
GROUP BY msi.SEGMENT1,  sourcing.vendor_name,ascp.DATE_RUN, ascp.ORGANIZATION_ID, ascp.INVENTORY_ITEM_ID, ascp.PLANNING_METHOD,CURRENT_ABC_CLASS,
SOURCING_COMMODITY, ascp.ITEM_COST, ascp.OPEN_PO_QTY, ascp.WEEKLY_GROSS_REQS_WEEK_1, ascp.WEEKLY_GROSS_REQS_WEEK_2, ascp.WEEKLY_GROSS_REQS_WEEK_3,
TOTAL_GR_26_WEEKS, ascp.PROJ_SPEND_NEXT_26_WEEKS_USD, ascp.TOTAL_DAYS_OF_SUPPLY, ascp.ACTIVE_SUPPLIER_LT
";

   $result = $dbOra->findBySql($sql);
   return !empty($result) ? array_pop($result) : false;
  }

  public function super_bom($parameters) {
   global $dbOra;

   $organization_id = !empty($parameters['ORGANIZATION_ID']) ? $parameters['ORGANIZATION_ID'] : false;
   $planner_code = !empty($parameters['PLANNER_CODE']) ? $parameters['PLANNER_CODE'] : false;
   $item_number = !empty($parameters['ITEM_NUMBER']) ? $parameters['ITEM_NUMBER'] : false;
   $this->_use_sa_as_fg = isset($parameters['use_sa_as_fg'][0]) ? true : false;
   $include_details_cb = isset($parameters['include_details_cb'][0]) ? true : false;
   $this->include_all_items_in_bom = !empty($parameters['include_all_items_in_bom']) ? 1 : false;
   $this->validate_in_new_org = !empty($parameters['validate_in_new_org']) ? $parameters['validate_in_new_org'] : false;

   if (!empty($item_number)) {
    $item_number_a = explode(',', $item_number);
    $all_items = $this->all_items_for_IB($organization_id, $item_number_a);
   } else {
    $all_items = $this->all_items_for_IB($organization_id, '', $planner_code);
   }
   $result = $this->superBOM($all_items, $organization_id);
   $superBom_a = [];

   /* FGI Description */
   $row_fgi_d = [];


   $row_fgi = ['Component', 'Description', 'Type', 'Planner'];
   if ($include_details_cb) {
    $row_fgi[] = 'On hand';
    $row_fgi[] = 'Source';
    $row_fgi[] = 'Planning Method';
    $row_fgi[] = 'ABC';
    $row_fgi[] = 'Commodity';
    $row_fgi[] = 'Cost';
    $row_fgi[] = 'LT';
    $row_fgi[] = 'GR_WK1';
    $row_fgi[] = 'GR_WK2';
    $row_fgi[] = 'GR_WK3';
    $row_fgi[] = 'TOTAL_GR_WK26';
    $row_fgi[] = 'TOTAL_SPEND_WK26_USD';
    $row_fgi[] = 'DOS';
    for ($i = 0; $i <= 16; $i++) {
     array_push($row_fgi_d, null);
    }
   } else {
    for ($i = 0; $i <= 3; $i++) {
     array_push($row_fgi_d, null);
    }
   }
   if (!empty($this->validate_in_new_org)) {
    $new_org_id = 'Org Id#' . $this->validate_in_new_org;
    array_push($row_fgi, $new_org_id);
    array_push($row_fgi_d, null);
   }
   $row_fgi_assembly_only = [];
   foreach ($result as $data) {
    if (($data->PARENT_ITEM_TYPE == 'FG' || $data->PARENT_ITEM_TYPE == 'SA') && (!(in_array($data->ASSEMBLY, $row_fgi_assembly_only)))) {
     array_push($row_fgi_assembly_only, $data->ASSEMBLY);
     array_push($row_fgi_d, $data->PARENT_DESCRIPTION);
    }
   }
   $row_fgi = array_merge($row_fgi, $row_fgi_assembly_only);
   array_push($superBom_a, $row_fgi);
   array_push($superBom_a, $row_fgi_d);

   /* Data */
   $row_data_component = [];
   $i = 0;
   foreach ($result as $data_c) {
    $row_data = [];

    if (!in_array($data_c->COMPONENT_NUMBER, $row_fgi_assembly_only)) {
     $row_data = [];
     $key = array_search($data_c->COMPONENT_NUMBER, $row_data_component);
     if ($key) {
      $com_number = $row_data_component[$key];
      array_push($row_data, $data_c->COMPONENT_NUMBER);
      array_push($row_data, $data_c->DESCRIPTION);
      array_push($row_data, $data_c->ITEM_TYPE);
      array_push($row_data, $data_c->PLANNER_CODE);
      if ($include_details_cb) {

       $other_details = $this->find_other_details($organization_id, $data_c->COMPONENT_ITEM_ID);
       if ($other_details) {
        array_push($row_data, $other_details->QUANTITY);
        array_push($row_data, $other_details->VENDOR_NAME);
        array_push($row_data, $other_details->PLANNING_METHOD);
        array_push($row_data, $other_details->CURRENT_ABC_CLASS);
        array_push($row_data, $other_details->SOURCING_COMMODITY);
        array_push($row_data, $other_details->ITEM_COST);
        array_push($row_data, $other_details->ACTIVE_SUPPLIER_LT);
        array_push($row_data, $other_details->GR_WK1);
        array_push($row_data, $other_details->GR_WK2);
        array_push($row_data, $other_details->GR_WK3);
        array_push($row_data, $other_details->TOTAL_GR_WK26);
        array_push($row_data, $other_details->TOTAL_SPEND_WK26_USD);
        array_push($row_data, $other_details->DOS);
       } else {
        for ($k = 0; $k <= 12; $k++) {
         array_push($row_data, null);
        }
       }
      }

      if (!empty($this->validate_in_new_org)) {
       $status_in_newOrg = $this->_item_type_in_new_org($data_c->COMPONENT_NUMBER, $this->validate_in_new_org);
       array_push($row_data, $status_in_newOrg);
      }
      if ($include_details_cb) {
       $element_num = 16;
      } else {
       $element_num = 3;
      }
      foreach ($row_fgi_assembly_only as $key => $val) {
       $element_num ++;
       if ($val == $data_c->ASSEMBLY) {
        array_push($row_data, $data_c->QUANTITY + $superBom_a[$com_number][$element_num]);
       } else {
        array_push($row_data, $superBom_a[$com_number][$element_num]);
       }
      }
      unset($superBom_a[$com_number]);
     } else {
      array_push($row_data_component, $data_c->COMPONENT_NUMBER);
      array_push($row_data, $data_c->COMPONENT_NUMBER);
      array_push($row_data, $data_c->DESCRIPTION);
      array_push($row_data, $data_c->ITEM_TYPE);
      array_push($row_data, $data_c->PLANNER_CODE);
      if ($include_details_cb) {
       $other_details = $this->find_other_details($organization_id, $data_c->COMPONENT_ITEM_ID);
       if ($other_details) {
        array_push($row_data, $other_details->QUANTITY);
        array_push($row_data, $other_details->VENDOR_NAME);
        array_push($row_data, $other_details->PLANNING_METHOD);
        array_push($row_data, $other_details->CURRENT_ABC_CLASS);
        array_push($row_data, $other_details->SOURCING_COMMODITY);
        array_push($row_data, $other_details->ITEM_COST);
        array_push($row_data, $other_details->ACTIVE_SUPPLIER_LT);
        array_push($row_data, $other_details->GR_WK1);
        array_push($row_data, $other_details->GR_WK2);
        array_push($row_data, $other_details->GR_WK3);
        array_push($row_data, $other_details->TOTAL_GR_WK26);
        array_push($row_data, $other_details->TOTAL_SPEND_WK26_USD);
        array_push($row_data, $other_details->DOS);
       } else {
        for ($k1 = 0; $k1 <= 12; $k1++) {
         array_push($row_data, null);
        }
       }
      }
      if (!empty($this->validate_in_new_org)) {
       $status_in_newOrg = $this->_item_type_in_new_org($data_c->COMPONENT_NUMBER, $this->validate_in_new_org);
       array_push($row_data, $status_in_newOrg);
      }
      foreach ($row_fgi_assembly_only as $key => $val) {
       if ($val == $data_c->ASSEMBLY) {
        array_push($row_data, $data_c->QUANTITY);
       } else {
        array_push($row_data, null);
       }
      }
     }

     $superBom_a[$data_c->COMPONENT_NUMBER] = $row_data;
    }
   }
   return $superBom_a;
  }

 }

//end of bom class
?>