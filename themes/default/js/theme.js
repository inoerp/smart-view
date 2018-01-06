function hideOverLay() {
 var ramNumber = Math.random() * 7;
 console.log(ramNumber);
 var options = {to: {width: 200, height: 60}};
 if (ramNumber > 6) {
  var selectedEffect = 'size';
 } else if (ramNumber > 4) {
  var selectedEffect = 'clip';
 } else if (ramNumber > 3) {
  var selectedEffect = 'fold';
 } else if (ramNumber > 1) {
  var selectedEffect = 'scale';
 } else {
  var selectedEffect = 'slide';
 }
 $('#overlay').hide(selectedEffect, options, 600);
}

$(document).ready(function () {
 $('body').on('click', '#dashborad_menu a', function () {
  $('#structure').css({
   visibility: 'hidden'
  });
  var bgColor = $(this).closest('li').css('background-color');
  var faClass = $(this).closest('li').find('i').attr('class');
  $('#overlay').css('background-color', bgColor);
  $('#overlay').removeClass();
  $('#overlay').addClass(faClass);
  var newStyle = $('<style>#path_by_module ul.child_menu > li > a { background-color: ' + bgColor + '; } #path_by_module ul.child_menu > li { border-color: ' + bgColor + '; }</style>');
  $('html > head').append(newStyle);
 });

 $('body').on('click', '.panel-heading.dashboard a', function () {
  $('#structure').css({
   visibility: 'hidden'
  });
  $('#overlay').removeClass();
   $('#overlay').css({
    minHeight : '1200px'
   });
  $('#overlay').addClass('fa fa-dashboard');
 });

 $('body').on('click', '#path_by_module a, .ino-breadcrumb-simple a', function () {
  $('#structure').css({
   visibility: 'hidden'
  });
 });
});

function resizeAnimation() {

}