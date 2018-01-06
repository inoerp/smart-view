<?php

class fp_reports extends dbObject {

 public static $table_name = "onhand_summary_v";
 public static $primary_column = "onhand_id";
 public $field_a = [
  'item_number',
  'item_description',
  'item_type',
  'sec_reporting',
  'current_abc_class',
  'org_family',
  'gr',
  'shortage_excess',
  'shortage_excess_val',
  'inventory_quantity',
  'receiving_quantity',
  'intransit_quantity',
  'total_onhand_qty',
  'item_cost',
  'buyer',
  'fixed_days_supply',
  'on_hand_days_of_supply',
  'on_order_days_of_supply',
  'wip_in_process_qty',
  'wip_days_of_supply',
  'total_days_of_supply',
  'active_supplier_lt',
  'active_or_inactive',
  'onorder_po_qty',
  'date_run',
  'fiscal_week_id',
  'organization_id',
  'organization_code',
 ];
 public $initial_search = [
  'organization_code',
  'current_abc_class',
  'org_family'
 ];
 public $dateField = [
 ];
 public $pageTitle = " Excess Supply Analysis "; //page Title
 public $date_run;
 public $fiscal_week_id;
 public $organization_id;
 public $organization_code;
 public $item_number;
 public $item_description;
 public $item_type;
 public $sec_reporting;
 public $current_abc_class;
 public $org_family;
 public $buyer;
 public $fixed_days_supply;
 public $item_cost;
 public $gr;
 public $inventory_quantity;
 public $receiving_quantity;
 public $intransit_quantity;
 public $total_onhand_qty;
 public $shortage_excess;
 public $shortage_excess_val;
 public $on_hand_days_of_supply;
 public $on_order_days_of_supply;
 public $wip_in_process_qty;
 public $wip_days_of_supply;
 public $total_days_of_supply;
 public $active_supplier_lt;
 public $active_or_inactive;
 public $onorder_po_qty;
// public $search_functions = [
//  'Inventory Org' => 'search_org_name'
// ];
 public $prg_shortage_excess_details = [
  'name' => 'Shortage Excess Analysis',
  'description' => 'Shortage Excess Analysis Report',
 ];
 public $prg_shortage_excess_parameters = [
  'Period Name' => 'search_gl_period_name',
  'Show Details' => 'search_show_details_cb',
  'Legal Org' => 'search_legal_org_name_m'
 ];

 public function shortage_excess($params) {
  $ret_a = [
   'name' => 'Shortage Excess Analysis',
   'description' => 'Shortage Excess Analysis Report',
  ];
  return $ret_a;
 }

 public function shortage_excess_search_records($parameters = '') {
  $pageno = !empty($parameters['pageno']) ? $parameters['pageno'] : 1;
  $per_page = !empty($parameters['per_page']) ? $parameters['per_page'] : 10;
  $whereClause = $_GET['whereClause'];
  $search_order_by = !(empty($_GET['search_order_by'])) ? $_GET['search_order_by'] : '';
  $search_asc_desc = !(empty($_GET['search_asc_desc'])) ? $_GET['search_asc_desc'] : '';

  if ((!empty($search_order_by)) && (!empty($search_asc_desc))) {
   if (is_array($search_order_by)) {
    $order_by = ' ORDER BY ';
    foreach ($search_order_by as $key_oby => $value_oby) {
     if (empty($search_asc_desc[$key_oby])) {
      $search_asc_desc[$key_oby] = ' DESC ';
     }
     $order_by .= $value_oby . ' ' . $search_asc_desc[$key_oby] . ' ,';
    }
    $order_by_i = rtrim($order_by, ',');
   } else {
    $order_by_i = ' ORDER BY ' . $search_order_by . ' ' . $search_asc_desc;
   }
  }

  $sql = $this->_shortage_excess_sql($parameters);
//  $sql .= " $order_by_i ";
  if (!empty($per_page)) {
   $offset = ($pageno - 1 ) * $per_page;
   $offset_i = $offset <= 0 ? 1 : $offset;
   $sql .=" LIMIT {$per_page} ";
   $sql .=" OFFSET {$offset_i} ";
  }

  $result = self::find_by_sql($sql);
  return !empty($result) ? $result : false;
 }

 public function shortage_excess_search_counts($parameters = '') {

  $sql = $this->_shortage_excess_sql($parameters);

  $result = self::find_by_sql($sql);
  return !empty($result) ? count($result) : false;
 }

 public function shortage_excess_search_downloads($parameters = '') {
  return $this->_shortage_excess_sql($parameters);
 }

 private function _shortage_excess_sql($parameters = '') {
  $whereClause = $_GET['whereClause'];
  $sql = " SELECT `date_run` , `fiscal_week_id` , `organization_id` , sum_amnt.organization_code , sum_amnt.item_number, `item_description` , `item_type` , `sec_reporting`
 , `current_abc_class` , `org_family` , `buyer` , `fixed_days_supply` , `item_cost` , sum_amnt.gr, `inventory_quantity` , `receiving_quantity` ,  `intransit_quantity` ,  `total_onhand_qty` , (sum_amnt.gr - IFNULL(total_onhand_qty,0) ) shortage_excess , ROUND (IFNULL(`item_cost`,0) * ((sum_amnt.gr - IFNULL(total_onhand_qty,0) )))  shortage_excess_val , `on_hand_days_of_supply` , `on_order_days_of_supply` , `wip_in_process_qty` , `wip_days_of_supply` , `total_days_of_supply` , `active_supplier_lt` , `active_or_inactive` , `onorder_po_qty`  
FROM 
`ra_operation_snapshot`, 
(
    SELECT SUM(IFNULL(`weekly_gross_reqs_week_0`,0) + IFNULL(`weekly_gross_reqs_week_1` , 0)  +  IFNULL(`weekly_gross_reqs_week_3` , 0) + IFNULL(`weekly_gross_reqs_week_4`,0))  as gr ,`organization_code` , `item_number`
    from ra_operation_snapshot
GROUP BY organization_code, item_number
    ) as sum_amnt
WHERE sum_amnt.organization_code = ra_operation_snapshot.organization_code
AND sum_amnt.item_number = ra_operation_snapshot.item_number
AND STR_TO_DATE(ra_operation_snapshot.date_run,'%d-%b-%y') = (SELECT MAX(STR_TO_DATE(date_run, '%d-%b-%y')) last_run_date
    from ra_operation_snapshot)
AND sum_amnt.gr > 0 ";
    if (!empty($whereClause)) {
   $sql .= "	AND $whereClause ";
  }
$sql .= " GROUP BY organization_id, item_number
ORDER BY shortage_excess_val asc
";


  echo $sql;
  return $sql;
 }

}

//end of po_detail class
?>