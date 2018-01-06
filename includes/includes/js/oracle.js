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