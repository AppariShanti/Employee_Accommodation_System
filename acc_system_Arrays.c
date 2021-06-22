#include<stdio.h>
#include<string.h>
#define SIZE 5          //Used size of 5 for testing purpose...can be changed
#define TYPE_SIZE 10
#define SUCCESS 1
#define FAILURE 0
int a_index[SIZE];

//counts to keep track of the indexes till where each type of alloment is filled
int type_count1=0;
int type_count2=0;
int type_count3=0;
int type_count4=0;

//part (h) special request accommodation type of block structure
struct type_block
{
	char type_I[3];
	char type_II[3];
	char type_III[3];
	char type_IV[3];
}Type[TYPE_SIZE];

//structure to store employee data
struct accommodation
{
	char firstname[50];
	char lastname[50];
	char accommodation_type[20];
	int idtype;
	struct idnum
	{
		char aadhar[15];
		char passport[15];
		char empcode[15];
	}id;
	char address[100];
}B[SIZE];


//initialises the main structure
void initialise_db(struct accommodation B[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		B[i].firstname[0]='\0';
		B[i].lastname[0]='\0';
		B[i].accommodation_type[0]='\0';
		B[i].idtype=-1;
		B[i].id.aadhar[0]='\0';
		B[i].id.passport[0]='\0';
		B[i].id.empcode[0]='\0';
		B[i].address[0]='\0';
	}
}


//initialises the index array for part (d)...index is a keyword that's why using a_index
void initialise_index(int a_index[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		a_index[i]=i;
	}
}


//initialises type structure for part (h)...here "NA" means NOT ALLOTED and "A" means ALLOTED
void initialise_type_struct(struct type_block Type[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		strcpy(Type[i].type_I,"NA");
		strcpy(Type[i].type_II,"NA");
		strcpy(Type[i].type_III,"NA");
		strcpy(Type[i].type_IV,"NA");
	}
}


//for test printing...used it for testing the code...it shows resetted values for the empty records
void test_print(struct accommodation B[],int size)
{
	int j;
	for(j=0;j<size;j++)
		{
			if(B[j].idtype!=-1)
			{
				printf("%s\t\t",B[j].firstname);
				printf("%s\t\t",B[j].lastname);
				printf("%s\t\t",B[j].accommodation_type);
				printf("%d\t\t",B[j].idtype);
				printf("%s\t\t",B[j].id.aadhar);
				printf("%s\t\t",B[j].id.passport);
				printf("%s\t\t",B[j].id.empcode);
				puts(B[j].address);
				printf("\n");
			}
			
		}
}


//for test printing the type structure...used it to test the code
void test_print_type(struct type_block Type[],int size)
{
	int j;
	for(j=0;j<size;j++)
		{
			printf("%s\t",Type[j].type_I);
			printf("%s\t",Type[j].type_II);
			printf("%s\t",Type[j].type_III);
			printf("%s\t",Type[j].type_IV);
			printf("\n");
		}
}


//resetting structure when using remove duplicate and delete record function 
void reset(struct accommodation B[],int j)
{
	B[j].firstname[0]='\0';
	B[j].lastname[0]='\0';
	strcpy(B[j].accommodation_type,"NA");
	B[j].idtype=-1;
	B[j].id.aadhar[0]='\0';
	B[j].id.passport[0]='\0';
	B[j].id.empcode[0]='\0';
	B[j].address[0]='\0';
}


//allots the type of accommodation when using insert record in part (a)...the format of type should be correct type_I, type_II, type_III, type_IV
int allot_type(struct type_block Type[],int size,char accommodation_type[])
{
	int correct=1;
	if(strcmp(accommodation_type,"type_I")==0)
	{
		strcpy(Type[type_count1].type_I,"A");
		type_count1++;
	}
	else if(strcmp(accommodation_type,"type_II")==0)
	{
		strcpy(Type[type_count2].type_II,"A");
		type_count2++;
	}
	else if(strcmp(accommodation_type,"type_III")==0)
	{
		strcpy(Type[type_count3].type_III,"A");
		type_count3++;
	}
	else if(strcmp(accommodation_type,"type_IV")==0)
	{
		strcpy(Type[type_count4].type_IV,"A");
		type_count4++;
	}
	else
	{
		correct=0;
	}
	return correct;
	
}


