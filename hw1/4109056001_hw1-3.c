#include<stdio.h>
#include<stdlib.h>
int nn=0,cost=-1,n=101;
void perm(int nm[], int i,int ans[][nn]) { 
    int j,k,tmp,total=0; 
    if(i < nn-1) { 
        for(j=i;j<nn;j++) { 
            tmp = nm[j];  // ����ӰϬq�̥k��Ʀr�̥ܳ��� 
            for(k=j;k>i;k--) 
                nm[k]=nm[k-1]; 
            nm[i]=tmp; 
            perm(nm,i+1,ans);  
            for(k=i;k<j;k++) 
                nm[k]=nm[k+1]; 
            nm[j]=tmp; 
        } 
    } 
    else {  // ��ܦ����ƦC 
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
}dest[6];//dest[0]�_�I��m 

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
	int count,out,num=1,i,j,sum=0,a,temp;//out �X�f�Ӽ�
	fscanf(fptr,"%d",&count);
	while(num<=count){
		fscanf(fptr,"%d%d",&out,&n);//�X�f�ӼơBn*n 
		fscanf(fptr,"%d%d",&dest[0].x,&dest[0].y);//��J�_�I��m 
		for(i=1;i<=out;i++){
			fscanf(fptr,"%d%d",&dest[i].x,&dest[i].y);//��J���I��m 
		}
		nn=out+1;
		cost=-1;
		int arr[n][n],visit[n][n],check[n][n],ans[nn][nn];
		for(i=0;i<n;i++){//��J�}�C��� 
			for(j=0;j<n;j++){
				fscanf(fptr,"%d",&arr[i][j]);
			}
		}
		int min=0,total,k,jump=0,s,l;
		while(sum<=out-1){//�p��ت��a 
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
						for(i=0;i<n;i++){//�B�z�̤p�� 
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
				ans[sum][i+1]=visit[dest[i+1].x][dest[i+1].y];//ans �U���I���̵u�Z��
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
			int nm[nn]; //�r��� 
			nm[0]=0;
	    	for(i=1;i<nn;i++) 
	    	    nm[i]=i; 
	  	  	perm(nm, 1,ans); 
			printf("#%d\ncost:%d\n",num,cost);
			//printf("#%d\ncost:%d\n",num,cost);
			num++;//�p��count 
			sum=0;
			cost=-1;
		}
		fclose(fptr); 
		fclose(fptr1);
		return 0;
}  
