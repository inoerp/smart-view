function drag_drop_urgent_card() {
 $("#urgent_card_block").sortable({
  revert: true
 });

 $(".draggable_element").draggable(
         {helper: 'clone',
          cursor: "crosshair",
          connectToSortable: "#sortable",
          revert: "invalid"
         });

 $("#urgent_card_block").droppable({
  accept: ".draggable_element",
  revert: "invalid",
  drop: function (event, ui) {
   $(this).append($(ui.draggable).clone());
//		remove_from_dragged_element();
  }
 });

 $('#urgent_card_block').on('dblclick', 'li.draggable_element', function () {
  $(this).remove();
 });

}

function drag_drop_system_trnx() {
 $("#mmb_transaction_block").sortable({
  revert: true
 });


 $("#mmb_transaction_block").droppable({
  accept: ".draggable_element",
  revert: "invalid",
  drop: function (event, ui) {
   $(this).append($(ui.draggable));
//		remove_from_dragged_element();
  }
 });

 $('#mmb_transaction_block').on('dblclick', 'li.draggable_element', function () {
  $(this).remove();
 });
}


function saveUrgentCards(options) {
 $('#save_urgent_card').on('click', function () {
  var defaults = {
   json_url: 'modules/fp/urgent_card/json_urgent_card.php',
   className: 'fp_urgent_card',
   dataToSave: $('#urgent_card_block').html()
  };
  var settings = $.extend({}, defaults, options);

  return $.ajax({
   url: settings.json_url,
   type: 'post',
   data: {
    class_name: settings.className,
    save_data: true,
    data_to_save: settings.dataToSave
   },
   beforeSend: function () {
    $('.show_loading_small').show();
   },
   complete: function () {
    $('.show_loading_small').hide();
   }
  }).done(function (result) {
   $('#save_urgent_card').closest('.urgent_card_block').find('.info').append(result);
  }).fail(function () {
   alert("Search Failed");
  });
 });
}

$(document).ready(function () {
//get Subinventory Name
 $("#org_id").on("change", function () {
  getSubInventory('modules/inv/subinventory/json_subinventory.php', $(this).val());
 });
 saveUrgentCards();
 drag_drop_urgent_card();
 drag_drop_system_trnx();
 //Get the po header id on refresh button click
 $('a.show3.onhand_id').click(function () {
  var link = 'form.php?class_name=fp_minmax_barcode_board_v';
  var ORGANIZATION_ID = $('#ORGANIZATION_ID').val();
  if (ORGANIZATION_ID) {
   link += '&ORGANIZATION_ID=' + ORGANIZATION_ID;
  }
  var SUBINVENTORY_CODE = $('#SUBINVENTORY_CODE').val();
  if (SUBINVENTORY_CODE) {
   link += '&SUBINVENTORY_CODE=' + SUBINVENTORY_CODE;
  }
  var SOURCE_SUBINVENTORY = $('#SOURCE_SUBINVENTORY').val();
  if (SOURCE_SUBINVENTORY) {
   link += '&SOURCE_SUBINVENTORY=' + SOURCE_SUBINVENTORY;
  }

  var PLANNER_CODE = $('#PLANNER_CODE').val();
  if (PLANNER_CODE) {
   link += '&PLANNER_CODE=' + PLANNER_CODE;
  }
  var PLANNING_MAKE_BUY_CODE = $('#PLANNING_MAKE_BUY_CODE').val();
  if (PLANNING_MAKE_BUY_CODE) {
   link += '&PLANNING_MAKE_BUY_CODE=' + PLANNING_MAKE_BUY_CODE;
  }
  
    var DESCRIPTION = $('#DESCRIPTION').val();
  if (DESCRIPTION) {
   link += '&DESCRIPTION=' + DESCRIPTION;
  }

  var DYNAMIC = $('#DYNAMIC').val();
  if (DYNAMIC) {
   link += '&DYNAMIC=' + DYNAMIC;
  }

  $(this).attr('href', link);

 });

 $('#min_max_boardId ul.child').each(function () {
  var height = $(this).data('height');
  $(this).css({
   'background': 'rgba(10,10,120,0.1)',
   'height': height + '%'
  });
 });




 $('#ORGANIZATION_ID').on('blur', function () {
  if ($(this).val()) {
   $.when(getOracleSubInventory()).
           then(function () {
           });
  }
 });



});