//part (a) ... inserts record in the places where hole is there ...delete record and empty records are present as holes i.e 0 for integers and '\0' for strings
int InsertRecord(struct accommodation B[],int size,char firstname[],char lastname[],char accommodation_type[],int idtype,char aadhar[],char passport[],char empcode[],char address[])
{
	int status_code=SUCCESS;
	int correct_type;
	int i,j,is_free_location=0;
	i=0;
	while(i<size && !is_free_location)
	{
		if(B[i].idtype==-1 && B[i].id.aadhar[0]=='\0' && B[i].id.empcode[0]=='\0' && B[i].id.passport[0]=='\0')
		{
			is_free_location=1;
		}
		else
		i++;
	}
	if(is_free_location)
	{
		correct_type=allot_type(Type,TYPE_SIZE,accommodation_type);
		if(correct_type==1)
		{
		    strcpy(B[i].firstname,firstname);
			strcpy(B[i].lastname,lastname);
			strcpy(B[i].accommodation_type,accommodation_type);
			B[i].idtype=idtype;
			strcpy(B[i].id.aadhar,aadhar);
			strcpy(B[i].id.passport,passport);
			strcpy(B[i].id.empcode,empcode);
			strcpy(B[i].address,address);
			test_print(B,size);
			test_print_type(Type,TYPE_SIZE);
		}
		else
		printf("Type entered is of wrong format\n");
	}
	else
	{
		status_code=FAILURE;
	}
	return status_code;
}


//part (b) remove duplicates based on type of id and id number...id number for a particular employee is unique
int removeDuplicates(struct accommodation B[],int size)
{
	int status_code=SUCCESS;
	int i,j;
	for(i=0;i<SIZE;i++)
	{
		for(j=i+1;j<SIZE;j++)
		{
			
			if(strcmp(B[i].id.aadhar,B[j].id.aadhar)==0 && B[i].idtype==0 && B[i].idtype==B[j].idtype)
			{
				reset(B,j);
			}
			else if(strcmp(B[i].id.passport,B[j].id.passport)==0 && B[i].idtype==1 && B[i].idtype==B[j].idtype)
			{
				reset(B,j);
			}
			else if(strcmp(B[i].id.empcode,B[j].id.empcode)==0 && B[i].idtype==2 && B[i].idtype==B[j].idtype)
			{
				reset(B,j);
			}
			else
			status_code=FAILURE;
		}
	}
	test_print(B,size);
	return status_code;
}


//part (c) prints record according to sequence given 1-passport, 0-aadhar, 2-empcode
void printRecords(struct accommodation B[],int size)
{
	int i,not_empty=0;
	for(i=0;i<size;i++)
	{
		if(B[i].id.aadhar[0]!='\0' || B[i].id.passport[0]!='\0' || B[i].id.empcode[0]!='\0')
		{
			not_empty=1;
			if(B[i].idtype==1)
			{
				printf("%s\t%s\t%s\t%d\t%s\t",B[i].firstname,B[i].lastname,B[i].accommodation_type,B[i].idtype,B[i].id.passport);
				puts(B[i].address);
				printf("\n");
			}
		}
	}
	for(i=0;i<size;i++)
	{
		if(B[i].id.aadhar[0]!='\0' || B[i].id.passport[0]!='\0' || B[i].id.empcode[0]!='\0')
		{
			not_empty=1;
			if(B[i].idtype==0)
			{
				printf("%s\t%s\t%s\t%d\t%s\t",B[i].firstname,B[i].lastname,B[i].accommodation_type,B[i].idtype,B[i].id.aadhar);
				puts(B[i].address);
				printf("\n");
			}
		}
	}
	for(i=0;i<size;i++)
	{
		if(B[i].id.aadhar[0]!='\0' || B[i].id.passport[0]!='\0' || B[i].id.empcode[0]!='\0')
		{
			not_empty=1;
			if(B[i].idtype==2)
			{
				printf("%s\t%s\t%s\t%d\t%s\t",B[i].firstname,B[i].lastname,B[i].accommodation_type,B[i].idtype,B[i].id.empcode);
				puts(B[i].address);
				printf("\n");
			}
		}
	}
	if(not_empty==0)
	{
		printf("Sorry No Records Available for display...Kindly Insert some records using Insert option\n");
	}
	
}


