      <div id ="form_line" class="form_line"><span class="heading">Lot On Hand </span>
       <div id="tabsDetail">
        <ul class="tabMain">
         <li><a href="#tabsDetail-1">Info-1 </a></li>
         <li><a href="#tabsDetail-2">Info-2 </a></li>
        </ul>
        <div class="tabContainer"> 
         <form action=""  method="post" id="inv_lot_transaction_entries_line"  name="inv_lot_transaction_entries_line">
          <div id="tabsDetail-1" class="tabContent">
           <table class="form_table">
            <thead> 
             <tr>
              <th>Item Number</th>
              <th>lot Number</th>
              <th>Quantity</th>
              <th>Origination Type</th>
              <th>Origination Date</th>
              <th>Activation Date </th>
              <th>Current Inventory</th>
              <th>Sub inventory</th>
              <th>Locator</th>
              <th>Inventory Id </th>
             </tr>
            </thead>
            <tbody class="form_data_line_tbody inv_lot_transaction_entries_values" >
             <?php
              $count = 0;
              foreach ($inv_onhand_lot_object as $inv_onhand_lot) {
                 ?>         
               <tr class="inv_lot_transaction_entries<?php echo $count ?>">
                <td><?php echo $f->text_field('item_number', $inv_onhand_lot->item_number); ?></td>
                <td><?php echo $f->text_field('lot_number', $inv_onhand_lot->lot_number); ?></td>
                <td><?php echo $f->text_field('lot_number', $inv_onhand_lot->lot_quantity); ?></td>
                <td><?php echo $f->text_field('origination_type', $inv_onhand_lot->origination_type); ?></td>
                <td><?php echo $f->text_field('origination_date', $inv_onhand_lot->origination_date); ?></td>
                <td><?php echo $f->text_field('activation_date', $inv_onhand_lot->activation_date); ?></td>
                <td><?php echo $f->text_field('org_name', $inv_onhand_lot->org_name); ?></td>
                <td><?php echo $f->text_field('subinventory', $inv_onhand_lot->subinventory); ?></td>
                <td><?php echo $f->text_field('locator', $inv_onhand_lot->locator); ?></td>
                <td><?php echo $f->text_field('inv_lot_number_id', $inv_onhand_lot->inv_lot_number_id); ?></td>

               </tr>
               <?php
               $count = $count + 1;
              }
             ?>
            </tbody>
           </table>
          </div>
          <div id="tabsDetail-2" class="tabContent">
           <table class="form_table">
            <thead> 
             <tr>
              <th>COO</th>
              <th>Org Id </th>
              <th>Item Description </th>
              <th>Lot Status</th>
              <th>lot Details</th>
             </tr>
            </thead>
            <tbody class="form_data_line_tbody inv_lot_transaction_entries_values" >
             <?php
              $count = 0;
              foreach ($inv_onhand_lot_object as $inv_onhand_lot) {
               $class_second = 'inv_lot_transaction_v';
               ?>         
               <tr class="inv_lot_transaction_entries<?php echo $count ?>">
                <td><?php echo $f->text_field('country_of_origin', $inv_onhand_lot->country_of_origin); ?></td>
                <td><?php echo $f->text_field('org_id', $inv_onhand_lot->org_id); ?></td>
                <td><?php echo $f->text_field('item_description', $inv_onhand_lot->item_description); ?></td>
                <td><?php echo $f->text_field('lot_number', $inv_onhand_lot->status); ?></td>
                <td><a class="button" href="form.php?class_name=inv_lot_number&mode=9&inv_lot_number_id=<?php echo $inv_onhand_lot->inv_lot_number_id; ?>">View</a></td>
               </tr>
               <?php
               $count = $count + 1;
              }
             ?>
            </tbody>
           </table>
          </div>
         </form>
        </div>

       </div>
      </div> 
      <div id="pagination" style="clear: both;">
       <?php echo!(empty($pagination_statement)) ? $pagination_statement : "";
       ?>
      </div>
<div id="js_data">
 <ul id="js_saving_data">
  <li class="headerClassName" data-headerClassName="inv_lot_number" ></li>
  <li class="savingOnlyHeader" data-savingOnlyHeader="true" ></li>
  <li class="primary_column_id" data-primary_column_id="inv_lot_number_id" ></li>
  <li class="form_header_id" data-form_header_id="inv_lot_number" ></li>
 </ul>
 <ul id="js_contextMenu_data">
  <li class="docHedaderId" data-docHedaderId="inv_lot_number_id" ></li>
  <li class="btn1DivId" data-btn1DivId="inv_lot_number_id" ></li>
 </ul>
</div>
