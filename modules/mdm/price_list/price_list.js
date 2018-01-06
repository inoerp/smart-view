function setValFromSelectPage(mdm_price_list_header_id, item_id_m, item_number, item_description, uom_id) {
 this.mdm_price_list_header_id = mdm_price_list_header_id;
 this.item_id_m = item_id_m;
 this.item_number = item_number;
 this.item_description = item_description;
 this.uom_id = uom_id;
}

setValFromSelectPage.prototype.setVal = function() {
 var mdm_price_list_header_id = this.mdm_price_list_header_id;
 var item_id_m = this.item_id_m;
 var item_number = this.item_number;
 var item_description = this.item_description;
 var uom_id = this.uom_id;
 
 var rowClass = '.' + localStorage.getItem("row_class");
 var fieldClass = '.' + localStorage.getItem("field_class");
 
 
  if (mdm_price_list_header_id) {
	$("#mdm_price_list_header_id").val(mdm_price_list_header_id);
 }
 
  rowClass = rowClass.replace(/\s+/g, '.');
 fieldClass = fieldClass.replace(/\s+/g, '.');
 if (item_id_m) {
	$('#content').find(rowClass).find('.item_id_m').val(item_id_m);
 }
 if (item_number) {
	$('#content').find(rowClass).find('.item_number').val(item_number);
 }
 if (item_description) {
	$('#content').find(rowClass).find('.item_description').val(item_description);
 }
 if (uom_id) {
	$('#content').find(rowClass).find('.uom_id').val(uom_id);
 }

 localStorage.removeItem("row_class");
 localStorage.removeItem("field_class");
 
};

 //Check the option_id while entering the option line code
 function copy_mdm_price_list_header_id() {
	$(".mdm_price_list_line_code").blur(function()
	{
	 if ($("#mdm_price_list_header_id").val() == "") {
		alert("First save header or select an Option Type");
		$(".mdm_price_list_line_code").val("");
	 } else {
		$(".mdm_price_list_header_id").val($("#mdm_price_list_header_id").val());
	 }
	});
 }
 

$(document).ready(function() {

//  var Mandatory_Fields = ["#org_id", "First Select Org Name", "#item_number", "First Select Item Number"];
// select_mandatory_fields(Mandatory_Fields);
//
// $('#form_line').on("click", function() {
//	if (!$('#mdm_price_list_header_id').val()) {
//	 alert('No header Id : First enter/save header details');
//	} else {
//	 var headerId = $('#mdm_price_list_header_id').val();
//	 if (!$(this).find('.mdm_price_list_header_id').val()) {
//		$(this).find('.mdm_price_list_header_id').val(headerId);
//	 }
//	}
//
// });
var mandatoryCheck = new mandatoryFieldMain();
mandatoryCheck.header_id = 'mdm_price_list_header_id';
mandatoryCheck.mandatoryHeader();

 //Popup for selecting option type
 $(".mdm_price_list_header_id.select_popup").on("click", function() {
	void window.open('select.php?class_name=mdm_price_list_header', '_blank',
					'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });




 //enable disbale parent & group
 $('.parent_cb').each(function() {
	if ($(this).is(":checked")) {
	 $(this).closest('tr').find('.parent_line_id').attr('disabled', 'true');
	}
 });

 $('body').on('change', '.parent_cb', function() {
	if ($(this).is(":checked")) {
	 $(this).closest('tr').find('.parent_line_id').attr('disabled', 'true');
	} else {
	 $(this).closest('tr').find('.parent_line_id').removeAttr('disabled');
	}
 });


 copy_mdm_price_list_header_id();
});

