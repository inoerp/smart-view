<?php

class inv_location_default extends dbObject {

 public static $table_name = "inv_location_default";
 public static $module = "inv";
 public static $primary_column = "inv_location_default_id";
 public static $key_column = "item_number";
 public static $system_info = [
  'name' => 'Location Default',
  'number' => '2118',
  'description' => 'Item Transaction Location Default',
  'version' => '0.1.1',
  'db_version' => '1001',
  'mod_version' => '1.1.1',
  'primary_entity_cb' => '',
  'primary_entity_cb' => '',
  'module_name' => 'mdm',
  'weight' => 4
 ];
 public $field_a = [
  'inv_location_default_id',
  'org_id',
  'item_number',
  'from_subinventory',
  'to_subinventory',
  'intransit_subinventory',
  'intransit_locator',
  'description',
  'locator_id',
  'address_id',
  'created_by',
  'creation_date',
  'last_update_by',
  'last_update_date',
 ];
 public $initial_search = [
  'item_number',
  'from_subinventory',
  'to_subinventory',
  'intransit_subinventory',
 ];
 public $requiredField = [
  'org_id',
  'item_number',
  'from_subinventory',
  'to_subinventory',
  'intransit_subinventory',
  'intransit_locator',
 ];
 public $fields_inForm_notInDataBase = [
  "item_number",
 ];
 public $fields_inHeader_needsToBeInserted_inPOST = [
  'org_id'
 ];
 public $search = [
  '_show_update_path' => 1,
  '_show_view_path' => 1,
 ];
 public $pageTitle = " Location Default For Item Transaction "; //Page Title
 public $inv_location_default_id;
 public $org_id;
 public $item_number;
 public $from_subinventory;
 public $to_subinventory;
 public $intransit_subinventory;
 public $intransit_locator;
 public $description;
 public $locator_id;
 public $address_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;

 Public static function location_default_types() {
  $option_header = option_header::find_by_name('INV_LOC_DEFAULT_TYPE');
  $ol = new option_line();
  $option_lines = $ol->findBy_parentId($option_header->option_header_id);
  return $option_lines;
 }

 public static function find_all_by_OrgId($org_id) {
  $sql = " 
	 SELECT *
	 FROM inv_location_default
	 WHERE org_id = '{$org_id}'
	";
  $result = self::find_by_sql($sql);
  return $result;
 }

 public static function find_by_item_Org_subinventories($org_id, $item_number, $from_subinventory, $to_subinventory) {
  $sql = " 
	 SELECT *
	 FROM inv_location_default
	 WHERE org_id = '{$org_id}'
   AND item_number = '{$item_number}'
   AND from_subinventory = '{$from_subinventory}'
   AND to_subinventory = '{$to_subinventory}' LIMIT 1
	";
   
//   echo $sql;
  $result = self::find_by_sql($sql);
  return !empty($result) ? array_pop($result) : false;
 }

}

//end of inv_location_default class
?>