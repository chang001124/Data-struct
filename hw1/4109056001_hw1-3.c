#include<stdio.h>
#include<stdlib.h>
int nn=0,cost=-1,n=101;
void perm(int nm[], int i,int ans[][nn]) { 
    int j,k,tmp,total=0; 
    if(i < nn-1) { 
        for(j=i;j<nn;j++) { 
            tmp = nm[j];  // 旋轉該區段最右邊數字至最左邊 
            for(k=j;k>i;k--) 
                nm[k]=nm[k-1]; 
            nm[i]=tmp; 
            perm(nm,i+1,ans);  
            for(k=i;k<j;k++) 
                nm[k]=nm[k+1]; 
            nm[j]=tmp; 
        } 
    } 
    else {  // 顯示此次排列 
        for(j=0;j<nn-1;j++) {
        	total+=ans[nm[j]][nm[j+1]];
        	printf("%2d-%2d :%3d  ",nm[j],nm[j+1],ans[nm[j]][nm[j+1]]);
        	//printf("%d ",nm[j]);
        }
        //printf("%d ",nm[j]);
        printf("%d\n",total);
        if(cost==-1||total<cost){
        	cost=total;
		}
		total=0; 
    } 
}  
struct destinations{
	int x,y;
}dest[6];//dest[0]起點位置 

void walk(int arr[][n],int visit[][n],int i,int j,int a,int b){
	int total;
	total=abs(arr[i][j]-arr[a][b]);
	if(visit[i][j]!=-1)
		total+=visit[i][j];
	if(visit[a][b]==-1||visit[a][b]>total){
		if(visit[a][b]==-1)
			visit[a][b]+=1;
		visit[a][b]=total; 	
	}
}
int main(){
	FILE *fptr,*fptr1;
	fptr=fopen("input_3.txt","r");
	fptr1=fopen("output_3.txt","w");
	int count,out,num=1,i,j,sum=0,a,temp;//out 出口個數
	fscanf(fptr,"%d",&count);
	while(num<=count){
		fscanf(fptr,"%d%d",&out,&n);//出口個數、n*n 
		fscanf(fptr,"%d%d",&dest[0].x,&dest[0].y);//輸入起點位置 
		for(i=1;i<=out;i++){
			fscanf(fptr,"%d%d",&dest[i].x,&dest[i].y);//輸入終點位置 
		}
		nn=out+1;
		cost=-1;
		int arr[n][n],visit[n][n],check[n][n],ans[nn][nn];
		for(i=0;i<n;i++){//輸入陣列資料 
			for(j=0;j<n;j++){
				fscanf(fptr,"%d",&arr[i][j]);
			}
		}
		int min=0,total,k,jump=0,s,l;
		while(sum<=out-1){//計算目的地 
			min=0;
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					visit[i][j]=-1;
					check[i][j]=0;
				}
			}
			visit[dest[sum].x][dest[sum].y]=0;
			for(k=1;k<=n*n-1;k++){
				if(k==1){
					s=dest[sum].x;
					l=dest[sum].y;
				}
				else{
					s=0;
					l=0;
				}
			for(i=s;i<n;i++){
				jump=0;
				for(j=l;j<n;j++){
					if(check[i][j]==0&&visit[i][j]==min){
						check[i][j]=1;
						if(i-1>=0&&j+1<n)
							walk(arr,visit,i,j,i-1,j+1);
							
						if(j+1<n)
							walk(arr,visit,i,j,i,j+1);
							
						if(i+1<n&&j+1<n)
							walk(arr,visit,i,j,i+1,j+1);
							
						if(i+1<n)
							walk(arr,visit,i,j,i+1,j);
							
						if(i+1<n&&j-1>=0)
							walk(arr,visit,i,j,i+1,j-1);
							
						if(i-1>=0)
							walk(arr,visit,i,j,i-1,j);
							
						if(j-1>=0)
							walk(arr,visit,i,j,i,j-1);
							
						if(i-1>=0&&j-1>=0)
							walk(arr,visit,i,j,i-1,j-1);
						min=-1;
						for(i=0;i<n;i++){//處理最小值 
							for(j=0;j<n;j++){
								if(check[i][j]==0&&visit[i][j]!=-1){
									if(min==-1||min>visit[i][j])
										min=visit[i][j];
								}
							}
						}
						jump=1;
						break;
					}
				}
				if(jump)
					break;
			}
		}	
			for(i=0;i<=out;i++){
				ans[i][i]=0;
				}
			for(i=sum;i<out;i++){
				ans[sum][i+1]=visit[dest[i+1].x][dest[i+1].y];//ans 各個點的最短距離
				ans[i+1][sum]=visit[dest[i+1].x][dest[i+1].y];
				temp++;
			}
			sum++;	
		}
			/*for(i=0;i<=out;i++){
				for(j=0;j<=out;j++){
					printf("%3d ",ans[i][j]);
				}
				printf("\n");
			}
			printf("\n");*/
			int nm[nn]; //字典序 
			nm[0]=0;
	    	for(i=1;i<nn;i++) 
	    	    nm[i]=i; 
	  	  	perm(nm, 1,ans); 
			printf("#%d\ncost:%d\n",num,cost);
			//printf("#%d\ncost:%d\n",num,cost);
			num++;//計算count 
			sum=0;
			cost=-1;
		}
		fclose(fptr); 
		fclose(fptr1);
		return 0;
}  
