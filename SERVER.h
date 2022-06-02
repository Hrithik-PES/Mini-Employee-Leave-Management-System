struct employee
{
  char employeeName[20];
  char employeePassword[15] ;
  char employeeID[20];
  int isInitalized;
  int casualLeaves,medicalLeaves,earnedLeaves;
  int noOFleavesApplied;
  struct leave
  {
  	char casualLeaveStatus[20],medicalLeaveStatus[20],earnedLeaveStatus[20];
  	char startDate[10],endDate[10];
    int noOfCasualLeaves,noOfMedicalLeaves,noOfEarnedLeaves,typeOFleave;
  } Leaves[100];
};

extern int employeeCount;

int displayMenu();
void flush();


void ADMIN(struct employee *Employees);
struct employee *runApplicationForAdmin(struct employee *Employees);
int displayMenuForAdmin();
struct employee *addEmployees(struct employee *Employees);
struct employee *displayApprovedEmployees(struct employee *Employees);
struct employee *displayRejectedEmployees(struct employee *Employees);
struct employee *displayAllEmployees(struct employee *Employees);
struct employee *leaveHistoryForAdmin(struct employee *Employees);
struct employee *ApproveOrReject(struct employee *Employees);
struct employee *dispalyWhoAreInWaitingList(struct employee *Employees);


void EMPLOYEE(struct employee *Employees);
struct employee *runApplicationForEmployee(struct employee *Employees,int i);
int displayMenuForEmployee();
void displayEmployeeInfo(struct employee *Employees);
struct employee *annualLeaves(struct employee *Employees);
int displayTypesOfLeaves(struct employee *Employees);
struct employee *applyLeaveNow(struct employee *Employees);
void checkLeaveRequest(struct employee *Employees);
struct employee *applyCasualLeave(struct employee *Employees);
struct employee *applyMedicalLeave(struct employee *Employees);
struct employee *applyEarnedLeave(struct employee *Employees);


void saveEmployees(struct employee *Employees,FILE *fp);
//struct employee *loadSavedEmployees(struct employee *Employees,FILE *infile);


