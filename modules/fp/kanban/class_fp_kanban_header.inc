<?php

/**
 * inoERP
 *
 * @copyright   2014 Nishit R. Das
 * @license     https://www.mozilla.org/MPL/2.0/
 * @link        http://inoideas.org
 * @source code https://github.com/inoerp/inoERP
 */

/**
 * fp_kanban_header
 * Contains all the fp_kanban_header information, such as - fp_kanban_header, fp_kanban_header_id, org_id,  type, etc.
 * 
 */
class fp_kanban_header extends dbObject {

 public static $table_name = "fp_kanban_header";
 public static $primary_column = "fp_kanban_header_id";
 public static $key_column = 'item_number';
 public static $dependent_classes = ['fp_kanban_line'];
 public static $module = "fp";
 public static $multi_select_template_path = 'modules/fp/kanban/multi_action/fp_kanban_header_template_ma.php';
//  data base variables as stored database column name
 public static $system_info = [
  'name' => 'Kanban Routing',
  'number' => '2231',
  'description' => 'fp_kanban_header',
  'version' => '0.1.1',
  'db_version' => '1001',
  'mod_version' => '1.1.1',
  'primary_entity_cb' => '',
  'module_name' => 'fp',
  'weight' => 17
 ];
 public $action_a = [
  'CREATE_CARD' => 'Create Card',
  'UPDATE_CARD' => 'Create/Update Card',
 ];
 public static $card_generate_mode_a = [
  'CREATE_NEW_CARD' => 'Create New Card',
  'UPDATE_CARD' => 'Update Existing Card',
  'CREATE_UPDATE' => 'Create & Update'
 ];
 public static $source_type_a = [
  'SUPPLIER' => 'Supplier',
  'SUBINV' => 'Sub Inventory',
  'PRODUCTION' => 'Production',
  'ORG' => 'Organization',
  'LOGICAL' => 'Logical'
 ];
 public static $calculate_a = [
  'CARD' => 'Number of Cards',
  'CARD_SIZE' => 'Card Size'
 ];
 public $field_a = [
  'fp_kanban_header_id',
  'org_code',
  'description',
    "item_number",
  "item_description",
  'effective_from',
  'effective_to',
  'subinventory',
  'locator',
  'source_type',
  'supplier',
  'supplier_site',
  'from_org_code',
  'from_subinventory',
  'from_locator',
  'planning_only_cb',
  'auto_request_cb',
  'calculate',
  'card_size',
  'noof_card',
  'moq',
  'lead_time',
  'allocation_per',
  'flm',
  'ssd',
  'rfid_reference',
  'created_by',
  'creation_date',
  'last_update_by',
  'last_update_date',
 ];
//variables used for showing data
 public $initial_search = [
  'description',
  'item_id_m',
  "item_number",
 ];
 public $checkbox = [
  'planning_only_cb',
  'auto_request_cb',
 ];
 public $requiredField = [
  'item_number',
  'org_code',
  'subinventory',
  
 ];
 public $fields_inForm_notInDataBase = [

  "supplier_name",
  "supplier_number",
  "supplier_site_name",
  'multibin_kanban_quantity',
  'overwrite_kanban_multibin_number',
  'overwrite_kanban_multibin_size',
  'kanban_multibin_number',
  'kanban_multibin_size',
  'action',
 ];
 public $search = [
  '_show_update_path' => 1,
  '_show_view_path' => 1,
 ];
 public $search_functions = [
  'Organization' => 'search_org_name'
 ];
 public $pageTitle = " Kanban Route "; //page Title
 public $fp_kanban_header_id;
 public $org_code;
 public $description;
 public $item_id_m;
 public $effective_from;
 public $effective_to;
 public $subinventory_id;
 public $locator;
 public $source_type;
 public $supplier_id;
 public $supplier_site_id;
 public $from_org_code;
 public $from_subinventory;
 public $from_locator;
 public $planning_only_cb;
 public $auto_request_cb;
 public $calculate;
 public $card_size;
 public $noof_card;
 public $moq;
 public $lead_time;
 public $allocation_per;
 public $flm;
 public $ssd;
 public $rfid_reference;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $time;
 public $msg;
 public $action;
 public $item_number;
 public $item_description;
 public $supplier_name;
 public $supplier_site_name;
 public $multibin_kanban_quantity;
 public $overwrite_kanban_multibin_number;
 public $overwrite_kanban_multibin_size;
 public $kanban_multibin_number;
 public $kanban_multibin_size;
 public $prg_generate_card_parameters = [
  'Organization' => 'search_org_name',
  'Item Number From' => 'search_item_number_from',
  'Item Number To' => 'search_item_number_to',
  'Item Id From' => 'search_item_id_m_from',
  'Item Id To' => 'search_item_id_m_to',
  'Mode' => 'search_kanban_card_generate_mode',
 ];
 public $prg_generate_card_details = [
  'name' => 'Kanban Card Update ',
  'description' => 'Update Kanban Card Details ',
 ];

