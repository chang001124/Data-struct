#include <stdio.h>
#include <stdlib.h>
int n;
/************************/
typedef struct orders *order;
typedef struct orders{
	int id;
	int arrival;
	int deadline;
	int cooking;
    int complete;
    int idletime;
	order link;
}orders;
order head=NULL;
/************************/
void creat(int id,int arrival,int deadline,int cooking){
	order newnode=(order)malloc(sizeof(orders));
	newnode->id=id;
	newnode->arrival=arrival;
	newnode->deadline=deadline;
	newnode->cooking=cooking;
	newnode->complete=newnode->arrival+newnode->cooking;
	newnode->idletime=newnode->deadline-newnode->complete;
	newnode->link=NULL;
	if(head==NULL){
		head=newnode;
		return;
	} 
	order ptr=head;
	while(ptr->link!=NULL)
		ptr=ptr->link;
	ptr->link=newnode;
}
/************************/
show(){
	order ptr=head;
	while(ptr!=NULL){
	printf("%2d %2d %2d %2d %2d %2d\n",ptr->id,ptr->arrival,ptr->deadline,ptr->cooking,ptr->complete,ptr->idletime);
	ptr=ptr->link;
	}
}
/************************/
void del(){
	order ptr=head,temp,trash;
	while(ptr!=NULL){
		if(ptr->idletime<0){
			if(head==ptr){
				trash=(head);
				head=head->link;
				ptr=head;
				free(trash);
				n--;
				continue;
			}
			else{
				temp->link=ptr->link;
				trash=ptr;
				ptr=temp;
			}
			free(trash);
			n--;
		}
		temp=ptr;
		ptr=ptr->link;
	}
}
/************************/
void sort(){
	int i,j;
	int a,b,c,d,e,f;
	for(i=1;i<=n;i++){
		order ptr=head;
		for(j=1;j<=n-1;j++){
			if(ptr->complete > ptr->link->complete||ptr->complete==ptr->link->complete&&ptr->idletime > ptr->link->idletime){
				a=ptr->id;
				b=ptr->arrival;
				c=ptr->deadline;
				d=ptr->cooking;
				e=ptr->complete;
				f=ptr->idletime;
				ptr->id=ptr->link->id;
				ptr->arrival=ptr->link->arrival;
				ptr->deadline=ptr->link->deadline;
				ptr->cooking=ptr->link->cooking;
				ptr->complete=ptr->link->complete;
				ptr->idletime=ptr->link->idletime;
				ptr->link->id=a;
				ptr->link->arrival=b;
				ptr->link->deadline=c;
				ptr->link->cooking=d;
				ptr->link->complete=e;
				ptr->link->idletime=f;
			}
			ptr=ptr->link;
		}
	}
}
/************************/
int main() {
	FILE *fptr;
	fptr=fopen("input_9-2.txt","r");
	int a,b,c,d,i,ans=0;
	fscanf(fptr,"%d",&n);
	for(i=1;i<=n;i++){
		fscanf(fptr,"%d%d%d%d",&a,&b,&c,&d);
		creat(a,b,c,d);
	}
	//show();
	del();
	sort();
	int time=0;
	while(n>0){
		order temp=head;
		time=temp->complete;
		head->idletime=-1;
		ans++;
		printf("%d\n",temp->id);
		temp=head->link;
		while(temp!=NULL){
			if(temp->arrival<time){
				temp->arrival=time;
				temp->complete=temp->arrival+temp->cooking;
				temp->idletime=temp->deadline-temp->complete;
			}
			temp=temp->link;
		}
		del();
		sort();	
	}
	printf("%d",ans);
	fclose(fptr);
	return 0;
}

