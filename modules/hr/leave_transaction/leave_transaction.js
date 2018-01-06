function setValFromSelectPage(hr_leave_transaction_id, hr_employee_id, first_name, last_name, identification_id) {
 this.hr_leave_transaction_id = hr_leave_transaction_id;
 this.hr_empoyee_id = hr_employee_id;
 this.first_name = first_name;
 this.last_name = last_name;
 this.identification_id = identification_id;
}

setValFromSelectPage.prototype.setVal = function () {

 var employee_type = localStorage.getItem("employee_type");

 var hr_leave_transaction_id = this.hr_leave_transaction_id;
 var name = this.first_name + ' ' + this.last_name;
 var identification_id = this.identification_id;

 $("#hr_leave_transaction_id").val(hr_leave_transaction_id);
 var hr_employee_id = this.hr_employee_id;
 if (employee_type == 'employee') {
  if (hr_employee_id) {
   $("#employee_id").val(hr_employee_id);
  }
  if (name) {
   $("#employee_name").val(name);
  }
  if (identification_id) {
   $("#identification_id").val(identification_id);
  }
 } else if (employee_type == 'approver') {
  if (name) {
   $("#approved_by").val(name);
  }
  if (hr_employee_id) {
   $("#approved_by_employee_id").val(hr_employee_id);
  }
 }
 localStorage.removeItem("employee_type");

};


$(document).ready(function () {
 //selecting Id
 $(".hr_leave_transaction_id.select_popup").on("click", function () {
  void window.open('select.php?class_name=hr_leave_transaction', '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });


 //selecting Id
 $(".hr_employee_id.select_popup").on("click", function () {
  var employeeType = $(this).closest('li').data('employee_type');
  localStorage.setItem("employee_type", employeeType);
  void window.open('select.php?class_name=hr_employee', '_blank',
          'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
 });


});
