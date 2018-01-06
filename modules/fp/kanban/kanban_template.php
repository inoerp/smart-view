<!-- * 
inoERP
 *
 * @copyright   2014 Nishit R. Das
 * @license     https://www.mozilla.org/MPL/2.0/
 * @link        http://inoideas.org
 * @source code https://github.com/inoerp/inoERP
-->

<div id ="form_header"><span class="heading"><?php
  $f = new inoform();
  echo gettext('Kanban Replenishment Strategy')
  ?></span>
 <form action=""  method="post" id="fp_kanban_header"  name="fp_kanban_header">
  <div id="tabsHeader">
   <ul class="tabMain">
    <li><a href="#tabsHeader-1"><?php echo gettext('Basic Info') ?></a></li>
    <li><a href="#tabsHeader-2"><?php echo gettext('Planning') ?></a></li>
    <li><a href="#tabsHeader-3"><?php echo gettext('Supply') ?></a></li>
    <li><a href="#tabsHeader-4"><?php echo gettext('Note') ?></a></li>
    <li><a href="#tabsHeader-5"><?php echo gettext('Attachments') ?></a></li>
    <li><a href="#tabsHeader-6"><?php echo gettext('Action') ?></a></li>
   </ul>
   <div class="tabContainer">
    <div id="tabsHeader-1" class="tabContent">
     <ul class="column header_field">
      <li><?php $f->l_text_field_dr_withSearch('fp_kanban_header_id') ?>
       <a name="show" href="form.php?class_name=fp_kanban_header&<?php echo "mode=$mode"; ?>" class="show document_id fp_kanban_header_id"><i class="fa fa-refresh"></i></a> 
      </li>
      <li><?php echo $f->l_select_field_from_object('org_code', org::find_all_inventory(), 'ORGANIZATION_CODE', 'ORGANIZATION_CODE', $$class->org_code, 'org_code'); ?>
      </li>
      <li><?php $f->l_text_field_dm('item_number'); ?></li>
      <li><?php $f->l_text_field_d('item_description'); ?></li>
      <li><?php $f->l_text_field_d('description'); ?></li>
      <li><?php $f->l_text_field_d('subinventory'); ?>         </li>
      <li><?php $f->l_text_field_d('locator'); ?>         </li>
      <li><?php $f->l_text_field_d('rfid_reference'); ?>         </li>
      
      <li><?php $f->l_select_field_from_array('source_type', fp_kanban_header::$source_type_a, $$class->source_type, 'source_type', 'medium'); ?></li>
     </ul>
    </div>
    <div id="tabsHeader-2" class="tabContent">
     <ul class="column header_field"> 
      <li><?php $f->l_select_field_from_array('calculate', fp_kanban_header::$calculate_a, $$class->calculate, 'calculate', 'medium'); ?></li>
      <li><?php $f->l_number_field_d('card_size'); ?></li> 
      <li><?php $f->l_number_field_d('noof_card'); ?></li> 
      <li><?php $f->l_number_field_d('moq'); ?></li> 
      <li><?php $f->l_number_field_d('lead_time'); ?></li> 
      <li><?php $f->l_number_field_d('allocation_per'); ?></li> 
      <li><?php $f->l_number_field_d('flm'); ?></li> 
      <li><?php $f->l_number_field_d('ssd'); ?></li> 
      <li><?php $f->l_checkBox_field_d('planning_only_cb'); ?></li> 
      <li><?php $f->l_checkBox_field_d('auto_request_cb'); ?></li> 
     </ul>
    </div>
    <div id="tabsHeader-3" class="tabContent">
     <ul class="column header_field">
      <li><?php $f->l_text_field_d('from_org_code'); ?>         </li>
      <li><?php $f->l_text_field_d('from_subinventory'); ?>         </li>
      <li><?php $f->l_text_field_d('from_locator'); ?>         </li>
      <li><?php $f->l_text_field_d('supplier_name'); ?>         </li>
      <li><?php $f->l_text_field_d('supplier_site'); ?>         </li>
     </ul>
    </div>
    <div id="tabsHeader-4" class="tabContent">
     <div> 
      <div id="comments">
       <div id="comment_list">
        <?php echo!(empty($comments)) ? $comments : ""; ?>
       </div>
       <div id ="display_comment_form">
        <?php
        $reference_table = 'fp_kanban_header';
        $reference_id = $$class->fp_kanban_header_id;
        ?>
       </div>
       <div id="new_comment">
       </div>
      </div>
     </div>
    </div>
    <div id="tabsHeader-5" class="tabContent">
     <div> <?php echo ino_attachement($file) ?> </div>
    </div>
    <div id="tabsHeader-6" class="tabContent">
     <ul class="column header_field">
      <li><label>Action</label>
       <?php
       echo $f->select_field_from_array('action', $$class->action_a, '', 'action', '', '', $readonly, '')
       ?>
      </li>
     </ul>
    </div>
   </div>
  </div>
 </form>
