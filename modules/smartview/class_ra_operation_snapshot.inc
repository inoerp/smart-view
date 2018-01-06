<?php

class ra_operation_snapshot extends dbObject {

 public static $table_name = "ra_operation_snapshot";
 public static $primary_column = "onhand_id";
 public $field_a = [
  'date_run',
  'period_year',
  'period_name',
  'period_end_date',
  'quarter_num',
  'fiscal_week_id',
  'me_week_id',
  'me_flag',
  'freeze_data',
  'osp_assemblies',
  'planning_method',
  'organization_id',
  'organization_code',
  'inventory_item_id',
  'item_number',
  'item_description',
  'uom_code',
  'uom',
  'item_status',
  'item_type_code',
  'item_type',
  'cost_source_type',
  'supply_source',
  'demand_source',
  'sec_reporting',
  'operations_reporting',
  'last_abc_class',
  'current_abc_class',
  'last_mrp_abc_class',
  'current_mrp_abc_class',
  'mas_tbu',
  'mas_family',
  'mas_line',
  'mas_forecast_field',
  'org_tbu',
  'org_family',
  'org_line',
  'org_forecast_field',
  'sourcing_commodity',
  'planner',
  'buyer_id',
  'buyer',
  'inventory_planning_method',
  'min_max_min_qty',
  'min_max_max_qty',
  'mrp_planning_method',
  'min_order_qty',
  'max_order_qty',
  'fixed_order_qty',
  'fixed_days_supply',
  'fixed_lot_size_multiplier',
  'acceptable_early_days',
  'shrinkage',
  'sr_vendor_id',
  'sr_vendor',
  'sr_vendor_site_id',
  'sr_vendor_site_code',
  'sr_pct',
  'sr_asl_status',
  'sr_vndr_src_org',
  'processing_lead_time',
  'item_cost_usd',
  'item_cost',
  'currency_code',
  'currency_rate',
  'open_po_qty',
  'open_po_value',
  'open_po_value_usd',
  'safety_stock_qty',
  'safety_stock_value',
  'safety_stock_value_usd',
  'cumulative_mfg_lt',
  'cumulative_lt',
  'weekly_gross_reqs_week_0',
  'weekly_gross_reqs_week_1',
  'weekly_gross_reqs_week_2',
  'weekly_gross_reqs_week_3',
  'weekly_gross_reqs_week_4',
  'weekly_gross_reqs_week_5',
  'weekly_gross_reqs_week_6',
  'weekly_gross_reqs_week_7',
  'weekly_gross_reqs_week_8',
  'weekly_gross_reqs_week_9',
  'weekly_gross_reqs_week_10',
  'weekly_gross_reqs_week_11',
  'weekly_gross_reqs_week_12',
  'weekly_gross_reqs_week_13',
  'weekly_gross_reqs_week_14',
  'weekly_gross_reqs_week_15',
  'weekly_gross_reqs_week_16',
  'weekly_gross_reqs_week_17',
  'weekly_gross_reqs_week_18',
  'weekly_gross_reqs_week_19',
  'weekly_gross_reqs_week_20',
  'weekly_gross_reqs_week_21',
  'weekly_gross_reqs_week_22',
  'weekly_gross_reqs_week_23',
  'weekly_gross_reqs_week_24',
  'weekly_gross_reqs_week_25',
  'weekly_gross_reqs_week_26',
  'total_gr_26_weeks',
  'inventory_quantity',
  'inventory_value',
  'inventory_value_usd',
  'receiving_quantity',
  'receiving_value',
  'receiving_value_usd',
  'intransit_quantity',
  'intransit_value',
  'intransit_value_usd',
  'total_quantity',
  'extended_value',
  'extended_value_usd',
  'total_onhand_qty',
  'onhand_qty_non_asset',
  'onhand_qty_asset',
  'total_usage_26_weeks',
  'so_usage_13_weeks',
  'so_usage_26_weeks',
  'total_usage_13_weeks',
  'wo_usage_13_weeks',
  'wo_usage_26_weeks',
  'spc_usage_volume_13_weeks_usd',
  'gross_inventory_turns',
  'average_daily_demand',
  'ave_daily_usage_26_weeks',
  'avg_daily_demand_else_usage',
  'purchasing_list_price',
  'purchasing_list_price_usd',
  'number_of_open_blankets',
  'sum_remaining_amount',
  'sum_usd_remaining_amount',
  'sum_remaining_qty_calculated',
  'blanket_days_supply_remaining',
  'on_hand_days_of_supply',
  'on_order_days_of_supply',
  'wip_in_process_qty',
  'wip_in_process_value',
  'wip_in_process_value_usd',
  'wip_days_of_supply',
  'total_days_of_supply',
  'active_supplier_lt',
  'attribute_lt',
  'purch_asl_lt',
  'subinventory_min_max_lt',
  'kanban_repl_lt',
  'kanban_type',
  'min_max_planned',
  'kanban_item',
  'open_blankets',
  'min_max_item',
  'mrp_active_or_inactive',
  'txn_active_or_inactive',
  'active_or_inactive',
  'proj_spend_next_26_weeks',
  'proj_spend_next_26_weeks_usd',
  'entity',
  'entity_id',
  'fin_product_group',
  'fin_product_family',
  'fin_product_id',
  'ora_product_id',
  'ir_po_qty',
  'ir_po_value',
  'ir_po_value_usd',
  'onorder_po_qty',
  'onorder_po_value',
  'onorder_po_value_usd',
  'item_tbu',
  'item_product_family',
  'ora_product_family',
  'ora_product_group',
  'target_days_of_supply',
  'target_days_of_supply_qty',
  'target_days_of_supply_value',
  'target_days_of_supply_savings',
  'lt_grouping',
  'product_line_obi',
  'item_status_obi',
  'invascp_key',
  'item_type_obi',
  'lt_grouping_id',
 ];
 public $initial_search = [
  'organization_code',
  'org_family',
  'item_number',
  'item_description',
 ];
 public $dateField = [
 ];
 public $pageTitle = " Operation Snapshot "; //page Title
 public $search = [
  '_view_path' => 'form.php?class_name=inv_onhand_serial',
  '_show_view_path' => 1,
 ];
 public $date_run;
 public $period_year;
 public $period_name;
 public $period_end_date;
 public $quarter_num;
 public $fiscal_week_id;
 public $me_week_id;
 public $me_flag;
 public $freeze_data;
 public $osp_assemblies;
 public $planning_method;
 public $organization_id;
 public $organization_code;
 public $inventory_item_id;
 public $item_number;
 public $item_description;
 public $uom_code;
 public $uom;
 public $item_status;
 public $item_type_code;
 public $item_type;
 public $cost_source_type;
 public $supply_source;
 public $demand_source;
 public $sec_reporting;
 public $operations_reporting;
 public $last_abc_class;
 public $current_abc_class;
 public $last_mrp_abc_class;
 public $current_mrp_abc_class;
 public $mas_tbu;
 public $mas_family;
 public $mas_line;
 public $mas_forecast_field;
 public $org_tbu;
 public $org_family;
 public $org_line;
 public $org_forecast_field;
 public $sourcing_commodity;
 public $planner;
 public $buyer_id;
 public $buyer;
 public $inventory_planning_method;
 public $min_max_min_qty;
 public $min_max_max_qty;
 public $mrp_planning_method;
 public $min_order_qty;
 public $max_order_qty;
 public $fixed_order_qty;
 public $fixed_days_supply;
 public $fixed_lot_size_multiplier;
 public $acceptable_early_days;
 public $shrinkage;
 public $sr_vendor_id;
 public $sr_vendor;
 public $sr_vendor_site_id;
 public $sr_vendor_site_code;
 public $sr_pct;
 public $sr_asl_status;
 public $sr_vndr_src_org;
 public $processing_lead_time;
 public $item_cost_usd;
 public $item_cost;
 public $currency_code;
 public $currency_rate;
 public $open_po_qty;
 public $open_po_value;
 public $open_po_value_usd;
 public $safety_stock_qty;
 public $safety_stock_value;
 public $safety_stock_value_usd;
 public $cumulative_mfg_lt;
 public $cumulative_lt;
 public $weekly_gross_reqs_week_0;
 public $weekly_gross_reqs_week_1;
 public $weekly_gross_reqs_week_2;
 public $weekly_gross_reqs_week_3;
 public $weekly_gross_reqs_week_4;
 public $weekly_gross_reqs_week_5;
 public $weekly_gross_reqs_week_6;
 public $weekly_gross_reqs_week_7;
 public $weekly_gross_reqs_week_8;
 public $weekly_gross_reqs_week_9;
 public $weekly_gross_reqs_week_10;
 public $weekly_gross_reqs_week_11;
 public $weekly_gross_reqs_week_12;
 public $weekly_gross_reqs_week_13;
 public $weekly_gross_reqs_week_14;
 public $weekly_gross_reqs_week_15;
 public $weekly_gross_reqs_week_16;
 public $weekly_gross_reqs_week_17;
 public $weekly_gross_reqs_week_18;
 public $weekly_gross_reqs_week_19;
 public $weekly_gross_reqs_week_20;
 public $weekly_gross_reqs_week_21;
 public $weekly_gross_reqs_week_22;
 public $weekly_gross_reqs_week_23;
 public $weekly_gross_reqs_week_24;
 public $weekly_gross_reqs_week_25;
 public $weekly_gross_reqs_week_26;
 public $total_gr_26_weeks;
 public $inventory_quantity;
 public $inventory_value;
 public $inventory_value_usd;
 public $receiving_quantity;
 public $receiving_value;
 public $receiving_value_usd;
 public $intransit_quantity;
 public $intransit_value;
 public $intransit_value_usd;
 public $total_quantity;
 public $extended_value;
 public $extended_value_usd;
 public $total_onhand_qty;
 public $onhand_qty_non_asset;
 public $onhand_qty_asset;
 public $total_usage_26_weeks;
 public $so_usage_13_weeks;
 public $so_usage_26_weeks;
 public $total_usage_13_weeks;
 public $wo_usage_13_weeks;
 public $wo_usage_26_weeks;
 public $spc_usage_volume_13_weeks_usd;
 public $gross_inventory_turns;
 public $average_daily_demand;
 public $ave_daily_usage_26_weeks;
 public $avg_daily_demand_else_usage;
 public $purchasing_list_price;
 public $purchasing_list_price_usd;
 public $number_of_open_blankets;
 public $sum_remaining_amount;
 public $sum_usd_remaining_amount;
 public $sum_remaining_qty_calculated;
 public $blanket_days_supply_remaining;
 public $on_hand_days_of_supply;
 public $on_order_days_of_supply;
 public $wip_in_process_qty;
 public $wip_in_process_value;
 public $wip_in_process_value_usd;
 public $wip_days_of_supply;
 public $total_days_of_supply;
 public $active_supplier_lt;
 public $attribute_lt;
 public $purch_asl_lt;
 public $subinventory_min_max_lt;
 public $kanban_repl_lt;
 public $kanban_type;
 public $min_max_planned;
 public $kanban_item;
 public $open_blankets;
 public $min_max_item;
 public $mrp_active_or_inactive;
 public $txn_active_or_inactive;
 public $active_or_inactive;
 public $proj_spend_next_26_weeks;
 public $proj_spend_next_26_weeks_usd;
 public $entity;
 public $entity_id;
 public $fin_product_group;
 public $fin_product_family;
 public $fin_product_id;
 public $ora_product_id;
 public $ir_po_qty;
 public $ir_po_value;
 public $ir_po_value_usd;
 public $onorder_po_qty;
 public $onorder_po_value;
 public $onorder_po_value_usd;
 public $item_tbu;
 public $item_product_family;
 public $ora_product_family;
 public $ora_product_group;
 public $target_days_of_supply;
 public $target_days_of_supply_qty;
 public $target_days_of_supply_value;
 public $target_days_of_supply_savings;
 public $lt_grouping;
 public $product_line_obi;
 public $item_status_obi;
 public $invascp_key;
 public $item_type_obi;
 public $lt_grouping_id;

