                                                                        MINI EMPLOYEE LEAVE MANAGEMENT SYSTEM

---> Mini Employee Leave Management System project has two modules,they are:
 1.Admin
 2.Employee

---> When user sign in as admin
 He can perform following operations:-
 1) Add Employee: Since only admin has the opportunity to regester new employee at any time,he can any number of employees.
 2) Display Approved Employees: If employee has applied for leave,and that leave request is approved by admin,then this function display those employees whose leave request are approved.
 3) Display Rejected Employees: If employee has applied for leave,and that leave request is rejected by admin,then this function display those employees whose leave request are rejected.
 4) Display All Employees: It will display employees list who are regetered by admin.
 5) Approve or Reject Employee: This is the main task of admin i.e to approve or reject the leave request which is sent by employee.Admin needs to approve or reject the leave request.
 6) Leave History of an Employee: It will show the leave history of employee.
 7) Display Employees who have applied for leave: This will display the employees who have applied for leave.

---> When user sign in as employee
 He can perform following operations:-
 1) My Information: It will show the employee's details like his name,ID,password 
 2) Apply Leave For Now: He can apply leave of any one type among casual,medical and earned leave,he should mention number of days he wants leave.If he is not within the allowed limits
    then he cannot apply that leave.
    For ex: Suppose his number of casual leaves is 10 days per year (this is like condition given by employee). 
    * For the first time he will apply for leave (casual),there he wants 5 casual leaves,he can apply,so there is no restriction for him. And if admin approve that leave then that leave is granted,employee can take 5 days leave. So now he is left with 5 casual leave
    (10-5=5). 
    * And for second time if he apply leave (casual) again,he can apply leave for only 5 days,(he cannot apply more than that),so he applied.Admin rejects that leave request,so employee cannot 
    take that leave (but still he is left with 5 days only, and those 5 days,he can take in any other time). If that leave request was approved,then employee has left with 0 casual leaves.
    * The main task of employee is to apply leave and that leave request need to be approved or rejected by admin.If admin approves the request,then only employee can take his leave.
      If admin rejects the request,then employee cannot take leave and for this admin has to provide a valid reason to employee.
 3) Check Leave Request: Here employee can check his leave history.