</div>

<div id="form_line" class="form_line"><span class="heading"><?php echo gettext('Kanban Cards') ?></span>
 <form action=""  method="post" id="fp_kanban_line"  name="fp_kanban_line">
  <div id="tabsLine">
   <ul class="tabMain">
    <li><a href="#tabsLine-1"><?php echo gettext('Basic') ?></a></li>
   </ul>
   <div class="tabContainer">
    <div id="tabsLine-1" class="tabContent">
     <table class="form_line_data_table">
      <thead> 
       <tr>
        <th><?php echo gettext('Action') ?></th>
        <th><?php echo gettext('Line Id') ?></th>
        <th><?php echo gettext('Card Number') ?></th>
        <th><?php echo gettext('Card Type') ?></th>
        <th><?php echo gettext('Description') ?></th>
        <th><?php echo gettext('Card Status') ?></th>
        <th><?php echo gettext('Supply Status') ?></th>
        <th><?php echo gettext('Kanban Size') ?></th>
        <th><?php echo gettext('Replenish') ?></th>        
       </tr>
      </thead>
      <tbody class="form_data_line_tbody">
       <?php
       $count = 0;
       foreach ($fp_kanban_line_object as $fp_kanban_line) {
        $readonly_ss = $$class_second->supply_status == 'FULL' ? '' : true;
        ?>         
        <tr class="fp_kanban_line<?php echo $count ?>">
         <td>
          <?php
          echo ino_inline_action($fp_kanban_line->fp_kanban_line_id, array('fp_kanban_header_id' => $fp_kanban_header->fp_kanban_header_id));
          ?>
         </td>
         <td><?php $f->text_field_d2sr('fp_kanban_line_id'); ?></td>
         <td><?php $f->text_field_d2('card_number'); ?></td>
         <td><?php echo $f->select_field_from_array('card_type', fp_kanban_line::$card_type_a, $$class_second->card_type, '', 'medium'); ?></td>
         <td><?php $f->text_field_d2('description'); ?></td>
         <td><?php echo $f->select_field_from_array('card_status', fp_kanban_line::$card_status_a, $$class_second->card_status, '', 'medium'); ?></td>
         <td><?php echo $f->select_field_from_array('supply_status', fp_kanban_line::$supply_status_a, $$class_second->supply_status, '', 'medium', '', $readonly_ss, $readonly_ss); ?></td>
         <td><?php $f->text_field_d2('kanban_size'); ?></td>
         <td><?php $f->checkBox_field_wid2('replenish_cb'); ?></td>
        </tr>
        <?php
        $count = $count + 1;
       }
       ?>
      </tbody>
     </table>
    </div>
   </div>
  </div>
 </form>
</div>


<div id="js_data">
 <ul id="js_saving_data">
  <li class="headerClassName" data-headerClassName="fp_kanban_header" ></li>
  <li class="lineClassName" data-lineClassName="fp_kanban_line" ></li>
  <li class="savingOnlyHeader" data-savingOnlyHeader="false" ></li>
  <li class="primary_column_id" data-primary_column_id="fp_kanban_header_id" ></li>
  <li class="form_header_id" data-form_header_id="fp_kanban_header" ></li>
  <li class="line_key_field" data-line_key_field="line_name" ></li>
  <li class="single_line" data-single_line="false" ></li>
  <li class="form_line_id" data-form_line_id="fp_kanban_line" ></li>
 </ul>
 <ul id="js_contextMenu_data">
  <li class="docHedaderId" data-docHedaderId="fp_kanban_header_id" ></li>
  <li class="docLineId" data-docLineId="fp_kanban_line_id" ></li>
  <li class="btn1DivId" data-btn1DivId="fp_kanban_header" ></li>
  <li class="btn2DivId" data-btn2DivId="form_line" ></li>
  <li class="tbodyClass" data-tbodyClass="form_data_line_tbody" ></li>
  <li class="noOfTabbs" data-noOfTabbs="1" ></li>
 </ul>
</div>