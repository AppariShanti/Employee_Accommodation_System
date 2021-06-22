//Name: APPARI SHANTI
//Roll No. : BT19CSE126
//Batch : R4

//ACCOMMODATION MANAGEMENT SYSTEM 

//Data Structure Used -- Doubly Linked List

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum{FAILURE,SUCCESS}status_code;
typedef enum{FALSE,TRUE}Boolean;
 
//structure to store all the data of the employees
typedef struct Itemtype_tag
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
}ItemType;

//Doubly Linked List Node with info as ItemType.
typedef struct accommodation_tag
{
	ItemType info;
	struct accommodation_tag* next;
	struct accommodation_tag* prev;
	int key;
}accommodation;

// Structure for sorting the records in alphabetical order
typedef struct Node_tag
{
    accommodation* my_ptr;
    struct Node_tag* next;
    int idx_key;
}Node;

// structure for type of accommodation - the types are type_I, type_II, type_III and type_IV
typedef struct type_tag
{
	char type_I[3];
	char type_II[3];
	char type_III[3];
	char type_IV[3];
	struct type_tag* next;
}Type;


Type* type_lptr=NULL;    // List pointer for the type of accommodation blocks
accommodation* record=NULL;  // List pointer for the records
Node* sort_idx;              // List pointer for index LL
int my_key=1;              	 // used to populate the index LL nodes


// Creates a Linked List with 10 blocks each for type_I,type_II,type_III and type_IV blocks
void create_type_list(Type** lpptr,int size)
{
	Type* ptr;
	int i;
	for(i=0;i<size;i++)
	{
		ptr=(Type*)malloc(sizeof(Type));
		ptr->next=NULL;
		strcpy(ptr->type_I,"NA");
		strcpy(ptr->type_II,"NA");
		strcpy(ptr->type_III,"NA");
		strcpy(ptr->type_IV,"NA");
		if(*lpptr==NULL)
		{
			*lpptr=ptr;
		}
		else
		{
			ptr->next=*lpptr;
			*lpptr=ptr;	
		}
	}
}

// print allocated Linked list..it shows the blocks that are allocated as "A" and not allocated "NA"
void print_type(Type* lptr)
{
	printf("\n\n Allocation List\n");
	Type* ptr=lptr;
	while(ptr!=NULL)
	{
		printf("%s\t%s\t%s\t%s\n",ptr->type_I,ptr->type_II,ptr->type_III,ptr->type_IV);
		ptr=ptr->next;
	}
}

// prints all the records
void test_print(accommodation* ptr)
{
	printf("%s\t\t",ptr->info.firstname);
    printf("%s\t\t",ptr->info.lastname);
    printf("%s\t\t",ptr->info.accommodation_type);
    printf("%d\t\t",ptr->info.idtype);
    if(ptr->info.idtype==0)
    {
    	printf("%s\t\t",ptr->info.id.aadhar);
	}
    else if(ptr->info.idtype==1)
    {
    	printf("%s\t\t",ptr->info.id.passport);
	}
    else if(ptr->info.idtype==2)
    {
    	printf("%s\t\t",ptr->info.id.empcode);
	}
    puts(ptr->info.address);
    printf("\n");
}
// (c) prints records so that all who have provided aadhar are listed first, after that those with passport number and then those with empcode
void printRecords(accommodation* lptr)
{
	accommodation* ptr=lptr;
	while(ptr!=NULL)
    {
        test_print(ptr);
		ptr=ptr->next;
    }
}

