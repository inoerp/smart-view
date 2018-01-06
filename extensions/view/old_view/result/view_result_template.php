<link href="<?php echo HOME_URL; ?>includes/ecss/getsvgimage.css" media="all" rel="stylesheet" type="text/css" />
<div id="all_contents">
 <div id="content_left"></div>
 <div id="content_right">
  <div id="content_right_left">
   <div id="content_top"></div>
   <div id="content">
    <div id="structure">
     <div id="viewResult_divId">
      <div id="form_top">
      </div>
      <!--    START OF FORM HEADER-->
      <div class="error"></div><div id="loading"></div>
      <div class="show_loading_small"></div>
      <?php echo (!empty($show_message)) ? $show_message : ""; ?> 

      <div class ="view_content">
       <span class="heading">
        <?php echo!empty($$class->view_name) ? "Custom Report : " . ucwords(str_replace('_', ' ', $$class->view_name)) : ''; ?></span>
       <div id="tabsDetailA">
        <ul class="tabMain">
         <li><a href="#tabsDetailA-1">Result Graph</a></li>
         <li><a href="#tabsDetailA-2">Result Data</a></li>
         <li><img class="showPointer" title="Refresh" alt="Refresh" class="view_refresh_button" src="<?php echo HOME_URL; ?>themes/default/images/refresh_24.png"></li>
        </ul>
        <div class="tabContainer">
         <div id="tabsDetailA-1" class="tabContent">
          <div class="draw_chart">
           <ul class="column four_column">
            <li><label>Chart Type : </label> 
             <?php echo $f->select_field_from_array('chart_type', getsvgimage::$chart_type_a, $$class->chart_type, 'chart_type'); ?></li>
            <li><label>Chart Width : </label><?php echo $f->number_field('chart_width', $$class->chart_width, '', 'chart_width'); ?></li>
            <li><label>Chart Height : </label><?php echo $f->number_field('chart_height', $$class->chart_height, '', 'chart_height'); ?></li>
            <li><label>Label Field : </label>
             <?php
             if (!empty($column_list)) {
              echo $f->select_field_from_array('chart_label', $column_list, $$class->chart_label, 'chart_label', 'medium');
             } else {
              echo $f->text_field_dl('chart_label', $$class->chart_label);
             }
             ?>
            </li>
            <li><label>Value Field : </label>
             <?php
             if (!empty($column_list)) {
              echo $f->select_field_from_array('chart_value', $column_list, $$class->chart_value, 'chart_value', 'medium');
             } else {
              echo $f->text_field_dl('chart_value', $$class->chart_value);
             }
             ?>
            </li>
            <li><label>Legend : </label>
             <?php
             if (!empty($column_list)) {
              echo $f->select_field_from_array('chart_legend', $column_list, $$class->chart_legend, 'chart_legend', 'medium');
             } else {
              echo $f->text_field_dl('chart_legend', $$class->chart_legend);
             }
             ?></li>
            <li><label>Graph : </label><input type="button" value="Draw Chart" class="button display_result draw_svg_image"></li>
           </ul>
           <div class="draw_chart_data" class="scrollElement">
            <div class="svg_image">
             <?php echo!empty($svg_chart) ? $svg_chart : ""; ?>
            </div>
           </div>
          </div>
         </div>
         <div id="tabsDetailA-2" class="tabContent">
          <?php echo $f->hidden_field('view_id', $$class->view_id); ?>
          <div class="view_filters">
          </div>
          <div class ="live_display_data scrollElement" >
           <?php
           echo $f->hidden_field_withId('view_id', $$class->view_id);
           echo!empty($$class->view_id) ? $$class->show_viewResult($$class->view_id) : "";
           ?>
          </div>
         </div>

        </div>
       </div>
      </div>


     </div>
    </div>
    <!--   end of structure-->
   </div>
   <div id="content_bottom"></div>
  </div>
  <div id="content_right_right"></div>
 </div>

</div>

<?php include_template('footer.inc') ?>