 public function _before_save() {
  if (!empty($this->action)) {
   if ($this->action == 'update_kanban') {
    $this->_update_kanban();
    return 10;
   }
  }
 }

 private function _update_kanban() {
  $kh = new fp_kanban_header();
  $kh->findBy_id($this->fp_kanban_header_id);

  if (!empty(trim($this->overwrite_kanban_multibin_number))) {
   $kh->noof_card = $this->overwrite_kanban_multibin_number;
  } else if (!empty(trim($this->kanban_multibin_number))) {
   $kh->noof_card = $this->kanban_multibin_number;
  }

  if (!empty(trim($this->overwrite_kanban_multibin_size))) {
   $kh->card_size = $this->overwrite_kanban_multibin_size;
  } else if (!empty(trim($this->kanban_multibin_size))) {
   $kh->card_size = $this->kanban_multibin_size;
  }
//  pa($this);
//  pa($kh);
  $kh->save();
 }

 public function create_new_card($kanban_header_id) {
  $kbh = new fp_kanban_header();
  $kbh->findBy_id($kanban_header_id);
  $no_of_cards = !empty($kbh->noof_card) ? $kbh->noof_card : 2;
  $max_card_number = fp_kanban_line::highest_card_number();
  for ($i = 0; $i < $no_of_cards; $i++) {
   $max_card_number++;
   $kbl = new fp_kanban_line();
   $kbl->fp_kanban_header_id = $kbh->fp_kanban_header_id;
   $kbl->card_number = $max_card_number;
   $kbl->description = "Auto Generated Card";
   $kbl->card_status = "ACTIVE";
   $kbl->supply_status = "NEW";
   $kbl->kanban_size = $kbh->card_size;
   $kbl->card_type = $kbh->source_type;
   $kbl->save();
  }
 }

 public function update_card($fp_kanban_line_id) {
  $kbl = new fp_kanban_line();
  $kbl->findBy_id($fp_kanban_line_id);
  $kbh = new fp_kanban_header();
  $kbh->findBy_id($kbl->fp_kanban_header_id);
  $kbl->kanban_size = $kbh->card_size;
  $kbl->card_type = $kbh->source_type;
  $kbl->save();
 }

 Public static function all_kanbans_for_itemOrg($item_id_m, $org_id) {
  $sql = " SELECT * FROM ";
  $sql .= self::$table_name;
  $sql .= " WHERE item_id_m = '{$item_id_m}' AND org_code='{$org_id}' ";
  
  $result = self::find_by_sql($sql);
  return !empty($result) ? $result : null;
 }

 private function _verify_create_update_card() {
  
 }

