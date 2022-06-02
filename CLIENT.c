#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include "SERVER.h"



int main()
{
	int currentSelectedOption;
	 employeeCount=0;
	struct employee Employees[100];
	struct employee tempEmployee;
	
	FILE *infile;
	
    infile = fopen("EMPLOYEES.txt","r");

	if(infile==NULL)
	{
	     
         printf("         \n\n         Number of employees  = %d \n",employeeCount);
	     currentSelectedOption = displayMenu();
	     switch(currentSelectedOption)
	    {
		  case 1:
			ADMIN(Employees);
			break;
		  case 2:
			EMPLOYEE(Employees);
			break;
		   case 3:
			exit(0);
			break;
		   default:
			printf(" You have made a wrong choice!\n");
			main();
			break;
	    }
	}
   else
   {
	   while(fread(&tempEmployee,sizeof(struct employee),1,infile))
	   {
		  Employees[employeeCount] = tempEmployee;
		employeeCount++;
	   }
	   printf("         \n\n           Number of employees  = %d \n",employeeCount);
	     currentSelectedOption = displayMenu();
	     switch(currentSelectedOption)
	    {
		  case 1:
			ADMIN(Employees);
			break;
		  case 2:
			EMPLOYEE(Employees);
			break;
		   case 3:
			exit(0);
			break;
		   default:
			printf(" You have made a wrong choice!\n");
			main();
			break;
	    }
   }

	return 0;
}
