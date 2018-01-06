<?php include_once("../../includes/basics/basics.inc"); ?>
<?php

if (!empty($_GET['find_result'])) {
 if (!empty($_GET['query_v'])) {
  $extn_report = new extn_report();
  $extn_report->pageno = !empty($_GET['pageno']) ? ($_GET['pageno']) : 1;
  $extn_report->per_page = !empty($_GET['per_page']) ? ($_GET['per_page']) : 20;
  $extn_report->query_v = ($_GET['query_v']);
  $extn_report->display_type = ($_GET['display_type']);
  $extn_report->no_of_grid_columns = !empty($_GET['no_of_grid_columns']) ? ($_GET['no_of_grid_columns']) : 0;
  echo '<div id="return_divId">' . $extn_report->show_extn_reportResult() . '</div>';
 } else if (!empty($_GET['report_id'])) {
  $extn_report = new extn_report();
  $extn_report->pageno = !empty($_GET['pageno']) ? ($_GET['pageno']) : 1;
  $extn_report->per_page = !empty($_GET['per_page']) ? ($_GET['per_page']) : 20;
  $extn_report->extn_report_id = ($_GET['report_id']);
  if (!empty($_GET['filter_data'])) {
   foreach ($_GET['filter_data'] as $filter_data) {
    $extn_report->user_filter[$filter_data['name']] = $filter_data['value'];
   }
  }
  if (!empty($_GET['sort_data'])) {
   foreach ($_GET['sort_data'] as $sort_data) {
    $extn_report->user_sort[$sort_data['name']] = $sort_data['value'];
   }
  }
  echo '<div id="return_divId">' ; 
  echo $extn_report->extn_reportResultById();
  echo '</div>';
 } else {
  return false;
 }
}
?>


<?php

if (!empty($_GET['viewResultById']) && !empty($_GET['view_id'])) {
 $view_i = new view();
 $view_i->view_id = $_GET['view_id'];
 echo '<div id="return_divId">';
 $view_i->viewResultById();
 echo '</div>';
}
?>


<?php

if (!empty($_GET['delete']) && $_GET['delete'] == 1) {
 echo '<div id="json_delete_fileds">';
 $content_name = $_GET['content_name'];
 $field_name = $_GET['field_name'];

 $result = content::drop_column($content_name, $field_name);

 if ($result == 1) {
  echo 'Comment is deleted!';
 } else {
  return false;
 }
 echo '</div>';
}
?>

<?php

if (!empty($_GET['tableName']) && $_GET['get_fieldName'] == 1) {
 echo '<div id="json_filed_names">';
 $tableName = $_GET['tableName'];

 $column_names = view::find_columns_of_table($tableName);

 if (count($column_names) == 0) {
  return false;
 } else {
  foreach ($column_names as $key => $value) {
   echo '<option class="table_fields_options" value="' . $value . '"';
   echo '>' . $value . '</option>';
  }
  echo '<option value="remove" class="remove_option" >Remove Field</option>';
 }
 echo '</div>';
}
?>
