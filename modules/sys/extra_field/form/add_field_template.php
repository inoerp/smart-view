<table class="form_line_data_table">
 <thead> 
  <tr>
   <th>Seq #</th>
   <th><?php echo $extra_element_label ; ?></th>
  </tr>
 </thead>
 <tbody class="form_data_line_tbody">
  <?php
   $count = 0;
   foreach ($class_name_object as $class_name_line) {
    $ef_refer_value_i = !empty($class_name_line->$ef_refer_value) ? $class_name_line->$ef_refer_value : null;
    ?>    
    <tr class="<?php echo $tr_class.$count ?>">
     <td><?php $f->seq_field_d($count) ?></td>
     <td class="add_detail_values1">
      <i class="fa fa-arrow-circle-down add_detail_values_img"></i>
      <div class="class_detail_form">
       <fieldset class="form_detail_data_fs"><legend>Extra Fields</legend>
        <div class="tabsDetailC">
         <ul class="tabMain">
          <li class="tabLink"><a href="#tabsDetailC-3-<?php echo $count ?>"> Basic Info</a></li>
          <li class="tabLink"><a href="#tabsDetailC-4-<?php echo $count ?>"> List Values</a></li>
         </ul>
         <div class="tabContainer">
          <div id="tabsDetailC-3-<?php echo $count ?>" class="tabContent">
           <table class="form form_detail_data_table detail">
            <thead>
             <tr>
              <th>Action</th>
              <th>Seq#</th>
              <th>Instance Id</th>
              <th>Field Name</th>
              <th>Label</th>
              <th>Type</th>
              <th>Control Type</th>
              <th>Control Value</th>
              <th>Control UOM</th>
              <th>Display Weight</th>
              <th>Active</th>
             </tr>
            </thead>
            <tbody class="form_data_detail_tbody_ln">
             <?php
             $detailCount = 0;
             if (!empty($ef_refer_value_i)) {
              $extra_field_object = [];
              $extra_field_object = sys_extra_field_instance::find_by_referenceKeyValue($ef_refer_key, $ef_refer_value_i);
             }
             if (empty($extra_field_object)) {
              $extra_field_object = array(new sys_extra_field_instance());
             }
             foreach ($extra_field_object as $extra_field) {
              ?>
              <tr class="sys_extra_field<?php echo $count . '-' . $detailCount; ?>">
               <td>   
                <ul class="inline_action">
                 <li class="add_row_detail_img3"><i class="fa fa-plus-circle"></i></li>
                 <li class="remove_row_img"><i class="fa fa-minus-circle"></i></li>
                 <li><input type="checkbox" name="detail_id_cb" value="<?php echo htmlentities($extra_field->sys_extra_field_instance_id); ?>">
                 </li>           
                </ul>
               </td>
               <td><?php $f->seq_field_detail_d($detailCount) ?></td>
               <td><?php echo $f->text_field('sys_extra_field_instance_id', $extra_field->sys_extra_field_instance_id, '8', '', '', '', 1); ?></td>
               <td><?php echo $f->select_field_from_object('sys_extra_field_id', sys_extra_field::find_all(), 'sys_extra_field_id', 'field_name', $extra_field->sys_extra_field_id, '', 'medium', '', '', '', '', '', 'field_type'); ?> </td>
               <td><?php echo $f->text_field('label', $extra_field->label); ?></td>
               <td><?php echo $f->text_field_ap(array('name' => 'field_type', 'value' => $extra_field->field_type, 'readonly' => true)); ?></td>
               <td><?php echo $f->select_field_from_array('control_type', dbObject::$control_type_a, $extra_field->control_type); ?></td>
               <td><?php echo $f->text_field('control_value', $extra_field->control_value); ?></td>
               <td><?php echo $f->select_field_from_object('control_uom', uom::find_all(), 'uom_id', 'uom_name', $extra_field->control_uom, '', 'uom_id small'); ?></td>
               <td><?php echo $f->select_field_from_array('display_weight', dbObject::$position_array, $extra_field->display_weight); ?></td>
               <td><?php echo $f->checkBox_field('active_cb', $extra_field->active_cb); ?></td>
              </tr>
              <?php
              $detailCount++;
             }
             ?>
            </tbody>
           </table>
          </div>
          <div id="tabsDetailC-4-<?php echo $count ?>" class="tabContent">
           <table class="form form_detail_data_table detail">
            <thead>
             <tr>
              <th>Seq#</th>
              <th>Lower Limit</th>
              <th>Upper Limit</th>
              <th>List Option Type</th>
              <th>Field Name</th>
             </tr>
            </thead>
            <tbody class="form_data_detail_tbody_ln">
             <?php
             $detailCount = 0;
             foreach ($extra_field_object as $extra_field) {
              ?>
              <tr class="sys_extra_field<?php echo $count . '-' . $detailCount; ?>">
               <td><?php $f->seq_field_detail_d($detailCount) ?></td>
               <td><?php echo $f->text_field('lower_limit', $extra_field->lower_limit); ?></td>
               <td><?php echo $f->text_field('upper_limit', $extra_field->upper_limit); ?></td>
               <td><?php echo $f->select_field_from_object('list_value_option_type', option_header::find_all(), 'option_header_id', 'option_type', $extra_field->list_value_option_type, '', 'medium'); ?></td>
               <td><?php
                $list_value = !empty($extra_field->list_values) ? implode(',', unserialize($extra_field->list_values)) : null;
                echo $f->text_area_ap(array('name' => 'list_values', 'value' => $list_value, 'column_size' => '60',
                 'rowsize' => '2', 'place_holder' => 'Enter comma(,) separated values'));
                ?> </td>
              </tr>
              <?php
              $detailCount++;
             }
             ?>
            </tbody>
           </table>
          </div>

         </div>
        </div>


       </fieldset>

      </div>
     </td>

    </tr>
    <?php
    $count = $count + 1;
   }
  ?>
 </tbody>
 <!--                  Showing a blank form for new entry-->

</table>