//part (e) for searching a particular employee
int search(struct accommodation B[],int size,char firstname[])
{
	int status_code=SUCCESS;
	int i,found=0;
	for(i=0;i<size;i++)
	{
		if(strcmp(B[i].firstname,firstname)==0)
		{
			printf("%s\t%s\t%s\t%d\t",B[i].firstname,B[i].lastname,B[i].accommodation_type,B[i].idtype);
			if(B[i].idtype==0)
			{
				printf("%s\t",B[i].id.aadhar);
			}
			else if(B[i].idtype==1)
			{
				printf("%s\t",B[i].id.passport);
			}
			else if(B[i].idtype==2)
			{
				printf("%s\t",B[i].id.empcode);
			}
			puts(B[i].address);
			printf("\n");
			found=1;
		}
		if(found==0)
		{
			printf("NO such record found...Please Try again!\n");
		}
		
	}
}


//part (d) print sorted records using a_index created
void printSortedRecords(struct accommodation B[],int size)
{
	int i,j,temp=0,is_sorted=0,not_empty=0;
	for(i=0;i<SIZE-1 && !is_sorted;i++) //sorting using bubble sort
	{
		is_sorted=1;
		if(a_index[i]!=(-1) || B[i].idtype!=(-1))
		{
			for(j=0;j<SIZE-i-1;j++)
			{
				if(strcmp(B[a_index[j]].firstname,B[a_index[j+1]].firstname)>0)  
				{
					temp=a_index[j];
					a_index[j]=a_index[j+1];
					a_index[j+1]=temp;
					is_sorted=0;	
				}
				else if(strcmp(B[a_index[j]].firstname,B[a_index[j+1]].firstname)==0) //if first names match
				{
					if(strcmp(B[a_index[j]].lastname,B[a_index[j+1]].lastname)>0)
					{
						temp=a_index[j];
						a_index[j]=a_index[j+1];
						a_index[j+1]=temp;
						is_sorted=0;
						
					}
				}
			}
		}
	}
	for(i=0;i<SIZE;i++) //printing sorted records
	{
		if(a_index[i]!=(-1) || B[i].idtype!=(-1) )
		{
			not_empty=1;
			printf("%s\t%s\t%s\t%d\t",B[a_index[i]].firstname,B[a_index[i]].lastname,B[a_index[i]].accommodation_type,B[a_index[i]].idtype);
			if(B[a_index[i]].idtype==0)
			{
				printf("%s\t",B[a_index[i]].id.aadhar);
			}
			else if(B[a_index[i]].idtype==1)
			{
				printf("%s\t",B[a_index[i]].id.passport);
			}
			else if(B[a_index[i]].idtype==2)
			{
				printf("%s\t",B[a_index[i]].id.empcode);
			}
			puts(B[a_index[i]].address);
			printf("\n");
		}
	}
	if(not_empty==0)
	{
		printf("Sorry No Records Available for display...Kindly Insert some records using Insert option\n");
	}
}


//part (f) deletes record when id type and id number given
int deleteRecord(struct accommodation B[],int size,int idtype,char id_num[])
{
	int status_code=SUCCESS;
	int i,found=0,j;
	for(i=0;i<size && !found;i++)
	{
		if((B[i].idtype==idtype) && (strcmp(B[i].id.aadhar,id_num)==0 || strcmp(B[i].id.passport,id_num)==0 || strcmp(B[i].id.empcode,id_num)==0 ))
		{
			reset(B,i);
			for(j=0;j<size;j++)
			{
				if(a_index[j]==i)
				{
					a_index[j]=-1; //sets value of the record in the a_index array to -1 to denote record is deleted
				}
			}
			found=1;
		}
		
	}
	if(found==0)
	{
		status_code=FAILURE;
	}
	return status_code;
}


