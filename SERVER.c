
/*  MINI EMPLOYEE LEAVE MANAGEMENT SYSTEM PROJECT HAS TWO MODULES ,ONE IS ADMIN AND ANOTHER IS EMPLOYEE, EMPLOYEE WILL APPLY LEAVE AND THAT LEAVE REQUEST HAS TO BE
    APPROVED OR REJECTED BY ADMIN        */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include "SERVER.h"


int employeeCount; // this is globally declared

int displayMenu()  // 
{
	int choice=-1;
	printf("\n\n          ******** WELCOME TO EMPLOYEE LEAVE MANAGEMENT SYSTEM ********\n");
	printf("                                  SIGN IN AS                             \n");
	printf("          *************************************************************\n");
	printf("          1.Admin\n");
	printf("          2.Employee\n");
	printf("          3.EXIT.\n");
	printf("          *************************************************************\n");
	printf("          Enter your choice  :  ");
	if(scanf("%d",&choice)!=1)  // VALIDATING THE INPUT
	{
		flush();
		return 0;
	}
	else
	{
		flush();
		return choice;
	}
}



//   NOW THE PROGRAM IS RUNNING AS ADMINISTRATOR (ADMIN)
void ADMIN(struct employee *Employees)
{
	int i;
	char username[20],userpwd[15];
	printf("\n\n******* Admin Login *******\n");
    printf("--------------------------\n");
    printf("Enter your username : ");        // THIS IS ADMIN LOGIN PART
    scanf("%s",username);
    printf("Enter your password : ");
    for(i=0;i<8;i++)
    {
      userpwd[i]=getch();  // IT WILL NOT DISPLAY THE ENTERED CHARACTER
      printf("*");
    }
     userpwd[i]='\0';
     getch();

     if(!strcmp(username,"smileadmin") && !strcmp(userpwd,"smile123"))  // VERIFYING USERNAME AND PASSWORD
     {
        printf("\n\nLogged In Successful");
        printf(" \nemployee count = %d \n",employeeCount);
        while(1)  Employees = runApplicationForAdmin(Employees);  // RUNNING ADMIN'S APPLICATION
	}
	 else
     {
        printf("\n\nIncorrect username or password  Please Retry!!!!!!!!!");  // IF ADMIN ENTERS INCORRECT USERNAME OR PASSWORD
        main();
     }
}

void EMPLOYEE(struct employee *Employees)  // EMPLOYEE PART
{
	int c,i,j;
	char empID[20],empPassword[15];
	printf("\n\n******* Employee Login *******\n");
    printf("----------------------------------\n");   // THIS IS EMPLOYEE LOGIN PART
    printf("Enter Employee ID       : ");
    scanf("%s",empID);

    for(i=0;i<employeeCount;i++)
   {
       if(!strcmp(empID,Employees->employeeID))
       {
          printf("\nEnter Employee Password : ");
          for( c=0 ; c < strlen(Employees->employeePassword) ; c++)
          {
          	empPassword[c]=getch();  // ENTERING THE PASSWORD (IT WILL NOT SHOW THE ENTERED CHARACTER)
        	printf("*");
          }
    	  empPassword[c]='\0';
          getch();
       }
	   Employees++;
   }
   
     Employees = Employees - i;
     int g=0;
     for(i=0 ; i<employeeCount ; i++)
	 {
       if(!strcmp(Employees->employeeID,empID) && !strcmp(Employees->employeePassword,empPassword)) // VERIFYING THE EMPLOYEE ID AND PASSWORD
        {
    	    g=1;
			printf("\n\n       Logged In Successful\n");
			if(Employees->isInitalized==0)  // CHECKING WHETHER EMPLOYEE HAS GIVEN NUMBER OF LEAVES HE WANT PER YEAR,IF NOT HE SHOULD GIVE THIS FIRST
	        {
				printf(" \nSo you are a newly Regestered Employee, Please Enter how many casual,medical and earned leaves you want in this year \n");
		        Employees = annualLeaves(Employees);
	        }
	        if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus,"rejected") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus,"rejected") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].earnedLeaveStatus,"rejected"))
	        	 printf(" \n\n Your previuos Leave has been rejected\n"); // TELLING EMPLOYEE ABOUT HIS PREVIOUS LEAVE REQUEST
    	    while(1) Employees = runApplicationForEmployee(Employees,i);
		}
		Employees++;
	 }
    if(g!=1)
    {                // IF EMPLOYEE ENTER INCORRECT EMPLOYEE ID OR PASSWORD
       	  printf("\n\nIncorrect Employee ID or Password Please Retry (Employee is not Regestred)!!!!!!!!\n");
          main();
    }
}

// THIS IS ADMINISTRATOR'S APPLICATION
struct employee *runApplicationForAdmin(struct employee *Employees)
{
	int selectedOption,i,k=0;
	char name[20];
	FILE *fp;
	selectedOption = displayMenuForAdmin();  // DISPLAYING THE MENU FOR ADMIN
	switch(selectedOption)
	{
		case 1:
		   {
                Employees = addEmployees(Employees);  // ADDING EMPLOYEES
				employeeCount++;  // INCREMENTING THE NUMBER OF REGESTERED EMPLOYEES
                return Employees;
		   }
		    break;
		case 2:
		   {
               Employees = displayApprovedEmployees(Employees);  // DISPLAYING APPROVED EMPLOYEES
			   return Employees;
		   }
			break;
		case 3:
		   {
               Employees=displayRejectedEmployees(Employees);  // DISPLAYING REJECTED EMPLOYEEES
			   return Employees;
		   }
		    break;
		case 4:
		  {
             Employees = displayAllEmployees(Employees); // DISPLAYING ALL EMPLOYEES
             return Employees;
		  }
		 break;
		case 5:
			{
				printf(" Enter the Employee Name to Approve or Reject his leave : ");
                scanf("%s",name);     // APPROVING OR REJECTING EMPLOYEES BY HIS NAME
                for(i=0 ; i<employeeCount ; i++)
                {
                  if(!strcmp(name,Employees->employeeName))
                  {
					    k=1;
					  	if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus,"waiting...") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus,"waiting...") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].earnedLeaveStatus,"waiting..."))
                	   {
                		 Employees = ApproveOrReject(Employees);  // APPROVING OR REJECTING THE EMPLOYEE LEAVE REQUEST
					   }
					   else
					   {
						  printf(" %s has not not applied any leave",Employees->employeeName); // IF HE HAS NOT APPLIED ANY LEAVE
					   }
				  }
				  Employees++;  
				}
				Employees = Employees - i;
				if(k!=1)
				    printf(" Employee name NOT FOUND!!!!!!!!!!\n");
				return Employees;
			}
			break;
        case 6:
		    {
                Employees = leaveHistoryForAdmin(Employees);  // THIS WILL DISPLAY EMPLOYEE'S LEAVE HISTORY
				return Employees;
			}
            break;
        case 7:
		   {
               Employees = dispalyWhoAreInWaitingList(Employees); // THIS WIL DISPLAY EMPLOYYES WHO HAVE APPLIED FOR LEAVE.
			   return Employees;
		   }
        	break;
		case 8:
		   {
			  saveEmployees(Employees,fp);  // SAVING THE EMPLOYEE DETAILS IN A TEXT FILE (WRITING THE DATA)
			  exit(0);
		   }
			break;
		default:
			printf("You have made a wrong Choice. Please Retry!!!!!!!\n\n"); // IF ADMIN MADE A WRONG CHOICE
			return Employees;
			break;
	}
}

