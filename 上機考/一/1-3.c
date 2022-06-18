#include <stdio.h>
#include <stdlib.h>
#define max 1001
#define max1 300
int visit[max],size[max];
int n,m,min=0,ans=-1;
/*******************************/
typedef struct node *graph;
struct node{
	int num;
	struct node *link;
}node;
struct node head[max];

struct colors{
	int total;
	int cost;
};
struct colors color[max1];
/*******************************/
void creat(int i,int j){
	graph newnode=(graph)malloc(sizeof(struct node));
	newnode->num=j;
	newnode->link=NULL;
	if(head[i].link==NULL){
		head[i].num=i;
		head[i].link=newnode;
		return;
	}
	graph ptr=&(head[i]);
	while(ptr->link!=NULL)
		ptr=ptr->link;
	ptr->link=newnode;
}
/*******************************/
void show(){
	int i;
	for(i=1;i<=n;i++){
		graph ptr=&(head[i]);
		printf("%d :",i);
		while(ptr!=NULL){
			
			printf("%d->",ptr->num);
			ptr=ptr->link;
		}
		printf("\n");
	}
}
/*******************************/
int check(int t,int num){
	if(color[num].total<size[t])
		return 0;
	graph ptr=&(head[t]);
	ptr=ptr->link;
	while(ptr!=NULL){
		if(visit[ptr->num]==num)
			return 0;
		ptr=ptr->link;
	}
	return 1;
}
/*******************************/
void dfs(int t,int c){
	int i;
	min+=color[c].cost*size[t];
	color[c].total-=size[t];
	if(t==n){
		if(ans==-1||ans>min)
			ans=min;
	}
	else{
		for(i=1;i<=m;i++){
			if(check(t+1,i)){
				visit[t+1]=i;
				dfs(t+1,i);
				visit[t+1]=0;
			}
		}
	}
	min-=color[c].cost*size[t];
	color[c].total+=size[t];
}
/*******************************/
int main() {
	FILE *fptr;
	fptr=fopen("input_3-1.txt","r");
	int edge,i,u,v;
	fscanf(fptr,"%d%d%d",&n,&edge,&m);
	//printf("%d %d %d\n",n,edge,m);
	for(i=1;i<=n;i++){
		fscanf(fptr,"%d",&size[i]);
		visit[i]=0;
		//printf("%d ",size[i]);
	}
	for(i=1;i<=edge;i++){
		fscanf(fptr,"%d%d",&u,&v);
		creat(u,v);
		creat(v,u);
	}
	show();
	char a[5];
	for(i=1;i<=m;i++){
		fscanf(fptr,"%s%d%d",&a,&color[i].total,&color[i].cost); 
	}
	for(i=1;i<=m;i++){
		if(check(1,i)){
			visit[1]=i;
			dfs(1,i);
			visit[1]=0;
		}
	}
	
	printf("%d",ans);
	fclose(fptr);
	return 0;
}

