<!-- * 
inoERP
 *
 * @copyright   2014 Nishit R. Das
 * @license     https://www.mozilla.org/MPL/2.0/
 * @link        http://inoideas.org
 * @source code https://github.com/inoerp/inoERP
-->


<div id="form_all"><span class="heading"><?php echo gettext('Material Element') ?></span><?php $f = new inoform() ?>
 <form action=""  method="post" id="bom_material_element"  name="bom_material_element">
  <div id ="form_header">
   <div id="tabsHeader">
    <ul class="tabMain">
     <li><a href="#tabsHeader-1"><?php echo gettext('Basic Info') ?></a></li>
     <li><a href="#tabsHeader-2"><?php echo gettext('Attachments') ?></a></li>
     <li><a href="#tabsHeader-3"><?php echo gettext('Notes') ?></a></li>
    </ul>
    <div class="tabContainer"> 
     <div id="tabsHeader-1" class="tabContent">
       <ul class="column header_field">
        <li><?php $f->l_text_field_dr_withSearch('bom_material_element_id'); ?>
         <a name="show" href="form.php?class_name=bom_material_element&<?php echo "mode=$mode"; ?>" class="show document_id bom_material_element_id"><i class="fa fa-refresh"></i></a> 
        </li>
        <li><?php $f->l_select_field_from_object('org_id', org::find_all_inventory(), 'org_id', 'org', $$class->org_id, 'org_id', '', '', $readonly); ?>      </li>
        <li><?php $f->l_text_field_d('material_element'); ?></li>
        <li><?php $f->l_text_field_d('description'); ?></li>
        <li><?php $f->status_field('status'); ?></li>
       </ul>
     </div>
     <div id="tabsHeader-2" class="tabContent">
      <div> <?php echo ino_attachement($file) ?> </div>
     </div>
     <div id="tabsHeader-3" class="tabContent">
      <div> 
       <div id="comments">
        <div id="comment_list">
         <?php echo!(empty($comments)) ? $comments : ""; ?>
        </div>
        <div id ="display_comment_form">
         <?php
         $reference_table = 'org';
         $reference_id = $$class->org_id;
         ?>
        </div>
        <div id="new_comment">
        </div>
       </div>
      </div>
     </div>
    </div>

   </div>
  </div>

  <div id ="form_line" class="form_line"><span class="heading"> Material Element Details </span>
   <div id="tabsLine">
    <ul class="tabMain">
     <li><a href="#tabsLine-1"><?php echo gettext('Details') ?></a></li>
     <li><a href="#tabsLine-2"><?php echo gettext('Future') ?> </a></li>
    </ul>
    <div class="tabContainer"> 
     <div id="tabsLine-1" class="tabContent">
      <div class="first_rowset"> 
       <ul class="column header_field"> 
        <li><?php $f->l_select_field_from_object('default_basis', bom_header::bom_charge_basis(), 'option_line_id', 'option_line_code', $$class->default_basis, 'default_basis', '' , '' , $readonly); ?>        </li>
       </ul>
      </div>
      <div class="second_rowset">
       <ul class="three_column">

       </ul>
      </div>
      <!--end of tab1 div three_column-->
     </div> 
     <!--end of tab1-->
     <div id="tabsLine-2" class="tabContent">
      <div class="first_rowset"> 
       <ul class="column five_column"> 
       </ul>
      </div>
      <div class="second_rowset">

      </div> 
      <!--                end of tab2 div three_column-->
     </div>
     <!--end of tab2 (purchasing)!!!! start of sales tab-->

    </div>

   </div>
  </div> 
 </form>
</div>

<div id="js_data">
 <ul id="js_saving_data">
  <li class="headerClassName" data-headerClassName="bom_material_element" ></li>
  <li class="savingOnlyHeader" data-savingOnlyHeader="true" ></li>
  <li class="primary_column_id" data-primary_column_id="bom_material_element_id" ></li>
  <li class="form_header_id" data-form_header_id="bom_material_element" ></li>
 </ul>
 <ul id="js_contextMenu_data">
  <li class="docHedaderId" data-docHedaderId="bom_material_element_id" ></li>
  <li class="btn1DivId" data-btn1DivId="bom_material_element" ></li>
 </ul>
</div>