//  THIS IS EMPLOYEES'S APPLICATION
struct employee *runApplicationForEmployee(struct employee *Employees,int i)
{
	int selectedOption;
	FILE *fp;
    selectedOption = displayMenuForEmployee() ;
	switch(selectedOption)
	{
	   case 1:
	      {
               displayEmployeeInfo(Employees); // DISPLAYING EMPLOYEE'S INFORMATION
			   return Employees;
		  }
	    break;
	   case 2:
	   	  {
			if(Employees->noOFleavesApplied==0)
	   	    {
				Employees = applyLeaveNow(Employees);  // APPLYING LEAVE
				return Employees;
			}
			else
			{
				if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus,"waiting...") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus,"waiting...") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].earnedLeaveStatus,"waiting..."))
	   	       {
					  printf("    You cannot apply leave now until the previous leave is Approved.\n"); // IF EMPLOYEE TRIES TO APPLY LEAVE,AND CHECKING HIS PREVIOUS LEAVE WHETHER IT IS UPDATED OR NOT
					  return Employees;
			   }
			   else
			   {
			   	 if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied].casualLeaveStatus,"Limit Exceeded!!!!!") && !strcmp(Employees->Leaves[Employees->noOFleavesApplied].medicalLeaveStatus,"Limit Exceeded!!!!!") && !strcmp(Employees->Leaves[Employees->noOFleavesApplied].earnedLeaveStatus,"Limit Exceeded!!!!!"))
	              {
				    if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus,"rejected") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus,"rejected") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].earnedLeaveStatus,"rejected"))
				  	 {
				  	 	Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves = 0; // INITIALISING EVERYTHING TO 0 (BECAUSE HIS LEAVE REQUEST IS REJECTED AND THAT LEAVE HE CAN TAKE IN ANY OTHER TIME)
				  	 	Employees->Leaves[Employees->noOFleavesApplied-1].noOfMedicalLeaves = 0;
				  	 	Employees->Leaves[Employees->noOFleavesApplied-1].noOfEarnedLeaves = 0;
				  	 	Employees = applyLeaveNow(Employees);
					 }
					 else
					 {
					 	printf("  \n  You are OUT OF LIMITS!!!!!!!!!!!  (YOU CANNOT APPLY ANY KIND OF LEAVE NOW)\n"); // IF EMPLOYEE HAS LEFT WITH NO LEAVES
					 }
					 return Employees;
			      }
			      else
			      {
			      	if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus,"rejected") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus,"rejected") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].earnedLeaveStatus,"rejected"))
				  	 {
				  	 	Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves = 0;
				  	 	Employees->Leaves[Employees->noOFleavesApplied-1].noOfMedicalLeaves = 0;
				  	 	Employees->Leaves[Employees->noOFleavesApplied-1].noOfEarnedLeaves = 0;
				  	 	Employees = applyLeaveNow(Employees);
					 }
					 else
					 {
                        Employees = applyLeaveNow(Employees); // APPLYING LEAVE
					 }
					 return Employees;
			      }
			   }
			}
		  }
	   	   break;
	   case 3:
	      {
              checkLeaveRequest(Employees);  // IT WILL SHOW EMPLOYEE'S LEAVE HISTORY
			  return Employees;
		  }
	   	    break;
	   case 4:
	     {
			 Employees = Employees - i;
			 saveEmployees(Employees,fp);  // WRITING THE DATA INTO A TEXT FILE
	   	    exit(0);
		 }
	   	 break;
	   default:
	   	    printf("You have made a wrong Choice. Please Retry!!!!!!!\n\n");
			return Employees;
			break;
	}
}

//  THIS IS THE DISPLAY MENU FOR ADMINISTRATOR
int displayMenuForAdmin()
{
	int choice=-1;
	printf("\n\n******* MINI EMPLOYEE LEAVE MANAGEMENT SYSTEM FOR ADMIN *******\n");
	printf("...................................................................\n");
	printf("                               MENU                                \n");
    printf("...................................................................\n");
    printf("1) Add Employee.\n");
    printf("2) Display Approved Employees.\n");
    printf("3) Display Rejected Employees.\n");
    printf("4) Display All Employees.\n");
    printf("5) Approve or Reject.\n");
    printf("6) Leave History.\n");
    printf("7) Display Employees who Have applied for Leave.\n");
    printf("8) Quit.\n");
    printf("...................................................................\n");
    printf(" Please Enter your choice : ");
    if(scanf("%d",&choice)!=1)  // VALIDATING THE INPUT FROM THE USER
    {
    	flush();
    	return 0;
	}
	else
	{
		flush();
		return choice;
	}
}

