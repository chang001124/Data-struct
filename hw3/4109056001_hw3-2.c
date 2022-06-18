#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n=75,total=0,ans=0;
/*********************/
struct ch{
	int sum;
	char d;
}ch[75];
/*********************/
typedef struct tree *treenode;
typedef struct tree{
	int sum;
	char d;
	treenode left;
	treenode right;
}tree;
treenode heap[100];
treenode root=NULL;
int heapsize=0;
/*********************/
void count(char d){
	int i,j;
	for(i=0;i<n;i++){
		if(ch[i].sum!=0&&ch[i].d==d){
			ch[i].sum++;
			break;		
		}
	}
	if(i==n){
		for(j=0;j<n;j++){
			if(ch[j].sum==0){
				total++;
				ch[j].sum++;
				ch[j].d=d;
				break;
			}
		}
	}
}
/*********************/
void insert(treenode node){
	heapsize++;
    heap[heapsize] = node;
	int now = heapsize;
    while(heap[now/2] -> sum > node -> sum){ 
            heap[now] = heap[now/2];
            now /= 2;
        }
    heap[now] = node;
}
/*********************/
void inal(){
	int i;
	heap[0]=(treenode)malloc(sizeof(tree));
	heap[0]->sum=0; 
	for(i=0;i<total;i++){
		treenode new_one=(treenode)malloc(sizeof(tree));
		new_one->d=ch[i].d;
		new_one->sum=ch[i].sum;
		new_one->left=NULL;
		new_one->right=NULL;
		insert(new_one);
	}
}
/*********************/
void del(){
	int i;
	total=0;
	ans=0;
	for(i=0;i<n;i++){
		ch[i].sum=0;
	}
}
/*********************/
treenode DeleteMin(){ 
        treenode minElement,lastElement;
        int child,now;
        minElement = heap[1];
        lastElement = heap[heapsize--];
        for(now = 1; now*2 <= heapsize ;now = child){ 
            child = now*2;
            if(child != heapsize && heap[child+1]->sum < heap[child] -> sum )
                child++;
            if(lastElement -> sum > heap[child] -> sum)
                heap[now] = heap[child];
            else
                break;
        }
        heap[now] = lastElement;
        return minElement;
}
/*********************/
void build(){
	int i;
	for(i=0;i<total-1;i++){
		treenode left = DeleteMin();
	    treenode right = DeleteMin();
	    treenode temp = (treenode) malloc(sizeof(tree));
	    temp -> d = 0;
	    temp -> left = left;
		temp -> right = right;
	    temp -> sum = left->sum + right -> sum;
	    insert(temp);
	}
}
/*********************/
void print(treenode temp,char *code){ 
	if(temp->left==NULL && temp->right==NULL){ 
        ans+=temp->sum*strlen(code);
        //printf("char %c code %s\n",temp->d,code);
        return;
    }
    int length = strlen(code);
    char leftcode[50],rightcode[50];
    strcpy(leftcode,code);
    strcpy(rightcode,code);
    leftcode[length] = '0';
    leftcode[length+1] = '\0';
    rightcode[length] = '1';
    rightcode[length+1] = '\0';
    print(temp->left,leftcode);
    print(temp->right,rightcode);
}
/*********************/
int main() {
	FILE *fptr;
	fptr=fopen("input_2.txt","r");
	int m,i;
	char d;
	fscanf(fptr,"%d ",&m);
	del();							//重置 
	while(m!=0){
		for(i=1;i<=m;i++){
			while(1){
				fscanf(fptr,"%c",&d);
				if(d=='\n')
					break;
				count(d);			//數每個字元個數 
			}
		}
		inal();						//初始化字元 
		build();					//建造二元數 
		root=DeleteMin();//heap[1]
		
		char code[50];				//編碼 
        code[0] = '\0';
        if(total==1)
        	ans=root->sum;
        else
        	print(root,code);
		printf("%d\n\n",ans);		//在螢幕上書出答案 
		fscanf(fptr,"%d ",&m);
		del();						//重置 
	}
	fclose(fptr);
	return 0;
}

