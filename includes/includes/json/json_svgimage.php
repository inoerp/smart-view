<?php include_once("../../includes/basics/basics.inc"); ?>
<link href="<?php echo HOME_URL; ?>includes/ecss/getsvgimage.css" media="all" rel="stylesheet" type="text/css" />
<?php
 if (!empty($_GET['find_result'])) {
  if (!empty($_GET['query_v']) && !empty($_GET['chart_label']) && !empty($_GET['chart_value'])) {
   $svgimg = new getsvgimage();
   $result = $result1 = dbObject::find_by_sql($_GET['query_v']);

   $chart_label = str_replace('.', '__', ($_GET['chart_label']));
   $chart_value = str_replace('.', '__', ($_GET['chart_value']));
   $chart_name = !empty($_GET['chart_name']) ? ($_GET['chart_name']) : 'Custom View Chart';
   $chart_width = !empty($_GET['chart_width']) ? ($_GET['chart_width']) : '450';
   $chart_height = !empty($_GET['chart_height']) ? ($_GET['chart_height']) : '450';
   $chart_type = !empty($_GET['chart_type']) ? ($_GET['chart_type']) : 'clustered_column';
   $legend_name = !empty($_GET['chart_legend']) ? ($_GET['chart_legend']) : '';
   $legend_name = str_replace('.', '__', $legend_name);

//getSvgData($result, $legend_name, $chart_label, $chart_value, $legend, $labels, $data);
   $svgimg->setProperty('_chart_name', $chart_name);
   $svgimg->setProperty('_chart_width', $chart_width);
   $svgimg->setProperty('_chart_height', $chart_height);
   $svgimg->setProperty('_chart_type', $chart_type);
   $svgimg->result = $result;
   $svgimg->legend_name = $legend_name;
   $svgimg->chart_label = $chart_label;
   $svgimg->chart_value = $chart_value;
   $svg_chart = $svgimg->getSvgChart_forView();
   echo '<div id="return_divId">' . $svg_chart . '</div>';
  } else if (!empty($_GET['view_id'])) {
   $view = new view();
   $view->pageno = !empty($_GET['pageno']) ? ($_GET['pageno']) : 1;
   $view->per_page = !empty($_GET['per_page']) ? ($_GET['per_page']) : 20;
   $view->view_id = ($_GET['view_id']);
   if (!empty($_GET['filter_data'])) {
    foreach ($_GET['filter_data'] as $filter_data) {
     $view->user_filter[$filter_data['name']] = $filter_data['value'];
    }
   }
   if (!empty($_GET['sort_data'])) {
    foreach ($_GET['sort_data'] as $sort_data) {
     $view->user_sort[$sort_data['name']] = $sort_data['value'];
    }
   }
   $view->update_view_query_by_userInputs();
   $view->chart_type = !empty($_GET['chart_type']) ? $_GET['chart_type'] : $view->chart_type;
   if (!empty($view->view_id) && !empty($view->chart_type)) {
    $svgimg = new getsvgimage();
    $result = $result1 = $view->findBySql($view->query_v);
    $chart_width = !empty($_GET['chart_width']) ? ($_GET['chart_width']) : $view->chart_width;
    $chart_height = !empty($_GET['chart_height']) ? ($_GET['chart_height']) : $view->chart_height;
    $chart_type = !empty($_GET['chart_type']) ? ($_GET['chart_type']) : $view->chart_type;
    $chart_legend = !empty($_GET['chart_legend']) ? ($_GET['chart_legend']) : $view->chart_legend;
    $chart_label = !empty($_GET['chart_label']) ? ($_GET['chart_label']) : $view->chart_label;
    $chart_value = !empty($_GET['chart_type']) ? ($_GET['chart_value']) : $view->chart_value;
//getSvgData($result, $legend_name, $chart_label, $chart_value, $legend, $labels, $data);
    $svgimg->setProperty('_chart_name', $view->view_name);
    $svgimg->setProperty('_chart_width', $chart_width);
    $svgimg->setProperty('_chart_height', $chart_height);
    $svgimg->setProperty('_chart_type', $chart_type);
    $svgimg->result = $result;
    $svgimg->legend_name = str_replace('.', '__', $chart_legend);
    $svgimg->chart_label = str_replace('.', '__', $chart_label);
    $svgimg->chart_value = str_replace('.', '__', $chart_value);
    $svg_chart = $svgimg->getSvgChart_forView();
    echo '<div id="return_divId">' . $svg_chart . '</div>';
   } else {
    return false;
   }
  } else {
   return false;
  }
 }

 function getSvgData($result, $legend_name, $chart_label, $chart_value, &$legend, &$labels, &$data) {
  $result1 = $result;
  foreach ($result as $obj) {
   if (!empty($legend_name)) {
    if (!in_array($obj->$legend_name, $legend)) {
     array_push($legend, $obj->$legend_name);
    }
   }
  }

  foreach ($result as $obj) {
   if (!in_array($obj->$chart_label, $labels)) {
    array_push($labels, $obj->$chart_label);
    $row = [];
    $label = $row['label'] = $obj->$chart_label;
    $row['value'] = [];

    foreach ($legend as $l_k => $l_v) {
     $isnull = true;
     foreach ($result1 as $data_obj) {
      if (($data_obj->$chart_label) == $label && ($data_obj->$legend_name == $l_v)) {
       $row['value'][] = $obj->$chart_value;
       $isnull = false;
       break;
      }
     }
     if ($isnull) {
      $row['value'][] = null;
     }
    }
    array_push($data, $row);
   }
  }
 }
?>