//  THIS IS THE INITIAL CONDITIONS SHOULD BE GIVEN BY AN EMPLOYEE IN HIS FIRST LOGIN
struct employee *annualLeaves(struct employee *Employees)
{
	  	printf(" This is like Condition or limits for this year \n");
		printf("...................................................................\n");
		printf("1) Casual Leave.\n");
		printf("2) Medical Leave.\n");
		printf("3) Earned Leave.\n");
		printf("...................................................................\n");
		printf(" Enter Casual Leaves  for one year: ");
		scanf("%d",&Employees->casualLeaves);
		printf(" Enter Medical Leaves for one year: ");
		scanf("%d",&Employees->medicalLeaves);
		printf(" Enter Earned Leaves  for one year: ");
		scanf("%d",&Employees->earnedLeaves);
        printf("...................................................................\n");
        Employees->isInitalized = 1;
		return Employees;
}

//  THIS IS THE DISPLAY MENU FOR EMPLOYEE
int displayMenuForEmployee()
{
	int choice=-1;
	printf("\n\n******* MINI EMPLOYEE LEAVE MANAGEMENT SYSTEM FOR EMPLOYEE ****\n");
	printf("...................................................................\n");
	printf("                               MENU                                \n");
    printf("...................................................................\n");
    printf("1) My Information.\n");
    printf("2) Apply Leave for Now.\n");
    printf("3) Check My Leave Requests.\n");
    printf("4) Quit.\n");
    printf("...................................................................\n");
    printf(" Please Enter your choice : ");
    if(scanf("%d",&choice)!=1)
    {
    	flush();
    	return 0;
	}
	else
	{
		flush();
		return choice; 
	}
}

//  THESE ARE ALL ADMINISTRATORS'S FUNCTIONS
struct employee *addEmployees(struct employee *Employees)
{
	Employees = Employees + employeeCount;
	int i;
	FILE *fp;
	struct employee emp;
	Employees->isInitalized = 0;
	printf("...................................................................\n");
	printf(" Employee SlNo            : %d\n",employeeCount+1);
	printf(" Enter Employee Name      :");
	scanf("%s[^\n]",Employees->employeeName );
	printf(" Enter Employee ID        :");
	scanf("%s",Employees->employeeID);
	printf(" Enter Employee Password  : ");
	scanf("%s",Employees->employeePassword);
	printf("...................................................................\n");
	Employees->noOFleavesApplied = 0;                                                           // [Employees[0]->employeeCount]
	Employees->casualLeaves = 0;
	Employees->medicalLeaves = 0;   // INITIALISING EVERYTHING TO 0
	Employees->earnedLeaves = 0;
	for(i=0 ; i<50 ; i++)
	{
	   strcpy(Employees->Leaves[i].casualLeaveStatus,"Not Applied");
	   strcpy(Employees->Leaves[i].earnedLeaveStatus,"Not Applied");
	   strcpy(Employees->Leaves[i].medicalLeaveStatus,"Not Applied");
	   strcpy(Employees->Leaves[i].startDate,"null");
	   strcpy(Employees->Leaves[i].endDate,"null");
	   Employees->Leaves[i].typeOFleave = 0;
	   Employees->Leaves[i].noOfCasualLeaves = 0;
	   Employees->Leaves[i].noOfEarnedLeaves = 0;
	   Employees->Leaves[i].noOfMedicalLeaves = 0;
	}
	 Employees = Employees - employeeCount;
	 return Employees;
}

struct employee *displayApprovedEmployees(struct employee *Employees)
{
	int t=0;
	int i,j;
	for(i=0 ; i<employeeCount ; i++)
	{
	  for(j=0 ; j<Employees->noOFleavesApplied ; j++)
      {
          if(!strcmp(Employees->Leaves[j].casualLeaveStatus,"approved"))
	     {
	  	   printf("\n...................................................................\n");
	  	   printf(" Employee SlNo : %d\n",i+1);
	       printf(" Employee Name : %s\n",Employees->employeeName);
	       printf("******************************\n");
		   printf("     Leave Request By %s     \n",Employees->employeeName);
		   printf("******************************\n");
		   printf("  From - %s             To - %s   \n",Employees->Leaves[j].startDate,Employees->Leaves[j].startDate);
		   printf(" %s wanted %d days Leave (Casual Leaves) \n",Employees->employeeName,Employees->Leaves[j].noOfCasualLeaves);
	       t=1;
	     }
	     if(!strcmp(Employees->Leaves[j].medicalLeaveStatus,"approved"))
	     {
	       printf("\n...................................................................\n");
	  	   printf(" Employee SlNo : %d\n",i+1);
	       printf(" Employee Name : %s\n",Employees->employeeName);
	       printf("******************************\n");
		   printf("     Leave Request By %s     \n",Employees->employeeName);
		   printf("******************************\n");
		   printf("  From - %s             To - %s   \n",Employees->Leaves[j].startDate,Employees->Leaves[j].startDate);
		   printf(" %s wanted %d days Leave (Medical Leaves) \n",Employees->employeeName,Employees->Leaves[j].noOfMedicalLeaves);
	       t=1;
		 }
		 if(!strcmp(Employees->Leaves[j].earnedLeaveStatus,"approved"))
		 {
		   printf("\n...................................................................\n");
	  	   printf(" Employee SlNo : %d\n",i+1);
	       printf(" Employee Name : %s\n",Employees->employeeName);
	       printf("******************************\n");
		   printf("     Leave Request By %s     \n",Employees->employeeName);
		   printf("******************************\n");
		   printf("  From - %s             To - %s   \n",Employees->Leaves[j].startDate,Employees->Leaves[j].startDate);
		   printf(" %s wanted %d days Leave (Earned Leaves) \n",Employees->employeeName,Employees->Leaves[j].noOfEarnedLeaves);
	       t=1;
		 }
	  }
	  Employees++;
	}
	printf("...................................................................\n");
	Employees = Employees - i;
	if(t!=1)
	  printf(" No Employee's leaves are Approved.\n");
	
	return Employees;
}

