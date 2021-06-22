/*	Name: APPARI SHANTI
	Roll No. : BT19CSE126
	Batch : R4
	
	Homework Assignment 2
	ACCOMMODATION MANAGEMENT SYSTEM 
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum{FAILURE,SUCCESS}status_code;
typedef enum{FALSE,TRUE}Boolean;
int my_key=1;

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
	int idx;
}Record;

//tree node
typedef struct node_tag
{
	Record info;
	struct node_tag* left;
	struct node_tag* right;
	int height;
}node;

//sorted tree node
typedef struct index_tree
{
	Record* my_sort;
	struct index_tree* left;
	struct index_tree* right;
	int idx_key;
	int height;
}index;

//type structure for storing accommodation types
typedef struct type_tag
{
	struct type_tag* next;
	char status[3];
	char blockName[4];
	Record* resident;
}acc_type;

//4 blocks for 4 types
acc_type* blocks[4];

//creating a 10 block structure for each type of blocks A,B,C,D and giving them names as A1,A2,...A10,B1,B2..10,D1...D10
//and setting status as NOT ACCOMMODATED 
// "NA" ----> Not Accommodated
// "A" -----> Accommodated
acc_type* create_block(acc_type* lptr,char t)
{
	int i;
	for(i=9;i>=0;i--)
	{
		acc_type* type_ptr=(acc_type*)malloc(sizeof(acc_type));
		type_ptr->blockName[0]=t;
		type_ptr->resident=NULL;
		if(i+1<10)
		{
			type_ptr->blockName[1]=i+1+'0';
			type_ptr->blockName[2]='\0';
		}
		else
		{
			type_ptr->blockName[1]=1+'0';
			type_ptr->blockName[2]=0+'0';
			type_ptr->blockName[3]='\0';
		}
		strcpy(type_ptr->status,"NA");
		type_ptr->next=NULL;
		if(lptr==NULL)
		{
			lptr=type_ptr;
		}
		else
		{
			type_ptr->next=lptr;
			lptr=type_ptr;
		}
	}
	return lptr;
}
void initialise_type()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		blocks[i]=NULL;
		blocks[i]=create_block(blocks[i],65+i);
	}
}

void print_type()
{
	int i;
	acc_type* lptr_A=blocks[0];
	acc_type* lptr_B=blocks[1];
	acc_type* lptr_C=blocks[2];
	acc_type* lptr_D=blocks[3];
	while(lptr_A!=NULL)
	{
		printf(" %s %s\t %s %s\t %s %s\t %s %s\n",lptr_A->blockName,lptr_A->status,lptr_B->blockName,lptr_B->status,lptr_C->blockName,lptr_C->status,lptr_D->blockName,lptr_D->status);
		lptr_A=lptr_A->next;
		lptr_B=lptr_B->next;
		lptr_C=lptr_C->next;
		lptr_D=lptr_D->next;
	}
}

void print_rec(Record* p_rec)
{
	printf("%s\t%s\t%s\t%d\t",p_rec->firstname,p_rec->lastname,p_rec->accommodation_type,p_rec->idtype);
	if(p_rec->idtype==0)
	{
		printf("%s\t",p_rec->id.aadhar);
	}
	if(p_rec->idtype==1)
	{
		printf("%s\t",p_rec->id.passport);
	}
	if(p_rec->idtype==2)
	{
		printf("%s\t",p_rec->id.empcode);
	}
	puts(p_rec->address);
}

//Block if NA is allocated to appropriate type
Boolean allocateBlock(char* req_type,Record* res)
{
	Boolean found=FALSE;
	if(strcmp("type_A",req_type)==0)
	{
		acc_type* ptr1=blocks[0];
		while(ptr1!=NULL && !found)
		{
			if(strcmp(ptr1->status,"NA")==0)
			{
				found=TRUE;
				strcpy(ptr1->status,"A");
				ptr1->resident=res;
			}
			else
			{
				ptr1=ptr1->next;
			}
		}
	}
	else if(strcmp("type_B",req_type)==0)
	{
		acc_type* ptr2=blocks[1];
		while(ptr2!=NULL && !found)
		{
			if(strcmp(ptr2->status,"NA")==0)
			{
				found=TRUE;
				strcpy(ptr2->status,"A");
				ptr2->resident=res;
			}
			else
			{
				ptr2=ptr2->next;
			}
		}
	}
	else if(strcmp("type_C",req_type)==0)
	{
		acc_type* ptr3=blocks[2];
		while(ptr3!=NULL && !found)
		{
			if(strcmp(ptr3->status,"NA")==0)
			{
				found=TRUE;
				strcpy(ptr3->status,"A");
				ptr3->resident=res;
			}
			else
			{
				ptr3=ptr3->next;
			}
		}
	}
	else if(strcmp("type_D",req_type)==0)
	{
		acc_type* ptr4=blocks[3];
		while(ptr4!=NULL && !found)
		{
			if(strcmp(ptr4->status,"NA")==0)
			{
				found=TRUE;
				strcpy(ptr4->status,"A");
				ptr4->resident=res;
			}
			else
			{
				ptr4=ptr4->next;
			}
		}
	}
	return found;
}

//Block is deallocated and set as NA 
void deallocateBlock(char* type,int idx)
{
	Boolean found=FALSE;
	if(strcmp("type_A",type)==0)
	{
		acc_type* ptr=blocks[0];
		print_rec(ptr->resident);
		while(ptr!=NULL && !found)
		{
			if(ptr->resident->idx==idx)
			{
				found=TRUE;
				strcpy(ptr->status,"NA");
				ptr->resident=NULL;
			}
			else
			{
				ptr=ptr->next;
			}
		}
	}
	else if(strcmp("type_B",type)==0)
	{
		acc_type* ptr=blocks[1];
		while(ptr!=NULL && !found)
		{
			if(ptr->resident->idx==idx)
			{
				found=TRUE;
				strcpy(ptr->status,"NA");
				ptr->resident=NULL;
			}
			else
			{
				ptr=ptr->next;
			}
		}
	}
	else if(strcmp("type_C",type)==0)
	{
		acc_type* ptr=blocks[2];
		while(ptr!=NULL && !found)
		{
			if(ptr->resident->idx==idx)
			{
				found=TRUE;
				strcpy(ptr->status,"NA");
				ptr->resident=NULL;
			}
			else
			{
				ptr=ptr->next;
			}
		}
	}
	else if(strcmp("type_D",type)==0)
	{
		acc_type* ptr=blocks[3];
		while(ptr!=NULL && !found)
		{
			if(ptr->resident->idx==idx)
			{
				found=TRUE;
				strcpy(ptr->status,"NA");
				ptr->resident=NULL;
			}
			else
			{
				ptr=ptr->next;
			}
		}
	}
}

//max for getting the max height of left subtree or right subtree
int max(int a,int b)
{
	return (a>b)?a:b;
}

//finding height of a node
int height(node* n)
{
	int ret_val;
	if(n==NULL)
	{
		ret_val=-1;
	}
	else if(n->left==NULL && n->right==NULL)
	{
		ret_val=0;
	}
	else
	{
		ret_val= 1+max(height(n->left),height(n->right));
	}
	return ret_val;
}

//Calculates balance factors of a node
int balanceFactor(node* n)
{
	int bal;
	if(n==NULL)
	{
		bal=0;
	}
	else
	{
		bal=height(n->left)-height(n->right);
	}
	return bal;
}

//Creating a tree node with record values
node* createNode(Record* details)
{
	node* nptr=(node*)malloc(sizeof(node));
	nptr->info=*details;
	nptr->left=NULL;
	nptr->right=NULL;
	nptr->height=1;
	return nptr;
}

//Creating index node to point to the correct node in tree to get sorted record
index* createIdx(Record* rec)
{
	index* nptr=(index*)malloc(sizeof(index));
	nptr->my_sort=rec;
	nptr->left=NULL;
	nptr->right=NULL;
	nptr->height=1;
	nptr->idx_key=rec->idx;;
	return nptr;
}

// a) Printing records in order of 0,1,2 id types
void print_root(node* root)   //preorder
{
	if(root!=NULL)
	{
		print_root(root->left);
		print_rec(&(root->info));
		print_root(root->right);
	}
}

//Printing a single record
void Visit(index* p_rec)
{
	printf("%s\t%s\t%s\t%d\t",p_rec->my_sort->firstname,p_rec->my_sort->lastname,p_rec->my_sort->accommodation_type,p_rec->my_sort->idtype);
	if(p_rec->my_sort->idtype==0)
	{
		printf("%s\t",p_rec->my_sort->id.aadhar);
	}
	if(p_rec->my_sort->idtype==1)
	{
		printf("%s\t",p_rec->my_sort->id.passport);
	}
	if(p_rec->my_sort->idtype==2)
	{
		printf("%s\t",p_rec->my_sort->id.empcode);
	}
	puts(p_rec->my_sort->address);
}

//Right Rotate for balancing
node *rightRotate(node *r)
{
    node* x;
    if(r!=NULL && r->left!=NULL)
    {
    	x=r->left;
    	r->left=x->right;
    	x->right=r;
    	r->height=height(r);
    	x->height=height(x);
	}
	return x;
}
  
//left Rotate for balancing
node* leftRotate(node* r)
{
    node* x;
    if(r!=NULL && r->right!=NULL)
    {
    	x=r->right;
    	r->right=x->left;
    	x->left=r;
    	r->height=height(r);
    	x->height=height(x);
	}
	return x;
}

//Create key creates a unique key using id_type and id_num
void create_key(Record* rec,char* rec_key)
{
	char ty[2];
	sprintf(ty,"%d",rec->idtype);
	strcpy(rec_key,ty);
	if(rec->id.aadhar[0]!='\0')
	{
		strcat(rec_key,rec->id.aadhar);
	}
	else if(rec->id.passport[0]!='\0')
	{
		strcat(rec_key,rec->id.passport);
	//	printf("%s",rec_key);
	}
	else if(rec->id.empcode[0]!='\0')
	{
		strcat(rec_key,rec->id.empcode);
	}
}

//a) Inserting a node to Tree using the order 0,1,2 of id_types
node* InsertNode(node* root,Record* rec)
{
	if(root==NULL)
	{
		root=createNode(rec);
	}
	else
	{
		char rec_key[20];
		create_key(rec,rec_key);
		char root_key[20];
		create_key(&(root->info),root_key);
	
		if(strcmp(rec_key,root_key)<0)
		{
			root->left=InsertNode(root->left,rec);
		}
		else
		{
			root->right=InsertNode(root->right,rec);
		}
	}
	root->height=height(root);
	
	if(balanceFactor(root)==2 && balanceFactor(root->left)==1)  //tree inclined in left direction
	{
		root=rightRotate(root);
	}
	else if(balanceFactor(root)==2 && balanceFactor(root->left)==-1) //LR case double rotation
	{
		root->left=leftRotate(root->left);
		root=rightRotate(root);
	}
	else if(balanceFactor(root)==-2 && balanceFactor(root->right)==-1) //tree inclined in right direction
	{
		root=leftRotate(root);
	}
	else if(balanceFactor(root)==-2 && balanceFactor(root->right)==1) //RL case double rotation
	{
		root->right=rightRotate(root->right);
		root=leftRotate(root);
	}
	return root;
}

//inserting the sorted index node in correct order of firstnamaes and last names
index* Sort_idx(index* idx_root,Record* rec)
{
	if(idx_root==NULL)
	{
		idx_root=createIdx(rec);
	}
	else
	{
		char in_name[100];
		strcpy(in_name,rec->firstname);
		strcat(in_name,rec->lastname);
		char node_name[100];
		strcpy(node_name,idx_root->my_sort->firstname);
		strcat(node_name,idx_root->my_sort->lastname);
		
		if(strcmp(in_name,node_name)<0)
		{
			idx_root->left=Sort_idx(idx_root->left,rec);
		}
		else
		{
			idx_root->right=Sort_idx(idx_root->right,rec);
		}
	}
	return idx_root;
}

// d) Print sorted Records based on firstname and lastname using index tree
void printSortedRecords(index* root)
{
	if(root!=NULL)
	{
		printSortedRecords(root->left);
		Visit(root);
		printSortedRecords(root->right);
	}
}

//  Search in the index tree if first name last name provided
index* search_idx(index* root,char* f_name,char* l_name)
{
	index* ret_val=NULL;
	if(root!=NULL)
	{
		if(strcmp(f_name,root->my_sort->firstname)==0)
		{
			if(strcmp(l_name,root->my_sort->lastname)==0)
				ret_val=root;
			else if(strcmp(l_name,root->my_sort->lastname)<0)
				ret_val=search_idx(root->left,f_name,l_name);
			else
				ret_val=search_idx(root->right,f_name,l_name);
		}
		else if(strcmp(f_name,root->my_sort->firstname)<0)
		{
			ret_val=search_idx(root->left,f_name,l_name);
		}
		else
		{
			ret_val=search_idx(root->right,f_name,l_name);
		}
	}
	return ret_val;
}

// (e) Search in the actual tree if idtype and id_num provided
node* search(node* root,int type,char* num)
{
	node* ret_val=NULL;
	node* current=root;
	char root_key[20];     //root key
   	char se_key[20];      //search key
    char typ[2];
    sprintf(typ,"%d",type);
    strcpy(se_key,typ);
    strcat(se_key,num);
	if(root!=NULL)
	{
		if(type==root->info.idtype)
		{
			if(type==0)
			{
				if(strcmp(num,root->info.id.aadhar)==0)
				{
					ret_val=root;
				}
				else if(strcmp(num,root->info.id.aadhar)<0)
				{
					ret_val=search(root->left,type,num);
				}
				else
				{
					ret_val=search(root->right,type,num);
				}
			}
			else if(type==1)
			{
				if(strcmp(num,root->info.id.passport)==0)
				{
					ret_val=root;
				}
				else if(strcmp(num,root->info.id.passport)<0)
				{
					ret_val=search(root->left,type,num);
				}
				else
				{
					ret_val=search(root->right,type,num);
				}
			}
			else if(type==2)
			{
				if(strcmp(num,root->info.id.empcode)==0)
				{
					ret_val=root;
				}
				else if(strcmp(num,root->info.id.empcode)<0)
				{
					ret_val=search(root->left,type,num);
				}
				else
				{
					ret_val=search(root->right,type,num);
				}
			}	
		}
		else if(type<root->info.idtype)
		{
			ret_val=search(root->left,type,num);
		}
		else
		{
			ret_val=search(root->right,type,num);
		}
	}
	return ret_val;
}

//Find the Extreme left child of a node in index tree
index* findExtremeChild(index* node)
{
    index* ptr=node;
    while(ptr!=NULL && ptr->left!=NULL)
    {
    	ptr=ptr->left;
	}
    return ptr;
}

//Find the Extreme left child of a node in tree
node* findExtremeChild_node(node* n)
{
    node* ptr=n;
    while(ptr!=NULL && ptr->left!=NULL)
    {
    	ptr=ptr->left;
	}
    return ptr;
}

//delete a node from index tree whenever a tree node is deleted or first name or last name is changed
index* deleteIdx(index* root,char* f_name,char* l_name)
{
	index* ret_val = NULL;
 	char de_key[100];    //delete key
 	strcpy(de_key,f_name);
 	strcat(de_key,l_name);
 	char root_key[100];  //root key
 	strcpy(root_key,root->my_sort->firstname);
 	strcat(root_key,root->my_sort->lastname);
    if (root == NULL)
    {
    	ret_val=root;
	}
        
    else if (strcmp(de_key,root_key)<0)
    {
    	root->left = deleteIdx(root->left, f_name,l_name);
	}
    else if (strcmp(de_key,root_key)>0)
    {
    	root->right = deleteIdx(root->right, f_name,l_name);
	}
    else 
	{
        if(root->left==NULL && root->right==NULL) //node to be removed is leaf node
        {
        	free(root);
        	root= NULL;
		}
        else if (root->left == NULL) //node to be removed has a right child
		{
            index* temp = root->right;
            free(root);
            ret_val=temp;
            root=temp;
        }
        else if (root->right == NULL) //node to be removed has left child
		{
            index* temp = root->left;
            free(root);
            ret_val=temp;
            root=temp;
        }
        else                         //node to be removed has 2 children
        {
        	index* temp = findExtremeChild(root->right);
        	root->my_sort->idtype = temp->my_sort->idtype;
       		strcpy(root->my_sort->firstname,temp->my_sort->firstname);
       		strcpy(root->my_sort->lastname,temp->my_sort->lastname);
       		strcpy(root->my_sort->accommodation_type,temp->my_sort->accommodation_type);
        	strcpy(root->my_sort->id.aadhar,temp->my_sort->id.aadhar);
        	strcpy(root->my_sort->id.passport,temp->my_sort->id.passport);
        	strcpy(root->my_sort->id.empcode,temp->my_sort->id.empcode);
        	strcpy(root->my_sort->address,temp->my_sort->address);
        	root->my_sort->idx=temp->my_sort->idx;

        	root->right = deleteIdx(root->right, temp->my_sort->firstname,temp->my_sort->lastname);
		}
        
    }
    return root;
}

//finding extreme right child in tree
node* rightChild(node* p)
{
    while(p->right!=NULL)
    {
    	 p = p->right;
	}
    return p;    
}
//finding extreme left child in the tree
node* leftChild(node* p)
{
    while(p->left!=NULL)
    {
        p = p->left;
	}
	return p;    
}

// (f) delete record when id_type and id_num given
node* deleteRecord(node* root,int type,char* num)
{
	node* ret_val=NULL;
    if(root->left == NULL && root->right == NULL)
	{
    	root=NULL;
        free(root);
        return NULL;
    }
    else
    {
    	node *t;
   		node *q;
   		char root_key[20];         //root key
    	create_key(&(root->info),root_key);
    	char de_key[20];          //delete key
    	char typ[2];
    	sprintf(typ,"%d",type);
    	strcpy(de_key,typ);
    	strcat(de_key,num);
    	
    	if(strcmp(de_key,root_key) < 0)
		{
            root->left = deleteRecord(root->left,type,num);
    	}
    	else if(strcmp(de_key,root_key) > 0)
		{
            root->right = deleteRecord(root->right,type,num);
    	}
    	else 
		{
			//printf("before balance %s %s\n",root->info.firstname,root->info.lastname);
            if(root->left != NULL)  //node to be deleted has a left child
			{
                q = rightChild(root->left);    //finding the rightmost child of left subtree
                root->info = q->info;
                if(q->info.idtype==0)          //aadhar number
                {
                	root->left=deleteRecord(root->left,q->info.idtype,q->info.id.aadhar);
				}
                else if(q->info.idtype==1)     //passport number
                {
                	root->left=deleteRecord(root->left,q->info.idtype,q->info.id.passport);
				}
                else if(q->info.idtype==2)      //empcode
                {
                	root->left=deleteRecord(root->left,q->info.idtype,q->info.id.empcode);
				}	
            }
            else                                 //node to be deleted has a right child
			{
                q=leftChild(root->right);      //finding the leftmost chhild of right subtree
                root->info=q->info;
                if(q->info.idtype==0)          //aadhar number
                {
                	root->right=deleteRecord(root->right,q->info.idtype,q->info.id.aadhar);
				}
                else if(q->info.idtype==1)     //passport number
                {
                	root->right=deleteRecord(root->right,q->info.idtype,q->info.id.passport);
				}
                else if(q->info.idtype==2)     //empcode
                {
                	root->right=deleteRecord(root->right,q->info.idtype,q->info.id.empcode);
				}	
            }
   		}
    }
    if(balanceFactor(root)==2 && balanceFactor(root->left)==1)  
	{ 
		root = rightRotate(root); 
	}                  
    else if(balanceFactor(root)==2 && balanceFactor(root->left)==-1) 
	{
		root->left=leftRotate(root->left);
		root=rightRotate(root);
	}
    else if(balanceFactor(root)==2 && balanceFactor(root->left)==0)   
	{ 
		root = rightRotate(root); 
	}
    else if(balanceFactor(root)==-2 && balanceFactor(root->right)==-1)
	{
		root = leftRotate(root); 
	}
    else if(balanceFactor(root)==-2 && balanceFactor(root->right)==1)
	{
		root->right=rightRotate(root->right);
		root=leftRotate(root);
	}
    else if(balanceFactor(root)==-2 && balanceFactor(root->right)==0)
	{
		root = leftRotate(root); 
	}
    return root;
}

// (g) update record based on the choice of the employee
node* updateRecord(node* root,index** idx_root)
{
	int update;
	int type;
	char num[20];
	node* found_node;
	Boolean found = FALSE;
	status_code sc=SUCCESS;
	printf("\nPlease Enter the idtype and id Number of the person whose record is to be updated ");
	scanf("%d%s",&type,num);
	found_node=search(root,type,num);
	if(found_node!=NULL)
	{
		printf("Which detail do you want to update...\n");
		printf("\t1: Update First Name\n");
		printf("\t2: Update Last Name\n");
		printf("\t3: Update Type of accommodation\n");
		printf("\t4: Update address\n");
		printf("\t0: Exit\n");
		printf("\t Please Enter your choice....");
		scanf("%d",&update);
		switch(update)
		{
			case 1:
				{
			    	char first_name[50];
			    	char changed_first[50];
			    	strcpy(first_name,found_node->info.firstname);
			    	printf("Enter the changed First Name ");
			    	scanf("%s",changed_first);
			    	
			    	
			    	//printSortedRecords(*idx_root);
			    	node* nptr=createNode(&(found_node->info));
			    	strcpy(nptr->info.firstname,changed_first);
			    	
			    	*idx_root=Sort_idx(*idx_root,&(nptr->info));//changing index tree
			    	strcpy(found_node->info.firstname,changed_first);
			    	
			    	*idx_root=deleteIdx(*idx_root,first_name,found_node->info.lastname); //deleting the earlier node of the index tree
			    	
			    	break;
				}
			case 2:
				{
					char last_name[50];
			    	char changed_last[50];
			    	strcpy(last_name,found_node->info.lastname);
			    	printf("Enter the changed Last Name ");
			    	scanf("%s",changed_last);
			    	
			    	//printSortedRecords(*idx_root);
			    	node* nptr=createNode(&(found_node->info));
			    	strcpy(nptr->info.lastname,changed_last);
			    	
			    	*idx_root=Sort_idx(*idx_root,&(nptr->info)); //changing the sorted index tree
			    	strcpy(found_node->info.lastname,changed_last);
			    	
			    	*idx_root=deleteIdx(*idx_root,found_node->info.firstname,last_name); //deleting th eearlier node 
			    	break;
				}
			case 3:
				{
					printf("To change the accommodation Type, Please use the special request accommodation option from the main menu.\n");
			    	break;
				}
			case 4:
				{
					printf("Enter New Adress\n");
					fflush(stdin);
					fgets(found_node->info.address,100,stdin);
					index* found_idx=search_idx(*idx_root,found_node->info.firstname,found_node->info.lastname);
					strcpy(found_idx->my_sort->address,found_node->info.address);
					break;
				}
			case 0:
				{
					printf("Exiting\n");
					break;
				}
			default:
				{
					printf("Wrong Input!! Please try again");
					break;
				}
		}
	}
	return found_node;
}

// (h) Allocated a requested block bassed on the availablility
Boolean specialRequestAllocation(node* root,int type,char* num,char* req,index* idx_root)
{
	char cur_type[10];
	Boolean reset_found=FALSE;
	node* found_node=search(root,type,num);
	if(found_node!=NULL)
	{
		strcpy(cur_type,found_node->info.accommodation_type);
		reset_found=allocateBlock(req,&(found_node->info));   //allocate the required block
		
		if(reset_found)      //if available
		{
			deallocateBlock(cur_type,found_node->info.idx);   //deallocate the previous block
			strcpy(found_node->info.accommodation_type,req);
			
			index* found_idx=search_idx(idx_root,found_node->info.firstname,found_node->info.lastname);
			strcpy(found_idx->my_sort->accommodation_type,req);
		}
	}
	if(found_node==NULL)
	{
		printf("\n No Record Found..Please Try Again\n");
	}
	return reset_found;
}

Boolean addressSearch(char* r1,char* r2)
{
	Boolean done=FALSE;
	if(r1[0]==r2[0])        //range search done in the same type of block storing in zeroth position
	{
		if(r1[1]-'0'<r2[1]-'0' || r1[2]<r2[2])  //the order should be ascending 
		{
			acc_type* lptr=blocks[r1[0]-'A'];
			while(lptr!=NULL && strcmp(lptr->blockName,r1)!=0)
			{
				lptr=lptr->next;		
			}
			while(lptr!=NULL && strcmp(lptr->blockName,r2)!=0)
			{
				if(strcmp(lptr->status,"A")==0)
				print_rec(lptr->resident);
				lptr=lptr->next;
			}
			done=TRUE;
		}	
	}
	return done;
}


int main()
{
	int choice=0;
	Boolean status;
	Record* nptr;
	index* idx_root=NULL;
	initialise_type();
	node* root=NULL;
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
		printf("\t9: Range Search\n");
		printf("\t0: Exit\n\n");
		printf("NOTE: The correct format for accommodation type is type_A,type_B,type_C,type_D. Kindly use correct format for entering accommodation type\n\n");
		printf("Please Enter your choice.....");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
				nptr=(Record*)malloc(sizeof(Record));
				nptr->idx=my_key;
				my_key++;
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
				
				strcpy(nptr->firstname,firstname);
				strcpy(nptr->lastname,lastname);
				strcpy(nptr->accommodation_type,accommodation_type);
				nptr->idtype=idtype;
				if(nptr->idtype==0)
				{	
					strcpy(nptr->id.aadhar,aadhar);
					nptr->id.passport[0]='\0';
					nptr->id.empcode[0]='\0';
				}
				else if(nptr->idtype==1)
				{
					nptr->id.aadhar[0]='\0';
					strcpy(nptr->id.passport,passport);
					nptr->id.empcode[0]='\0';
				}
				else if(nptr->idtype==2)
				{
					nptr->id.aadhar[0]='\0';
					nptr->id.passport[0]='\0';
					strcpy(nptr->id.empcode,empcode);
				}
				strcpy(nptr->address,address);
				status=allocateBlock(nptr->accommodation_type,nptr);
				if(status==TRUE)
				{
					idx_root=Sort_idx(idx_root,nptr);
					root=InsertNode(root,nptr);
					print_root(root);
					printf("\nPrinting Accomodation table with availability\n\n");
					print_type();
				}
				else
				{
					printf("Requested Allocation Not Available\n");
				}
				break;
			}
			case 2:
				{
					printf("No duplicates Found\n\n");
					break;
				}
			case 3:
				{
					print_root(root);
					break;
				}
			case 4:
				{
					printSortedRecords(idx_root);
					break;
				}
			case 5:
				{
					int type;
					char num[20];
					printf("\nEnter the type and num you want to search  ");
					scanf("%d%s",&type,num);
					node* found_node= search(root,type,num);
					if(found_node==NULL)
					{
						printf("Record Doesn't Exist\n");
					}
					else
					{
						printf("Found!! Printing Details-----\n");
						print_rec(&(found_node->info));
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
					int sc;
					if(root->right==NULL && root->left==NULL)
					{
						if(root->info.idtype==idtype && (strcmp(root->info.id.aadhar,id_num)==0 ||
															strcmp(root->info.id.passport,id_num)==0 ||
															strcmp(root->info.id.empcode,id_num)==0))
							{
								deallocateBlock(root->info.accommodation_type,root->info.idx);
								idx_root=deleteIdx(idx_root,root->info.firstname,root->info.lastname);
							
								print_type();
								free(root);
								root=NULL;							
							}
						else
						{
							printf("Entered details are incorrect\n");
						}
					}
					else
					{
						node* found_node=search(root,idtype,id_num);
						if(found_node!=NULL)
						{
							char acc_ty[10];
							int idx;
							strcpy(acc_ty,found_node->info.accommodation_type);
							idx=found_node->info.idx;
							deallocateBlock(acc_ty,idx); //deallocate the accommodation block
							
							idx_root=deleteIdx(idx_root,found_node->info.firstname,found_node->info.lastname);
							root=deleteRecord(root,idtype,id_num);
						}
						else if(found_node==NULL)
						{
							printf("No such record found\n");
						}
						printf("\n\n Accommodation table after deletion\n\n");
						print_type();
					}
					break;
				}
				case 7:
					{
						node* found_node;
						found_node=updateRecord(root,&idx_root);
						if(found_node!=NULL)
						{
							printf("Displaying Upadated details------\n");
							print_rec(&(found_node->info));
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
						status=specialRequestAllocation(root,idtype,id_number,request_type,idx_root);
						if(status==0)
						{
							printf("Sorry!!Requested Type Not Available\n");
						}
						break;
					}
				case 9:
					{
						char r1[4],r2[4];
						printf("Enter the range you want to search ");
						scanf("%s%s",r1,r2);
						status=addressSearch(r1,r2);
						if(status==0)
						{
							printf("Invalid address range\n");
						}
						break;
					}
	    }
	}while(choice!=0);
}

