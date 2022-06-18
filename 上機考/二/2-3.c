#include <stdio.h>
#include <stdlib.h>

struct point{
	int x;
	int y;
};
struct point dir[8],start,end[5];
int map[100][100],mark[100][100],n,d,ans=-1;
/*********************************/
void reset(){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			mark[i][j]=-1;
		}
	}
}
/*********************************/
void setdir(){
	int i,j,k=0;
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++){
			if(i==0&&j==0)
				continue;
			dir[k].x=i;
			dir[k].y=j;
			k++;
		}
	}
}
/*********************************/
void swap(struct point *a,struct point *b){
	struct point temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
/*********************************/
void show(){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%3d ",map[i][j]);
		}
		printf("\n");
	}
}
/*********************************/
int check(int cost,int x,int y,struct point e){
	int i,re;
	struct point temp;
	for(i=0;i<8;i++){
		temp.x=x+dir[i].x;
		temp.y=y+dir[i].y;
		if(temp.x<0||temp.y<0||temp.x>=n||temp.y>=n)
			continue;
		if((abs(map[temp.x][temp.y]-map[x][y])+mark[x][y]<=cost)&&mark[temp.x][temp.y]<0){
			mark[temp.x][temp.y]=abs(map[temp.x][temp.y]-map[x][y])+mark[x][y];
			re=check(cost,temp.x,temp.y,e);
			if(re||temp.x==e.x&&temp.y==e.y)
				return 1; 
		} 
	}
	return 0;
}
/*********************************/
int minpath(struct point s,struct point e){
	reset();
	mark[s.x][s.y]=0;
	int i,j,cost=0;
	while(1){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(mark[i][j]>=0){
					if(check(cost,i,j,e))
						return mark[e.x][e.y];
				}
			}
		}
		cost++;
	}
}
/*********************************/
void dict(struct point e[],int k){//
	int i,c=0;
	if(k==d-1){
		c+=minpath(start,e[0]);
		for(i=1;i<d;i++){
			c+=minpath(e[i-1],e[i]);
		}
		if(ans==-1||c<ans)
			ans=c;
	}
	for(i=k;i<d;i++){
		swap(&e[i],&e[k]);
		dict(e,k+1);
		swap(&e[k],&e[i]);
	}
}
/*********************************/
int main(){
	FILE *fptr;
	fptr=fopen("input_6-1.txt","r");
	fscanf(fptr,"%d%d",&d,&n);
	fscanf(fptr,"%d%d",&start.x,&start.y);
	int i,j;
	for(i=0;i<d;i++){
		fscanf(fptr,"%d%d",&end[i].x,&end[i].y);
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fscanf(fptr,"%d",&map[i][j]);
			mark[i][j]=-1;
		}
	}
	setdir();
	//show();
	dict(end,0);
	printf("%d",ans);
	fclose(fptr);
	return 0;
}