 private function create_ra_operation_snapshot() {
  $sql = "
	 CREATE OR REPLACE VIEW ra_operation_snapshot
(onhand_id, item_number, item_description, product_line, org_name, subinventory, locator,
uom_id,onhand, standard_cost, ra_operation_snapshotalue,
item_id_m, revision_name, org_id, subinventory_id, subinventory_type,
locator_id, lot_id, serial_id, reservable_onhand, 
transactable_onhand, lot_status, serial_status,  
secondary_uom_id, onhand_status, ef_id, created_by, 
creation_date, last_update_by, last_update_date)
AS
SELECT onhand.onhand_id, 
item.item_number, item.item_description, item.product_line,
org.org, subinventory.subinventory, locator.locator,
onhand.uom_id,onhand.onhand,
cic.standard_cost, (onhand.onhand * cic.standard_cost) as ra_operation_snapshotalue,
onhand.item_id_m, onhand.revision_name, onhand.org_id, onhand.subinventory_id, subinventory.type,
onhand.locator_id, onhand.lot_id, onhand.serial_id, onhand.reservable_onhand, 
onhand.transactable_onhand, onhand.lot_status, onhand.serial_status,  
onhand.secondary_uom_id, onhand.onhand_status, onhand.ef_id, onhand.created_by, 
onhand.creation_date, onhand.last_update_by, onhand.last_update_date

FROM onhand 
LEFT JOIN item ON onhand.item_id_m = item.item_id_m AND item.org_id = onhand.org_id
LEFT JOIN org ON onhand.org_id = org.org_id
LEFT JOIN subinventory ON onhand.subinventory_id = subinventory.subinventory_id
LEFT JOIN locator ON onhand.locator_id = locator.locator_id
LEFT JOIN cst_item_cost_v cic ON cic.item_id_m = onhand.item_id_m AND cic.bom_cost_type='FROZEN' AND cic.org_id = onhand.org_id
";
 }


}

//end of po_detail class
?>