struct employee *displayRejectedEmployees(struct employee *Employees)
{
	int t=0;
	int i,j;
	for(i=0 ; i<employeeCount ; i++)
	{
      for(j=0 ; j<Employees->noOFleavesApplied ; j++)
      {
         if(!strcmp(Employees->Leaves[j].casualLeaveStatus,"rejected"))
	     {
	  	   printf("\n...................................................................\n");
	  	   printf(" Employee SlNo : %d\n",i+1);
	       printf(" Employee Name : %s\n",Employees->employeeName);
	       printf("******************************\n");
		   printf("     Leave Request By %s     \n",Employees->employeeName);
		   printf("******************************\n");
		   printf("  From - %s             To - %s   \n",Employees->Leaves[j].startDate,Employees->Leaves[j].startDate);
		   printf(" %s wanted %d days Leave (Casual Leaves) \n",Employees->employeeName,Employees->Leaves[j].noOfCasualLeaves);
	       t=1;
	     }
	     if(!strcmp(Employees->Leaves[j].medicalLeaveStatus,"rejected"))
	     {
	       printf("\n...................................................................\n");
	  	   printf(" Employee SlNo : %d\n",i+1);
	       printf(" Employee Name : %s\n",Employees->employeeName);
	       printf("******************************\n");
		   printf("     Leave Request By %s     \n",Employees->employeeName);
		   printf("******************************\n");
		   printf("  From - %s             To - %s   \n",Employees->Leaves[j].startDate,Employees->Leaves[j].startDate);
		   printf(" %s wanted %d days Leave (Medical Leaves) \n",Employees->employeeName,Employees->Leaves[j].noOfMedicalLeaves);
	       t=1;
		 }
		 if(!strcmp(Employees->Leaves[j].earnedLeaveStatus,"rejected"))
		 {
		   printf("\n...................................................................\n");
	  	   printf(" Employee SlNo : %d\n",i+1);
	       printf(" Employee Name : %s\n",Employees->employeeName);
	       printf("******************************\n");
		   printf("     Leave Request By %s     \n",Employees->employeeName);
		   printf("******************************\n");
		   printf("  From - %s             To - %s   \n",Employees->Leaves[j].startDate,Employees->Leaves[j].startDate);
		   printf(" %s wanted %d days Leave (Earned Leaves) \n",Employees->employeeName,Employees->Leaves[j].noOfEarnedLeaves);
	       t=1;
		 }
      }
	  Employees++;
	}
	Employees = Employees - i;
	printf("...................................................................\n");
	if(t!=1)
	  printf(" \n   No Employee' leaves are Rejected.\n");
		
	return Employees;
}

struct employee *displayAllEmployees(struct employee *Employees)
{
	int i;
	printf("\n   SL NO       Employee Name        Employee ID       Employee Password  \n");
	for(i=0 ; i<employeeCount ; i++)
	{
		printf("\n...................................................................\n");
		printf("    %d           %s                %s                   %s  \n",i+1,Employees->employeeName,Employees->employeeID,Employees->employeePassword);
		Employees++;
	}
	printf("\n...................................................................\n");
	Employees = Employees - i;
	return Employees;
}

struct employee *ApproveOrReject(struct employee *Employees)
{
   printf("no of applied leaves of employee till now = %d",Employees->noOFleavesApplied);
   	      
			     if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus,"waiting..."))
			     {
			  		printf(" \nEmployee %s is within the allowed Limits\n",Employees->employeeName);
			  		printf("******************************\n");
				    printf("     Leave Request By %s     \n",Employees->employeeName);
				    printf("******************************\n");
				    printf("  From - %s             To - %s   \n",Employees->Leaves[Employees->noOFleavesApplied-1].startDate,Employees->Leaves[Employees->noOFleavesApplied-1].endDate);
				    printf(" %s wants %d days Leave (Casual Leaves) \n",Employees->employeeName,Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves);
				    printf("----------------------------------\n");
				    printf(" Enter Leave Status (Either approve or reject) : ");
				    scanf("%s",Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus);
				 }
			     else if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus,"waiting..."))
			      {
			  	    printf(" \nEmployee %s is within the allowed Limits\n",Employees->employeeName);
			  		printf("******************************\n");
				    printf("     Leave Request By %s     \n",Employees->employeeName);
				    printf("******************************\n");
				    printf("  From - %s             To - %s   \n",Employees->Leaves[Employees->noOFleavesApplied-1].startDate,Employees->Leaves[Employees->noOFleavesApplied-1].endDate);
				    printf(" %s wants %d days Leave (Medical Leaves) \n",Employees->employeeName,Employees->Leaves[Employees->noOFleavesApplied-1].noOfMedicalLeaves);
				    printf("----------------------------------\n");
				    printf(" Enter Leave Status (Either approve or reject) : ");
				    scanf("%s",Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus);
				  }
				  else
			      {
			  	  printf(" \nEmployee %s is within the allowed Limits\n",Employees->employeeName);
			  	  printf("******************************\n");
				  printf("     Leave Request By %s     \n",Employees->employeeName);
				  printf("******************************\n");
				  printf("  From - %s             To - %s   \n",Employees->Leaves[Employees->noOFleavesApplied-1].startDate,Employees->Leaves[Employees->noOFleavesApplied-1].endDate);
				  printf(" %s wants %d days Leave (earned leaves) \n",Employees->employeeName,Employees->Leaves[Employees->noOFleavesApplied-1].noOfEarnedLeaves);
				  printf("----------------------------------\n");
				  printf(" Enter Leave Status (Either approve or reject) : ");
				  scanf("%s",Employees->Leaves[Employees->noOFleavesApplied-1].earnedLeaveStatus);
			     } 
	return Employees;
}

struct employee *leaveHistoryForAdmin(struct employee *Employees)
{
   char name[20];
   int i,j,t=0,g=0;
   printf("...................................................................\n");
   printf(" Please Enter the Name of the Employee to See His Leave History : ");
   scanf("%s",name);
   for(i=0 ; i<employeeCount ; i++)
   {
      if(!strcmp(name,Employees->employeeName))
      {
         for(j=0;j<Employees->noOFleavesApplied;j++)
	    {
          g=1;
	      printf("...................................................................\n");
	      if(Employees->Leaves[j].typeOFleave == 1)
	      {
	      	 printf(" Leave Type - Casual Leave ");
	      	 printf("        Leave Status : %s",Employees->Leaves[j].casualLeaveStatus);
		  }
          if(Employees->Leaves[j].typeOFleave == 2)
          {
          	  printf(" Leave Type - Medical Leave ");
          	  printf("        Leave Status : %s",Employees->Leaves[j].medicalLeaveStatus);
		  }
          if(Employees->Leaves[j].typeOFleave == 3)
          {
          	  printf(" Leave Type - Earned Leave ");
          	  printf("        Leave Status : %s",Employees->Leaves[j].earnedLeaveStatus);
		  }
		  printf(" From - %s     To - %s",Employees->Leaves[j].startDate,Employees->Leaves[j].endDate);
	    }
	    printf("...................................................................\n");
        t=1;
      }
	  Employees++;
   }
   Employees = Employees - i;
   if(t!=1)
     printf(" Employee Name NOT FOUND!!!!!!!\n");
   if(g!=1)
    printf(" Employee has not applied any leave\n");

