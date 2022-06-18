#include <stdio.h>
#include <stdlib.h>
/*********************/
int map[1001][1001];
/*********************/

int main() {
	FILE *fptr;
	fptr=fopen("input_1.txt","r");
	int n,r,j,i,k,check=1;
	fscanf(fptr,"%d%d",&n,&r);
	int visit[n+1],ans[n+1];
	
	for(i=0;i<=n;i++){
		for(k=0;k<=n;k++){
			map[i][k]=0;
			visit[i]=0;
			ans[i]=0;
		}
	}
	for(i=1;i<=r;i++){
		fscanf(fptr,"%d%d",&j,&k);
		map[j][k]=1;
	}
	for(j=0;j<n;j++){
		for(i=1;i<=n;i++){ //找到最小的頭點 
			check=1;
			for(k=1;k<=n;k++){
				if(map[k][i]==1)
					check=0;
			}
			if(check==1&&visit[i]==0){
				ans[j]=i;
				visit[i]=1;
				for(r=1;r<=n;r++){
					map[i][r]=0;
				}
				break;
			}
		}
		if(i>n){
			printf("not exist");
			break;
		}
	}
	
	if(check==1){
		for(i=0;i<n;i++){
			printf("%d ",ans[i]);
		}
	}
	fclose(fptr);
	return 0;
}

