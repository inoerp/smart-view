<div class="row small-left-padding">
 <div id="form_all">
 <div id="form_headerDiv">
  <form action=""  method="post" id="inv_location_default_line"  name="location_default_line"><span class="heading">
   <?php echo gettext('Item Transaction Location Default') ?></span>
   <div class="tabContainer">
    <label><?php echo gettext('Inventory Org') ?> </label>
    <?php echo $f->l_select_field_from_object('org_id', org::find_all_inventory(), 'ORGANIZATION_CODE', 'ORGANIZATION_CODE', $org_id_h, 'org_id'); ?>
    <a name="show" href="form.php?class_name=inv_location_default&<?php echo "mode=$mode"; ?>" class="show document_id inv_location_default_id">
     <i class='fa fa-refresh'></i></a> 
   </div>
   <div id ="form_line" class="inv_location_default"><span class="heading"><?php echo gettext('Location Defaults') ?></span>
    <div id="tabsLine">
     <ul class="tabMain">
      <li><a href="#tabsLine-1"><?php echo gettext('Item-Location') ?></a></li>
     </ul>
     <div class="tabContainer"> 
      <div id="tabsLine-1" class="tabContent">
       <table class="form_table">
        <thead> 
         <tr>
          <th><?php echo gettext('Action') ?></th>
          <th><?php echo gettext('Id') ?></th>
          <th><?php echo gettext('Item') ?></th>
          <th><?php echo gettext('From Sub inventory') ?></th>
          <th><?php echo gettext('To Sub inventory') ?></th>
          <th><?php echo gettext('Intransit Sub inventory') ?></th>
          <th><?php echo gettext('Intransit Locator') ?></th>
         </tr>
        </thead>
        <tbody class="form_data_line_tbody location_default_values" >
         <?php
         $f = new inoform();
         $count = 0;
         $location_default_object_ai = new ArrayIterator($location_default_object);
         $location_default_object_ai->seek($position);
         while ($location_default_object_ai->valid()) {
          $inv_location_default = $location_default_object_ai->current();
          ?>         
          <tr class="inv_location_default<?php echo $count ?>">
           <td><?php
            echo ino_inline_action($$class->inv_location_default_id, array('org_id' => $org_id_h));
            ?>
           </td>
           <td><?php form::number_field_drs('inv_location_default_id') ?></td>
           <td><?php $f->text_field_wid('item_number' ); ?></td>
           <td><?php $f->text_field_wid('from_subinventory'); ?></td>
           <td><?php $f->text_field_wid('to_subinventory'); ?></td>
           <td><?php $f->text_field_wid('intransit_subinventory'); ?></td>
           <td><?php $f->text_field_wid('intransit_locator'); ?></td>
          </tr>
          <?php
          $location_default_object_ai->next();
          if ($location_default_object_ai->key() == $position + $per_page) {
           break;
          }
          $count = $count + 1;
         }
         ?>
        </tbody>
       </table>
      </div>
     </div>

    </div>
   </div> 
  </form>
 </div>
</div>
</div>


<div class="row small-top-margin" >
 <div id="pagination" style="clear: both;">
  <?php echo $pagination->show_pagination(); ?>
 </div>
</div>
<div id="js_data">
 <ul id="js_saving_data">
  <li class="lineClassName" data-lineClassName="inv_location_default" ></li>
  <li class="line_key_field" data-line_key_field="location_default" ></li>
  <li class="primary_column_id" data-primary_column_id="org_id" ></li>
  <li class="single_line" data-single_line="false" ></li>
  <li class="form_line_id" data-form_line_id="inv_location_default" ></li>
 </ul>
 <ul id="js_contextMenu_data">
  <li class="docLineId" data-docLineId="inv_location_default_id" ></li>
  <li class="btn2DivId" data-btn2DivId="form_line" ></li>
  <li class="trClass" data-trclass="inv_location_default" ></li>
  <li class="tbodyClass" data-tbodyClass="form_data_line_tbody" ></li>
  <li class="noOfTabbs" data-noOfTabbs="1" ></li>
 </ul>
</div>