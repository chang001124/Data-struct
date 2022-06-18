#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE *fptr1;

typedef struct listNode *listPointer;
typedef struct listNode {	
	int data;
	listPointer link;
}listNode;
listPointer head=NULL,tail;
void push_back(int num){
	listPointer new_one=(listPointer)malloc(sizeof(listNode));
	new_one->data=num;
	new_one->link=NULL;
	if(head==NULL){
		head=new_one;
		return;
	}
	listPointer last=head;
	while(last->link!=NULL){
		last=last->link;
	}
	last->link=new_one;
}
void del(int num){
	if(head==NULL||num==0){
		return;
	}
	int i;
	listPointer last=head;
	if(num==1){
		head=last->link;
		free(last);
		return;
	}
	listPointer temp;
	for(i=1;i<num-1;i++){
		last=last->link;
		if(last==NULL)
			return;
	}
	temp=last->link;
	if(temp==NULL)
		return;
	last->link=last->link->link;
	free(temp);
}
void mul(int num,int num1){
	if(head==NULL||num==0){
		return;
	}
	int i,count=0;
	listPointer last=head;
	while(last->link!=NULL){
		last=last->link;
		count++;
	}
	count++;
	last=head;
	for(i=1;i<=count-num;i++){
		last=last->link;
	}
	last->data*=num1;
}
void ins(int num,int num1){
	listPointer new_one=(listPointer)malloc(sizeof(listNode));
	new_one->data=num1;
	int i;
	if(head==NULL){
		new_one->link=NULL;
		head=new_one;
		return;
	}
	listPointer last=head;
	for(i=1;i<num;i++)
		last=last->link;
	new_one->link=last->link;   
	last->link=new_one;
}
listPointer rev(listPointer header, int num){
	int i;
	listPointer rear, middle, lead;
	
	rear = NULL;
	middle = NULL;
	lead = header;
	
	for(i=0 ; i<num && lead!=NULL ; i++){
		rear = middle;
		middle = lead;
		lead = lead->link;
		middle->link = rear;
	}
	
	if( i==num && lead!=NULL)
		header->link = rev(lead, num);

		
	return middle;
	
}
void show(){
	if(head==NULL){
		printf("empty");
		return;
	}
	listPointer last=head;
	while(1){
		printf("%d ",last->data);
		//printf("%d ",last->data);
		if(last->link==NULL)
			break;
		last=last->link;
	}
	printf("\n");
	//printf("\n");
}
int main(){
	FILE *fptr;
	fptr=fopen("input_1.txt","r");
	fptr1=fopen("output_1.txt","w");
	int num,count,i,num1;
	char arr[4],a;
	while(a!='\n'){//list
		fscanf(fptr,"%d%c",&num,&a);
		push_back(num);
	}
	fscanf(fptr,"%d",&count);
	for(i=1;i<=count;i++){
		fscanf(fptr,"%s",&arr);
		if(!strcmp(arr,"add")){
			fscanf(fptr,"%d",&num);
			push_back(num);
		}
		else if(!strcmp(arr,"del")){
			fscanf(fptr,"%d",&num);
			del(num);
		}
		else if(!strcmp(arr,"mul")){
			fscanf(fptr,"%d%d",&num,&num1);
			mul(num,num1);
		}
		else if(!strcmp(arr,"ins")){
			fscanf(fptr,"%d%d",&num,&num1);
			ins(num,num1);
		}
		else if(!strcmp(arr,"rev")){
			fscanf(fptr,"%d",&num);
			head=rev(head,num);
		}
		else if(!strcmp(arr,"show")){
			show();
		}
	}
	fclose(fptr);
	fclose(fptr1);
	return 0;
}