   return Employees;
}

struct employee *dispalyWhoAreInWaitingList(struct employee *Employees)
{
	int i,g=0;
	for(i=0 ; i<employeeCount ; i++)
	{
		if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus,"waiting...") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus,"waiting...") || !strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].earnedLeaveStatus,"waiting..."))
			{
				printf("\n...................................................................\n");
				printf(" Employee Name : %s\n",Employees->employeeName);
				printf(" %s's has applied for %d th Leave\n",Employees->employeeName,Employees->noOFleavesApplied);
				g=1;
			}
			Employees++;
	}
	printf("\n...................................................................\n");
	Employees = Employees - i;
	if(g!=1)
	 printf(" No Employees have applied for leave.\n");
	 return Employees;
}

//  THESE ARE ALL EMPLOYEES'S FUNCTIONS
void displayEmployeeInfo(struct employee *Employees)
{
	printf("...................................................................\n");
	printf(" Employee Name     : %s\n",Employees->employeeName);
	printf(" Employee ID       : %s\n",Employees->employeeID);
	printf(" Employee Password : %s\n",Employees->employeePassword);
	printf("...................................................................\n");
}

struct employee *applyLeaveNow(struct employee *Employees)
{
	Employees->Leaves[Employees->noOFleavesApplied].typeOFleave = displayTypesOfLeaves(Employees);
    switch(Employees->Leaves[Employees->noOFleavesApplied].typeOFleave)
    {
    	case 1:
		   {
              Employees = applyCasualLeave(Employees);
			  return Employees;
		   }
    		break;
    	case 2:
		   {
              Employees = applyMedicalLeave(Employees);
			  return Employees;
		   }
    		break;
    	case 3:
		   {
              Employees = applyEarnedLeave(Employees);
			  return Employees;
		   }
    		break;
    	default:
    		printf(" You have made a wrong choice!!!!  Please Retry \n");
    		applyLeaveNow(Employees);
    		break;
	}
}

int displayTypesOfLeaves(struct employee *Employees)
{
	int choice;
	printf("...................................................................\n");
    printf("1) Casual Leave.\n");
	printf("2) Medical Leave.\n");
	printf("3) Earned Leave.\n");
    printf("...................................................................\n");
    printf(" Please Enter your choice that you want now (you can choose only one): ");
    if(scanf("%d",&Employees->Leaves[Employees->noOFleavesApplied].typeOFleave)!=1)
    {
    	flush();
    	return 0;
	}
	else
	{
		flush();
		return Employees->Leaves[Employees->noOFleavesApplied].typeOFleave;
	}
}

