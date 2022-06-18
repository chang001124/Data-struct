#include <stdio.h>
#include <stdlib.h>
#define MAX_NODE 1001
#define MAX_COLOR 300
/*******************************/
int min = 0, n = 0, m, ans = -1,b;
int visited[MAX_NODE], size[MAX_NODE];
struct color {
    int cost, total;
};
typedef struct node *graph;
struct node{
    int num,count;
    graph link;
};
struct node head[MAX_NODE];
struct color color[MAX_COLOR];
/*******************************/
void creat (int i, int j){
    graph new, ptr;
    new=(graph)malloc(sizeof(struct node));
    new->num=j;
    new->link=NULL;
    head[i].count++;
    if (head[i].link==NULL){
        //printf("%d NULL\n", i);
        head[i].link=new;
        head[i].num=i;
        return;
    }
    ptr=&(head[i]);
    while (ptr->link != NULL)
        ptr=ptr->link;
    ptr->link=new;
    return;
}
/*******************************/
int check (int t, int color_num){
    if(color[color_num].total<size[t]){ 
        return 0;
    }
    graph ptr = &(head[t]);
    ptr=ptr->link;
    while(ptr!=NULL){
        if(visited[ptr->num]==color_num){
            return 0;
        }
        ptr=ptr->link;
    }
    return 1;
}
/*******************************/
void dfs (int t, int c){ 
    int i;
    min+=color[c].cost*size[t];
    color[c].total-=size[t];
    if(t==n){
        if(ans<0||(ans>min))
            ans=min;
    } 
	else{
        for(i=1;i<=m;i++){
            if(check(t+1,i)){
                visited[t+1] = i;
                dfs(t+1,i);
                visited[t+1] = 0;
            }
        }
    }
    min-=color[c].cost*size[t];
    color[c].total+=size[t];
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
int main() {
    FILE *fptr;
    fptr = fopen("input_3-3.txt","r");
    int edge, u, v,i;
    char a[5];
    fscanf(fptr,"%d %d %d ",&n,&edge,&m); 
    //printf("%d %d %d\n", n, edge, l);
    for (i=1;i<=n;i++){
        fscanf(fptr,"%d ",&size[i]);
        visited[i]=0;
    }
    for (i=1;i<=edge;i++) {
        fscanf(fptr, "%d %d ",&u,&v);
        //printf("%d %d\n",u,v);
        creat(u,v);
        creat(v,u);
    }
    //show();
    for (i=1;i<=m;i++) {
        fscanf(fptr,"%s %d %d ",&a,&u,&v);
        color[i].total=u;
        color[i].cost=v;
    }
    for (i=1;i<=m;i++){
        if (check(1,i)){
            visited[1]=i;
            dfs(1,i);
            visited[1]=0;
        }
    }
    printf("%d",ans);
    fclose(fptr);
    return 0;
}