// Allocates type based on the type requested by user -- this validates the types as well
Boolean allocate_type(Type* lptr,char* req_type)
{
	Type* ptr = lptr;
	Boolean free=FALSE;
	Boolean found=FALSE;
	while(ptr!=NULL && !found)
	{
		if(strcmp("type_I",req_type)==0)
		{
			if(strcmp(ptr->type_I,"NA")==0)
			{
				strcpy(ptr->type_I,"A");
				found=TRUE;
				free=TRUE;
			}
			else
			{
				free=FALSE;
				ptr=ptr->next;
			}	
		}
		else if(strcmp("type_II",req_type)==0)
		{
			if(strcmp(ptr->type_II,"NA")==0)
			{
				strcpy(ptr->type_II,"A");
				found=TRUE;
				free=TRUE;
			}
			else
			{
				free=FALSE;
				ptr=ptr->next;
			}
		}
		else if(strcmp("type_III",req_type)==0)
		{
			if(strcmp(ptr->type_III,"NA")==0)
			{
				strcpy(ptr->type_III,"A");
				found=TRUE;
				free=TRUE;
			}
			else
			{
				free=FALSE;
				ptr=ptr->next;
			}
		}
		else if(strcmp("type_IV",req_type)==0)
		{
			if(strcmp(ptr->type_IV,"NA")==0)
			{
				strcpy(ptr->type_IV,"A");
				found=TRUE;
				free=TRUE;
			}
			else
			{
				free=FALSE;
				ptr=ptr->next;
			}
		}
		else
		{
			ptr=ptr->next;
		}
	}
	if(found && free)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// resets the type if the record is deleted ---
//   1) Duplicates Removed
//	 2) Record is deleted
//   3) Special Request Allocation
void reset_type(Type* lptr,char* change)
{
	Type* ptr=lptr;
	Boolean found=FALSE;
	while(ptr!=NULL && !found)
	{
		if(strcmp(change,"type_I")==0)
		{
			if(strcmp(ptr->type_I,"A")==0)
			{
				found=TRUE;
				strcpy(ptr->type_I,"NA");
			}
			else
			{
				ptr=ptr->next;
			}
		}
		else if(strcmp(change,"type_II")==0)
		{
			if(strcmp(ptr->type_II,"A")==0)
			{
				found=TRUE;
				strcpy(ptr->type_II,"NA");
			}
			else
			{
				ptr=ptr->next;
			}
		}
		else if(strcmp(change,"type_III")==0)
		{
			if(strcmp(ptr->type_III,"A")==0)
			{
				found=TRUE;
				strcpy(ptr->type_III,"NA");
			}
			else
			{
				ptr=ptr->next;
			}
		}
		else if(strcmp(change,"type_IV")==0)
		{
			if(strcmp(ptr->type_IV,"A")==0)
			{
				printf("resetted");
				found=TRUE;
				strcpy(ptr->type_IV,"NA");
			}
			else
			{
				ptr=ptr->next;
			}
		}
		else
		{
			ptr=ptr->next;
		}
	}
}

// Inserts the index node at appropriate location based on first name and last name(incase of ties) -- insertion sort
void insertSort(Node** lpptr,Node* idx)
{
    Node* ptr=*lpptr;
    Boolean done=FALSE;
    
    if(*lpptr==NULL)
    {
        *lpptr=idx;
    }
    else if((*lpptr)->next==NULL)
    {
        if(strcmp(ptr->my_ptr->info.firstname,idx->my_ptr->info.firstname)>0)
        {
            idx->next=ptr;
            *lpptr=idx;
        }
        else if(strcmp(ptr->my_ptr->info.firstname,idx->my_ptr->info.firstname)==0)
        {
            if(strcmp(ptr->my_ptr->info.lastname,idx->my_ptr->info.lastname)>0)
            {
                idx->next=ptr;
                *lpptr=idx;
            }
            else
            {
            	(*lpptr)->next=idx;
			}
        }
        else 
        {
        	(*lpptr)->next=idx;
		}
    }
    else
    {
        while((ptr->next!=NULL) && !done && (strcmp(ptr->next->my_ptr->info.firstname,idx->my_ptr->info.firstname)<=0 ))
        {
            if(strcmp(ptr->next->my_ptr->info.firstname,idx->my_ptr->info.firstname)<0)
            {
                ptr=ptr->next;
            }
            else if(strcmp(ptr->next->my_ptr->info.firstname,idx->my_ptr->info.firstname)==0)
            {
                if(strcmp(ptr->next->my_ptr->info.lastname,idx->my_ptr->info.lastname)<0)
                {
                    ptr=ptr->next;
                }
                else
                {
                	idx->next=ptr->next;
                	ptr->next=idx;
                	done=TRUE;
				}
            }  
        }
        if(ptr->next==NULL)
        {
        	ptr->next=idx;
		}
		else if((strcmp(ptr->next->my_ptr->info.firstname,idx->my_ptr->info.firstname)>0) || 
				(strcmp(ptr->next->my_ptr->info.lastname,idx->my_ptr->info.lastname)>0))
		{
			idx->next=ptr->next;
			ptr->next=idx;
		} 
    }
}

// (a) Inserts Records such that records with idtype 0 are stored first followed idtype 1 and idtype 2
void InsertRecord(accommodation** lpptr,accommodation* nptr)
{
    accommodation* lptr=*lpptr;
    accommodation* ptr=*lpptr;
    if(lptr==NULL)              //given record is the first record in the list .. List is empty
    {
        lptr=nptr;
        lptr->next=NULL;
        lptr->prev=NULL;
    }
    else if(lptr->info.idtype>nptr->info.idtype)
    {
        nptr->next=lptr;
        lptr->prev=nptr;
        lptr=nptr;
        lptr->prev=NULL;
    }
    else
    {
        while(ptr->next!=NULL && ptr->next->info.idtype <= nptr->info.idtype)
        {
            ptr=ptr->next;
        }
        nptr->next=ptr->next;            //insert in between
        if(ptr->next!=NULL)
        {
            nptr->next->prev=nptr;
        }
        ptr->next=nptr;
        nptr->prev=ptr;
    }
    *lpptr=lptr;
}

// Delete Index node from the List when the record is deleted..either because it is requested or is duplicate
Node* delete_index(Node** lpptr,Node* idx)
{
	Node* prev=*lpptr;
	Node* ptr=prev->next;
	
	if(prev->idx_key==idx->idx_key)  
	{
		*lpptr=prev->next;
		prev->next=NULL;
	}
	else
	{
		while(ptr->idx_key!=idx->idx_key)
		{
			ptr=ptr->next;
			prev=prev->next;
		}
		if(ptr->next==NULL)
		{
			prev->next=NULL;
		}
		else
		{
			prev->next=ptr->next;
		}
	}
	return idx;
}

// Searching for index which mapped to the Record which was deleted
Node* modifyIndex(Node** lpptr,accommodation* rem)
{
	Node* ptr=*lpptr;
	Boolean found=FALSE;
	while(ptr!=NULL && !found)
	{		
		if(ptr->idx_key==rem->key)
		{
			found=TRUE;
			ptr=delete_index(lpptr,ptr);
		}
		else
		{
			ptr=ptr->next;
		}
			
	}
	return ptr;
}

// Deleted Record Node -- when duplicate Record is deleted or delete node is requested
void delete_node(accommodation** lpptr,accommodation* ptr)
{
    accommodation *prev_node,*next_node;
    accommodation* lptr=*lpptr;
    Node* retval;
    if(lptr!=NULL && ptr!=NULL)
    {
        prev_node=ptr->prev;
        next_node=ptr->next;
        if(ptr->prev==NULL)
        {
            lptr=ptr->next;
        }
        if(prev_node!=NULL)
        {
            prev_node->next=next_node;
        }
        if(next_node!=NULL)
        {
            next_node->prev=prev_node;
        }
        ptr->prev=NULL;
        retval=modifyIndex(&sort_idx,ptr);
        free(ptr);
        free(retval);
        retval=NULL;
        ptr=NULL;
    }
    *lpptr=lptr;
}

// (b) removes duplicates if any
void removeDuplicates(accommodation** lpptr)
{
	accommodation *ptr1,*ptr2,*temp;
	ptr1=*lpptr;
	while(ptr1!=NULL && ptr1->next!=NULL)
	{
		ptr2=ptr1;
		while(ptr2->next!=NULL)
		{
			if((strcmp(ptr1->info.id.empcode,ptr2->next->info.id.empcode)==0) && 
				(strcmp(ptr1->info.id.aadhar,ptr2->next->info.id.aadhar)==0) && 
				(strcmp(ptr1->info.id.passport,ptr2->next->info.id.passport)==0))
			{
				temp=ptr2->next;
				ptr2->next=ptr2->next->next;
				reset_type(*lpptr,ptr2->info.accommodation_type);
				delete_node(lpptr,temp);
			}
			else
			{
				ptr2=ptr2->next;
			}
		}
		ptr1=ptr1->next;
	}
}

// (d) Print the Records in sorted order using index LL
void printSortedRecords(Node** lpptr)
{
    Node* ptr=*lpptr;
    while(ptr!=NULL)
    {
        test_print(ptr->my_ptr);
        ptr=ptr->next;
    }
}

// (e) Search for a record requested based on firstname and lastname 
Boolean search(accommodation* lptr,char* f_name,char* l_name)
{
	accommodation* ptr=lptr;
	Boolean found=FALSE;
	while(ptr!=NULL && !found)
	{
		if(strcmp(ptr->info.firstname,f_name)==0 && strcmp(ptr->info.lastname,l_name)==0)
		{
			found=TRUE;
			test_print(ptr);
		}
		else
		{
			ptr=ptr->next;
		}
	}
	
	return found;
}

// (f) searches for the record to be deleted
status_code deleteRecord(accommodation** lpptr,int type,char* num)
{
	accommodation* ptr=*lpptr;
	status_code sc=SUCCESS;
	Boolean found =FALSE;
	while(ptr!=NULL && !found)
	{
		if((type==ptr->info.idtype)&&(strcmp(ptr->info.id.aadhar,num)==0 || strcmp(ptr->info.id.passport,num)==0 || strcmp(ptr->info.id.empcode,num)==0))
		{
			found=TRUE;
			
			delete_node(lpptr,ptr);
			reset_type(type_lptr,ptr->info.accommodation_type);
			sc=SUCCESS;
		}
		else
		{
			ptr=ptr->next;
		}
	}
	if(found==FALSE)
	{
		sc=FAILURE;
	}
	return sc;
}

// Change the index position when the Update request is made for Firstname and Lastname
void change_index(Node** lpptr,accommodation* rec)
{
	Node* ptr;
	ptr=modifyIndex(lpptr,rec);
	insertSort(lpptr,ptr);
}

// (g) Update request on name ,id ,Address
status_code updateRecord(accommodation** lpptr)
{
	accommodation* ptr=*lpptr;
	int update;
	char firstname[50];
	char lastname[50];
	char address[100];
	Boolean found = FALSE;
	status_code sc=SUCCESS;
	printf("\nPlease Enter the first name and last name of the person whose record is to be updated ");
	scanf("%s%s",&firstname,&lastname);
	while(ptr!=NULL && !found)
	{
		if(strcmp(ptr->info.firstname,firstname)==0 && strcmp(ptr->info.lastname,lastname)==0)
		{
			found=TRUE;
			printf("Which detail do you want to update...\n");
			printf("\t1: Update First Name\n");
			printf("\t2: Update Last Name\n");
			printf("\t3: Update Type of accommodation\n");
			printf("\t4: Update ID Type and ID Number\n");
			printf("\t5: Update address\n");
			printf("\t0: Exit\n");
			printf("\t Please Enter your choice....");
			scanf("%d",&update);
			switch(update)
			{
			    case 1:
			    {
			    	printf("Enter the changed First Name ");
			    	scanf("%s",ptr->info.firstname);
			    	change_index(&sort_idx,ptr); //changes index linked list
			    	break;
				}
				case 2:
				{
					printf("Enter the changed Last Name ");
			    	scanf("%s",ptr->info.lastname);
			    	change_index(&sort_idx,ptr); //changes index linked list
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
			    	scanf("%d",&(ptr->info.idtype));
			    	if(ptr->info.idtype==0)
			    	{
			    		scanf("%s",ptr->info.id.aadhar);
			    		ptr->info.id.passport[0]='\0';
						ptr->info.id.empcode[0]='\0';
					}
					else if(ptr->info.idtype==1)
			    	{
			    		scanf("%s",ptr->info.id.passport);
			    		ptr->info.id.aadhar[0]='\0';
						ptr->info.id.empcode[0]='\0';
					}
					else if(ptr->info.idtype==2)
			    	{
			    		scanf("%s",ptr->info.id.empcode);
			    		ptr->info.id.aadhar[0]='\0';
						ptr->info.id.passport[0]='\0';
					}
			    	break;
				}
				case 5:
				{
					printf("Enter New addressress\n");
					fflush(stdin);
					fgets(ptr->info.address,100,stdin);
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
		else
		{
			ptr=ptr->next;
		}
	}
	if(found==FALSE)
	{
		sc=FAILURE;
	}
	return sc;
}

// (h) special Request to change the allocated block
status_code specialRequestAllocation(accommodation* lptr,int id_type,char* id_num,Type* acc_type,char* request_type)
{
	status_code sc=SUCCESS;
	Boolean found=FALSE;
	Boolean reset_found=FALSE;
	accommodation* a_ptr;
	char cur_type[10];
	for(a_ptr=lptr;a_ptr!=NULL && !found ;a_ptr=a_ptr->next)
	{
		if(a_ptr->info.idtype==id_type && ((strcmp(a_ptr->info.id.aadhar,id_num)==0) || 
											(strcmp(a_ptr->info.id.passport,id_num)==0) || 
											(strcmp(a_ptr->info.id.empcode,id_num)==0)))
		{
			found=TRUE;
			strcpy(cur_type,a_ptr->info.accommodation_type);
			reset_found=allocate_type(acc_type,request_type);
			if(reset_found==TRUE)
			{
				strcpy(a_ptr->info.accommodation_type,request_type);
				reset_type(acc_type,cur_type);
			}
		}
	}
	if(found==FALSE)
	{
		printf("\n No Record Found..Please Try Again\n");
	}
	return reset_found;
}

int main()
{
    Node* idx;
	int choice=0;
	Boolean status;
	accommodation* nptr;
	create_type_list(&type_lptr,2);
	char firstname[50],lastname[50],accommodation_type[10],aadhar[15],passport[15],empcode[5],address[100];
	int idtype;
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
				nptr=(accommodation*)malloc(sizeof(accommodation));
				nptr->next=NULL;
				nptr->prev=NULL;

                idx=(Node*)malloc(sizeof(Node));
                idx->my_ptr=nptr;
                idx->next=NULL;
				idx->idx_key=my_key;
				printf("\nPlease Enter the details seperated by space ");
				scanf("%s%s%s%d",firstname,lastname,accommodation_type,&idtype);
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
				status=allocate_type(type_lptr,accommodation_type);
				if(status==TRUE)
				{
					strcpy(nptr->info.firstname,firstname);
					strcpy(nptr->info.lastname,lastname);
					strcpy(nptr->info.accommodation_type,accommodation_type);
					nptr->info.idtype=idtype;
					nptr->key=my_key;
					my_key++;
					if(nptr->info.idtype==0)
					{	
						strcpy(nptr->info.id.aadhar,aadhar);
						nptr->info.id.passport[0]='\0';
						nptr->info.id.empcode[0]='\0';
					}
					else if(nptr->info.idtype==1)
					{
						nptr->info.id.aadhar[0]='\0';
						strcpy(nptr->info.id.passport,passport);
						nptr->info.id.empcode[0]='\0';
					}
					else if(nptr->info.idtype==2)
					{
						nptr->info.id.aadhar[0]='\0';
						nptr->info.id.passport[0]='\0';
						strcpy(nptr->info.id.empcode,empcode);
					}
					strcpy(nptr->info.address,address);
					InsertRecord(&record,nptr);
					insertSort(&sort_idx,idx);
					
				}
				else
				{
					printf("Requested Allocation Not Available\n");
				}
				break;
			}
			case 2:
				{
					removeDuplicates(&record);
					break;
				}
			case 3:
				{
					printRecords(record);
                    print_type(type_lptr);
					break;
				}
			case 4:
				{
					printSortedRecords(&sort_idx);
					break;
				}
			case 5:
				{
					char first_name[50], last_name[50];
					printf("\nEnter the first name and last name you want to search  ");
					scanf("%s%s",first_name,last_name);
					status=search(record,first_name,last_name);
					if(status==FALSE)
					{
						printf("\nSorry no such record exist\n");
					}
					break;
				}
			case 6:
				{
					int idtype;
					status_code status;
					char id_num[15];
					printf("Enter ID Type and ID Number of the Employee, whose record you want to delete  ");
					scanf("%d%s",&idtype,&id_num);
					
					status=deleteRecord(&record,idtype,id_num);
					if(status==FALSE)
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
					status_code status;
					status=updateRecord(&record);
					if(status==FALSE)
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
					status=specialRequestAllocation(record,idtype,id_number,type_lptr,request_type);
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
					{
						printf("Wrong input\n Please try again\n\n");
						break;
					}
					
		}
	} while(choice!=0);
}