struct employee *applyCasualLeave(struct employee *Employees)  // WHILE APPLYING CASUAL LEAVE
{
	int sc=0,sca=0,i;   
	char ch[5];
	if(strcmp(Employees->Leaves[Employees->noOFleavesApplied].casualLeaveStatus,"Limit Exceeded!!!!!")) // IF EMPLOYEE IS NOT WITHIN THE ALLOWED LIMITS
			  {
				  printf(" Enter Date -  \n");
        	      printf("        From (dd/mm/yyyy) : ");
	              scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].startDate);
	              printf("        To (dd/mm/yyyy)   : ");
	              scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].endDate);
	              printf(" Enter number of casual Leaves you want now - ");
	              scanf("%d",&Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves);
	              
					  for(i=0;i<Employees->noOFleavesApplied+1;i++)
	                  {
	              	       sc = sc + Employees->Leaves[i].noOfCasualLeaves;  //  FINDING THE TOTAL NUMBER OF CASUAL LEAVES APPLIED TILL NOW
				      }
                    
	               if(sc > Employees->casualLeaves)  // IF TOTAL NUMBER OF CASUAL LEAVES IS GREATER THAN THE NUMBER OF CASUAL LEAVES THAT HE WANT NOW.
	               {
	               	     if(Employees->noOFleavesApplied==0) // IF EMPLOYEE IS APPLYING LEAVE FOR THE FIRST TIME.
	               	     {
	               	     	printf(" \n    So you are applying leave for the first time\n");
							printf("   Sorry you cannot take %d leaves ",sc);
	               	     	printf("You can take only %d leaves for now \n",Employees->casualLeaves);
	               	     	printf("   Do you want to take all those %d leaves,now only (y/n) : ",Employees->casualLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves = Employees->casualLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].casualLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].casualLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further casual leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
							{
								printf("  Leave Request is not sent (Thank you) \n");
							}
							else
							{
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyCasualLeave(Employees);
							}
							 return Employees;
						 } 
						 else if(Employees->noOFleavesApplied==1) // IF HE IS APPLYING FOR THE SECOND TIME
						 {
						 	printf(" Sorry you cannot take %d leaves now \n",Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves);
	               	     	printf(" You can take only %d leaves for now \n",Employees->casualLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves);
						    printf(" Do you want to take all those %d leaves now only (y/n) : \n",Employees->casualLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves = Employees->casualLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].casualLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].casualLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further casual leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
							{
								printf("  Leave Request is not sent (Thank you) \n");
							}
							else
							{
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyCasualLeave(Employees);
							}
							 return Employees;
						 }
						 else  // APPLYING LEAVE MORE THAN TWO TIMES
						 {
							 for(i=0 ; i<=Employees->noOFleavesApplied-1 ; i++)
			                 {
			                 	  sca = sca + Employees->Leaves[i].noOfCasualLeaves;
							 }
			                 printf(" Sorry You cannot apply %d casual leaves now \n",Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves);
			                 printf(" you can take last %d casual leaves now\n",Employees->casualLeaves-sca);
			                 printf(" Do you want to take all those last %d leaves now? (y/n) :",Employees->casualLeaves-sca);
			                 scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
			                 {
						        Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves = Employees->casualLeaves-sca;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].casualLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].casualLeaveStatus,"Limit Exceeded!!!!!");// LEAVE REQUEST IS SENT SUCCESFULLY
						        printf(" You cannot apply further casual leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n"); 
						        Employees->noOFleavesApplied++;
						        return Employees;
					         }
			                 else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                 {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							 }
							 else
							{
								printf("\n   You Have Entered Wrong  Please Retry\n ");
								applyCasualLeave(Employees);
							}
							 return Employees;
						 } 
				   }
				   else
				   {
				   	  printf("  So Now you are left with last %d casual leaves \n",Employees->casualLeaves-sc);
				   	  if((Employees->casualLeaves-sc)==0)
				   	  {
				   	  	 printf(" You cannot apply further casual leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
				   	  	 for(i=Employees->noOFleavesApplied ; i<49 ; i++)
							 strcpy(Employees->Leaves[i+1].casualLeaveStatus,"Limit Exceeded!!!!!");
					  }
					  strcpy(Employees->Leaves[Employees->noOFleavesApplied].casualLeaveStatus,"waiting...");
					  Employees->noOFleavesApplied++;
					  return Employees;
				   }
		     }
		     else  // IF HIS PREVIOUS LEAVE IS REJECTED,THEN HE IS ABLE TO TAKE THOSE LEAVES NEXT TIME 
		     {
		     	if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].casualLeaveStatus,"rejected"))
		     	{
		     		printf(" Enter Date -  \n");
        	      printf("        From (dd/mm/yyyy) : ");
	              scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].startDate);
	              printf("        To (dd/mm/yyyy)   : ");
	              scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].endDate);
	              printf(" Enter number of casual Leaves you want now - ");
	              scanf("%d",&Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves);
	              
					  for(i=0;i<Employees->noOFleavesApplied+1;i++)
	                  {
	              	       sc = sc + Employees->Leaves[i].noOfCasualLeaves;
				      }
				  if(sc>Employees->casualLeaves)
				  {
				  	printf(" Sorry you cannot take %d leaves now \n",Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves);
	               	     	printf(" You can take only %d leaves for now \n",Employees->casualLeaves - Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves);
						    printf(" Do you want to take all those %d leaves now only (y/n) : ",Employees->casualLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfCasualLeaves = Employees->casualLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfCasualLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].casualLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].casualLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further casual leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                 {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							 }
							 else
							{
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyCasualLeave(Employees);
							}
							 return Employees;
				  }
				  else
				  {
				  	printf("  So Now you are left with last %d casual leaves \n",Employees->casualLeaves-sc);
				   	  if((Employees->casualLeaves-sc)==0)
				   	  {
				   	  	 printf(" You cannot apply further casual leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
				   	  	 for(i=Employees->noOFleavesApplied ; i<49 ; i++)
							 strcpy(Employees->Leaves[i+1].casualLeaveStatus,"Limit Exceeded!!!!!");
					  }
					  strcpy(Employees->Leaves[Employees->noOFleavesApplied].casualLeaveStatus,"waiting...");
					  Employees->noOFleavesApplied++;
					  return Employees;
				  }
				}
				else
				{
					printf("   \nSorry you can't apply casual leave - LIMIT EXCEEDED!!!!!   (your casual leave limit has already exceeded)  Please Retry  \n");
		     	    applyLeaveNow(Employees);
				}
			 }
}