//part (g) updates record when first name and last name is provided
int updateRecord(struct accommodation B[],int size)
{
	int i,found=0,update;
	char firstname[50];
	char lastname[50];
	char address[100];
	int status_code=SUCCESS;
	printf("\nPlease Enter the first name and last name of the person whose record is to be updated ");
	scanf("%s%s",&firstname,&lastname);
	for(i=0;i<size;i++)
	{
		if(strcmp(B[i].firstname,firstname)==0 && strcmp(B[i].lastname,lastname)==0)
		{
			
			printf("Which detail do you want to update...\n");
			printf("\t1: Update First Name\n");
			printf("\t2: Update Last Name\n");
			printf("\t3: Update Type of accommodation\n");
			printf("\t4: Update ID Type and ID Number\n");
			printf("\t5: Update addressress\n");
			printf("\t0: Exit\n");
			printf("\t Please Enter your choice....");
			scanf("%d",&update);
			switch(update)
			{
			    case 1:
			    {
			    	printf("Enter the changed First Name ");
			    	scanf("%s",B[i].firstname);
			    	initialise_index(a_index,size); //changes a_index array
			    	break;
				}
				case 2:
				{
					printf("Enter the changed Last Name ");
			    	scanf("%s",B[i].lastname);
			    	initialise_index(a_index,size); //changes a_index array
			    	break;
				}
				case 3:
				{
					printf("To change the accommodation Type, Please use the special request accommodation option from the main menu.\n");
			    	break;
				}
				case 4:
				{
					printf("Enter the changed ID Type and ID Number ");
			    	scanf("%d",&B[i].idtype);
			    	if(B[i].idtype==0)
			    	{
			    		scanf("%s",B[i].id.aadhar);
			    		B[i].id.passport[0]='\0';
						B[i].id.empcode[0]='\0';
					}
					else if(B[i].idtype==1)
			    	{
			    		scanf("%s",B[i].id.passport);
			    		B[i].id.aadhar[0]='\0';
						B[i].id.empcode[0]='\0';
					}
					else if(B[i].idtype==2)
			    	{
			    		scanf("%s",B[i].id.empcode);
			    		B[i].id.aadhar[0]='\0';
						B[i].id.passport[0]='\0';
					}
			    	break;
				}
				case 5:
				{
					printf("Enter New addressress\n");
					fflush(stdin);
					fgets(B[i].address,100,stdin);
					break;
				}
				case 0:
				{
					break;
				}
				default:
				{
					printf("Wrong Input!! Please try again");
					break;
				}
			}
		}
	}
	
	if(found==0)
	{
		status_code=FAILURE;
	}
	return status_code;
}


//when made a special request to change allotment, the original type needs to be made "NOT ALLOTED"...searches the type structure and resets the previous type
void reset_type(struct type_block Type[],int type_size,char change[])
{
	int k,reset_found=0;
	for(k=0;k<type_size && !reset_found;k++)
	{
		if(strcmp(change,"type_I")==0)
		{
			if(strcmp(Type[k].type_I,"A")==0)
			{
				reset_found=1;
				strcpy(Type[k].type_I,"NA");
			}
		}
		else if(strcmp(change,"type_II")==0)
		{
			if(strcmp(Type[k].type_II,"A")==0)
			{
				reset_found=1;
				strcpy(Type[k].type_II,"NA");
			}
		}
		else if(strcmp(change,"type_III")==0)
		{
			if(strcmp(Type[k].type_III,"A")==0)
			{
				reset_found=1;
				strcpy(Type[k].type_III,"NA");
			}
		}
		else if(strcmp(change,"type_IV")==0)
		{
			if(strcmp(Type[k].type_IV,"A")==0)
			{
				reset_found=1;
				strcpy(Type[k].type_IV,"NA");
			}
		}
	}
}


//part (h) special request to change allotment searches for requested type and allots it to the employee if requested type is available
int specialRequestAllocation(struct accommodation B[],int size_db,int idtype,char id_number[],struct type_block Type[],int type_size,char request_type[])
{
	int i,j,k,found=0,type_found=0,reset_found=0;
	int status_code=SUCCESS;
	for(i=0;i<size_db && !found;i++)
	{
		if(B[i].idtype==idtype && (strcmp(B[i].id.aadhar,id_number)==0 || strcmp(B[i].id.passport,id_number)==0 || strcmp(B[i].id.empcode,id_number)==0))
		{
			found=1;
			for(j=0;j<type_size && !type_found;j++)
			{
				if(strcmp(request_type,"type_I")==0)
				{
					if(strcmp(Type[j].type_I,"NA")==0)
					{
						type_found=1;
						reset_type(Type,type_size,B[i].accommodation_type);
						strcpy(B[i].accommodation_type,"type_I");
						strcpy(Type[j].type_I,"A");	
					}
					else
					{
						status_code=FAILURE;
					}
				}
				else if(strcmp(request_type,"type_II")==0)
				{
					if(strcmp(Type[j].type_II,"NA")==0)
					{
						type_found=1;
						reset_type(Type,type_size,B[i].accommodation_type);
						strcpy(B[i].accommodation_type,"type_II");
						strcpy(Type[j].type_II,"A");	
					}
					else
					{
						status_code=FAILURE;
					}
				}
				else if(strcmp(request_type,"type_III")==0)
				{
					if(strcmp(Type[j].type_III,"NA")==0)
					{
						type_found=1;
						reset_type(Type,type_size,B[i].accommodation_type);
						strcpy(B[i].accommodation_type,"type_III");
						strcpy(Type[j].type_III,"A");	
					}
					else
					{
						status_code=FAILURE;
					}
				}
				else if(strcmp(request_type,"type_IV")==0)
				{
					if(strcmp(Type[j].type_IV,"NA")==0)
					{
						type_found=1;
						reset_type(Type,type_size,B[i].accommodation_type);
						strcpy(B[i].accommodation_type,"type_IV");
						strcpy(Type[j].type_IV,"A");	
					}
					else
					{
						status_code=FAILURE;
					}
				}
			}
		}
	}
	return status_code;
}


