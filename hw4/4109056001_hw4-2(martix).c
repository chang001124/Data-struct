#include <stdio.h>
#include <stdlib.h>
/*********************/
int map[10001][10001];
int n;
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
}order[10001];
/*********************/
int main() {
	FILE *fptr;
	fptr=fopen("input_2.txt","r");
	int m,i,j,k,cost,c,min=-1,a;
	fscanf(fptr,"%d%d",&n,&m);
	int visit[10001],check[10001],ans[10001];
	reset(visit,-1);
	reset(check,0);
	reset(ans,0);
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			map[i][j]=0;
		}
	} 
	for(i=1;i<=n-1;i++){
		fscanf(fptr,"%d%d%d",&j,&k,&cost);
		map[j][k]=cost;
		map[k][j]=cost;
	}
	
	for(i=1;i<=m;i++){
		fscanf(fptr,"%d%d",&j,&k);
		order[i].a=j;
		order[i].b=k;
	}
	
	for(c=1;c<=n;c++){
		cost=0;
		visit[c]=0;
		for(i=1;i<=n;i++){//每個點 
			for(k=1;k<=n;k++){
				if(check[k]==0&&visit[k]!=-1)
					break;
			}		
			check[k]=1;
			for(j=1;j<=n;j++){//目標點 
				if(map[k][j]>0){
					if(visit[j]==-1||visit[j]>visit[j]+map[k][j]){
						if(visit[j]==-1)
							visit[j]++;
						visit[j]=visit[j]+visit[k]+map[k][j];
					}
				}
			}	
		}
		for(i=1;i<=m;i++){
			cost+=visit[order[i].a]*2*order[i].b;
			if(min!=-1&&cost>min)
				break;
		}
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