struct employee *applyMedicalLeave(struct employee *Employees)
{
	int sm=0,sca=0,i;
	char ch[5];
	if(strcmp(Employees->Leaves[Employees->noOFleavesApplied].medicalLeaveStatus,"Limit Exceeded!!!!!"))
				 {
    		      printf(" Enter Date -  ");
        	      printf(" From (dd/mm/yyyy) : ");
	              scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].startDate);
	              printf("               To (dd/mm/yyyy)   : ");
	              scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].endDate);
	              printf(" Enter number of medical Leaves you want now - ");
	              scanf("%d",&Employees->Leaves[Employees->noOFleavesApplied].noOfMedicalLeaves);
	              
					  for(i=0;i<Employees->noOFleavesApplied+1;i++)
	                  {
	              	       sm = sm + Employees->Leaves[i].noOfMedicalLeaves;
				      }
		      	   
	               if(sm > Employees->medicalLeaves)
	               {
	               	    if(Employees->noOFleavesApplied==0)
	               	     {
	               	     	printf("     \nSo you are applying leave for the first time ");
							printf(" you cannot take %d leaves now \n",sm);
	               	     	printf("     You can take only %d leaves for now \n",Employees->medicalLeaves);
	               	     	printf("     Do you want to take all those %d leaves now only (y/n) : ",Employees->medicalLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfMedicalLeaves = Employees->medicalLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].medicalLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].medicalLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further medical leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                 {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							 }
							 else
							{
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyMedicalLeave(Employees);
							}
							 return Employees;
						 } 
						 else if(Employees->noOFleavesApplied==1)
						 {
						 	printf(" Sorry you cannot take %d leaves now \n",Employees->Leaves[Employees->noOFleavesApplied].noOfMedicalLeaves);
	               	     	printf(" You can take only %d leaves for now \n",Employees->medicalLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfMedicalLeaves);
						    printf(" Do you want to take all those %d leaves now only (y/n) : ",Employees->medicalLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfMedicalLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfMedicalLeaves = Employees->medicalLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfMedicalLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].medicalLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].medicalLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further medical leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                 {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							 }
							 else
							{
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyMedicalLeave(Employees);
							}
							 return Employees;
						 }
						 else
						 {
						 	  for(i=0;i<=Employees->noOFleavesApplied-1;i++)
			                     sca = sca + Employees->Leaves[i].noOfMedicalLeaves;
			                  printf(" Sorry You cannot apply %d medical leaves now \n",Employees->Leaves[Employees->noOFleavesApplied].noOfMedicalLeaves);
			                  printf(" you can take last %d medical leaves now\n",Employees->medicalLeaves-sca);
			                  printf(" Do you want to take those last %d leaves now? (y/n) : ",Employees->medicalLeaves-sca);
			                  scanf("%s",ch);
	               	     	  if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
			                  {
						        Employees->Leaves[Employees->noOFleavesApplied].noOfMedicalLeaves = Employees->medicalLeaves-sca;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].medicalLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].medicalLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further medical leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
					          }
					          else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                  {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							  }
							 else
							  {
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyMedicalLeave(Employees);
							  }
			                   return Employees;
						 }
				   }
				   else
				   {
				   	  printf("   you are left with last %d medical leaves \n",Employees->medicalLeaves-sm);
				   	  if((Employees->medicalLeaves-sm)==0)
				   	  {
				   	  	  for(i=Employees->noOFleavesApplied ; i<49 ; i++)
							 strcpy(Employees->Leaves[i+1].medicalLeaveStatus,"Limit Exceeded!!!!!");
					  }
					  strcpy(Employees->Leaves[Employees->noOFleavesApplied].medicalLeaveStatus,"waiting...");
					  Employees->noOFleavesApplied++;
					   return Employees;
				   }
	            }
	            else
		        {
		        	if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].medicalLeaveStatus,"rejected"))
					{
						printf(" Enter Date -  ");
        	           printf(" From (dd/mm/yyyy) : ");
	                   scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].startDate);
	                   printf(" To (dd/mm/yyyy)   : ");
	                   scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].endDate);
	                   printf(" Enter number of medical Leaves you want now - ");
	                   scanf("%d",&Employees->Leaves[Employees->noOFleavesApplied].noOfMedicalLeaves);
	              
					    for(i=0;i<Employees->noOFleavesApplied+1;i++)
	                    {
	              	       sm = sm + Employees->Leaves[i].noOfMedicalLeaves;
				        }
		      	   
	                   if(sm > Employees->medicalLeaves)
	                   {
	                   	   printf(" So you are applying leave for the first time\n");
							printf(" Sorry you cannot take %d leaves now \n",sm);
	               	     	printf(" You can take only %d leaves for now \n",Employees->medicalLeaves);
	               	     	printf(" Do you want to take all those %d leaves now only (y/n) : ",Employees->medicalLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfMedicalLeaves = Employees->medicalLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].medicalLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].medicalLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further medical leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                  {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							  }
							 else
							  {
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyMedicalLeave(Employees);
							  }
							   return Employees;
					   }
					   else
					   {
					   	  printf("   you are left with last %d medical leaves \n",Employees->medicalLeaves-sm);
				   	      if((Employees->medicalLeaves-sm)==0)
				   	      {
				   	  	      for(i=Employees->noOFleavesApplied ; i<49 ; i++)
							    strcpy(Employees->Leaves[i+1].medicalLeaveStatus,"Limit Exceeded!!!!!");
					      }
					       strcpy(Employees->Leaves[Employees->noOFleavesApplied].medicalLeaveStatus,"waiting...");
					       Employees->noOFleavesApplied++;
					         return Employees;
					   }
				   }
					else
					{
						printf(" Sorry you can't apply medical leave - LIMIT EXCEEDED!!!!! (your casual leave limit has already exceeded)  Please Retry  \n");
		     	    applyLeaveNow(Employees);
					}
			    }  
}

