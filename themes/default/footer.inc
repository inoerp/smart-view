<!--footer content-->
<div id="comment_form" class="none">
 <?php
 
 if (!empty($reference_table) && !empty($reference_id)) {
  include_once HOME_DIR . '/comment.php';
 }
 ?>
</div>

<div class="make-bg-full">
 <div class="calloutbox-full-mini nocontainer">
 </div><!-- end calloutbox -->
</div><!-- make bg -->

<div id="footer-style-1">
 <div class="container">
  <div id="footer_top"></div>
 </div>
</div>
<div id="copyrights">
 <div class="container">
  <div class="col-lg-5 col-md-6 col-sm-12">
   <div class="copyright-text">
    <p>
     <?php
     global $si;
     echo nl2br($si->footer_message);
     ?>
    </p>
   </div><!-- end copyright-text -->
  </div><!-- end widget -->
  <div class="col-lg-7 col-md-6 col-sm-12 clearfix">
   <div class="footer-menu">
   </div>
  </div><!-- end large-7 --> 
 </div><!-- end container -->
</div><!-- end copyrights -->

<?php
global $f;
echo (!empty($footer_bottom)) ? "<div id=\"footer_bottom\"> $footer_bottom </div>" : "";
echo $f->hidden_field_withId('home_url', HOME_URL);
echo $si->analytics_code;
?>
</body>
</html>
<?php
// 5. Close connection
if (isset($dbc)) {
 $dbc->close_connection();
}
?>
