#include<stdio.h>
#include<stdlib.h>
int main(){
	int count,n,g,num=1,i,j,sum,k;
	FILE *fptr,*fptr1;
	fptr=fopen("input_2.txt","r");
	fptr1=fopen("output_2.txt","w");
	fclose(fptr1);
	fptr1=fopen("output_2.txt","a+");
	fscanf(fptr,"%d",&count);
	while(num<=count){
		fscanf(fptr,"%d%d",&n,&g);
		int arr[n][n],arr1[n][n];
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				fscanf(fptr,"%d",&arr[i][j]);
				arr1[i][j]=0;
			}
		}
	for(k=1;k<=g;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				arr1[i][j]=0;
				sum=0;
				if(i-1>=0){//上 
					if(arr[i-1][j]==1){
						sum++;
					}
				}
				if(i-1>=0&&j+1<n){
					if(arr[i-1][j+1]==1){
						sum++;
					}
				}
				if(j+1<n){
					if(arr[i][j+1]==1){
						sum++;
					}
				}
				if(i+1<n&&j+1<n){
					if(arr[i+1][j+1]==1){
						sum++;
					}
				}
				if(i+1<n){
					if(arr[i+1][j]==1){
						sum++;
					}
				}
				if(i+1<n&&j-1>=0){
					if(arr[i+1][j-1]==1){
						sum++;
					}
				}
				if(j-1>=0){
					if(arr[i][j-1]==1){
						sum++;
					}
				}
				if(i-1>=0&&j-1>=0){
					if(arr[i-1][j-1]==1){
						sum++;
					}
				}
				if(sum==1||sum==0){ 
					arr1[i][j]=0;
				}
				else if(sum>=4){
					arr1[i][j]=0;
				}
				else if(sum==2&&arr[i][j]==0){
					arr1[i][j]=0;
				}
				else{
					arr1[i][j]=1;
				}
			}
		}
		for(i=0;i<n;i++){//複製陣列 
			for(j=0;j<n;j++){
				arr[i][j]=arr1[i][j];
			}
		}
	}
		int total=0;
		for(i=0;i<n;i++){//計算有幾個一 
			for(j=0;j<n;j++){
				if(arr1[i][j]==1)
					total++;
			}
		}
		fprintf(fptr1,"%d %d %d\n",n,n,total);
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(arr1[i][j]==1){
					sum=0;
					if(i-1>=0){
						if(arr[i-1][j]==1){
							sum++;
						}
					}
					if(i-1>=0&&j+1<n){
						if(arr[i-1][j+1]==1){
							sum++;
						}
					}
					if(j+1<n){
						if(arr[i][j+1]==1){
							sum++;
						}
					}	
					if(i+1<n&&j+1<n){
						if(arr[i+1][j+1]==1){
							sum++;
						}
					}
					if(i+1<n){
						if(arr[i+1][j]==1){
							sum++;
						}
					}
					if(i+1<n&&j-1>=0){
						if(arr[i+1][j-1]==1){
							sum++;
						}
					}
					if(j-1>=0){
						if(arr[i][j-1]==1){
							sum++;
						}
					}
					if(i-1>=0&&j-1>=0){
						if(arr[i-1][j-1]==1){
							sum++;
						}
					}
				fprintf(fptr1,"%d %d %d\n",i,j,sum);
				}
			}
		}
	num++;
	}
	fclose(fptr);
	fclose(fptr1);
	return 0;
}
