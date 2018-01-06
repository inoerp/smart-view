<div class="row small-left-padding">
 <div id="form_all">
  <span class="heading"><?php echo gettext('Tax Regions') ?></span>
  <div id="form_headerDiv"><?php $f = new inoform(); ?>
   <form action=""  method="post" id="ar_sales_region_line"  name="sales_region_line">
    <div id="form_serach_header" class="tabContainer">
     <label><?php echo gettext('Country') ?></label>
     <?php $f->l_select_field_from_object('country_code', ar_sales_region::country(), 'option_line_code', 'option_line_value', $country_code_h, 'country_code', ' ', '', $readonly1); ?>
     <a name="show" href="form.php?class_name=ar_sales_region&<?php echo "mode=$mode"; ?>" class="show document_id ar_sales_region_id">
      <i class="fa fa-refresh"></i></a> 
    </div>
    <div id ="form_line" class="ar_sales_region">
     <div id="tabsLine">
      <ul class="tabMain">
       <li><a href="#tabsLine-1"><?php echo gettext('Location') ?></a></li>
       <li><a href="#tabsLine-2"><?php echo gettext('Reporting') ?></a></li>
      </ul>
      <div class="tabContainer"> 

       <div id="tabsLine-1" class="tabContent">
        <table class="form_table">
         <thead> 
          <tr>
           <th><?php echo gettext('Action') ?></th>
           <th><?php echo gettext('Seq') ?>#</th>
           <th><?php echo gettext('Id') ?></th>
           <th><?php echo gettext('Country Code') ?></th>
           <th><?php echo gettext('State') ?></th>
           <th><?php echo gettext('City') ?></th>
           <th><?php echo gettext('Street') ?></th>
           <th><?php echo gettext('Region Name') ?></th>
           
          </tr>
         </thead>
         <tbody class="form_data_line_tbody sales_region_values" >
          <?php
          $count = 0;
          $sales_region_object_ai = new ArrayIterator($sales_region_object);
          $sales_region_object_ai->seek($position);
          while ($sales_region_object_ai->valid()) {
           $ar_sales_region = $sales_region_object_ai->current();
           if (empty($ar_sales_region->country_code)) {
            $ar_sales_region->country_code = $country_code_h;
           }
           ?>         
           <tr class="ar_sales_region<?php echo $count ?>">
            <td>
                        <?php
           echo ino_inline_action($$class->ar_sales_region_id, array('country_code' => $country_code_h));
           ?>
            </td>
            <td><?php $f->seq_field_d($count) ?></td>
            <td><?php form::number_field_drs('ar_sales_region_id') ?></td>
            <td><?php $f->text_field_widrm('country_code', 'line_data, copy'); ?></td>
            <td><?php $f->text_field_wid('state', 'copy'); ?></td>
            <td><?php $f->text_field_wid('city', 'copy'); ?></td>
            <td><?php $f->text_field_wid('street', 'dontCopy'); ?></td>
            <td><?php $f->text_field_wid('sales_region_name', 'dontCopy'); ?></td>
            
           </tr>
           <?php
           $sales_region_object_ai->next();
           if ($sales_region_object_ai->key() == $position + $per_page) {
            break;
           }
           $count = $count + 1;
          }
          ?>
         </tbody>
        </table>
       </div>
       <div id="tabsLine-2" class="tabContent">
        <table class="form_table">
         <thead> 
          <tr>
           <th><?php echo gettext('Seq') ?>#</th>
           <th><?php echo gettext('Description') ?></th>
           <th><?php echo gettext('Status') ?></th>
           <th><?php echo gettext('Tax Region') ?></th>
           
          </tr>
         </thead>
         <tbody class="form_data_line_tbody sales_region_values" >
          <?php
          $count = 0;
          $sales_region_object_ai = new ArrayIterator($sales_region_object);
          $sales_region_object_ai->seek($position);
          while ($sales_region_object_ai->valid()) {
           $ar_sales_region = $sales_region_object_ai->current();
           ?>         
           <tr class="ar_sales_region<?php echo $count ?>">
            <td><?php $f->seq_field_d($count) ?></td>
            <td><?php $f->text_field_wid('description', 'dontCopy'); ?></td>
            <td><?php $f->status_field_d('status'); ?></td>
            <td><?php form::text_field_wid('mdm_tax_region_id'); ?></td>
           </tr>
           <?php
           $sales_region_object_ai->next();
           if ($sales_region_object_ai->key() == $position + $per_page) {
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

<div class="row small-top-margin">
 <div id="pagination" style="clear: both;">
  <?php echo $pagination->show_pagination(); ?>
 </div>
</div>

<div id="js_data">
 <ul id="js_saving_data">
  <li class="primary_column_id" data-primary_column_id="country_code" ></li>
  <li class="lineClassName" data-lineClassName="ar_sales_region" ></li>
  <li class="line_key_field" data-line_key_field="sales_region_name" ></li>
  <li class="single_line" data-single_line="false" ></li>
  <li class="form_line_id" data-form_line_id="ar_sales_region" ></li>
 </ul>
 <ul id="js_contextMenu_data">
  <li class="docLineId" data-docLineId="ar_sales_region_id" ></li>
  <li class="btn2DivId" data-btn2DivId="form_line" ></li>
  <li class="trClass" data-trclass="ar_sales_region" ></li>
  <li class="tbodyClass" data-tbodyClass="form_data_line_tbody" ></li>
  <li class="noOfTabbs" data-noOfTabbs="2" ></li>
 </ul>
</div>