struct employee *applyEarnedLeave(struct employee *Employees)
{
	int se=0,sca=0,i;
	char ch[5];
	if(strcmp(Employees->Leaves[Employees->noOFleavesApplied].earnedLeaveStatus,"Limit Exceeded!!!!!"))
				{
			      printf(" Enter Date -  ");
        	      printf("           From (dd/mm/yyyy) : ");
	              scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].startDate);
	              printf("           To (dd/mm/yyyy)   : ");
	              scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].endDate);
	              printf(" Enter number of earned Leaves you want now - ");
	              scanf("%d",&Employees->Leaves[Employees->noOFleavesApplied].noOfEarnedLeaves);
	              
					  for(i=0;i<Employees->noOFleavesApplied+1;i++)
	                  {
	              	       se = se + Employees->Leaves[i].noOfEarnedLeaves;
				      }
		      	   
	               if(se > Employees->earnedLeaves)
	               {
	               	     if(Employees->noOFleavesApplied==0)
	               	     {
	               	     	printf("   So you are applying leave for the first time\n");
							printf("  you cannot take %d leaves now \n",se);
	               	     	printf("   You can take only %d leaves for now \n",Employees->earnedLeaves);
	               	     	printf("  Do you want to take all those %d leaves now only (y/n) : ",Employees->earnedLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfEarnedLeaves = Employees->earnedLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].earnedLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].earnedLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further earned leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                  {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							  }
							 else
							  {
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyEarnedLeave(Employees);
							  }
							   return Employees;
						 } 
						 else if(Employees->noOFleavesApplied==1)
						 {
						 	printf(" Sorry you cannot take %d leaves now \n",Employees->Leaves[Employees->noOFleavesApplied].noOfEarnedLeaves);
	               	     	printf(" You can take only %d leaves for now \n",Employees->earnedLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfEarnedLeaves);
						    printf(" Do you want to take all those %d leaves now only (y/n) : ",Employees->earnedLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfEarnedLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfEarnedLeaves = Employees->earnedLeaves-Employees->Leaves[Employees->noOFleavesApplied-1].noOfEarnedLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].earnedLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].earnedLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further earned leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                  {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							  }
							 else
							  {
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyEarnedLeave(Employees);
							  }
							   return Employees;
						 }
						else
						{
						  for(i=0;i<=Employees->noOFleavesApplied-1;i++)
			                sca = sca + Employees->Leaves[i].noOfEarnedLeaves;
			              printf(" Sorry You cannot apply %d earned leaves now \n",Employees->Leaves[Employees->noOFleavesApplied].noOfEarnedLeaves);
			              printf(" you can take last %d earned leaves now\n",Employees->earnedLeaves-sca);
			              printf(" Do you want to take those last %d leaves now? (y/n) : ",Employees->earnedLeaves-sca);
			              scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
			              {
						    Employees->Leaves[Employees->noOFleavesApplied].noOfEarnedLeaves = Employees->earnedLeaves-sca;
						    strcpy(Employees->Leaves[Employees->noOFleavesApplied].earnedLeaveStatus,"waiting...");
						    for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].earnedLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further earned leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						    Employees->noOFleavesApplied++;
					      }
					      else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                  {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							  }
							 else
							  {
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyEarnedLeave(Employees);
							  }
			               return Employees;
			            }
				   }
				   else
				   {
				   	  printf("   you are left with last %d earned leaves \n",Employees->earnedLeaves-se);
				   	  if((Employees->earnedLeaves-se)==0)
				   	  {
				   	  	for(i=Employees->noOFleavesApplied ; i<49 ; i++)
							 strcpy(Employees->Leaves[i+1].earnedLeaveStatus,"Limit Exceeded!!!!!");
					  }
					  strcpy(Employees->Leaves[Employees->noOFleavesApplied].earnedLeaveStatus,"waiting...");
					  Employees->noOFleavesApplied++;
					   return Employees;
				   }
		       }
		       else
		        {
		          if(!strcmp(Employees->Leaves[Employees->noOFleavesApplied-1].earnedLeaveStatus,"rejected"))
		          {
		          	       printf(" Enter Date -  ");
        	            printf("           From (dd/mm/yyyy) : ");
	                    scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].startDate);
	                    printf("           To (dd/mm/yyyy)   : ");
	                    scanf("%s",Employees->Leaves[Employees->noOFleavesApplied].endDate);
	                    printf(" Enter number of earned Leaves you want now - ");
	                    scanf("%d",&Employees->Leaves[Employees->noOFleavesApplied].noOfEarnedLeaves);
	              
					    for(i=0;i<Employees->noOFleavesApplied+1;i++)
	                    {
	              	       se = se + Employees->Leaves[i].noOfEarnedLeaves;
				        }
		      	   
	                    if(se > Employees->earnedLeaves)
	                    {
	                    	printf(" \n  So you are applying leave for the first time  ");
							printf(" Sorry you cannot take %d leaves now \n",se);
	               	     	printf(" You can take only %d leaves for now \n",Employees->earnedLeaves);
	               	     	printf(" Do you want to take all those %d leaves now only (y/n) : ",Employees->earnedLeaves);
	               	     	scanf("%s",ch);
	               	     	if(!strcmp(ch,"y") || !strcmp(ch,"Y") || !strcmp(ch,"Yes") || !strcmp(ch,"yes"))
	               	     	{
	               	     		Employees->Leaves[Employees->noOFleavesApplied].noOfEarnedLeaves = Employees->earnedLeaves;
						        strcpy(Employees->Leaves[Employees->noOFleavesApplied].earnedLeaveStatus,"waiting...");
						        for(i=Employees->noOFleavesApplied ; i<49 ; i++)
						           strcpy(Employees->Leaves[i+1].earnedLeaveStatus,"Limit Exceeded!!!!!");
						        printf(" You cannot apply further earned leaves! (IF THIS LEAVE REQUEST IS APPROVED)\n");
						        Employees->noOFleavesApplied++;
							}
							else if(!strcmp(ch,"n") || !strcmp(ch,"N") || !strcmp(ch,"No") || !strcmp(ch,"no"))
			                  {
			                 	printf("Leave Request is not sent. (Thank You)\n");
							  }
							 else
							  {
								printf("\n   You Entered Wrong  Please Retry\n ");
								applyEarnedLeave(Employees);
							  }
							   return Employees;
						}
						else
						{
							printf("   you are left with last %d earned leaves \n",Employees->earnedLeaves-se);
				   	        if((Employees->earnedLeaves-se)==0)
				   	        {
				   	  	       for(i=Employees->noOFleavesApplied ; i<49 ; i++)
							      strcpy(Employees->Leaves[i+1].earnedLeaveStatus,"Limit Exceeded!!!!!");
					        }
					        strcpy(Employees->Leaves[Employees->noOFleavesApplied].earnedLeaveStatus,"waiting...");
					        Employees->noOFleavesApplied++;
							 return Employees;
						}
				  }
				  else
				  {
				  	printf(" Sorry you can't apply earned leave - LIMIT EXCEEDED!!!!! (Earned Leave Limit Has Exceeded) Please Retry  \n");
		     	    applyLeaveNow(Employees);
				  }
			    }  
}

void checkLeaveRequest(struct employee *Employees)  // IT WILL SHOW EMPLOYEE'S LEAVE HISTORY
{
	int i;
	if(Employees->noOFleavesApplied!=0)
	{
	   for(i=0;i<Employees->noOFleavesApplied;i++)
	   {
	    printf("\n...................................................................\n");
        if(Employees->Leaves[i].typeOFleave == 1)
	      {
	      	 printf(" Leave Type - Casual Leave ");
	      	 printf("        Leave Status : %s",Employees->Leaves[i].casualLeaveStatus);  // DISPLAYING THE LEAVE STATUS OF EMPLOYEE'S LEAVE
		  }
          if(Employees->Leaves[i].typeOFleave == 2)           // WE NEED TO VERIFY THE TYPE OF LEAVE
          {
          	  printf(" Leave Type - Medical Leave ");
          	  printf("        Leave Status : %s",Employees->Leaves[i].medicalLeaveStatus);
		  }
          if(Employees->Leaves[i].typeOFleave == 3)
          {
          	  printf(" Leave Type - Earned Leave ");
          	  printf("        Leave Status : %s",Employees->Leaves[i].earnedLeaveStatus);
		  }
	    printf(" From - %s   to - %s",Employees->Leaves[i].startDate,Employees->Leaves[i].endDate);  // IT WILL SHOW THE DATES ALSO
	   }
	  printf("\n...................................................................\n");
     }
     else
     {
     	printf(" You have'nt applied any leave till now!\n'");  // IF NUMBER OF APPLIED LEAVES OF AN EMPLOYEE IS 0.
	 }
}

void saveEmployees(struct employee *Employees,FILE *fp)  // WRITING ALL THE DATA INTO A TEXT FILE
{
	int i,j;                                                                                        //fwrite(Employees,sizeof(struct employee),1,fp);
	fp = fopen("EMPLOYEES.txt","w");
	for(i=0;i<employeeCount;i++)
	{
		fwrite(Employees,sizeof(struct employee),1,fp);                                                                                         
		Employees++;
	}
	fclose(fp);
}

void flush()  // THIS IS TO VALIDATE ALL THE INPUTS GIVEN BY THE USER
{
     int c;
     while((c=getchar())!=EOF && c!='\n');
}
