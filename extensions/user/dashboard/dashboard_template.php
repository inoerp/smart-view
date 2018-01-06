<link href="<?php echo HOME_URL; ?>includes/ecss/getsvgimage.css" media="all" rel="stylesheet" type="text/css" />
<div id ="user_dashboard_divId">
 <div id="tabsHeader">
  <form action="" method="post" id="user_header" name="user_header"><span class="heading">User Dashboard 
    <a href="<?php echo HOME_URL ?>form.php?class_name=user_dashboard_config&mode=9&user_id=<?php echo $user_id ?>" 
       class='fa fa-cog'></a>
   </span>
   <div id="tabsHeader">
    <ul class="tabMain">
     <li><a href="#tabsHeader-1">Navigation</a></li>
     <li><a href="#tabsHeader-2">Quick Info</a></li>
     <li><a href="#tabsHeader-3" class="get-report-content" data-report_id="2">Lead Time</a></li>
     <li><a href="#tabsHeader-4" class="get-report-content" data-report_id="4">Inventory Health</a></li>
     <li><a href="#tabsHeader-5" class="get-view-content" data-view_id="13">Purchasing</a></li>
     <li><a href="#tabsHeader-6">WIP Value</a></li>
    </ul>
    <div class="tabContainer"> 
     <div id="tabsHeader-1" class="tabContent">
      <?php echo!empty($module_icons) ? $module_icons : '' ?>
     </div>
     <div id="tabsHeader-2" class="tabContent">
      <ul class="column three_column">
       <li>
        <h2>Notifications</h2>
        <?php
        echo block::show_block_content_by_BlockId('55');
        ?>
       </li>
       <li>
        <h2>Recent Comments</h2>
        <?php
        echo block::show_block_content_by_BlockId('52');
//                include_once HOME_URL.'report.php?class_name=ra_item&report_name=ra_report_set_item_leadtime';
        ?>
       </li>
       <li>
        <a title='Update Favourite' href="<?php echo HOME_URL ?>form.php?class_name=user_favourite&mode=9"><h2>Favourites 
          <i class="fa fa-edit"> </i></h2></a>
        <?php
        echo $fav->show_currentUser_fav();
        ?>
       </li>
      </ul>
     </div>
     <div id="tabsHeader-3" class="tabContent"></div>
     <div id="tabsHeader-4" class="tabContent"></div>
     <div id="tabsHeader-5" class="tabContent"></div>
     <div id="tabsHeader-6" class="tabContent"></div>
    </div>

   </div>
  </form>
 </div>
</div>    