 public function prg_generate_card($seralized_parameters) {
  $parameters = unserialize($seralized_parameters);
  $this->message = '<br> Starting Kanban Card Generation Program....<br>';
  pa($parameters);

  $kh_m = new fp_kanban_header();

  if (!empty($parameters['org_id'][0])) {
   $org_id = $parameters['org_id'][0];
   $this->message .= '<br> Entered Org Id is : ' . $org_id;
  } else {
   $this->message .= '<br> Error! : No org id found @ item ' . __LINE__;
   return $this->message;
  }

  if (!empty($parameters['from_item_id_m'][0])) {
   $this->message .= "<br/>Using  Kanban Card Generation Program for Item Id Range ";
   $from_item_id = $parameters['from_item_id_m'][0];
   if (!empty($parameters['to_item_id_m'][0])) {
    $to_item_id = $parameters['to_item_id_m'][0];
   } else {
    $to_item_id = $from_item_id;
   }
   $item = new item();
   $item_range = $item->findBy_itemIdRange($from_item_id, $to_item_id);
   foreach ($item_range as $item_record) {
    $mms->item_id = $item_record->item_id;
    $mms_i = $mms->findBy_planId_itemId();
    $all_kanbans_for_item = $mm_item = new item();
    foreach ($mms->field_a as $key => $value) {
     if (property_exists($mm_item, $value)) {
      $mm_item->$value = $mms_i->$value;
     }
    }
    try {
     $mm_item->_update_item_minmax();
     $this->message .= "<br>Min Max Item Attributes is Successfullyupdated for item_id - " . $mms->plan_id .
      ' fp_minmax_header_id : ' . $fp_minmax_header_id;
    } catch (Exception $e) {
     $this->message .= "<br>Min Max Plannerp failed for Item id " . $mms_records->item_id . $e->getMessage();
    }
   }
   return $this->message;
  }

  if (!empty($parameters['from_item_number'][0])) {
   $this->message .= "<br/>Using  Min Max Planner by Item Number Range ";
   $from_item_number = $parameters['from_item_number'][0];
   if (!empty($parameters['to_item_number'][0])) {
    $to_item_number = $parameters['to_item_number'][0];
   } else {
    $to_item_number = $from_item_number;
   }
   $item = new item();
   $item_range = $item->findBy_itemNumberRange_OrgId($from_item_number, $to_item_number, $org_id);
   foreach ($item_range as $item_record) {
    $mms->item_id = $item_record->item_id;
    $mms_i = $mms->findBy_planId_itemId();
    $mm_item = new item();
    foreach ($mms->field_a as $key => $value) {
     if (property_exists($mm_item, $value)) {
      $mm_item->$value = $mms_i->$value;
     }
    }
    try {
     $mm_item->_update_item_minmax();
     $this->message .= "<br>Min Max Item Attributes is Successfullyupdated for item_id - " . $mms->plan_id .
      ' fp_minmax_header_id : ' . $fp_minmax_header_id;
    } catch (Exception $e) {
     $this->message .= "<br>Min Max Plannerp failed for Item id " . $mms_records->item_id . $e->getMessage();
    }
   }
   return $this->message;
  }

  //if no item id/number is given
  $this->message .= "<br/>Updating Min Max Attributes for all Items ";
  $mms_all = $mms->findBy_planId();
  foreach ($mms_all as $mms_records) {
   $mm_item = new item();
   foreach ($mms->field_a as $key => $value) {
    if (property_exists($mm_item, $value)) {
     $mm_item->$value = $mms_records->$value;
    }
   }
   try {
    $mm_item->_update_item_minmax();
    $this->message .= "<br>Min Max Item Attributes is Successfullyupdated for item_id - " . $mms_records->item_id .
     ' fp_minmax_header_id : ' . $mms->plan_id;
   } catch (Exception $e) {
    $this->message .= "<br>Min Max Plannerp failed for Item id " . $mms_records->item_id . $e->getMessage();
   }
  }
  return $this->message;
 }

 public function multi_select_input_fields() {
  $multi_select_input = [

   'overwrite_kanban_multibin_number',
   'overwrite_kanban_multibin_size'
  ];
  return $multi_select_input;
 }

 public function multi_select_hidden_fields() {
  $multi_select_hidden = [
   'action_class_name',
   'mode',
   'action',
   'show_block',
  ];

  return $multi_select_hidden;
 }

}

//end of fp_kanban_header class
?>