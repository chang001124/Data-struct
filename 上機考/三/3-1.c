#include <stdlib.h>
#include <stdio.h>

int main() {
	FILE *fptr;
	fptr=fopen("input_7-1.txt","r");
	int n,num,i,a,b,j,check=1;
	fscanf(fptr,"%d%d",&n,&num);
	int arr[n+1][n+1],visit[n+1],ans[n+1];
	for(i=0;i<=n;i++){
		visit[i]=0;
		ans[i]=0;
		for(j=0;j<=n+1;j++){
			arr[i][j]=0;
		}
	}
	for(i=1;i<=num;i++){
		fscanf(fptr,"%d%d",&a,&b);
		arr[a][b]=1;
	}
	
	for(b=0;b<n;b++){
		for(i=1;i<=n;i++){
			check=1;
			for(j=1;j<=n;j++){
				if(arr[j][i]==1){
					break;
					check=0;
				}
			}
			if(check==1&&visit[i]==0&&j>n){
				visit[i]=1;
				for(a=0;a<=n;a++){
					arr[i][a]=0;	
				}
				ans[b]=i;
				break;
			}
		}
		if(i>n){
			printf("not exixt");
			break;
		}
	}
	if(i<=n){
		for(i=0;i<n;i++){
			printf("%d ",ans[i]);
		}
	}
	fclose(fptr);
	system("PAUSE");
	return 0;
}

