<?php include_once("../../../includes/basics/basics.inc"); ?>

<?php
if (($_GET['find_cost_elements'] = 1) && (!empty($_GET['class_name']))) {
 echo '<div id="cost_elements_find_all">';
 $class = $_GET['class_name'];
 $$class = new $class;
 $key_column = $class::$key_column;
 $primary_column = $class::$primary_column;
 $all_data = $$class->findAll();
 foreach ($all_data as $obj) {
	echo '<option value="' . $obj->$primary_column . '"';
	echo '>' . $obj->$key_column . '</option>';
 }

 echo '</div>';
}
?>

