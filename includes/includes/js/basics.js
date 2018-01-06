function animateCycle()
{
 var interval = null;
 $("#animated_content > div:gt(0)").hide();

 function animateContent() {
  $('#animated_content > div:first')
          .slideUp(1000)
          .next()
          .delay(1000)
          .slideDown(1000)
          .end()
          .appendTo('#animated_content');
 }

 interval = setInterval(animateContent, 5000);
 $('#all_contents').on('click', '#animated_block', function () {
  clearInterval(interval);
 });

 $('#all_contents').on('click', '.stop_play', function () {
  clearInterval(interval);
 });

}

function getFormDetails(url) {
 $.ajax({
  url: url,
  type: 'get',
  data: {
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var newContent = $(result).find('div#structure').html();
  var allButton = $(result).find('div#header_top_container #form_top_image').html();
  if (typeof allButton === 'undefined') {
   allButton = '';
  }
  ;

  var commentForm = $(result).find('div#comment_form').html();
  if (newContent) {
   $('#structure').replaceWith('<div id="structure">' + newContent + '</div>');
   $('#header_top_container').replaceWith('<div id="header_top_container"> <ul id="form_top_image" class="draggable">' + allButton + '</ul></div>');
   $('#display_comment_form').append(commentForm);
   if ($(result).find('div#document_history').html()) {
    $('#document_history').replaceWith('<div id="document_history">' + $(result).find('div#document_history').html() + '</div>');
   }
   $.getScript("includes/js/reload.js");
   $(result).find('#js_files').find('li').each(function () {
    $.getScript($(this).html());
   });
   $(result).find('ul#css_files').find('li').each(function () {
    var filePath = $(this).html();
    if (!$("link[href='" + filePath + "']").length) {
     $('<link href="' + filePath + '" rel="stylesheet">').appendTo("head");
    }
   });
  }
 }).fail(function () {
  alert("Form loading failed!");
 });
}

function applyFilter() {

}

function arrow_menu() {
 //menu arrow
 $("#header_top .menu li > ul").each(function () {
  var parent = $(this).parent("li");
  parent.addClass("parent").find("> a").append("<span class='arrow-down'></span>");
 });

 //Add the parent class and arrow to third tier sub-menu
 $("#header_top .menu li > ul li > ul").each(function () {
  var parent = $(this).parent("li");
  parent.addClass("parent").find("> a span").removeClass("arrow-down").addClass("arrow-right");
 });
}

function getCommentForm() {
 $('#loading').show();
 var content_id = $("#content_id").val();
 $.ajax({
  url: 'comment.php',
  data: {reference_table: 'content',
   reference_id: content_id},
  type: 'get'
 }).done(function (data) {
  var div = $('#comment', $(data)).html();
  $("#new_comment").append(div);
  $('#loading').hide();
 }).fail(function () {
  alert("Comment content loading failed");
  $('#loading').hide();
 });
// $(".form_table #subinventory_id").attr("disabled",false);
}
$('body').on('click', '#comment_button', function () {
 getCommentForm();
});

function deleteComment() {
 var homeUrl = $('#home_url').val();
 var daletePath = homeUrl + 'form.php?class_name=comment';
 $("body").on('click', '.delete_button', function (e) {
  var headerId = $(this).val();
  $(".delete_button").addClass("show_loading_small");
  $(".delete_button").prop('disabled', true);
  e.preventDefault();
  if (confirm("Do you really want to delete ?\n" + headerId)) {
   $.ajax({
    url: daletePath,
    data: {
     delete_id: headerId,
     deleteType: 'header',
     delete: '1'},
    type: 'get',
    beforeSend: function () {
     $('.show_loading_small').show();
    },
    complete: function () {
     $('.show_loading_small').hide();
    }
   }).done(function (result) {
    $(".error").prepend(result);
    $("#accordion").accordion({active: 0});
    $(".delete_button").removeClass("show_loading_small");
    $(".delete_button").prop('disabled', false);
   }).fail(function (error, textStatus, xhr) {
    alert("delete failed \n" + error + textStatus + xhr);
    $(".delete_button").removeClass("show_loading_small");
    $(".delete_button").prop('disabled', false);
   });
  }
 });
}

function updateComment(comment_id, ulId) {
 var homeUrl = $('#home_url').val();
 var savePath = homeUrl + 'comment.php';
 $('#loading').show();
 return $.ajax({
  url: savePath,
  data: {update: '1',
   comment_id: comment_id},
  type: 'get'
 }).done(function (result) {
  var div = $(result).filter('div#commentForm').html();
  var ulId_h = '#' + ulId;
  $('#content').find(ulId_h).find('li.line_li').append(div);
  $('#loading').hide();
 }).fail(function (e) {
  alert("Comment update failed ");
  $('#loading').hide();
 });
}

function include_once(src) {
 var all_scripts = $(document).find('script');
 if (all_scripts) {
  for (var k = 0; k < all_scripts.length; k++) {
   if (all_scripts[k].src == src) {
    return;
   }
  }
 }
 var script = document.createElement('script');
 script.src = src;
 script.type = 'text/javascript';
 ($(document).find('HEAD')[0] || document.body).appendChild(script);
}

function getFieldNames(options) {
 var defaults = {
  fieldClass: 'table_fields',
  josnurl: 'extensions/view/json_view.php'
 };
 var settings = $.extend({}, defaults, options);
 $('#loading').show();
 $.ajax({
  url: settings.josnurl,
  data: {
   tableName: settings.tableName,
   get_fieldName: 1},
  type: 'get'
 }).done(function (result) {
  var parentClass = '.' + settings.parentClass.replace(/\s+/g, '.');
  var fieldClass = '.' + settings.fieldClass.replace(/\s+/g, '.');
  var div = $(result).filter('div#json_filed_names').html();
  if (div.length > 5) {
   $('#content').find(parentClass).find(fieldClass).empty().append(div);
  }
  $('#loading').hide();
 }).fail(function () {
  alert("table field loading failed");
  $('#loading').hide();
 });
 $(".table_fields").attr("disabled", false);
}

//function treeview
function treeView() {
 $('ul.tree_view  ul').hide();
 $('ul.tree_view > li').show();
 $('ul.tree_view > li').has('ul').addClass('contentContainer fa fa-plus-square');
 $('.tree_view').on('click', '.contentContainer, .contentViewing',
         function (e) {
          if (e.target === this && $(this).hasClass('contentContainer')) {
           $(this).find('>ul').show();
           $(this).find('>ul').find('>li').show();
           $(this).find('>ul').find('>li').has('ul').addClass('contentContainer fa-plus-square');
           $(this).removeClass('contentContainer fa-plus-square').addClass('contentViewing fa fa-minus-square');
           e.stopPropagation();
          } else if (e.target === this) {
           $(this).find('>ul').hide();
           $(this).find('>ul').find('>li').hide().removeClass('contentContainer fa-plus-square');
           $(this).removeClass('contentViewing fa-minus-square').addClass('contentContainer fa-plus-square');
           e.stopPropagation();
          }
          if (e.target === this) {
           $(this).parent().find('.contentContainer, .contentViewing').not(this).each(function (e) {
            $(this).find('ul').hide();
            $(this).find('ul').find('li').hide().removeClass('contentContainer fa-minus-square');
            $(this).removeClass('contentViewing fa-minus-square').addClass('contentContainer fa-plus-square');
           });
          }

         });

 $('body').on('click', '#expand_all_nav', function () {
  $('#sys_menu_left_vertical').find('.tree_view').find('.contentContainer, .contentViewing').each(function (e) {
   $(this).find('ul').show();
   $(this).find('ul').find('li').show();
   $(this).find('ul').find('li').has('ul').addClass('contentContainer fa-plus-square');
   $(this).removeClass('contentContainer fa-plus-square').addClass('contentViewing fa-minus-square');
  });
 });

 $('body').on('click', '#collapse_all_nav', function () {
  $('#sys_menu_left_vertical').find('.tree_view').find('.contentContainer, .contentViewing').each(function (e) {
   $(this).find('ul').hide();
   $(this).find('ul').find('li').hide().removeClass('contentContainer fa-minus-square');
   $(this).removeClass('contentViewing fa-minus-square').addClass('contentContainer fa-plus-square');
  });
 });

}


function treeView_simple() {
 $('ul.tree_view  ul').hide();
 $('ul.tree_view > li').show();
 $('ul.tree_view > li').has('ul').addClass('contentContainer');
 $('.tree_view').on('click', '.contentContainer, .contentViewing',
         function (e) {
          if ($(this).hasClass('contentContainer')) {
           $(this).find('>ul').show();
           $(this).find('>ul').find('>li').show();
           $(this).find('>ul').find('>li').has('ul').addClass('contentContainer');
           $(this).removeClass('contentContainer').addClass('contentViewing');
           e.stopPropagation();
          } else {
           $(this).find('>ul').hide();
           $(this).find('>ul').find('>li').hide().removeClass('contentContainer');
           $(this).removeClass('contentViewing').addClass('contentContainer');
           e.stopPropagation();
          }
         });

 $('.expand_collapse_all').on('click', function () {
  $(this).parent().find('.tree_view').find('.contentContainer, .contentViewing').each(
          function (e) {
           if ($(this).hasClass('contentContainer')) {
            $(this).find('ul').show();
            $(this).find('ul').find('li').show();
            $(this).find('ul').find('li').has('ul').addClass('contentContainer');
            $(this).removeClass('contentContainer').addClass('contentViewing');
           } else {
            $(this).find('ul').hide();
            $(this).find('ul').find('li').hide().removeClass('contentContainer');
            $(this).removeClass('contentViewing').addClass('contentContainer');
           }
          });
 });

}



//get blocks
function setConetntRightLeft() {
 var content_right_right = $("#content_right_right").html();
 if ((content_right_right === undefined) ||
         (content_right_right === "")) {
  $("#content_right_left").width("100%");
  $("#content_right_right").width("0%");
 } else {
  $("#content_right_left").width("84%");
  $("#content").css("float:left");
  $("#content_right_right").width("12%");
 }

}

function getBlocks() {
 var pathname = window.location.href;
 var homeUrl = $('#home_url').val();
 var blockPath = homeUrl + 'includes/basics/json.basics.php';
 var smallLoadingImg = homeUrl + 'files/images/small_loading.gif';
 $.ajax({
  url: blockPath,
  data: {all_blocks: '1',
   pathname: pathname,
  },
  type: 'POST',
  timeout: 50000,
  beforeSend: function () {
   $('#content_left').html('<img src="' + smallLoadingImg + '"\> loading...');
  }
 }).done(function (data) {
  var header_top = $('#header_top', $(data)).html();
  var header_bottom = $('#header_bottom', $(data)).html();
  var navinagtion_top = $('#navinagtion_top', $(data)).html();
  var navinagtion_bottom = $('#navinagtion_bottom', $(data)).html();
  var content_top = $('#content_top', $(data)).html();
  var content_left_top = $('#content_left_top', $(data)).html();
  var content_right_top = $('#content_right_top', $(data)).html();
  var content_left_bottom = $('#content_left_bottom', $(data)).html();
  var content_right_bottom = $('#content_right_bottom', $(data)).html();
  var content_bottom = $('#content_bottom', $(data)).html();
  var content_left = $('#content_left', $(data)).html();
  var content_right_right = $('#content_right_right', $(data)).html();
  var footer_top = $('#footer_top', $(data)).html();
  var footer_bottom = $('#footer_bottom', $(data)).html();
  $("#header_top").append(header_top);
  $("#header_bottom").append(header_bottom);
  $("#navinagtion_top").append(navinagtion_top);
  $("#navinagtion_bottom").append(navinagtion_bottom);
  $("#content_top").append(content_top);
  $("#content_left_top").append(content_left_top);
  $("#content_right_top").append(content_right_top);
  $("#content_left_bottom").append(content_left_bottom);
  $("#content_right_bottom").append(content_right_bottom);
  $("#content_bottom").append(content_bottom);
  $("#content_left").html(content_left);
  $("#content_right_right").append(content_right_right);
  $("#footer_top").append(footer_top);
  $("#footer_bottom").append(footer_bottom);
//	setConetntRightLeft();
  if ((typeof (header_top) !== 'undefined') && (header_top.length > 1)) {
   $('#header_top_container').css('display', 'block');
  }
//  treeView_simple();
//  arrow_menu();
 }).fail(function () {
  $('#content_left').html('');
 });
// $(".form_table #subinventory_id").attr("disabled",false);
}
//remoe & replace content from summary
function update_summary_list(maxListCount, shownListCount) {
 $('ul.summary_list').find('li').each(function () {
  var className = $(this).prop('class');
  var startPoint = className.lastIndexOf('_') + 1;
  var listCount = +className.substring(startPoint);
  if (listCount > maxListCount || listCount <= shownListCount) {
   $(this).hide();
  } else {
   $(this).show();
  }
 });
}

//get parameter value from window.location - equivalent og $_GET
function getUrlValues(name, user_link) {
 var link = typeof user_link === 'undefined' ? location.search : user_link;
 name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
 var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
         results = regex.exec(link);
 return results == null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
}

function modepath() {
 var url = '';
 url += getUrlValues('class_name') == null ? '' : 'class_name=' + getUrlValues('class_name') + '&';
 url += getUrlValues('mode') == null ? '' : 'mode=' + getUrlValues('mode') + '&';
 if (url != null) {
  url = '?' + url;
 }
 return url;
}

function formModePath(user_link) {
 var url = '';
 url += getUrlValues('class_name', user_link) == null ? '' : 'class_name=' + getUrlValues('class_name', user_link) + '&';
 url += getUrlValues('mode', user_link) == null ? '' : 'mode=' + getUrlValues('mode', user_link) + '&';
 if (url != null) {
  url = '?' + url;
 }
 return url;
}

//select mandatory fields
var Mandatory_Fields = "";
function select_mandatory_fields_all(form_area, Mandatory_Fields) {
 var i = 0;
 if (Mandatory_Fields.length / 2 >= 1) {
  var fieldId = Mandatory_Fields[i];
  var msg = Mandatory_Fields[i + 1];
  $(form_area + " :input").not(fieldId).on("focusin", function () {
   if ($(fieldId).val().length === 0) {
    alert(msg);
    $(fieldId).focus();
   }
  });
  $(fieldId).on("change", function () {
   if ($(fieldId).val().length === 0) {
    alert(msg);
    $(fieldId).focus();
   }
   else if (Mandatory_Fields.length >= 2) {
    Mandatory_Fields.splice(0, 2);
    if (Mandatory_Fields.length >= 2) {
     select_mandatory_fields(Mandatory_Fields);
    }
   }
  });
 }

}


function select_mandatory_fields(Mandatory_Fields) {
 select_mandatory_fields_all('#content', Mandatory_Fields);
}

function select_mandatory_fields_line(Mandatory_Fields) {
 select_mandatory_fields_all('#form_line', Mandatory_Fields);
}

function remove_row() {
 $("body").on("click", ".remove_row_img", function () {
  var trclass = $(this).closest('tr').attr("class");
  var newTrclass = trclass.replace(/\s+/g, '.');
  if (($("tr." + newTrclass).closest('form').find('tbody').first().children().filter('tr').length) > 1) {
   $("tr." + newTrclass).remove();
  } else if (($("tr." + newTrclass).closest('form').find('tbody.form_data_line_tbody').first().children().filter('tr').length) > 1) {
   $("tr." + newTrclass).remove();
  } else if (($("tr." + newTrclass).closest('form').find('tbody.form_data_detail_tbody').first().children().filter('tr').length) > 1) {
   $("tr." + newTrclass).remove();
  } else if (($("tr." + newTrclass).closest('form').find('tbody.form_data_detail_tbody_sn').first().children().filter('tr').length) > 1) {
   $("tr." + newTrclass).remove();
  } else if (($("tr." + newTrclass).closest('form').find('tbody.form_data_detail_tbody_ln').first().children().filter('tr').length) > 1) {
   $("tr." + newTrclass).remove();
  }

 });
}
//function lineDetail_QuantityValidation
function lineDetail_QuantityValidation() {
 $('#content').on('change, blur', '.line_quantity', function () {
  var lineQuantity = $(this).val();
  var detailQuantity = 0;
  $(this).closest('tr').find('.add_detail_values').find('.quantity').each(function () {
   detailQuantity += +$(this).val();
  });

  if ((detailQuantity > 0) && (lineQuantity != detailQuantity)) {
   $(this).val(detailQuantity);
   alert('Sum of detail quantity should be same as sum of line quantity\nChange detail quanityt if required');
  }
 });

 $('#content').on('change, blur', '.quantity', function () {
  var detailQuantity = 0;
  $(this).closest('tbody').find('.quantity').each(function () {
   detailQuantity += +$(this).val();
  });
  $(this).closest('.add_detail_values').closest('tr').find('.line_quantity').val(detailQuantity);
  $('.line_quantity').trigger('lineChange_t');
 });
}

//add new search criteria
function new_searchCriteria_onClick(json_url) {
 $("#new_search_criteria_add").on("click", function () {
  $('#loading').show();
  var new_search_criteria = $(".new_search_criteria").val();
  $.ajax({
   url: json_url,
   data: {new_search_criteria: new_search_criteria},
   type: 'get'
  }).done(function (result) {
   var div = $(result).filter('div#new_search_criteria').html();
   $("ul.search_form").append(div);
   $('#loading').hide();
  }).fail(function () {
   $('#loading').hide();
  });
 });
}

//add a new line on clickint add a new detail line
var detailObjectCount = 2001;
var dateCount = 30000;
function onClick_addDetailLine(noOfTabs, add_row_detail_img, tabsDetailName) {
 add_row_detail_img = (typeof add_row_detail_img !== 'undefined') ? add_row_detail_img : '.add_row_detail_img';
 tabsDetailName = (typeof tabsDetailName !== 'undefined') ? tabsDetailName : 'tabsDetail';
 var highest_seq_num = 1;
 var lastDetailNumber = 1;
 $("#content").off('click', add_row_detail_img).on("click", add_row_detail_img, function () {
  noOfTabs = $(this).closest('.tabContainer').find('.tabContent').length;
  var trClass = '.' + $(this).closest("tr").attr('class').replace(/\s+/g, '.');
  var trClass_wod = trClass.replace(/tr\./g, '');
  trClass_wod = trClass_wod.replace(/\./g, '');
  var tbodyClass = 'tbody.' + $(this).closest("tbody").attr('class').replace(/\s+/g, '.');
  if ($(this).closest('tbody').find('.detail_seq_number').last().val()) {
   highest_seq_num = +$(this).closest('tbody').find('.detail_seq_number').last().val();
  } else {
   highest_seq_num++;
  }
  var nextDetailSeqNumber_seq = (highest_seq_num) + 1;

  if ($(this).closest('tbody').find('.detail_number').last().val()) {
   lastDetailNumber = +$(this).closest('tbody').find('.detail_number').last().val();
  } else {
   lastDetailNumber++;
  }
  var nextDetailNumber = (lastDetailNumber + 1);
//	var nextDetailSeqNumber = (+lastDetailSeqNumber + 0.1).toFixed(1);
  var closetLineRowClass = $(this).closest(".class_detail_form").closest('tr').attr('class');
  var closetLineRowClass = '.' + closetLineRowClass;
  if (noOfTabs > 1) {
   var startingTab = $("tr[class*='" + trClass_wod + "']").first().closest('.tabContent').attr('id');
   var startingTabArray = startingTab.split('-');
   var startingTabLastNumber = startingTabArray[2];
   var startingTabFirstNumber = startingTabArray[1];
   var tabCount = 1;
   do {
    $("#" + tabsDetailName + "-" + startingTabFirstNumber + "-" + startingTabLastNumber).find(trClass).clone().attr("class", "new_object" + detailObjectCount).appendTo($(closetLineRowClass + " #" + tabsDetailName + "-" + startingTabFirstNumber + "-" + startingTabLastNumber + " " + tbodyClass));
    startingTabFirstNumber++;
    tabCount++;
   } while (tabCount <= noOfTabs);
  } else {
   $(trClass + ':first').clone().attr("class", "new_object" + detailObjectCount).appendTo($(closetLineRowClass + ' ' + tbodyClass));
  }

  $("tr.new_object" + detailObjectCount).find("td input[type=text]").each(function () {
   $(this).val("");
  });
  $("tr.new_object" + detailObjectCount).find("td input[type=number]").each(function () {
   $(this).val("");
  });
  $("tr.new_object" + detailObjectCount).find("td select").each(function () {
   $(this).val("");
  });

  $(".new_object" + detailObjectCount).find(".detail_seq_number").val(nextDetailSeqNumber_seq);
  $(".new_object" + detailObjectCount).find(".detail_number").val(nextDetailNumber);
  $(".new_object" + detailObjectCount).find(".date").each(function () {
   $(this).attr("id", "date" + dateCount);
   $(this).attr("class", "date");
   dateCount++;
  });
  detailObjectCount++;
 });
}


function onClick_add_new_row(trClass, tbodyClass, noOfTabs, divClassToBeCopied) {
 $("body table").on("click", ".add_row_img", function () {
//	add_new_row(trClass, tbodyClass, noOfTabs);

  var addNewRow = new add_new_rowMain();
  addNewRow.trClass = trClass;
  addNewRow.tbodyClass = tbodyClass;
  addNewRow.noOfTabs = noOfTabs;
  addNewRow.removeDefault = true;
  addNewRow.divClassToBeCopied = divClassToBeCopied;
  addNewRow.add_new_row();
 }).one();
 return 1;
}
//onClick_add_new_row();
//toggle detail lines if exists else create a new detail line
var objectDetailTabCount = 2;
var detailObjectRowCount = 600;
function addOrShow_lineDetails(afterAddNewDetail) {
 var highest_seq_num = 0;
 if ($('.form_data_detail_tbody').find('.detail_seq_number').last().val()) {
  highest_seq_num = $('.form_data_detail_tbody').find('.detail_seq_number').last().val();
 }
 var nextDetailSeqNumber_seq = (+highest_seq_num) + 1;
 $('body').on("click", "table.form_line_data_table .add_detail_values_img", function () {
  var tabID = '#' + $(this).closest('.tabContent').attr('id');
  var tdClass = '.' + $(this).closest('td').attr('class').replace(/tr\./g, '');
  var detailExists = $(this).closest("td").find(".form_detail_data_fs").length;
  if (detailExists > 0) {
   $(this).closest("td").find(".form_detail_data_fs").toggle();
  } else {
   var detailNumber = 1;
   var elementToBeCloned = $('#content').find(tabID).find(tdClass).find('.class_detail_form').first();
   var clonedElement = elementToBeCloned.clone();

   var firstTrClass = '.' + $(clonedElement).find('tbody').find("tr").first().attr('class').replace(/tr\./g, '');
   clonedElement.find("tr").not(':first-child').not(firstTrClass).remove();
   $(clonedElement).find('tbody tr').attr("class", "new_object" + detailObjectRowCount);
   clonedElement.find("input").not('.hidden').each(function () {
    $(this).val("");
   });
   clonedElement.appendTo($(this).closest("td"));
   $(this).closest("td").find("li.tabLink").each(function () {
    var tabLink = $(this).find("a[href]").attr('href');
    var n = tabLink.lastIndexOf("-");
    var newStr = tabLink.substring(0, n);
    var newTabLink = newStr + '-' + objectDetailTabCount;
    $(this).find("a[href]").attr('href', newTabLink);
   });
   $(this).closest("td").find(".tabContent").each(function () {
    var tabLink = $(this).attr('id');
    var n = tabLink.lastIndexOf("-");
    var newStr = tabLink.substring(0, n);
    var newTabLink = newStr + '-' + objectDetailTabCount;
    $(this).attr('id', newTabLink);
   });
   $(".tabsDetail").tabs();
   $(this).closest("td").find(".form_detail_data_fs").toggle();
   $(this).closest("td").find(".detail_number:first").val(detailNumber);
   $(this).closest("td").find(".detail_seq_number").val(nextDetailSeqNumber_seq);
  }
  objectDetailTabCount++;
  detailObjectRowCount++;
  if (typeof afterAddNewDetail === 'function') {
   afterAddNewDetail();
  }
 });


}

function deleteLine(json_url, delete_id, delete_type) {
 switch (delete_type) {
  case 'detail':
   var deleteType = 'detail';
   break;

  case 'line':
   var deleteType = 'line';
   break;

  case 'line2':
   var deleteType = 'line2';
   break;

  case 'header':
   var deleteType = 'header';
   break;

  case 'default':
   var deleteType = 'header';
   break;
 }
 $.ajax({
  url: json_url,
  data: {
   delete: '1',
   delete_id: delete_id,
   deleteType: deleteType},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
//	if (isDetail == 1) {
//	 var div = $(result).filter('div#json_delete_detail').html();
//	} else {
//	 var div = $(result).filter('div#json_delete_line').html();
//	}
  $(".error").append(result);
  $("#delete_button").removeClass("show_loading_small");
  $("#delete_button").prop('disabled', false);
 }).fail(function (error, textStatus, xhr) {
  alert("delete failed \n" + error + textStatus + xhr);
  $("#delete_button").removeClass("show_loading_small");
  $("#delete_button").prop('disabled', false);
 });
}
//used for deleting header forms like content/page/comment
function deleteHeader(json_url, headerId) {
 $("#delete_button").click(function (e) {
  $("#delete_button").addClass("show_loading_small");
  $("#delete_button").prop('disabled', true);
  e.preventDefault();
  if (confirm("Do you really want to delete ?\n" + headerId)) {
   $.ajax({
    url: json_url,
    data: {
     delete_id: headerId,
     deleteType: 'header',
     delete: '1'
    },
    type: 'get',
    beforeSend: function () {
     $('.show_loading_small').show();
    },
    complete: function () {
     $('.show_loading_small').hide();
    }
   }).done(function (result) {
//		var div = $(result).filter('div#json_delete_header').html();
    $(".error").append(result);
    $("#delete_button").removeClass("show_loading_small");
    $("#delete_button").prop('disabled', false);
   }).fail(function (error, textStatus, xhr) {
    alert("delete failed \n" + error + textStatus + xhr);
    $("#delete_button").removeClass("show_loading_small");
    $("#delete_button").prop('disabled', false);
   });
  }
 });
}

function deleteReferences(options) {
 var defaults = {
  deleteType: 'header',
  json_url: 'form.php?class_name=extn_contact_reference'
 };
 var settings = $.extend({}, defaults, options);

 $('#content').on('click', '.delete_ref', function () {
  var headerId = $(this).data('delete_id');
  if (confirm("Do you really want to delete ?\n" + headerId)) {
   $.ajax({
    url: settings.json_url,
    data: {
     delete_id: headerId,
     deleteType: settings.deleteType,
     delete: '1'
    },
    type: 'get',
    beforeSend: function () {
     $('.show_loading_small').show();
    },
    complete: function () {
     $('.show_loading_small').hide();
    }
   }).done(function (result) {
//		var div = $(result).filter('div#json_delete_header').html();
    $(".error").append(result);
    $("#delete_button").removeClass("show_loading_small");
    $("#delete_button").prop('disabled', false);
   }).fail(function (error, textStatus, xhr) {
    alert("delete failed \n" + error + textStatus + xhr);
    $("#delete_button").removeClass("show_loading_small");
    $("#delete_button").prop('disabled', false);
   });
  }

 });
}

function deleteData(json_url) {
 $("#delete_button").click(function (e) {
  $("#delete_button").addClass("show_loading_small");
  $("#delete_button").prop('disabled', true);
  e.preventDefault();
  $('input[name="detail_id_cb"]:checked').each(function () {
   var detail_id = $(this).val();
   if (confirm("Are you sure?\nDetail Id #" + detail_id)) {
    deleteLine(json_url, detail_id, 'detail');
   }
  });

  $('input[name="line_id_cb"]:checked').each(function () {
   var line_id = $(this).val();
   if (confirm("Are you sure?\nLine Id #" + line_id)) {
    if ($(this).closest('tbody').hasClass('form_data_line_tbody2')) {
     var lineType = 'line2';
    } else {
     var lineType = 'line';
    }
    deleteLine(json_url, line_id, lineType);
   }
  });

  if (!$('input[name="line_id_cb"]').val()) {
   var primary_column_id = $('ul#js_saving_data').find('.primary_column_id').data('primary_column_id');
   var header_id_h = '#' + primary_column_id;
   var headerId = $(header_id_h).val();
   if (confirm("Are you sure?\nHeader Id #" + headerId)) {
    deleteLine(json_url, headerId, 'header');
   }
  }

 });
}

function deleteFile(json_url, file_reference_id) {
 $('.show_loading_small').show();
 $.ajax({
  url: json_url,
  data: {delete: '1',
   file_reference_id: file_reference_id
  },
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var div = $(result).filter('div#json_delete_file').html();
  $(".error").append(div);
  $('.show_loading_small').hide();
 }).fail(function () {
  alert("File delete failed");
  $('#loading').hide();
 });
// $(".form_table #subinventory_id").attr("disabled",false);
}

function getAttachmentForm(divId, jsonFileLink) {
 $('#loading').show();
//var org_id = $(".form_table #org_id").val();
 $.ajax({
  url: jsonFileLink,
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (data) {
  var div = $('#add_attachments', $(data)).html();
  $(divId).append(div);
  $('#loading').hide();
  $('li#loading').hide();
 }).fail(function () {
  alert("Attachment loading failed");
  $('#loading').hide();
 });
}

//get the attachement form
function get_attachment_form(jsonFileLink) {
 $("body").on("click", ".attachment_button", function () {
  var closestDiv = $(this).closest("div").attr("id");
  divId = "#" + closestDiv;
  getAttachmentForm(divId, jsonFileLink);
 });
}

//get default values
//get  gl exchange conversion rate
function getExchangeRate(options) {
 var defaults = {
  json_url: 'modules/gl/currency_conversion/json_currency_conversion.php',
  rate_type: $('#exchange_rate_type').val(),
  from_currency: $('#currency').val(),
  to_currency: $('#document_currency').val() ? $('#document_currency').val() : $('#doc_currency').val()
 };
 var settings = $.extend({}, defaults, options);

 $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   rate_type: settings.rate_type,
   from_currency: settings.from_currency,
   to_currency: settings.to_currency,
   find_exchange_rate: 1
  },
  success: function (result) {
   if (result) {
    $.each(result, function (key, value) {
     switch (key) {
      case 'rate':
       $('#exchange_rate').val(+value);
       break;
     }
    });
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

//get Supplier details - supplier Sites, addresses etc - supplier_id, afterFunction not mandatory
function getSupplierDetails(jsonurl, org_id, supplier_id, trClass) {
 supplier_id = typeof (supplier_id) !== 'undefined' ? supplier_id : $("#supplier_id").val();
 $('.show_loading_small').show();
 return $.ajax({
  url: jsonurl,
  data: {supplier_id: supplier_id,
   org_id: org_id,
   find_supplier_details: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  $.each(result, function (key, value) {
   switch (key) {
    case 'supplier_site_id':
     if (typeof (trClass) !== 'undefined') {
      $('#content').find(trClass).find('.supplier_site_id').replaceWith(value);
     } else {
      $("#supplier_site_id").replaceWith(value);
     }
     break;

    case 'payment_term_id':
    case 'site_address_id':
     var className = '.' + key;
     $('#content').find(className).val(value);
     break;
   }

  });
  $('.show_loading_small').hide();
 }).fail(function () {
  alert("Supplier Site Loading failed");
  $('.show_loading_small').hide();
 }).always(function () {
  $('.show_loading_small').hide();
 });
 $(".form_table .from_subinventory_id").attr("disabled", false);
}

function get_supplier_detail_for_bu(search_all_bu) {
 var all_bu = typeof search_all_bu === 'undefined' ? false : true;
 if ($('#bu_org_id').val()) {
  var bu_org_id = $('#bu_org_id').val();
 } else {
  var bu_org_id = null;
 }
 $("#supplier_id, #supplier_name, #supplier_number").data('last', '').on("blur", function () {
  if ((!all_bu) && !$('#bu_org_id').val()) {
   alert('Select BU First!');
   return;
  }
  var last = $(this).data('last');
  var current = $(this).val();
  if (current !== '' && current !== last) {
   getSupplierDetails('modules/ap/supplier/json_supplier.php', bu_org_id);
  }
  $("#supplier_id, #supplier_name, #supplier_number").each(function () {
   var current = $(this).val();
   $(this).data('last', current);
  });
 });
}

//get Supplier site details - currency, payment terms, attachements
function getSupplierSiteDetails(jsonUrl, supplier_site_id) {
 $('.show_loading_small').show();
 $.ajax({
  url: jsonUrl,
  data: {supplier_site_id: supplier_site_id,
   find_site_details: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  $.each(result, function (key, value) {
   switch (key) {
    case 'currency':
     $("#doc_currency").val(value);
     break;

    case 'payment_term_id':
     var divId = '#' + key;
     $('#content').find(divId).val(value);
     break;
   }
  });
  $('.show_loading_small').hide();
 }).fail(function () {
  alert("Supplier Site Loading failed");
  $('.show_loading_small').hide();
 });
 $(".form_table .from_subinventory_id").attr("disabled", false);
}

//get Customer details - customer Sites, addresses etc
function getCustomerDetails(jsonurl, org_id) {
 $('.show_loading_small').show();
 var ar_customer_id = $("#ar_customer_id").val();
 $.ajax({
  url: jsonurl,
  data: {ar_customer_id: ar_customer_id,
   org_id: org_id,
   find_all_sites: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var customer_sites = $(result).find('div#json_customerSites_find_all').html();
  var receivable_ac_id = $(result).find('div#receivable_ac_id').html();
  var customer_attachment = $(result).find('#customer_header_level_attachement').html();
  var ship_to_id = $(result).find('#ship_to_id').html();
  var bill_to_id = $(result).find('#bill_to_id').html();
  var ship_to_address = $(result).find('#ship_to_address').html();
  var bill_to_address = $(result).find('#bill_to_address').html();
  var errorMsg = $(result).filter('.errorMsg').html();
  if (customer_sites.length > 5) {
   $("#ar_customer_site_id").replaceWith(customer_sites);
  }
  if (customer_attachment) {
   $("#customer_header_level_attachement").replaceWith(customer_attachment);
  }
  if (receivable_ac_id) {
   $("#receivable_ac_id").val(receivable_ac_id);
  }
  $("#ship_to_id").val(ship_to_id);
  $("#bill_to_id").val(bill_to_id);
  $("#ship_to_address").val(ship_to_address);
  $("#bill_to_address").val(bill_to_address);
  if (errorMsg !== undefined) {
   $(".error").append(errorMsg);
  }
  $('.show_loading_small').hide();
 }).fail(function () {
  alert("Customer Loading failed");
  $('.show_loading_small').hide();
 }).always(function () {
  $('.show_loading_small').hide();
 });
 $(".form_table .from_subinventory_id").attr("disabled", false);
}

function get_customer_detail_for_bu(search_all_bu) {
 var all_bu = typeof search_all_bu === 'undefined' ? false : true;
 if ($('#bu_org_id').val()) {
  var bu_org_id = $('#bu_org_id').val();
 } else {
  var bu_org_id = null;
 }
 $("#ar_customer_id, #customer_name, #customer_number").data('last', '').on("blur", function () {
  if ((!all_bu) && !$('#bu_org_id').val()) {
   alert('Select BU First!');
   return;
  }
  var last = $(this).data('last');
  var current = $(this).val();
  if (current !== '' && current !== last) {
   getCustomerDetails('modules/ar/customer/json_customer.php', bu_org_id);
  }
  $("#ar_customer_id, #customer_name, #customer_number").each(function () {
   var current = $(this).val();
   $(this).data('last', current);
  });
 });
}

//get Customer site details - currency, payment terms, attachements
function getCustomerSiteDetails(jsonUrl, customer_site_id) {
 $('.show_loading_small').show();
 $.ajax({
  url: jsonUrl,
  data: {ar_customer_site_id: customer_site_id,
   find_site_details: 1},
  type: 'get'
 }).done(function (result) {
  $.each(result, function (key, value) {
   switch (key) {
    case 'currency':
    case 'payment_term_id':
    case 'site_address_id':
     var className = '.' + key;
     $('#content').find(className).val(value);
     break;
   }

  });
  $('.show_loading_small').hide();
 }).fail(function () {
  alert("Supplier Site Loading failed");
  $('.show_loading_small').hide();
 });
 $(".form_table .from_subinventory_id").attr("disabled", false);
}

//get Subinventories
function getSubInventory(options) {
 var defaults = {
  json_url: 'modules/inv/subinventory/json_subinventory.php',
  org_id: $('#org_id').val(),
  subinventory_class: ('.subinventory_id')
 };
 var settings = $.extend({}, defaults, options);

 $('#loading').show();
 return $.ajax({
  url: settings.json_url,
  data: {
   org_id: settings.org_id,
   find_all_subinventory: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var div = $(result).filter('div#json_subinventory_find_all').html();
  if (settings.rowClass) {
   $('#content').find(settings.rowClass_d).find(settings.subinventory_class).empty().append(div);
  } else {
   $('#content').find(settings.subinventory_class).empty().append(div);
  }
 }).fail(function () {
  alert(settings.json_url);
//  alert("org name loading failed");
 }).always(function () {
  $('#loading').hide();
 });
 $(".form_table .from_subinventory_id").attr("disabled", false);
}

//get locator name
function getLocator(json_url, subinventory_id, subinventory_type, trClass) {
 $('#loading').show();
 $.ajax({
  url: json_url,
  data: {subinventory_id: subinventory_id,
   find_all_locator: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
//   var div = $('#json_locator', $(data)).html();
  var div = $(result).filter('div#json_locator_find_all').html();
  if (subinventory_type == "from_subinventory_id") {
   $(trClass + " .from_locator_id").find('option').remove();
   $(trClass + " .from_locator_id").empty().append(div);
  }
  if (subinventory_type == "to_subinventory_id") {
   $(trClass + " .to_locator_id").find('option').remove();
   $(trClass + " .to_locator_id").empty().append(div);
  }
  if (subinventory_type == "subinventory") {
   $(trClass).find(".locator_id").find('option').remove();
   $(trClass).find(".locator_id").empty().append(div);
  }

  if (subinventory_type == "oneSubinventory") {
   $('#content').find(".locator_id").find('option').remove();
   $('#content').find(".locator_id").empty().append(div);
  }

  $('#loading').hide();
 }).fail(function () {
  alert("Locator name loading failed");
  $('#loading').hide();
 });
 $(".form_table .from_locator_id").attr("disabled", false);
}

//fetch all the accounts from inventory details
function getAllInventoryAccounts(jsonUrl, ship_to_inventory, classValue) {
 $('.show_loading_small').show();
 $.ajax({
  url: jsonUrl,
  data: {ship_to_inventory: ship_to_inventory,
   find_account_details: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var div = $(result).filter('div#json_inventory_ac_all').html();
  var inv_ap_accrual_ac_id = $(result).find('div#json_ap_accrual_ac_id').html();
  var material_ac_id = $(result).find('div#json_material_ac_id').html();
  var inv_ppv_ac_id = $(result).find('div#json_inv_ppv_ac_id').html();
  $(classValue).closest('.tabContainer').find(classValue).find('.charge_ac_id').val(material_ac_id);
  $(classValue).closest('.tabContainer').find(classValue).find('.accrual_ac_id').val(inv_ap_accrual_ac_id);
  $(classValue).closest('.tabContainer').find(classValue).find('.ppv_ac_id').val(inv_ppv_ac_id);
 }).fail(function () {
  alert("Supplier Site Loading failed");
 });
 $(".form_table .from_subinventory_id").attr("disabled", false);
}

//get WIP Accounting Group
function getWipAccountingGroup(json_url, org_id) {
 $('#loading').show();
 $.ajax({
  url: json_url,
  data: {org_id: org_id,
   find_all_accounting_group: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var div = $(result).filter('div#json_accounting_group_find_all').html();
  $(".wip_accounting_group_id").empty().append(div);
  return div;
 }).fail(function () {
  alert("Accounting Group Loading Failed!!!");
 }).always(function () {
  $('#loading').hide();
 });
 $(".form_table .from_subinventory_id").attr("disabled", false);
}

//get Tax Codes
function getTaxCodes(json_url, org_id, in_out_tax, trClass) {
 $('#loading').show();
 $.ajax({
  url: json_url,
  data: {
   org_id: org_id,
   in_out_tax: in_out_tax,
   find_all_tax: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var div = $(result).filter('div#json_tax_code_find_all').html();
  if (in_out_tax === 'IN') {
   if (trClass) {
    $('#content').find(trClass).find(".input_tax").empty().append(div);
   } else {
    $(".input_tax").empty().append(div);
   }
  } else if (in_out_tax === 'OUT') {
   if (trClass) {
    $('#content').find(trClass).find(".output_tax").empty().append(div);
   } else {
    $(".output_tax").empty().append(div);
   }
  }
  return div;
 }).fail(function () {
//  alert("org name loading failed");
 }).always(function () {
  $('#loading').hide();
 });
}

//get Document Type Details
function getDocumentTypeDetails(sd_document_type_id, json_url) {
 json_url = (typeof json_url !== 'undefined') ? json_url : 'modules/sd/document_type/json_document_type.php';
 sd_document_type_id = (typeof sd_document_type_id !== 'undefined') ? sd_document_type_id : '1';
 $.ajax({
  url: json_url,
  type: 'get',
  dataType: 'json',
  data: {
   sd_document_type_id: sd_document_type_id,
   find_document_detail: 1
  },
  success: function (result) {
   $.each(result, function (key, value) {
    switch (key) {
     case 'price_list_header_id':
     case 'destination_type':
     case 'supply_source':
      var className = '.' + key;
      $('#content').find(className).val(value);
      break;
    }

   });
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

//get Price Details -- rowClass, item_id_m
function getPriceDetails(options) {
 var d = new Date();
 var month = d.getMonth() + 1;
 var day = d.getDate();
 var curernt_date = d.getFullYear() + '-' + (month < 10 ? '0' : '') + month + '-' + (day < 10 ? '0' : '') + day;
 var defaults = {
  json_url: 'modules/mdm/price_list/json_price_list.php',
  price_list_header_id: $('#price_list_header_id').val(),
  price_date: curernt_date
 };
 var settings = $.extend({}, defaults, options);
 $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   price_list_header_id: settings.price_list_header_id,
   find_price: 1,
   price_date: settings.price_date,
   item_id_m: settings.item_id_m
  },
  success: function (result) {
   if (result) {
    $.each(result, function (key, value) {
     switch (key) {
      case 'unit_price':
       var className = '.' + key;
       $('#content').find(settings.rowClass).find(className).val(value);
       break;
     }
    });
   } else {
    $('#content').find(settings.rowClass).find('.unit_price').val('');
   }

  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getBUDetails(bu_org_id, json_url) {
 json_url = (typeof json_url !== 'undefined') ? json_url : 'modules/org/business/json_bu.php';
 $.ajax({
  url: json_url,
  type: 'get',
  dataType: 'json',
  data: {
   bu_org_id: bu_org_id,
   find_bu_details: 1
  },
  success: function (result) {
   $.each(result, function (key, value) {
    switch (key) {
     case 'ledger_id':
      var className = '.' + key;
      $('#content').find(className).val(value);
      break;

     case 'currency':
      var className = '.' + key;
      $('#content').find(className).val(value);
      $('#content').find('.document_currency').val(value);
      $('#content').find('.doc_currency').val(value);
      break;

     case 'period_name_stmt':
      $('#period_id').replaceWith(value);
      break;

     case 'transaction_type' :
      $('#transaction_type').replaceWith(value);
      break;

     case 'output_tax' :
      $('#content').find('.output_tax').replaceWith(value);
      break;
    }

   });
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getLedgerDetails(gl_ledger_id, json_url) {
 json_url = (typeof json_url !== 'undefined') ? json_url : 'modules/gl/ledger/json_ledger.php';
 $.ajax({
  url: json_url,
  type: 'get',
  dataType: 'json',
  data: {
   gl_ledger_id: gl_ledger_id,
   find_ledger_details: 1
  },
  success: function (result) {
   $.each(result, function (key, value) {
    switch (key) {
     case 'currency':
      var className = '.' + key;
      $('#content').find(className).val(value);
      $('#content').find('.document_currency').val(value);
      $('#content').find('.doc_currency').val(value);
      break;

     case 'period_name_stmt':
      $('#period_id').replaceWith(value);
      break;

     case 'coa_id' :
      $('#coa_id').val(value);
      break;

     default :
      break;
    }

   });
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getARTransactionTypeDetails(ar_transaction_type_id, json_url) {
 json_url = (typeof json_url !== 'undefined') ? json_url : 'modules/ar/transaction_type/json_transaction_type.php';
 $.ajax({
  url: json_url,
  type: 'get',
  dataType: 'json',
  data: {
   ar_transaction_type_id: ar_transaction_type_id,
   find_ar_transaction_type_detail: 1
  },
  success: function (result) {
   $.each(result, function (key, value) {
    switch (key) {
     case 'payment_term_id':
     case 'transaction_class':
      var diId = '#' + key;
      $('#content').find(diId).val(value);
      break;
     case 'period_name_stmt':
      $('#period_id').replaceWith(value);
      break;

     case 'transaction_type' :
      $('#transaction_type').replaceWith(value);
      break;

     case 'receivable_ac' :
      $('#receivable_ac_id').val(value);
      break;
    }

   });
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getOnhandDetails(options) {
 var defaults = {
  json_url: 'modules/inv/onhand/json_onhand.php'
 };
 var settings = $.extend({}, defaults, options);

 $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   item_id_m: settings.item_id_m,
   org_id: settings.org_id,
   subinventory_id: settings.subinventory_id,
   locator_id: settings.locator_id,
   find_onhand_details: 1
  },
  success: function (result) {
   if (result) {
    $.each(result, function (key, value) {
     switch (key) {
      case 'onhand':
       var className = '.' + key;
       var trClass = settings.trClass;
       if (settings.fieldClass) {
        className += '.' + settings.fieldClass;
       }
       $('#content').find(trClass).find(className).val(value);
       break;
     }
    });
   } else {

   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function get_ar_receipt_source_details(bu_org_id, json_url) {
 json_url = (typeof json_url !== 'undefined') ? json_url : 'modules/ar/receipt_source/json_receipt_source.php';
 $.ajax({
  url: json_url,
  type: 'get',
  dataType: 'json',
  data: {
   bu_org_id: bu_org_id,
   find_receipt_source_details: 1
  },
  success: function (result) {
   $.each(result, function (key, value) {
    switch (key) {
     case 'receipt_source_stmt':
      $('#ar_receipt_source_id').replaceWith(value);
      break;
    }

   });
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getBPAList(options) {
 var defaults = {
  json_url: 'modules/po/json_po.php',
  bu_org_id: $('#bu_org_id').val(),
  field_name: 'po_number',
  replacing_field: 'po_number',
  trclass: false
 };
 var settings = $.extend({}, defaults, options);

 $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   bu_org_id: settings.bu_org_id,
   supplier_site_id: settings.supplier_site_id,
   item_id_m: settings.item_id_m,
   find_bpa_list: 1
  },
  success: function (result) {
   if (result) {
    if (settings.trclass) {
     var select_stmt = '<select class="select ' + settings.field_name + '" name="' + settings.field_name + '[]" style="max-width:95%;">';
    } else {
     var select_stmt = '<select id="' + settings.field_name + '" class="select ' + settings.field_name + '" name="' + settings.field_name + '[]" style="max-width:95%;">';
    }
    $.each(result, function (f_key, f_name) {
     select_stmt += '<option data-ref_po_line_id="' + f_name.po_line_id + '" value="' + f_name.po_header_id + '">' + f_name.po_number + ' Line ' + f_name.po_line_number + '</option>';
    });
    select_stmt += '</select>';
    if (settings.trclass) {
     var trclass_d = '.' + settings.trclass;
     var replacing_field_d = '.' + settings.replacing_field;
     $(trclass_d).find(replacing_field_d).replaceWith(select_stmt);
    } else {
     var replacing_field_id_h = '#' + settings.replacing_field;
     $(replacing_field_id_h).replaceWith(select_stmt);
    }
   } else {
    if (settings.trclass) {
     var select_stmt = '<select class="select ' + settings.field_name + '" name="' + settings.field_name + '[]" style="max-width:95%;">';
    } else {
     var select_stmt = '<select id="' + settings.field_name + '" class="select ' + settings.field_name + '"  name="' + settings.field_name + '[]" style=max-width:95%;">';
    }
    select_stmt += '<option></option>';
    select_stmt += '</select>';
    if (settings.trclass) {
     var trclass_d = '.' + settings.trclass;
     var replacing_field_d = '.' + settings.replacing_field;
     $(trclass_d).find(replacing_field_d).replaceWith(select_stmt);
    } else {
     var replacing_field_id_h = '#' + settings.replacing_field;
     $(replacing_field_id_h).replaceWith(select_stmt);
    }
   }
  },
  complete: function () {
   $('.document_header_id').trigger('changeHeader');
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getBPADetails(options) {
 var defaults = {
  json_url: 'modules/po/json_po.php'
 };
 var settings = $.extend({}, defaults, options);

 $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   po_header_id: settings.po_header_id,
   find_bpa_details: 1
  },
  success: function (result) {
   if (result) {
    $.each(result, function (key, value) {
     switch (key) {
      case 'po_header_id':
      case 'po_type':
      case 'po_status':
       break;

      default :
       var key_h = '#' + key;
       $(key_h).val(value);
       break;
     }
    });
   } else {

   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getBPALineDetails(options) {
 var defaults = {
  json_url: 'modules/po/json_po.php'
 };
 var settings = $.extend({}, defaults, options);

 $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   po_line_id: settings.po_line_id,
   find_bpa_line_details: 1
  },
  success: function (result) {
   if (result) {
    var trClass_d = '.' + settings.trClass;
    $.each(result, function (key, value) {
     switch (key) {
      case 'po_header_id':
      case 'po_line_id':
      case 'po_detail_id':
       break;

      case 'ship_to_id':
       $('#form_line').find(trClass_d).find('.receving_org_id').val(value);
       break;

      default :
       var key_c = '.' + key;
       $('#form_line').find(trClass_d).find(key_c).val(value);
       break;
     }
    });
   } else {

   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getSerialNumber(options) {
 var defaults = {
  json_url: 'modules/inv/serial/json_serial_number.php',
  org_id: $('#org_id').val(),
  trclass: false
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   current_org_id: settings.org_id,
   current_subinventory_id: settings.subinventory_id,
   current_locator_id: settings.locator_id,
   status: settings.status,
   item_id_m: settings.item_id_m,
   find_serial_list: 1
  },
  success: function (result) {
   if (result) {
    if (settings.trclass) {
     var select_stmt = '<select class="select inv_serial_number_id" name="inv_serial_number_id[]" style="max-width:95%;">';
    } else {
     var select_stmt = '<select id="inv_serial_number_id" class="select inv_serial_number_id" name="inv_serial_number_id[]" style="max-width:95%;">';
    }
    $.each(result, function (f_key, f_name) {
     select_stmt += '<option data-status="' + f_name.status + '" value="' + f_name.inv_serial_number_id + '">' + f_name.serial_number + '</option>';
    });
    select_stmt += '</select>';
    if (settings.trclass) {
     var trclass_d = '.' + settings.trclass;
     $(trclass_d).find('.serial_number').replaceWith(select_stmt);
    } else {
     $('#serial_number').replaceWith(select_stmt);
    }
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}


function getCoaStructure(options) {
 var defaults = {
  json_url: 'modules/gl/coa/json_coa.php',
  coa_structure_id: $('#coa_structure_id').val(),
  trclass: false
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   coa_structure_id: settings.coa_structure_id,
   find_coa_structure: 1
  },
  success: function (result) {
   if (result) {
    var count = 1;
    var option_stmt;
    $.each(result, function (f_key, f_name) {
     option_stmt += '<option data-description="' + f_name.description + '" value="' + f_name.option_line_code + '">' + f_name.option_line_value + '</option>';
    });

    $('body').find('.coa_qualifier').each(function () {
     $(this).empty().append(option_stmt);
    });
    $('#no_coa_structure_id').html('');
    $('ul#segment_structure').empty();
    $.each(result, function (f_key, f_name) {
     var field_name = 'field' + count + '[]';
     var field_stmt = '<li><label>Field #: ' + count + '</label>';
     field_stmt += '<select class="select coa_segment fields" name="' + field_name + '" style="max-width:95%;">';
     field_stmt += option_stmt;
     field_stmt += '</select>';
     field_stmt += '</li>';
     $('ul#segment_structure').append(field_stmt);
     count++;
    });
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getlotNumber(options) {
 var defaults = {
  json_url: 'modules/inv/lot/json_lot_number.php',
  org_id: $('#org_id').val(),
  trclass: false
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   org_id: settings.org_id,
   subinventory_id: settings.subinventory_id,
   locator_id: settings.locator_id,
   status: settings.status,
   item_id_m: settings.item_id_m,
   find_lot_list: 1
  },
  success: function (result) {
   if (result) {
    if (settings.trclass) {
     var select_stmt = '<select class="select inv_lot_number_id" name="inv_lot_number_id[]" style="max-width:95%;">';
    } else {
     var select_stmt = '<select id="inv_lot_number_id" class="select inv_lot_number_id" name="inv_lot_number_id[]" style="max-width:95%;">';
    }
    $.each(result, function (f_key, f_name) {
     select_stmt += '<option data-status="' + f_name.status + '" value="' + f_name.inv_lot_number_id + '">' + f_name.lot_number + '</option>';
    });
    select_stmt += '</select>';
    if (settings.trclass) {
     var trclass_d = '.' + settings.trclass;
     $(trclass_d).find('.lot_number').replaceWith(select_stmt);
    } else {
     $('#lot_number').replaceWith(select_stmt);
    }
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}
//end of get default values


function beforeSave_serial() {
 var retValue = 1;
 $('.add_detail_values').each(function () {
  if ($(this).children('.serial_generation').val()) {
   var trClass = '.' + $(this).closest("tr").attr('class').replace(/\s+/g, '.');
   var qty = +$('#content').find(trClass).find('.quantity').val();
   var noOfSerialIds = 0;
   $(this).closest('td').find('.inv_serial_number_id').each(function () {
    if ($(this).val()) {
     noOfSerialIds++;
    }
   })

   if (noOfSerialIds != qty) {
    var noOfSerials = 0;
    $(this).closest('td').find('.serial_number').each(function () {
     if ($(this).val()) {
      noOfSerials++;
     }
    })
    if (noOfSerials != qty) {
     alert('Can\'t save data as no of serial numbers doesnt match quantity');
     retValue = -10;
     return false;
    }
   }
  }
 });
 return retValue;
}

function getSerialInStore(orgId) {
 orgId = (typeof orgId !== 'undefined') ? orgId : $('#org_id').val();
 $('#content').on('blur', '.item_number', function () {
  var trClass = $(this).closest("tr").attr('class').replace(/\s+/g, '.');
  var trClass_d = '.' + trClass;
  var generation_type = $('#content').find(trClass_d).find('.serial_generation').val();

  if (!generation_type) {
   var field_stmt = '<input class="textfield serial_number" type="text" size="25" readonly name="serial_number[]" >';
   $('#content').find(trClass_d).find('.inv_serial_number_id').replaceWith(field_stmt);
   $('#content').find(trClass_d).find('.serial_number').replaceWith(field_stmt);
   alert('Item is not serial controlled.\nNo serial informatio \'ll be saved in database');
   return;
  }
  var itemIdM = $('#content').find(trClass_d).find('.item_id_m').val();
  if (!itemIdM) {
   return;
  }

  getSerialNumber({
   'org_id': orgId,
   'status': 'IN_STORE',
   'item_id_m': itemIdM,
   'trclass': trClass,
   'current_subinventory_id': $('#content').find(trClass_d).find('.from_subinventory_id').val(),
   'current_locator_id': $('#content').find(trClass_d).find('.from_locator_id').val()
  });
 });
}


function getViewResult(options) {
 var defaults = {
  json_url: 'extensions/view/json_view.php',
  display_field_id: 'live_display_data',
  query_v: $('#query_v').val(),
  show_from_query: true,
  display_type: $('#display_type').val(),
  no_of_grid_columns: $('#no_of_grid_columns').val(),
  update_result: true
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  data: {
   query_v: settings.query_v,
   find_result: 1,
   class_name: settings.class_name,
   view_id: settings.view_id,
   pageno: settings.pageno,
   per_page: settings.per_page,
   show_from_query: settings.show_from_query,
   display_type: settings.display_type,
   no_of_grid_columns: settings.no_of_grid_columns,
   filter_data: settings.filterData,
   sort_data: settings.sortData
  },
  success: function (result) {
   if (result) {
    if (settings.update_result) {
     var divHtml = $(result).filter('div#return_divId').html();
     $('.live_display_data').empty().append(divHtml);
     $.getScript("includes/js/reload.js");
    }
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function viewResultWith_pagination() {
 $('body').on('click', '.ajax_view.pagination .page_nos a', function (e) {
  e.preventDefault();
  var link = $(this).attr('href');
  var class_name = getUrlValues('class_name', link);
  var view_id = getUrlValues('view_id', link);
  var pageno = getUrlValues('pageno', link);
  var per_page = getUrlValues('per_page', link);
  var filterData = $(this).closest('div.view_content').find('.view_filters').find('.filtered_field:input').serializeArray();
  var sortData = $(this).closest('div.view_content').find('.view_filters').find('.sorted_field:input').serializeArray();
  //calling the ajax function
  getViewResult({
   class_name: class_name,
   view_id: view_id,
   pageno: pageno,
   per_page: per_page,
   show_from_query: false,
   filterData: filterData,
   sortData: sortData
  });
 });

 $('body').on('click', '.ajax_view.pagination .content_per_page', function (e) {
  e.preventDefault();
  var link = $(this).closest('.pagination').find('a').first().attr('href');
  var class_name = getUrlValues('class_name', link);
  var view_id = getUrlValues('view_id', link);
  var pageno = getUrlValues('pageno', link);
  var per_page = $(this).closest('.noOfcontents').find('.per_page').val();
  var filterData = $(this).closest('div.view_content').find('.view_filters').find('.filtered_field:input').serializeArray();
  var sortData = $(this).closest('div.view_content').find('.view_filters').find('.sorted_field:input').serializeArray();
  //calling the ajax function
  getViewResult({
   class_name: class_name,
   view_id: view_id,
   pageno: pageno,
   per_page: per_page,
   show_from_query: false,
   filterData: filterData,
   sortData: sortData
  });
 });
}

function getSearchResult(options) {
 var defaults = {
  json_url: 'includes/json/json_search.php',
  className: $('.search.class_name').val(),
  searchParameters: $('#generic_search_form').find(":input").filter(function () {
   return !!this.value;
  }).serializeArray(),
  pageno: 1,
  per_page: 0
 };
 var settings = $.extend({}, defaults, options);

 $.ajax({
  url: settings.json_url,
  type: 'get',
  data: {
   class_name: settings.className,
   search_parameters: settings.searchParameters,
   pageno: settings.pageno,
   per_page: settings.per_page
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var newContent = $(result).find('div#searchResult').html();
  $('#searchResult').empty().append(newContent);
  $.getScript("includes/js/reload.js");

 }).fail(function () {
  alert("Search Failed");
 });
}

function getSiteSearchResult(options) {
 var defaults = {
  json_url: 'includes/json/json_site_search.php',
//  className: $('.search.class_name').val(),
  searchParameters: $('#site_search').find(":input").serializeArray(),
  pageno: 1,
  per_page: 0
 };
 var settings = $.extend({}, defaults, options);

 $.ajax({
  url: settings.json_url,
  type: 'get',
  data: {
//   class_name: settings.className,
   search_parameters: settings.searchParameters,
   pageno: settings.pageno,
   per_page: settings.per_page
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var newContent = $(result).filter('#json_search_result').html();
  $('#structure').replaceWith('<div id="structure">' + newContent + '</div>');
//  $.getScript("includes/js/reload.js");
 }).fail(function () {
  alert("Search Failed");
 });
}


function getMultiSelectResult(options) {
 var defaults = {
  json_url: 'includes/json/json_multi_select.php',
  className: $('.search.class_name').val(),
  actionclassName: $('.action_class_name').val(),
  action: $('.action').val(),
  searchParameters: $('#generic_search_form').find(":input").serializeArray(),
  pageno: 1,
  per_page: 0
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  data: {
   search_class_name: settings.className,
   action_class_name: settings.actionclassName,
   action: settings.action,
   search_parameters: settings.searchParameters,
   pageno: settings.pageno,
   per_page: settings.per_page
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var allButton = $(result).filter('div#header_top_container').html();
  var newContent = $(result).find('div#structure').html();
  if (newContent) {
   $('#header_top_container').replaceWith('<div id="header_top_container">' + allButton + '</div>');
  }
  $('#structure').empty().append(newContent);
  $.getScript("includes/js/reload.js");
  $.getScript("includes/js/multi_select.js");
  $(result).find('#js_files').find('li').each(function () {
   $.getScript($(this).html());
  });
  $(result).find('ul#css_files').find('li').each(function () {
   var filePath = $(this).html();
   if (!$("link[href='" + filePath + "']").length) {
    $('<link href="' + filePath + '" rel="stylesheet">').appendTo("head");
   }
  });
 }).fail(function () {
  alert("Search Failed");
 });
}

function getSvgImage(options) {
 var defaults = {
  json_url: 'includes/json/json_svgimage.php',
  display_field_class: 'svg_image',
  query_v: $('#query_v').val(),
  chart_type: $('#chart_type').val(),
  chart_label: $('#chart_label').val(),
  chart_value: $('#chart_value').val(),
  chart_name: $('#view_name').val(),
  chart_width: $('#chart_width').val(),
  chart_height: $('#chart_height').val(),
  chart_legend: $('#chart_legend').val(),
  update_image: true
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  datatype: 'image/svg+xml',
  data: {
   query_v: settings.query_v,
   find_result: 1,
   class_name: settings.class_name,
   view_id: settings.view_id,
   chart_type: settings.chart_type,
   chart_label: settings.chart_label,
   chart_value: settings.chart_value,
   chart_name: settings.chart_name,
   chart_width: settings.chart_width,
   chart_height: settings.chart_height,
   chart_legend: settings.chart_legend,
   filter_data: settings.filterData,
   sort_data: settings.sortData
  },
  success: function (result) {
   if (result) {
    if (settings.update_image) {
     $('.svg_image').empty().append(result);
    }
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getItemRevision(options) {
 var defaults = {
  json_url: 'modules/inv/item/revision/json_item_revision.php',
  org_id: $('#org_id').val(),
  trclass: false,
  show_date: false
 };
 var settings = $.extend({}, defaults, options);
// if (!settings.item_id_m) {
//  return;
// }
 return $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   org_id: settings.org_id,
   item_id_m: settings.item_id_m,
   find_revision: 1
  },
  success: function (result) {
   if (result) {
    if (settings.trclass) {
     var select_stmt = '<select name="revision_name[]" class="from_array select revision_name">';
    } else {
     var select_stmt = '<select id="revision_name" class="select revision_name medium" name="revision_name[]" style="max-width:95%;">';
    }
    $.each(result, function (f_key, f_name) {
     if (settings.show_date) {
      select_stmt += '<option data-effective_start_date="' + f_name.effective_start_date + '" value="' + f_name.revision_name + '">' + f_name.revision_name + ' - ' + f_name.effective_start_date + '</option>';
     } else {
      select_stmt += '<option data-effective_start_date="' + f_name.effective_start_date + '" value="' + f_name.revision_name + '">' + f_name.revision_name + '</option>';
     }
    });
    select_stmt += '</select>';
    if (settings.trclass) {
     var trclass_d = '.' + settings.trclass;
     $(trclass_d).find('.revision_name').replaceWith(select_stmt);
    } else {
     $('#revision_name').replaceWith(select_stmt);
    }
   } else {
    if (settings.trclass) {
     var trclass_d = '.' + settings.trclass;
     $(trclass_d).find('.revision_name').children().remove();
    } else {
     $('#revision_name').children().remove();
    }
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getDBReportList(options) {
 var defaults = {
  json_url: 'extensions/user/dashboard/config/json_dbconfig.php',
  report_type: 'block',
  update_data: true
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  data: {
   report_type: settings.report_type,
   find_report_list: 1
  },
  success: function (result) {
   if (result) {
    var trClass = settings.trClass;
    var trClass_d = '.' + trClass.replace(/\s+/g, '.');
    var newContent = $(result).filter('div#return_divId').html();
    alert(trClass_d + ' : ' + newContent);
    if (settings.update_data) {
     $(trClass_d).find('.report_id').empty().append(newContent);
    }
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function printLabel(options) {
 var defaults = {
  json_url: 'modules/bc/static_label/json_static_label.php',
  org_id: $('#org_id').val(),
  subinventory_id: $('#subinventory_id').val(),
  item_id: $('#item_id').val(),
  bc_static_label_id: $('#bc_static_label_id').val()
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  data: {
   org_id: settings.org_id,
   subinventory_id: settings.subinventory_id,
   locator_id: settings.locator_id,
   status: settings.status,
   item_id_m: settings.item_id_m,
   print_label: 1,
   bc_static_label_id: settings.bc_static_label_id,
   print_parameters: settings.print_parameters
  },
  success: function (result) {
   if (result) {
    var divContent = $(result).filter('div#ret_message').html();
    $('.error').append(divContent);
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

//show Default Dialog Box 
function show_dialog_box() {
 $("#dialog_box").dialog({
  dialogClass: "no-close",
  modal: true,
  minWidth: 600,
  title: "Action Message",
  buttons: [
   {
    text: "OK",
    click: function () {
     $(this).dialog("close");
    }
   }
  ],
  closeOnEscape: true,
  position: {my: "center center", at: "center bottom", of: "#structure "}
 });
}

function getPayrollSchedules(options) {
 var defaults = {
  min_length: 3,
  hr_payroll_schedule_id: 'hr_payroll_schedule_id',
  json_url: 'modules/hr/payroll/json_payroll.php',
  hr_payrollId: $('#hr_payroll_id').val()
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   find_payroll_schedules: 1,
   hr_payroll_id: settings.hr_payrollId
  },
  success: function (result) {
   if (result) {
    if (settings.trDivId) {
     var select_stmt = '<select class="select hr_payroll_schedule_id" name="hr_payroll_schedule_id[]" style="max-width:95%;">';
    } else {
     var select_stmt = '<select id="hr_payroll_schedule_id" class="select hr_payroll_schedule_id" name="hr_payroll_schedule_id[]" style="max-width:95%;">';
    }
    $.each(result, function (f_key, f_name) {
     select_stmt += '<option value="' + f_name.hr_payroll_schedule_id + '">' + f_name.scheduled_date + ' : ' + f_name.period_name + '</option>';
    });
    select_stmt += '</select>';
    if (settings.trDivId) {
     var select_class_d = '.' + settings.trDivId;
     $(select_class_d).replaceWith(select_stmt);
    } else {
     $('#hr_payroll_schedule_id').replaceWith(select_stmt);
    }
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function enableLineForSaveAfterFieldChange() {
 //enable lines with change data for save
 $('#content').data('last', '').on("blur", ':input', function () {
  var last = $(this).data('last');
  var current = $(this).val();
  if ($(this).parent().prop('tagName') === 'TD') {
   if (current && current !== '' && current !== last) {
    var trClass = '.' + $(this).closest('tr').prop('class').replace(/\s+/g, '.');
    var detail_line_cb = $('#content').find(trClass).find('input[name="line_id_cb"],input[name="detail_id_cb"]');
    if (detail_line_cb) {
     $('#content').find(trClass).find('input[name="line_id_cb"],input[name="detail_id_cb"]').prop('checked', true);
     $('#content').find('input[name="detail_id_cb"]:checked').each(function () {
      $(this).closest('td.add_detail_values').closest('tr').find('input[name="line_id_cb"]').prop('checked', true);
     });
    }
   }

  }
 });
}

function openNextGLPeriod(options) {
 var defaults = {
  json_url: 'modules/gl/period/json_period.php',
  new_gl_calendar_id: $('#new_gl_calendar_id').val(),
  new_gl_calendar_name: $('#new_gl_calendar_id :selected').text(),
  ledger_id: $('#ledger_id').val(),
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  data: {
   new_gl_calendar_id: settings.new_gl_calendar_id,
   ledger_id: settings.ledger_id,
   open_next_gl_period: 1
  },
  success: function (result) {
   if (result) {
    $('.error').append('<br>Period ' + settings.new_gl_calendar_name + ' is opened<br>' + result);
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function getOpenPeriodsFromLedgerId(options) {
 var defaults = {
  json_url: 'modules/gl/period/json_period.php',
  gl_ledger_id: $('#gl_ledger_id').val(),
  trclass: false
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   gl_ledger_id: settings.gl_ledger_id,
   find_open_periods: 1
  },
  success: function (result) {
   if (result) {
    $.each(result, function (key, value) {
     switch (key) {
      case 'period_name_stmt':
       $('#gl_period_id').replaceWith(value);
       break;

      default :
       break;
     }

    });
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

//POS Terminal Number
function save_posTerminalName(options) {
 var defaults = {
  json_url: 'modules/pos/transaction/json_pos_transaction.php',
  terminal_name: $('#terminal_name').val()
 };
 var settings = $.extend({}, defaults, options);

 return $.ajax({
  url: settings.json_url,
  type: 'get',
  data: {
   terminal_name: settings.terminal_name,
   save_terminal_name: 1
  },
  success: function (result) {
   if (result) {
    $.each(result, function (key, value) {
     switch (key) {
      case 'result':
       alert(value);
       break;

      default :
       break;
     }

    });
   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

function refreshData(options) {
 var defaults = {
  json_url: 'includes/json/json_refresh.php'
 };
 var settings = $.extend({}, defaults, options);

 $.ajax({
  url: settings.json_url,
  type: 'get',
  dataType: 'json',
  data: {
   data_type: settings.data_type,
   refresh_data: 1
  },
  success: function (result) {
   if (result) {
    $.each(result, function (key, value) {
     switch (key) {
      case 'string_data':
       var dataString = value;
       if (settings.divId) {
        var idName = '#' + settings.divId;
        $('body').find(idName).empty().append(dataString);
       }

       break;
     }
    });
   } else {

   }
  },
  complete: function () {
   $('.show_loading_small').hide();
  },
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  error: function (request, errorType, errorMessage) {
   alert('Request ' + request + ' has errored with ' + errorType + ' : ' + errorMessage);
  }
 });
}

//end of global functions
$(document).ready(function () {
 var homeUrl = $('#home_url').val();
 $('.non_clickable').on('click', function (e) {
  e.preventDefault();
 });
 $('#loading').hide();
 $('.show_loading_small').hide();
 viewResultWith_pagination();
 //show & remove select search icon
 $('.select_popup').hide();
 $('#content').on('focusin', 'input', function () {
  $('#content').find('.select_popup').hide();
  $(this).parent().find('.select_popup').show();
//  if(!$(this).prop('readonly')){
//  $(this).parent().find('.select_popup').show();
// }
 });
 if ($('#display_comment_form').length > 0) {
  $('#display_comment_form').html($('#commentForm_witoutjs').html());
  $('#commentForm_witoutjs').html('');
 }

 $('body').on('click', '.content_per_page', function (e) {
  var currentUrl = window.location.toString();
  var newURL = currentUrl.replace(/per_page=/g, '');
  newURL = newURL.replace(/&&/g, '&');
  if (newURL.indexOf('?') > -1) {
   newURL = newURL + '&per_page=' + $(this).closest('div').find('select').val();
  } else {
   newURL = newURL + '?per_page=' + $(this).closest('div').find('select').val();
  }
  $(this).attr('href', newURL);
 });
//enable lines with change data for save
 enableLineForSaveAfterFieldChange();
//hiding the loader
 var $loader = $('#loading'), timer;
 $loader.hide().ajaxStart(function ()
 {
  timer && clearTimeout(timer);
  timer = setTimeout(function ()
  {
   $loader.show();
  },
          10000);
 }).ajaxStop(function ()
 {
  clearTimeout(timer);
  $loader.hide();
 });
//select page data selction in parent window
 $('body').on('click', '.quick_select', function () {
  var setData = new opener.setValFromSelectPage;
  var elemenType = $(this).parent().prop('tagName');
  if (elemenType === 'LI') {
   $(this).closest('ul').find('input').each(function () {
    setData[$(this).prop('id')] = $(this).prop('value');
   });
  } else {
   $(this).closest('tr').find('td').each(function () {
    setData[$(this).prop('class')] = $(this).text();
   });
  }

  setData.setVal();
  if (opener.setPopUpValue) {
   opener.setPopUpValue(setData);
  }
  localStorage.removeItem("field_class");
  localStorage.removeItem("reset_link");
  window.close();
 });
 //search reset button
 var link = localStorage.getItem("reset_link");
 if (link) {
  $('#multi_select a#search_reset_btn').on('click', function () {
   $(this).attr('href', link);
  });
 }

 var reset_link_ofSelect = localStorage.getItem("reset_link_ofSelect");
 if (reset_link_ofSelect) {
  $('#select_page a#search_reset_btn').on('click', function () {
   $(this).attr('href', reset_link_ofSelect);
  });
 }

//new object
 $('body').on('click', '#new_object_button', function (e) {
  e.preventDefault();
  $('#content').find(':input').not('#attach_submit').val('');
  $('#content').find(':input').not('#attach_submit').prop('disabled', false);
  $('#content').find(':checkbox').prop('checked', false);
 });
 remove_row();
 //Coa auto complete
// var coaCombination = new autoCompleteMain();
//// var coa_id = $('#coa_id').val();
// coaCombination.json_url = 'modules/gl/coa_combination/coa_search.php';
// coaCombination.primary_column1 = 'coa_id';
// coaCombination.select_class = 'select_account';
// coaCombination.min_length = 4;
// coaCombination.autoComplete();

 $('.select_account').inoAutoCompleteElement({
  json_url: 'modules/gl/coa_combination/coa_search.php',
  primary_column1: 'coa_id',
 });
 var supplierName = new autoCompleteMain();
 supplierName.json_url = 'modules/ap/supplier/json_supplier.php';
 supplierName.primary_column1 = 'bu_org_id';
 supplierName.select_class = 'select_supplier_name';
 supplierName.extra_elements = ['supplier_id', 'supplier_number'];
 supplierName.min_length = 3;
 supplierName.autoComplete();
 var customerName = new autoCompleteMain();
 customerName.json_url = 'modules/ar/customer/json_customer.php';
 customerName.primary_column1 = 'bu_org_id';
 customerName.select_class = 'select_customer_name';
 customerName.extra_elements = ['ar_customer_id', 'customer_number'];
 customerName.min_length = 3;
 customerName.autoComplete();
 var itemNumber = new autoCompleteMain();
 itemNumber.json_url = 'modules/inv/item/item_search.php';
 itemNumber.select_class = 'select_item_number';
 itemNumber.primary_column1 = 'org_id';
 itemNumber.extra_elements = ['item_id', 'item_id_m', 'item_description', 'uom_id', 'processing_lt', 'lot_generation', 'serial_generation', 'kit_cb'];
 itemNumber.min_length = 2;
 itemNumber.autoComplete();
 $('.select_item_number_all').inoAutoCompleteElement({
  json_url: 'modules/inv/item/json_item.php',
  primary_column1: 'org_id'
 });
 //auto complete for allowed BOM
 var itemNumber = new autoCompleteMain();
 itemNumber.json_url = 'modules/inv/item/item_search.php';
 itemNumber.select_class = 'select_item_number_allowedBOM';
 itemNumber.primary_column1 = 'org_id';
 itemNumber.extra_elements = ['item_id', 'item_id_m', 'item_description', 'uom_id', 'processing_lt', 'lot_generation', 'serial_generation'];
 itemNumber.min_length = 2;
 itemNumber.options = {bom_enabled_cb: "1"};
 itemNumber.autoComplete();
 $('#form_line').on('blur', '.textfield.select_item_number', function () {
  var elemenType = $(this).parent().prop('tagName');
  if (elemenType === 'TD') {
   var trClass = '.' + $(this).closest("tr").attr('class').replace(/\s+/g, '.');
   if ($('#form_line').find(trClass).find('.serial_generation').val()) {
    $('#form_line').find(trClass).find('.serial_number').attr('required', true).css('background-color', 'pink');
   }
   if ($('#form_line').find(trClass).find('.lot_generation').val()) {
    $('#form_line').find(trClass).find('.lot_number').attr('required', true).css('background-color', 'pink');
   }
  }
 });
 //popu for selecting employee
 $('#content').on('click', '.select_employee_name.select_popup', function () {
  var elemenType = $(this).parent().prop('tagName');
  if (elemenType === 'TD') {
   var rowClass = $(this).closest('tr').prop('class');
   var fieldClass = $(this).closest('td').find('.select_employee_name').prop('class');
   localStorage.setItem("row_class", rowClass);
   localStorage.removeItem("li_divId", liId);
  } else {
   var liId = $(this).closest('li').find('.employee_name').prop('id');
   localStorage.setItem("li_divId", liId);
   localStorage.removeItem("row_class");
  }
  var openUrl = 'select.php?class_name=hr_employee';
  if ($(this).siblings('.org_id').val()) {
   openUrl += '&org_id=' + $(this).siblings('.org_id').val();
  } else if ($('#org_id').val()) {
   openUrl += '&org_id=%3D' + $('#org_id').val();
  }

  if ($(this).siblings('.employee_name').val()) {
   openUrl += '&employee_name=' + $(this).siblings('.employee_name').val();
  }
  void window.open(openUrl, '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
 //popu for selecting accounts
 $('#content').on('click', '.account_popup', function () {
  var ulink = 'select.php?class_name=coa_combination';
  if ($(this).closest('td').find('input').hasClass('select_account')) {
   var rowClass = $(this).closest('tr').prop('class');
   var fieldClass = $(this).closest('td').find('.select_account').prop('class');
   localStorage.setItem("row_class", rowClass);
   if ($(this).closest('td').find('input').data('ac_type')) {
    ulink += 'ac_type=' + $(this).closest('td').find('input').data('ac_type');
   }
  } else {
   var fieldClass = $(this).closest('li').find('.select_account').prop('class');
   if ($(this).closest('li').find('select_account').data('ac_type')) {
    ulink += 'ac_type=' + $(this).closest('td').find('input').data('ac_type');
   }
  }


  localStorage.setItem("field_class", fieldClass);
  void window.open(ulink, '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
 //popu for selecting items
 $('#content').on('click', '.select_item_number.select_popup', function () {
  var elemenType = $(this).parent().prop('tagName');
  if (elemenType === 'TD') {
   var rowClass = $(this).closest('tr').prop('class');
   var fieldClass = $(this).closest('td').find('.select_item_number').prop('class');
   localStorage.setItem("row_class", rowClass);
   localStorage.setItem("field_class", fieldClass);
  } else {
   var liId = $(this).closest('li').find('.item_number').prop('id');
   localStorage.setItem("li_divId", liId);
  }
  var openUrl = 'select.php?class_name=item';
  if ($(this).siblings('.org_id').val()) {
   openUrl += '&org_id=' + $(this).siblings('.org_id').val();
  } else if ($('#org_id').val()) {
   openUrl += '&org_id=%3D' + $('#org_id').val();
  }

  if ($(this).siblings('.item_number').val()) {
   openUrl += '&item_number=' + $(this).siblings('.item_number').val();
  }
  void window.open(openUrl, '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
 $('#content').on('click', '.select_item_number_only.select_popup', function () {
  var rowClass = $(this).closest('tr').prop('class');
  var fieldClass = $(this).closest('td').find('.select_item_number').prop('class');
  localStorage.setItem("row_class", rowClass);
  localStorage.setItem("field_class", fieldClass);
  var openUrl = 'select.php?class_name=item_select';
  if ($(this).siblings('.item_number').val()) {
   openUrl += '&item_number=' + $(this).siblings('.item_number').val();
  }
  void window.open(openUrl, '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
 //toggle sereah form
// $('#searchForm').on('dblclick', function() {
//	$(this).find('.search_form').toggle();
// });
 //add new columns
 $('body').on('change', '.new_column:first', function () {
  if ($(this).val()) {
   $(this).clone().insertBefore($(this));
  }
 });
 //add new order by
 $('#content').on('change', '.search_order_by', function () {
  if ($(this).val() !== 'remove') {
   $(this).closest('li').clone().insertAfter($(this).closest('li'));
  } else {
   $(this).closest('li').remove();
  }
 });
 $('body').on('change', '#searchForm .new_search_criteria', function () {
  if ($(this).val()) {
   var newSearchCriteria = $(this).val();
   var newSearchCriteriaName = newSearchCriteria + '[]';
   var elementToBeCloned = $('.text_search').first().closest('li');
   var elementClass = $('.text_search').first().prop('class');
   var elementName = $('.text_search').first().prop('name');
   var elementLabelClass = '.label_' + elementName;
   elementLabelClass = elementLabelClass.replace('[', '');
   elementLabelClass = elementLabelClass.replace(']', '');
   clonedElement = elementToBeCloned.clone();
   $('label[for="' + elementName + '"]').text(newSearchCriteria);
   clonedElement.children().removeClass(elementClass);
   clonedElement.children().addClass(newSearchCriteria);
   clonedElement.children().prop('name', newSearchCriteriaName);
   clonedElement.find("input").each(function () {
    $(this).val("");
   });
//	 clonedElement.appendTo($(this).closest("ul"));
   clonedElement.insertBefore($(this).closest("li"));
   $(elementLabelClass + ':last').text(newSearchCriteria);
  }
 });
 //toggle detail lines
 $(".form_detail_data_fs").hide();
 $("#content").on('click', '.error', function () {
  $(this).html("");
 });
 $('body').on('click', '#sys_msg_box button.close', function () {
  $('.alert-dismissible').alert('close');
 });
 //export to excel from search result
 $("#content").on('click', '#export_excel_searchResult', function (e) {
  window.open('data:application/vnd.ms-excel,' + encodeURIComponent($('#search_result').html()));
  e.preventDefault();
 });
//remove row
 remove_row();
 //remove attached files
 $('#content').on('click', '.remove_file', function () {
  $(this).closest('ul').remove();
 });
 $('body').on('focus', ".dateTime", function () {
  var currentDate = new Date();
  var timeStamp = currentDate.getHours() + ':' + currentDate.getMinutes() + ':' + currentDate.getSeconds();
  $(this).datepicker({
   defaultDate: currentDate,
   changeMonth: true,
   changeYear: true,
   dateFormat: "yy-mm-dd " + timeStamp,
   setDate: currentDate
  });
 });
 $('body').on('focus', ".anyDate", function () {
  if ($(this).hasClass('readonly')) {
   $(this).prop('disabled', true);
   alert('readonly field');
  } else {
   var currentDate = new Date();
   $(this).datepicker({
    defaultDate: 0,
    changeMonth: true,
    changeYear: true,
    dateFormat: "yy-mm-dd",
    setDate: currentDate,
    onSelect: function (dateText, inst) {
     if ($(this).hasClass('from_date')) {
      var date = '>' + $(this).val();
      $(this).val(date);
     } else if ($(this).hasClass('to_date')) {
      var date = '<' + $(this).val();
      $(this).val(date);
     }
    }
   });
  }

 });
 $('body').on('focus', ".dateFromToday", function () {
  if ($(this).hasClass('readonly')) {
   $(this).prop('disabled', true);
   alert('readonly field');
  } else {
   var currentDate = new Date();
   $(this).datepicker({
    defaultDate: 0,
    minDate: 0,
    changeMonth: true,
    changeYear: true,
    dateFormat: "yy-mm-dd",
    setDate: currentDate
   });
  }
 });
 $('body').on('focus', ".MondayFromToday", function () {
  if ($(this).hasClass('readonly')) {
   $(this).prop('disabled', true);
   alert('readonly field');
  } else {
   var currentDate = new Date();
   $(this).datepicker({
    defaultDate: 0,
    minDate: 0,
    changeMonth: true,
    changeYear: true,
    dateFormat: "yy-mm-dd",
    setDate: currentDate,
    beforeShowDay: function (date) {
     var day = date.getDay();
     return [day == 1, ""];
    }
   });
  }
 });
 var today_date = new Date();
 var formatted_date = today_date.getFullYear() + '-' + (today_date.getMonth() + 1) + '-' + today_date.getDate();
 $(".default_date").val(formatted_date);
 //dont allow past dates if manually entered
 $('body').on('change', '.dateFromToday', function () {
  var toDay = new Date();
  var enteredDate = $(this).datepicker("getDate");
  var diff = enteredDate - toDay;
  if ((enteredDate) && (diff < -86400000)) {
   $(this).attr('value', '');
   $(this).focus();
   alert("Past date is not allowed");
  }
 });
 //creating tabs
// $("#tabs").tabs();
 //creating tabs
 $(function () {
  var tabs = $("#tabsHeader").tabs();
  var tabs = $("#tabsLine").tabs();
  tabs.find(".ui-tabs-nav").sortable({
   axis: "x",
   stop: function () {
    tabs.tabs("refresh");
   }
  });
 });
 $("#tabsVertical").tabs().addClass("ui-tabs-vertical ui-helper-clearfix");
 $("#tabsVertical li").removeClass("ui-corner-top").addClass("ui-corner-left");
// $("#tabsLine").tabs();
 $("#tabsDetail, #tabsDetailA ,#tabsDetailB, #tabsDetailC, #tabsDetailD, #tabsDetailSN, #tabsDetailLN").tabs();
 $(".tabsDetail, .tabsDetailA , .tabsDetailB, .tabsDetailC, .tabsDetailD, .tabsDetailSL, .tabsDetailLN").tabs();
//Refresh the page
 $("#refresh_button").on("click", function () {
  location.reload(true);
  localStorage.removeItem("disableContextMenu");
 });
//setConetntRightLeft();
 tinymce.init({
  selector: '.mediumtext',
  mode: "exact",
//    theme: "modern",
  plugins: 'textcolor link image lists code table emoticons',
  width: 680,
  height: 70,
  toolbar: "styleselect code | emoticons forecolor backcolor bold italic pagebreak | alignleft aligncenter alignright | bullist numlist outdent indent | link image inserttable ",
  menubar: false,
  statusbar: false,
  valid_elements: '*[*]',
  file_browser_callback: function () {
   $('#attachment_button').click();
  }
 });
 tinymce.init({
  selector: '.bigtext',
  mode: "exact",
//    theme: "modern",
  plugins: 'textcolor link image lists code table emoticons',
  width: 700,
  height: 250,
  toolbar: "styleselect code | emoticons forecolor backcolor bold italic pagebreak | alignleft aligncenter alignright | bullist numlist outdent indent | link image inserttable ",
  menubar: false,
  statusbar: false,
  valid_elements: '*[*]',
  file_browser_callback: function () {
   $('#attachment_button').click();
  }
 });
 //include tinymce for all text areas
 tinymce.init({
//  selector:'textarea',
  mode: "exact",
  theme: "modern",
  width: 200,
  height: 30,
  toolbar: false,
  menubar: "format edit",
  statusbar: false
 });
 //Popup for selecting address
 $(".address_id.select_popup").click(function (e) {
  e.preventDefault();
  var rowClass = $(this).parent().find('input').first().prop('class');
  localStorage.setItem("field_class", rowClass);
  void window.open('select.php?class_name=address', '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
  return false;
 });
//diable/enable auto complete
 $('#content').on('click', '.disable_autocomplete', function () {
  $(this).parent().siblings().each(function () {
   $(this).autocomplete({
    disabled: true
   });
  });
  $(this).parent().children().each(function () {
   $(this).autocomplete({
    disabled: true
   });
  });
 });
 $('#content').on('dblclick', ':input', function () {
  if ($(this).hasClass('ui-autocomplete-input')) {
   $(this).autocomplete({
    disabled: false
   });
  }
 });
 //basic finction --making background colors for form fields
 $("[required]").addClass('required');
 $("[readonly]").addClass('readonly');
 //Popup for print
 $(".print").click(function () {
  window.print();
 });
 //all download
 $('#export_excel_allResult').on('click', function () {
  $('#download_all').submit();
 });
 $('body').on('click', '#generate_report', function () {
  $('#program_header').submit();
 });
 show_dialog_box();
 animateCycle();
 $('#all_contents').on('click', '.start_play', function () {
  animateCycle();
 });
 $('#all_contents').on('focusIn', '#animated_block', function () {
  clearInterval(interval);
 });
 $('#all_contents').on('focusOut', '#animated_block', function () {
  animateCycle();
 });
//tree view
 treeView();
 $("#search_message").dialog({
  autoOpen: false,
  dialogClass: "no-close",
  modal: true,
  minWidth: 600,
  title: "Searching Tips",
  show: {
   effect: "blind",
   duration: 1000
  },
  hide: {
   effect: "explode",
   duration: 1000
  },
  buttons: [
   {
    text: "OK",
    click: function () {
     $(this).dialog("close");
    }
   }
  ],
  closeOnEscape: true,
  position: {my: "left top", at: "left top", of: "#structure "}
 });
 $('body').off('click', '#search_tip').on('click', '#search_tip', function () {
  $("#search_message").dialog("open");
 });
 $('body').off('click', '#menu_button8').on('click', '#menu_button8', function () {
  $("#document_history_ul").dialog("open");
 });
//save data
 if ($('ul#js_saving_data').length > 0) {
  var classSave = new saveMainClass();
  var headerClassName = $('ul#js_saving_data').find('.headerClassName').data('headerclassname');
  var lineClassName = $('ul#js_saving_data').find('.lineClassName').data('lineclassname');
  var lineClassName2 = $('ul#js_saving_data').find('.lineClassName2').data('lineclassname2');
  var detailClassName = $('ul#js_saving_data').find('.detailClassName').data('detailclassname');
  var form_header_id = $('ul#js_saving_data').find('.form_header_id').data('form_header_id');
  var form_line_id = $('ul#js_saving_data').find('.form_line_id').data('form_line_id');
  var primary_column_id = $('ul#js_saving_data').find('.primary_column_id').data('primary_column_id');
  var primary_column_id2 = $('ul#js_saving_data').find('.primary_column_id2').data('primary_column_id2');
  var line_key_field = $('ul#js_saving_data').find('.line_key_field').data('line_key_field');
  var savingOnlyHeader = $('ul#js_saving_data').find('.savingOnlyHeader').data('savingonlyheader');
  var save_vertical_tab = $('ul#js_saving_data').find('.save_vertical_tab').data('save_vertical_tab');
  var onlyOneLineAtATime = $('ul#js_saving_data').find('.onlyOneLineAtATime').data('onlyonelineatatime');
  var allLineTogether = $('ul#js_saving_data').find('.allLineTogether').data('alllinetogether');
  var single_line = $('ul#js_saving_data').find('.single_line').data('single_line');
  var before_save_function = $('ul#js_saving_data').find('.before_save_function').data('before_save_function');
  if (!before_save_function) {
   window.beforeSave = function () {
    return false;
   }
  }

  classSave.enable_select = true;
  classSave.json_url = 'form.php?class_name=' + headerClassName;
  classSave.form_header_id = form_header_id;
  classSave.form_line_id = (typeof form_line_id !== 'undefined') ? form_line_id : 'form_line';
  classSave.line_key_field = (typeof line_key_field !== 'undefined') ? line_key_field : null;
  classSave.primary_column_id = primary_column_id;
  classSave.primary_column_id2 = primary_column_id2;
  classSave.savingOnlyHeader = (savingOnlyHeader == true) ? true : false;
  classSave.saveVerticalTab = (save_vertical_tab == true) ? true : false;
  classSave.allLineTogether = (allLineTogether == true) ? true : false;
  classSave.onlyOneLineAtATime = (onlyOneLineAtATime == true) ? true : false;
  classSave.single_line = (single_line == true) ? true : false;
  if (single_line == true) {
   var primary_column_id_h = '#' + primary_column_id;
   if (!$(primary_column_id_h).val()) {
    classSave.savingOnlyHeader = true;
   } else {
    classSave.savingOnlyHeader = false;
   }
  }
  classSave.headerClassName = headerClassName;
  classSave.lineClassName = (typeof lineClassName !== 'undefined') ? lineClassName : null;
  classSave.lineClassName2 = (typeof lineClassName2 !== 'undefined') ? lineClassName2 : null;
  classSave.detailClassName = (typeof detailClassName !== 'undefined') ? detailClassName : null;
  classSave.saveMain(before_save_function);
 }

//context menu
 if ($('ul#js_contextMenu_data').length > 0) {
  var classContextMenu = new contextMenuMain();
  var docHedaderId = $('ul#js_contextMenu_data').find('.docHedaderId').data('dochedaderid');
  var docLineId = $('ul#js_contextMenu_data').find('.docLineId').data('doclineid');
  var docDetailId = $('ul#js_contextMenu_data').find('.docDetailId').data('docdetailid');
  var btn1DivId = $('ul#js_contextMenu_data').find('.btn1DivId').data('btn1divid');
  var btn2DivId = $('ul#js_contextMenu_data').find('.btn2DivId').data('btn2divid');
  var trClass = $('ul#js_contextMenu_data').find('.trClass').data('trclass');
  var tbodyClass = $('ul#js_contextMenu_data').find('.tbodyClass').data('tbodyclass');
  var noOfTabbs = $('ul#js_contextMenu_data').find('.noOfTabbs').data('nooftabbs');
  classContextMenu.docHedaderId = (typeof docHedaderId !== 'undefined') ? docHedaderId : null;
  classContextMenu.docLineId = (typeof docLineId !== 'undefined') ? docLineId : null;
  classContextMenu.docDetailId = (typeof docDetailId !== 'undefined') ? docDetailId : null;
  classContextMenu.btn1DivId = (typeof btn1DivId !== 'undefined') ? btn1DivId : null;
  classContextMenu.btn2DivId = (typeof btn2DivId !== 'undefined') ? btn2DivId : 'form_line';
  classContextMenu.trClass = (typeof trClass !== 'undefined') ? trClass : null;
  classContextMenu.tbodyClass = (typeof tbodyClass !== 'undefined') ? tbodyClass : null;
  classContextMenu.noOfTabbs = (typeof noOfTabbs !== 'undefined') ? noOfTabbs : null;
  classContextMenu.contextMenu();
 }

 $('body').on("click", "#form_line .add_row_img", function () {
  var addNewRow = new add_new_rowMain();
  var noOfTabbs = $('ul#js_contextMenu_data').find('.noOfTabbs').data('nooftabbs');
  var lineClassName = $('ul#js_saving_data').find('.lineClassName').data('lineclassname');
  addNewRow.trClass = lineClassName;
  addNewRow.tbodyClass = 'form_data_line_tbody';
  addNewRow.noOfTabs = noOfTabbs;
  addNewRow.removeDefault = true;
  addNewRow.add_new_row();
  $(".tabsDetail").tabs();
 });
 addOrShow_lineDetails();
 onClick_addDetailLine();
//selecting customer
 $(".ar_customer_id.select_popup").on("click", function () {
  localStorage.idValue = "";
  void window.open('select.php?class_name=ar_customer', '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
//selecting supplier
 $(".supplier_id.select_popup").on("click", function () {
  localStorage.idValue = "";
  void window.open('select.php?class_name=supplier', '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
 onClick_addDetailLine(2, '.add_row_detail_img3', 'tabsDetailC');
 $('#content').on('change', '.sys_extra_field_id', function () {
  var field_type = $(this).find('option:selected').data('field_type');
  $(this).closest('tr').find('.field_type').val(field_type);
 });
 $('#content').on('change', '.sys_secondary_field_id', function () {
  var field_type = $(this).find('option:selected').data('field_type');
  $(this).closest('tr').find('.field_type').val(field_type);
 });
 $('body').off('click', '.hideDiv').on('click', '.hideDiv', function () {
  $('.hideDiv').children().toggle();
  $(this).parent().find('.hideDiv_element').toggle();
  $(this).parent().parent().find('.hideDiv_element').toggle();
  $(this).removeClass('hideDiv').addClass('showDiv');
 });
 $('body').off('click', '.showDiv').on('click', '.showDiv', function () {
  $(this).children().toggle();
  $(this).parent().find('.hideDiv_element').toggle();
  $(this).parent().parent().find('.hideDiv_element').toggle();
  $(this).removeClass('showDiv').addClass('hideDiv');
 });
 $('body').off('click', '.hideDiv_input').on('click', '.hideDiv_input', function () {
  $(this).parent().find('.hideDiv_input_element').toggle();
  $(this).removeClass('hideDiv_input').addClass('showDiv_input');
 });
 $('body').off('click', '.showDiv_input').on('click', '.showDiv_input', function () {
  $(this).parent().find('.hideDiv_input_element').toggle();
  $(this).removeClass('showDiv_input').addClass('hideDiv_input');
 });
// $('#user_info .block_menu').menu();

 $('body').on('click', '#search_page #search_submit_btn', function (e) {
  e.preventDefault();
  $('.hideDiv_input').trigger('click');
  getSearchResult();
 });
 $('body').on('click', '#search_page .page_nos a', function (e) {
  e.preventDefault();
  $('.hideDiv_input').trigger('click');
  var page_no = getUrlValues('pageno', $(this).prop('href'));
  var per_page = getUrlValues('per_page', $(this).prop('href'));
  getSearchResult({
   pageno: page_no,
   per_page: per_page
  });
 });
 $('body').on('click', '#search_page a.content_per_page', function (e) {
  e.preventDefault();
  $('.hideDiv_input').trigger('click');
  var per_page = $(this).closest('.noOfcontents').find('.per_page').val();
  getSearchResult({
   per_page: per_page
  });
 });
 $('body').on('click', '#site_search_submit', function (e) {
  e.preventDefault();
  getSiteSearchResult();
 });
 $('body').on('submit', '#site_search', function (e) {
  e.preventDefault();
  getSiteSearchResult();
 });
 $('body').on('click', '#site_search_content .page_nos a', function (e) {
  e.preventDefault();
  $('.hideDiv_input').trigger('click');
  var page_no = getUrlValues('pageno', $(this).prop('href'));
  var per_page = getUrlValues('per_page', $(this).prop('href'));
  getSiteSearchResult({
   pageno: page_no,
   per_page: per_page
  });
 });
 $('body').on('click', '#site_search_content a.content_per_page', function (e) {
  e.preventDefault();
  $('.hideDiv_input').trigger('click');
  var per_page = $(this).closest('.noOfcontents').find('.per_page').val();
  getSiteSearchResult({
   per_page: per_page
  });
 });
 $('body').on('click', '#multi_select #search_submit_btn', function (e) {
  e.preventDefault();
  $('.hideDiv_input').trigger('click');
  getMultiSelectResult();
 });
 $('body').on('click', '#multi_select .page_nos a', function (e) {
  e.preventDefault();
  $('.hideDiv_input').trigger('click');
  var page_no = getUrlValues('pageno', $(this).prop('href'));
  var per_page = getUrlValues('per_page', $(this).prop('href'));
  getMultiSelectResult({
   pageno: page_no,
   per_page: per_page
  });
 });
 $('body').on('click', '#multi_select a.content_per_page', function (e) {
  e.preventDefault();
  $('.hideDiv_input').trigger('click');
  var per_page = $(this).closest('.noOfcontents').find('.per_page').val();
  getMultiSelectResult({
   per_page: per_page
  });
 });
 var contactObjectCount = 2;
 $('#content').on('click', 'li#add_new_contact', function () {
  $(this).closest('ul').find('li').first().clone().attr("class", "new_object" + contactObjectCount).prependTo($(this).closest('ul'));
  contactObjectCount++;
 });
 //popup for contact
 $('#content').on('click', '.extn_contact_id.select_popup', function () {
  var fieldClass = $(this).closest('li').prop('class');
  localStorage.setItem("contact_field_class", fieldClass);
  void window.open('select.php?class_name=extn_contact', '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
 getBlocks();
 $('body').on('click', '#path_by_module a,.search_result a, #header_top .menu a, #sys_menu_left_vertical .menu a,#search_result .action a, #pagination .page_nos a, #new_page_button', function (e) {
  e.preventDefault();
  var urlLink = $(this).attr('href');
  var urlLink_a = urlLink.split('?');
  var urlLink_firstPart_a = urlLink_a[0].split('/');
  var pageType = urlLink_firstPart_a.pop();
  if (pageType == 'form.php') {
   var formUrl = 'includes/json/json_form.php?' + urlLink_a[1];
  } else if (pageType == 'program.php') {
   var formUrl = 'includes/json/json_program.php?' + urlLink_a[1];
  } else {
   var formUrl = urlLink;
  }
  getFormDetails(formUrl);
 }).one();
// $('#sys_menu_left_vertical .menu a').on('click', function (e) {
//  e.preventDefault();
//  var urlLink = $(this).attr('href');
//  var urlLink_a = urlLink.split('?');
//  var urlLink_firstPart_a = urlLink_a[0].split('/');
//  var pageType = urlLink_firstPart_a.pop();
//  if (pageType == 'form.php') {
//   var formUrl = 'includes/json/json_form.php?' + urlLink_a[1];
//  } else if (pageType == 'program.php') {
//   var formUrl = 'includes/json/json_program.php?' + urlLink_a[1];
//  } else {
//   var formUrl = urlLink;
//  }
//  getFormDetails(formUrl);
// }).one();

 $('body').on('click', '#pagination a.content_per_page', function (e) {
  e.preventDefault();
  var urlLink = $(this).closest('#pagination').find('a').first().attr('href');
  var urlLink_a = urlLink.split('?');
  var urlLink_firstPart_a = urlLink_a[0].split('/');
  var pageType = urlLink_firstPart_a.pop();
  if (pageType == 'form.php') {
   urlLink_a[1] += '&per_page=' + $(this).parent().find('.per_page').val();
   var formUrl = 'includes/json/json_form.php?' + urlLink_a[1];
  } else {
   var formUrl = urlLink;
  }
  getFormDetails(formUrl);
 }).one();
 $('body').on('click', '#content a.show', function (e) {
  var headerId_v = $(this).parent().find(':input').val();
  var headerId = $(this).parent().find(':input').attr('id');
  e.preventDefault();
  var urlLink = $(this).attr('href');
  var urlLink_a = urlLink.split('?');
  var formUrl = 'includes/json/json_form.php?' + urlLink_a[1] + '&' + headerId + '=' + headerId_v;
  getFormDetails(formUrl);
 }).one();
 //Delete the comment form
 deleteComment();
//Update the comment form
 $("body").on('click', '.update_button', function (e) {
  e.preventDefault();
  var comment_id = $(this).val();
  var ulId = $(this).closest(".commentRecord").prop('id');
  if (confirm("Are you sure?")) {
   updateComment(comment_id, ulId);
  }
  e.stopPropagation();
 });
 $('body').on('click', '.submit_comment', function () {
  $('.show_loading_small').show();
  $(this).closest('form').find('textarea').each(function () {
   var divId = $(this).prop('id');
   var data = tinyMCE.get(divId).getContent();
   $(this).html(data);
  });
  var headerData = $(this).closest('form').serializeArray();
  var homeUrl = $('#home_url').val();
  var savePath = homeUrl + 'form.php?class_name=comment';
  saveHeader(savePath, headerData, '#comment_id', '', '', true, 'comment');
  $(".comment_error").replaceWith('<input type="button" value="Reload page" onclick="location.reload();">');
 });
 $('body').off('click', '#save_program').on('click', '#save_program', function () {
  $('.show_loading_small').show();
  var headerData = $(this).closest('form').serializeArray();
  var class_name = $('.class_name').val();
  var homeUrl = $('#home_url').val();
  var savePath = homeUrl + 'program.php?class_name=' + class_name;
  saveHeader(savePath, headerData, '#sys_program', '', '', true, 'program_header');
 });
 //FILE attachment
 var fu = new fileUploadMain();
 fu.json_url = homeUrl + 'extensions/file/upload.php';
 fu.fileUpload();
 //popu for selecting AR Transaction
 $('body').on('click', '.select_transaction_number.select_popup', function () {
  if ($(this).closest('tr').find('.ar_receipt_line_id').first().val()) {
   alert('You are not allowed to select a new transaction\nCancell or Viod the payment if required');
   return;
  }
  var rowClass = $(this).closest('tr').prop('class');
  var fieldClass = $(this).closest('td').find('.select_transaction_number').prop('class');
  localStorage.setItem("row_class", rowClass);
  localStorage.setItem("field_class", fieldClass);
  var openUrl = 'select.php?class_name=ar_unpaid_transaction_v';
  openUrl += '&ar_customer_id=' + $('#ar_customer_id').val();
  localStorage.setItem("reset_link_ofSelect", openUrl);
  void window.open(openUrl, '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
 //bank account popup
 $("body").on("click", '.mdm_bank_account_id.select_popup', function () {
  void window.open('select.php?class_name=mdm_bank_account_v', '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });
 //coa structure
 $('body').on('change', '#coa_structure_id', function () {
  if (!$('#coa_id').val()) {
   getCoaStructure();
  }
 });
//open new period
 $('body').on('click', '#open_next_period', function () {
  if ($('#new_gl_calendar_id').val()) {
   var period_name = $('#new_gl_calendar_id option:selected').text();
   if (confirm("Open " + period_name + " Period ?\n")) {
    openNextGLPeriod();
   }
  } else {
   alert('No period avaibale to open');
  }
 });
 $('body').on('click', 'a.payslipBy_periodName', function (e) {
  var headerId_v = $(this).closest('td').find('select').val();
  var headerId = $(this).closest('td').find('select').attr('id');
  e.preventDefault();
  var urlLink = $(this).attr('href');
  var urlLink_a = urlLink.split('?');
  var formUrl = 'includes/json/json_form.php?' + urlLink_a[1] + '&' + headerId + '=' + headerId_v + '&employee_id=' + $('#employee_id').val();
  getFormDetails(formUrl);
 }).one();
 $('body').on('click', 'a.hr_approval_limit_assignment_id', function (e) {
  var position_id_v = $('#position_id').val();
  var job_id_v = $('#job_id').val();
  var bu_org_id_v = $('#bu_org_id').val();
  e.preventDefault();
  var urlLink = $(this).attr('href');
  var urlLink_a = urlLink.split('?');
  var formUrl = 'includes/json/json_form.php?' + urlLink_a[1] + '&position_id=' + position_id_v + '&job_id=' + job_id_v + '&bu_org_id=' + bu_org_id_v;
  getFormDetails(formUrl);
 }).one();
 $('body').on('click', 'a.sys_profile_header_id', function (e) {
  e.preventDefault();
  var sys_profile_header_id = $('#sys_profile_header_id').val();
  var profile_level = $('#profile_level').val();
  var urlLink = $(this).attr('href');
  var urlLink_a = urlLink.split('?');
  var formUrl = 'includes/json/json_form.php?' + urlLink_a[1] + '&sys_profile_header_id=' + sys_profile_header_id + '&profile_level=' + profile_level;
  getFormDetails(formUrl);
 }).one();
 $('body').on('click', 'a.sys_hold_reference_doc_id', function (e) {
  e.preventDefault();
  var reference_table = $('#reference_table').val();
  var reference_id = $('#reference_id').val();
  var urlLink = $(this).attr('href');
  var urlLink_a = urlLink.split('?');
  var formUrl = 'includes/json/json_form.php?' + urlLink_a[1] + '&reference_table=' + reference_table + '&reference_id=' + reference_id;
  getFormDetails(formUrl);
 }).one();
 $('body').on('click', 'a.bc_label_auto_trigger_id', function (e) {
  e.preventDefault();
  var transaction_type_id = $('#transaction_type_id').val();
  var association_level = $('#association_level').val();
  var urlLink = $(this).attr('href');
  var urlLink_a = urlLink.split('?');
  var formUrl = 'includes/json/json_form.php?' + urlLink_a[1] + '&transaction_type_id=' + transaction_type_id + '&association_level=' + association_level;
  getFormDetails(formUrl);
 }).one();
 $("#filter_area").dialog({
  autoOpen: false,
  dialogClass: "no-close",
  modal: true,
  minWidth: 800,
  title: "Filters",
  show: {
   effect: "blind",
   duration: 1000
  },
  hide: {
   effect: "explode",
   duration: 1000
  },
  buttons: [
   {
    text: "Done",
    click: function () {
     $("#filter_area").find('input.field_name').val('');
     $(this).dialog("close");
    }
   }
  ],
  closeOnEscape: true,
  position: {my: "center center", at: "center center"}
 });
 $('body').off('click', '.apply-filter').on('click', '.apply-filter', function () {
  var inputFieldName = $(this).closest('.list_filter').find('select.field_name').val();
  var inputFieldCondition = $(this).closest('.list_filter').find('select.condition_name').val();
  var inputFieldValue = $(this).closest('.list_filter').find('input.condition_value').val();
  var filterHtml = ' ' + inputFieldName;
  filterHtml += ' ' + inputFieldCondition;
  filterHtml += ' ' + inputFieldValue;
  var elementClass = 'applied-filter ' + inputFieldName;
  var elementToBeCloned = $('.applied_filters').last().clone().attr('data-field_name', inputFieldName).attr('class', elementClass);
  $(elementToBeCloned).find('button.toggle-filter').append(filterHtml);
  $('#searchForm').append(elementToBeCloned);
  var hiddenFieldValue = inputFieldCondition + inputFieldValue;
  var hiddenInput = '<input class="filter_field ' + inputFieldName + ' " type="hidden" value="' + hiddenFieldValue + '" name="' + inputFieldName + '[]" form="generic_search_form">';
  $('#generic_search_form').find('ul.search_form').append(hiddenInput);
  getSearchResult();
 });
 $('body').on('click', '#search_result .ino_filter', function () {
  $("#filter_area").dialog("open");
  var select_field = '<select class="field_name form-control" name="field_name">';
  $(this).closest('#search_result').find('th').each(function () {
   if ($(this).data('field_name')) {
    var fname = $(this).data('field_name');
    select_field += '<option value="' + fname + '"> ' + fname + ' </option> ';
   }
  });
  select_field += '</select>';
  $("#filter_area").find('input.field_name').replaceWith(select_field);
  $("#filter_area").find('select.field_name').val($(this).closest('th').data('field_name'));
 });
// $('body').off('click', '#search_result .ino_filter').on('click', '#search_result .ino_filter', function () {
//  $("#filter_area").dialog("open");
//  $("#filter_area").find('input.field_name').val($(this).closest('th').data('field_name'));
// });

 $('body').on('click', '#search_result .ino_sort_a_z', function () {
  $('#searchForm').find('.search_order_by').val($(this).closest('th').data('field_name'));
  $('#searchForm').find('.search_asc_desc').val('asc');
  getSearchResult();
 });
 $('body').on('click', '.add-element', function () {
  $(this).closest('.list_filter').clone().appendTo($(this).closest('.well'));
 });
 $('body').on('click', '.remove-element', function () {
  if ($('.list_filter').length > 1) {
   $(this).closest('.list_filter').remove();
  } else {
   alert('You cannot remove the last filter element\nClick on Done to close the filter form');
  }
 });
 $('body').on('click', '#search_result .ino_sort_z_a', function () {
  $('#searchForm').find('.search_order_by').val($(this).closest('th').data('field_name'));
  $('#searchForm').find('.search_asc_desc').val('desc');
  getSearchResult();
 });
 $('body').on('click', '.remove-filter', function () {
  var field_name = '.' + $(this).closest('.applied-filter').data('field_name');
  $('#generic_search_form').find('ul.search_form').find(field_name).remove();
  $(this).closest('.applied-filter').remove();
  getSearchResult();
 });
 $('select.search_document_list').find('option[value="gl_calendar"]').prepend('<i class="fa fa-calendar"></i> ');
 $('select.search_document_list').find('option[value="mdm_bank_header"]').prepend('<i class="fa fa-bank"></i> ');
 $('select.search_document_list').find('option[value="bc_label_format_header"]').prepend('<i class="fa fa-barcode"></i> ');
 $('select.search_document_list').find('option[value="gl_journal_header"]').prepend('<i class="fa fa-book"></i> ');
 $('select.search_document_list').find('option[value="all"]').prepend('<i class="fa fa-database"></i> ');
 $('select.search_document_list').find('option[value="org"]').prepend('<i class="fa fa-university  "></i> ');
 $('select.search_document_list').find('option[value="supplier"]').prepend('<i class="fa fa-university"></i> ');
 $('select.search_document_list').find('option[value="ar_customer"]').prepend('<i class="fa fa-university"></i> ');
 $('select.search_document_list').find('option[value="user"]').prepend('<i class="fa fa-user"></i> ');
 $('select.search_document_list').find('option[value="all_bom_routing_v"]').prepend('<i class="fa fa-cog"></i> ');
 $('select.search_document_list').find('option[value="bom_header"]').prepend('<i class="fa fa-sitemap"></i> ');
 $('select.search_document_list').find('option[value="sd_so_header"]').prepend('<i class="fa fa-shopping-cart"></i> ');
 $('select.search_document_list').find('option[value="po_header"]').prepend('<i class="fa fa-file-text-o"></i> ');
 $('select.search_document_list').find('option[value="item"]').prepend('<i class="fa fa-tags"></i> ');
 $('select.search_document_list').find('option[value="address"]').prepend('<i class="fa fa-bars"></i> ');
 $('select.search_document_list').find('option[value="cc_co_header"]').prepend('<i class="fa fa-square-o"></i> ');
 $('select.search_document_list').find('option[value="inv_receipt_header"]').prepend('<i class="fa fa-square-o"></i> ');
 $('select.search_document_list').find('option[value="sd_delivery_header"]').prepend('<i class="fa fa-truck"></i> ');
 $('select.search_document_list').find('option[value="inv_transaction"]').prepend('<i class="fa fa-tasks"></i> ');
 $('select.search_document_list').find('option[value="ar_receipt_header"]').prepend('<i class="fa fa-money"></i> ');
 $('select.search_document_list').find('option[value="ap_payment_header"]').prepend('<i class="fa fa-money"></i> ');
 $('select.search_document_list').find('option[value="ap_transaction_header"]').prepend('<i class="fa fa-info-circle"></i> ');
 $('select.search_document_list').find('option[value="ar_transaction_header"]').prepend('<i class="fa fa-info-circle"></i> ');
 $('body').on('click', '#reset_program', function () {
  $(this).closest('form').find(':input').not('.button').val('');
 });
 $('body').on('click', '.right_bar_navigation_menu', function () {
  if ($('.sidebar').is(':visible')) {
   var containerWidth = $('body').width();
   $('#divider-bar').css({
    'margin-left': '-1000px'});
   $('.mainbar,  #navigation_bar').css({
    'margin-left': '6px',
    'width': containerWidth + 'px'});
   $('#header_top_quick_nav .right_bar_navigation_menu').removeClass('fa-toggle-left').addClass('fa-toggle-right');
  } else {
   var containerWidth = $('body').width();
   var leftPos = (containerWidth * 16.66 / 100);
   var mainBarWidth = containerWidth - leftPos;
   $('#divider-bar').css({
    'margin-left': '0px'});
   $('.mainbar,  #navigation_bar').css({
    'margin-left': leftPos + 6 + 'px',
    'width': mainBarWidth + 'px'});
   $('#header_top_quick_nav .right_bar_navigation_menu').removeClass('fa-toggle-right').addClass('fa-toggle-left');
  }
  $('.sidebar').slideToggle();
 });
 $("#divider-bar").draggable({
  axis: "x",
  delay: 150,
  topValue: null,
  leftValue: null,
  start: function () {
   this.topValue = $(this).position().top;
   this.leftValue = $(this).position().left;
  },
  stop: function (e, ui) {
   var topPos = ui.position.top;
   var leftPos = ui.position.left;
   var leftBarWidth = leftPos;
   var containerWidth = $('body').width();
   var mainBarWidth = containerWidth - leftPos;
   $('.container-fluid .sidebar').css('width', leftBarWidth + 'px');
   $('.mainbar, #navigation_bar').css({
    'margin-left': leftPos + 'px',
    'width': mainBarWidth + 'px'});
  }
 });
 $("#accordion").accordion({
  heightStyle: "content",
  active: 1,
  collapsible: true
 });
 $('body').on('click', '#accordion h3.recent-visits', function () {
  refreshData({
   data_type: 'recent_visit',
   divId: 'recent-visits'
  });
 });
 recentVisitInAjax();
 $('body').on('click', '#header_top_quick_nav .fa-close', function () {
  window.close();
 });
 $('body').on('click', '.fa-arrow-circle-down', function () {
  $(this).removeClass('fa-arrow-circle-down').addClass('fa-arrow-circle-up');
 });
 $('body').on('click', '.fa-arrow-circle-up', function () {
  $(this).removeClass('fa-arrow-circle-up').addClass('fa-arrow-circle-down');
 });
});
function toUpperCase(str)
{
 return str.toLowerCase().replace(/([^a-z])([a-z])(?=[a-z]{2})|^([a-z])/g, function (_, g1, g2, g3) {
  return (typeof g1 === 'undefined') ? g3.toUpperCase() : g1 + g2.toUpperCase();
 });
}

function recentVisitInAjax() {
 $('body #recent-visits').on('click', 'a', function (e) {
  e.preventDefault();
  getFormDetails($(this).attr('href'));
 });
}


/*Used in Oracle*/
function getOracleSubInventory(options) {
 var defaults = {
  json_url: 'modules/inv/subinventory/json_subinventory.php',
  ORGANIZATION_ID: $('#ORGANIZATION_ID').val(),
  SUBINVENTORY_CODE: '.SUBINVENTORY_CODE'
 };
 var settings = $.extend({}, defaults, options);
 $('#loading').show();
 return $.ajax({
  url: settings.json_url,
  data: {
   ORGANIZATION_ID: settings.ORGANIZATION_ID,
   find_all_oracle_subinventory: 1},
  type: 'get',
  beforeSend: function () {
   $('.show_loading_small').show();
  },
  complete: function () {
   $('.show_loading_small').hide();
  }
 }).done(function (result) {
  var div = $(result).filter('div#json_oralce_subinventory_find_all').html();
  $('#content').find(settings.SUBINVENTORY_CODE).empty().append(div);
 }).fail(function () {
//  alert("org name loading failed");
 }).always(function () {
  $('#loading').hide();
 });
 $(".form_table .SUBINVENTORY_CODE").attr("disabled", false);
}