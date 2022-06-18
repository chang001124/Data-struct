#include <stdio.h>
#include <stdlib.h>
/****************************/
typedef struct listnode *listpointer;
typedef struct listnode {
	int data;
	listpointer link;
}listnode;
listpointer head=NULL;
/****************************/
void creat(int num){
	listpointer newnode=(listpointer)malloc(sizeof(listnode));
	newnode->data=num;
	newnode->link=NULL;
	if(head==NULL){
		head=newnode;
		return;
	} 
	listpointer ptr=head;
	while(ptr->link!=NULL){
		ptr=ptr->link;
	}
	ptr->link=newnode;
}
/****************************/
void del(int num){
	if(num<=0)
		return;
	int i;
	listpointer ptr=head,back;
	for(i=1;i<num;i++){
		back=ptr;
		ptr=ptr->link;if(ptr==NULL)
		return;
	}
	
	if(ptr==head){
		back=head;
		head=head->link;
	}
	back->link=ptr->link;
	back=ptr;
	free(back);
}
/****************************/
void ins(int num1,int num2){
	int i;
	listpointer newnode=(listpointer)malloc(sizeof(listnode));
	newnode->data=num2;
	newnode->link=NULL;
	listpointer ptr=head;
	for(i=1;i<num1;i++)
		ptr=ptr->link;
	newnode->link=ptr->link;
	ptr->link=newnode;
}
/****************************/
listpointer rev(listpointer header,int num){
	listpointer rear,middle,last;
	rear=NULL;
	middle=NULL;
	last=header;
	int i;
	for(i=0;i<num&&last!=NULL;i++){
		rear=middle;
		middle=last;
		last=last->link;
		middle->link=rear;
	}
	if(i==num&&last!=NULL)
		header->link=rev(last,num);
	return middle;
}
/****************************/
void show(){
	listpointer ptr=head;
	while(ptr!=NULL){
		printf("%d ",ptr->data);
		ptr=ptr->link;
	}
	printf("\n");
}
/****************************/
int main() {
	FILE *fptr;
	fptr=fopen("input_4-2.txt","r");
	int n,m,num1,num2,i;
	fscanf(fptr,"%d%d",&n,&m);
	//printf("%d %d\n",n,m);
	for(i=1;i<=n;i++){
		fscanf(fptr,"%d",&num1);
		creat(num1);
	}
	char a[5];
	for(i=1;i<=m;i++){
		fscanf(fptr,"%s",a);
		if(!strcmp(a,"add")){
			fscanf(fptr,"%d",&num1);
			creat(num1);
		}
		else if(!strcmp(a,"del")){
			fscanf(fptr,"%d",&num1);
			del(num1);
		}
		else if(!strcmp(a,"ins")){
			fscanf(fptr,"%d%d",&num1,&num2);
			ins(num1,num2);
		}
		else if(!strcmp(a,"rev")){
			fscanf(fptr,"%d",&num1);
			head=rev(head,num1);
		}
		else if(!strcmp(a,"show")){
			show();
		}
	}
	//show();
	fclose(fptr);
	return 0;
}