//main menu written here...exits when input is zeo
void main()
{
	int choice=0,i=0;
	int status;
	
	char firstname[50],lastname[50],accommodation_type[20],aadhar[15],passport[15],empcode[5],address[100];
	int idtype;
	initialise_db(B,SIZE);
	initialise_type_struct(Type,TYPE_SIZE);
	initialise_index(a_index,SIZE);
	printf("Welcome to VNIT Resident Record System!!\n\n");
	printf("NOTE: Since the record is empty currently, First Insert some records to use other options in the Menu");
	do
	{
		printf("\n\nRefer the following Menu to Access the System.\n");
		printf("\t1: Insert Record\n");
		printf("\t2: Remove Duplicates\n");
		printf("\t3: Print Records\n");
		printf("\t4: Print Sorted Records\n");
		printf("\t5: Search Employee\n");
		printf("\t6: Delete Record\n");
		printf("\t7: Update Record\n");
		printf("\t8: Special Request Allotment\n");
		printf("\t0: Exit\n\n");
		printf("NOTE: The correct format for accommodation type is type_I,type_II,type_III,type_IV. Kindly use correct format for entering accommodation type\n\n");
		printf("Please Enter your choice.....");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: 
			{
				printf("\nPlease Enter the details seperated by space ");
				scanf("%s%s%s%d",&firstname,&lastname,&accommodation_type,&idtype);
				if(idtype==0)
				{
					scanf("%s",&aadhar);
					passport[0]='\0';
					empcode[0]='\0';
				}
				else if(idtype==1)
				{
					aadhar[0]='\0';
					scanf("%s",&passport);
					empcode[0]='\0';
				}
				else if(idtype==2)
				{
					aadhar[0]='\0';
					passport[0]='\0';
					scanf("%s",&empcode);
				}
				gets(address);   
				status=InsertRecord(B,SIZE,firstname,lastname,accommodation_type,idtype,aadhar,passport,empcode,address);
				initialise_index(a_index,SIZE);
				if(status==0)
				{
					printf("Sorry!! NO SPACE...DB FULL...Record can't be entered\n\n");
				}
				break;
			}
			case 2:
				{
					status=removeDuplicates(B,SIZE);
					if(status==0)
					{
						printf("No Duplicates Found!!\n\n");
					}
					break;
				}
			case 3:
				{
					printRecords(B,SIZE);
					break;
				}
			case 4:
				{
					printSortedRecords(B,SIZE);
					break;
				}
			case 5:
				{
					char first_name[50];
					printf("Enter the name you want to search  ");
					scanf("%s",&first_name);
					search(B,SIZE,first_name);
					break;
				}
			case 6:
				{
					int idtype,status;
					char id_num[15];
					printf("Enter ID Type and ID Number of the Employee, whose record you want to delete  ");
					scanf("%d%s",&idtype,&id_num);
					status=deleteRecord(B,SIZE,idtype,id_num);
					if(status==0)
					{
						printf("Record Not Found...Please try Again!\n");
					}
					else
					{
						printf("Record Deleted Successfully!!\n");
					}
					break;
				}
			case 7:
				{
					int status;
					status=updateRecord(B,SIZE);
					if(status==0)
					{
						printf("Record Not Found...Please try Again!\n");
					}
					break;
				}
			case 8:
				{
					int status;
					int idtype;
					char request_type[20],id_number[15];
					printf("Please Enter Your ID Type and ID number...");
					scanf("%d%s",&idtype,id_number);
					printf("Please enter the type of Block you want... ");
					scanf("%s",request_type);
					status=specialRequestAllocation(B,SIZE,idtype,id_number,Type,TYPE_SIZE,request_type);
					if(status==0)
					{
						printf("Sorry!!Requested Type Not Available\n");
					}
					break;
				}
				case 0:
					{
						printf("Thank You!!!\n");
						break;
					}
				default:
					break;
		}
	} while(choice!=0);
}
