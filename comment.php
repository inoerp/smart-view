<?php
$dont_check_login = true;
$class_names = [
		'comment'
];
?>
<?php require_once("includes/functions/loader.inc"); ?>
<?php
//delete comment
if (!empty($_GET['delete']) && $_GET['delete'] == 1 && !empty($_GET['comment_id'])) {
 $comment_id = $_GET['comment_id'];
 $result = comment::delete($comment_id);
 echo '<div id="delete_comment">';
 if ($result == 1) {
	echo '<div class="message">Comment is deleted!</div>';
 } else {
	return false;
 }
 echo '</div>';
 return;
}
?>
<?php
if (!empty($_POST)) {
 return;
}
?>
<?php require_once('extensions/comment/comment_template.php') ?>
