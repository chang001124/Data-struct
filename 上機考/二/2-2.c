#include <stdlib.h>
#include <stdio.h>
#define max 10001
int n,top=0;
int stack[max];
/*************************/
struct node{
	int num,sum;
	struct node *link;
};
typedef struct node *graph;
struct node head[max];
/*************************/
void creat(int a,int num,int sum){
	graph newnode=(graph)malloc(sizeof(struct node));
	newnode->num=num;
	newnode->sum=sum;
	newnode->link=NULL;
	graph ptr=&(head[a]);
	if(ptr->num==0){
		ptr->num=newnode->num;
		ptr->sum=newnode->sum;
		ptr->link=newnode->link;
		return;
	}
	while(ptr->link!=NULL)
		ptr=ptr->link;
	ptr->link=newnode;
}
/*************************/
void show(int n){
	graph ptr;
	int i;
	for(i=1;i<=n;i++){
		ptr=&(head[i]);
		printf("%d :",i);
		while(ptr!=NULL){
			printf("%d ",ptr->num);
			ptr=ptr->link;
		}
		printf("\n");
	}
}
/*************************/
struct orders{
	int a,b;
}order[max];
/*************************/
void reset(int arr[],int n,int num){
	int i;
	for(i=0;i<=n;i++){
		arr[i]=num;
	}
} 
/*************************/
int main() {
	FILE *fptr;
	fptr=fopen("input_5-1.txt","r");
	int n,i,j,k,cost,a,min=-1;
	int check[max],visit[max],ans[max];
	fscanf(fptr,"%d%d",&n,&a);
	reset(visit,n,-1);
	reset(check,n,0);
	for(i=0;i<=n;i++){
		head[i].num=0;
	}
	for(i=1;i<=n-1;i++){
		fscanf(fptr,"%d%d%d",&j,&k,&cost);
		//printf("%d %d %d\n",j,k,cost);
		creat(j,k,cost);
		creat(k,j,cost);
	}
	for(i=1;i<=a;i++){
		fscanf(fptr,"%d%d",&order[i].a,&order[i].b);
	}
	graph ptr;
	for(j=1;j<=n;j++){
		cost=0;
		visit[j]=0;
		stack[top]=j;
		for(i=1;i<=n;i++){
			if(top!=0)
				top--;
			k=stack[top];
			check[k]=1;
			ptr=&(head[k]);
			while(ptr!=NULL){
				if(check[ptr->num]==0){
					stack[top]=ptr->num;
					top++;
				}
				if(visit[ptr->num]==-1||visit[ptr->num]>visit[k]+ptr->sum){
					if(visit[ptr->num]==-1)
						visit[ptr->num]++;
					visit[ptr->num]=ptr->sum+visit[k];
				}
				ptr=ptr->link;
			}
		} 
		for(i=1;i<=a;i++){
			cost+=order[i].b*2*visit[order[i].a];
		}
		ans[j]=cost;
		if(min==-1||min>cost)
			min=cost;
		reset(visit,n,-1);
		reset(check,n,0);
	}
	printf("%d\n",min);
	for(i=1;i<=n;i++){
		if(ans[i]==min)
			printf("%d ",i);
	}
	fclose(fptr);
	return 0;
}

