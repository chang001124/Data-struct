#include <stdio.h>
#include <stdlib.h>
#define max 10001
/*********************/
int n;
/*********************/
struct node{
	int num,sum;
	struct node *link;
};
typedef struct node *graph;
struct node head[max];
/*********************/
void creat(int s,int num,int sum){
	graph newnode=(graph)malloc(sizeof(struct node));
	newnode->num=num;
	newnode->sum=sum;
	newnode->link=NULL;
	graph ptr=&(head[s]);
	if(ptr->num==0){
		ptr->sum=newnode->sum;
		ptr->num=newnode->num;
		ptr->link=newnode->link;
		return;
	}
	while(ptr->link!=NULL)
		ptr=ptr->link;
	ptr->link=newnode;
}
/*********************/
void show(){
	printf("\n");
	graph ptr;
	int i;
	for(i=1;i<=n;i++){
		printf("頭點%d =>",i);
		ptr=&(head[i]);
		while(ptr!=NULL){
			printf("%d ",ptr->num);
			ptr=ptr->link;
		} 
		printf("\n");
	}
}
/*********************/
void reset(int arr[],int num){
	int i;
	for(i=0;i<=n;i++){
		arr[i]=num;
	}
}
/*********************/
struct orders{
	int a;
	int b;
}order[max];
/*********************/
int main() {
	FILE *fptr;
	fptr=fopen("input_2.txt","r");
	int m,i,j,k,cost,c,min=-1,a;
	fscanf(fptr,"%d%d",&n,&m);
	int visit[max],check[max],ans[max];
	reset(visit,-1);
	reset(check,0);
	reset(ans,0);
	for(i=1;i<=n-1;i++){
		fscanf(fptr,"%d%d%d",&j,&k,&cost);
		creat(j,k,cost);
		creat(k,j,cost);
	}
	
	for(i=1;i<=m;i++){
		fscanf(fptr,"%d%d",&j,&k);
		order[i].a=j;
		order[i].b=k;
	}
	graph ptr;
	for(c=1;c<=n;c++){
		cost=0;
		visit[c]=0;
		for(i=1;i<=n;i++){//每個點 
			for(k=1;k<=n;k++){
				if(check[k]==0&&visit[k]!=-1)
					break;
			}		
			check[k]=1;
			ptr=&(head[k]);
			while(ptr!=NULL){
				if(visit[ptr->num]==-1||visit[ptr->num]>visit[ptr->num]+ptr->sum){
					if(visit[ptr->num]==-1)
						visit[ptr->num]++;
					visit[ptr->num]=visit[ptr->num]+visit[k]+ptr->sum;
				}
				ptr=ptr->link;
			}
		}
		
		for(i=1;i<=m;i++){
			cost+=visit[order[i].a]*2*order[i].b;
			//if(min!=-1&&cost>min)
			//	break;
		}
		//printf("%d %d\n",cost,c);
		ans[c]=cost;
		if(min==-1||min>cost){
			min=cost;
		}
		reset(visit,-1);
		reset(check,0);
	}
	printf("%d\n",min);//印答案 
	for(i=1;i<=n;i++){
		if(ans[i]==min){
			printf("%d ",i);
		}
	}
	fclose(fptr);
	return 0;
}

