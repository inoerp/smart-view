<div id="all_contents">
  <div id="content_left"></div>
  <div id="content_right">
    <div id="content_right_left">
      <div id="content_top"></div>
      <div id="content">
        <div id="structure">
          <div id="view_path">
            <div id="form_top">
              <ul class="form_top">
                <li> <a class="button" href="view_path.php">Create New</a> </li> 
                <li><input type="submit" class="button" form="view_path_header" name="submit_view_path" id="submit_view_path" Value="Save"></li>
        <!--        <li><input type="submit" class="button" form="org_line" name="submit_line"  id="submit_line" Value="Save Line"></li>-->
                <li><input type="reset" class="button" name="reset" form="org_line" Value="Reset All"></li>
                <li><a name="show" href="view_path.php?view_path_id=<?php echo htmlentities($view_path->view_path_id); ?>" class="show button">View</a></li>
                <li><a name="view_paths" href="view_paths.php" class="button view_paths">Paths</a></li>
                <li> <input type="submit" class="button" form="view_path_header" name="delete" id="delete"
                            onclick="return confirm('Are you sure?');"     value="Delete"></li>
                <li><script>document.write('<a class="button" href="' + document.referrer + '">Go Back</a>');</script></li>
              </ul>
            </div>
            <div id ="form_header">
              <form action="view_path.php" method="post" size="30" id="view_path_header"  >
                <ul id="form_box"> 
                  <li>

                    <div id="loading"><img alt="Loading..." 
                                           src="<?php echo HOME_URL; ?>themes/images/loading.gif"/></div>
                  </li>
                  <li>   <!--    Place for showing error messages-->

                    <div class="error"></div>
                    <?php echo (!empty($show_message)) ? $show_message : ""; ?> 


                    <!--    End of place for showing error messages-->
                  </li>
                  <h9>New View Path Entry! </h9>
                  <li class="ncontrol">
                    <div class="two_column"> 
                      <ul> 
                        <li><label>
                           View Path Id :</label> 
                          <input type="text" readonly name="view_path_id" id="view_path_id" maxlength="30" size="30"
                                 placeholder="System Generated No" value="<?php echo htmlentities($view_path->view_path_id); ?>">
                          <!--<a name="show" href="view_path.php?view_path_id=" class="show">Show</a>-->
                        </li>
                        <li><label>Column Name :</label> 
                          <select name="parent_id" id="parent_id"> 
                            <option value="" ></option> 
                            <?php
                            $coumn_name = view::find_all_idColumns();
                            foreach ($coumn_name as $key=>$value) {
                              echo '<option value="' . $value . '" ';
                              echo $value == $view_path->column_name ? 'selected' : 'none ';
                              echo '>' . $value . '</option>';
                            }
                            ?> 
                          </select> 
                        </li>
                        <li><label>Path :</label> 
                          <input type="text" required name="path" id="path" maxlength="60" size="60"
                                 placeholder="Enter a valid path" value="<?php echo htmlentities($view_path->path); ?>">
                        </li>
                        <li><label>Description  : </label> 
                          <input type="text" required name="description" maxlength="100" id="description" size="60" 
                                 placeholder="Enter view_path descrip. Limit 100 characters" value="<?php echo htmlentities($view_path->description); ?>">
                        </li>
                      </ul>
                    </div>
                    </li>
                </ul>

              </form> 
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
