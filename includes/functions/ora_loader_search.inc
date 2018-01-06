<?php

if (!empty($_GET['submit_search']) && ($_GET['search_class'] === $class)) {
 if (count($whereFields) > 0) {
	$whereClause = implode(" AND ", $whereFields);
	$sqlWhereClause = implode(" AND ", $sqlWhereFields);
	// And then create the SQL query itself.
	$count_sql = "SELECT COUNT(*) FROM " . $table_name . ' WHERE ' . $whereClause;
	$all_download_sql = "SELECT COUNT(*) FROM " . $table_name . ' WHERE ' . $whereClause;
 } else {
	$whereClause = '';
	$count_sql = "SELECT COUNT(*) FROM " . $table_name;
	$all_download_sql = "SELECT COUNT(*) FROM " . $table_name ;
 }

//		if (!empty($_GET['group_by'])) {
//	$sql .= " GROUP BY " . $_GET['group_by'];
//	$count_sql .= " GROUP BY " . $_GET['group_by'];
//	$all_download_sql .= " GROUP BY " . $_GET['group_by'];
// }
//echo "count $count_sql";

 $total_count_a = $$class->findBySql($count_sql);
 $total_count_b = array_pop($total_count_a);
 foreach ($total_count_b as $key => $val) {
	$total_count = $val;
	break;
 }


 if (!empty($per_page)) {
	$pagination = new pagination($pageno, $per_page, $total_count);
	$pagination->setProperty('_query_string', $query_string);
	$pagination_statement = $pagination->show_pagination();
	$offset = $pagination->offset();
	$offset_s = !empty($offset) ? $offset : 0;
	$offset_e = $offset_s + $per_page;
	$sql = " SELECT * FROM (SELECT tbl.*, rownum r FROM $table_name tbl) WHERE r <= $offset_e  AND r > $offset_s ";
	if (!empty($sqlWhereClause)) {
	 $sql = " SELECT * FROM (SELECT tbl.*, rownum r FROM $table_name tbl WHERE $sqlWhereClause) WHERE r <= $offset_e  AND r > $offset_s ";
	}
 } else {
	$sql = " SELECT * FROM " . $table_name . ' WHERE ' . $whereClause;
 }
 if ((!empty($search_order_by)) && (!empty($search_asc_desc))) {
	if (is_array($search_order_by)) {
	 $sql .= ' ORDER BY ';
	 foreach ($search_order_by as $key_oby => $value_oby) {
		if (empty($search_asc_desc[$key_oby])) {
		 $search_asc_desc[$key_oby] = ' DESC ';
		}
		$sql .= $value_oby . ' ' . $search_asc_desc[$key_oby] . ' ,';
	 }
	 $sql = rtrim($sql, ',');
	} else {
	 $sql .= ' ORDER BY ' . $search_order_by . ' ' . $search_asc_desc;
	 $all_download_sql .= ' ORDER BY ' . $search_order_by . ' ' . $search_asc_desc;
	}
 }
 $search_result = $$class->findBySql($sql);
}
?>