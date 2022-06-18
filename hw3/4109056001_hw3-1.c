#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/****************/
FILE *fptr1;
/****************/
typedef struct tree *treenode;
typedef struct tree{
	int data;
	treenode left;
	treenode right;
}tree;
treenode root=NULL;
/****************/
void create(int num){
	treenode new_one=(treenode)malloc(sizeof(tree));
	new_one->data=num;
	new_one->left=NULL;
	new_one->right=NULL;
	if(root==NULL){
		root=new_one;
		return;
	}
	treenode current=root;
	treenode back;
	while(current!=NULL){
		back=current;
		if(current->data>num)
			current=current->left;
		else
			current=current->right;
	}
	if(back->data>num)
		back->left=new_one;
	else
		back->right=new_one;
}
/****************/
void search(int num){
	int level=1;//
	treenode current=root;
	while(current!=NULL){
		if(current->data==num){
			fprintf(fptr1,"%d\n",level);
			break;
		}
		if(current->data>num)
			current=current->left;
		else
			current=current->right;
		level++;
	}
}
/****************/
int check(int num){
	int c=0;
	treenode current=root;
	while(current!=NULL){
		if(current->data==num){
			c=1;
			break;
		}
		if(current->data>num)
			current=current->left;
		else
			current=current->right;
	}
	return c;
}
/****************/
void del(int num){
	int check=1;
	treenode current=root;
	treenode temp,back;
	while(current->data!=num&&current->data!=num){//尋找目標點 
		back=current;
		if(current->data>num)
			current=current->left;
		else
			current=current->right;
	}
	if(current->left==NULL&&current->right==NULL){//處裡業節點 
		temp=current;
		if(back->left!=NULL){
			if(back->left->data==current->data){
				back->left=NULL;
			}
			else
				back->right=NULL;
		}
		else{
			back->right=NULL;
		}
		free(temp);
		return;
	}
	else if(current->left!=NULL){//具有左子樹 
		back=current->left;
		while(back->right!=NULL){
			check=0;
			temp=back;
			back=back->right;
		}
		if(check){
			current->data=back->data;
			current->left=back->left;
			free(back);
		}
		else{
			current->data=back->data;
			temp->right=back->left;
			free(back);
		}
		return;
	}
	else if(current->left==NULL&&current->right!=NULL) {//不具左子樹，尋找右子樹最小值 
		back=current->right;
		temp=back;
		while(back->left!=NULL){
			check=0;
			temp=back;
			back=back->left;
		}	
		if(check){
			current->data=back->data;
			current->right=back->right;
			free(back);
		}
		else{
			current->data=back->data;
			temp->left=back->right;
			free(back);
		}
		return;
	}
}	
/****************/
void road(int x,int y){
	int sum=0,check=1;//check=0代表兩個點同一邊 
	treenode current=root,temp=current;//temp是兩點的共通父節點 
	if(x<temp->data&&y<temp->data||x>temp->data&&y>temp->data){//兩點同一邊 
		while(1){
			if(x<=temp->data&&y>=temp->data||x>=temp->data&&y<=temp->data)
				break;
			if(x<temp->data)
				temp=temp->left;
			else
				temp=temp->right;
		}
		current=temp;
		check=0;
	}
	if(current->data<x&&current->data>y||current->data<y&&current->data>x){//兩邊各一個 
		if(current->data>0)
			sum+=current->data;
		while(x!=current->data){
			if(x<current->data)
				current=current->left;
			else	
				current=current->right;
			if(current->data>0)
				sum+=current->data;
		}
		if(check)
			current=root;
		else
			current=temp;
		while(y!=current->data){
			if(y<current->data)
				current=current->left;
			else	
				current=current->right;
			if(current->data>0)
				sum+=current->data;
		}
	}
	else if(x==current->data){//x=root 
		if(current->data>0)
			sum+=current->data;
		while(y!=current->data){
			if(y<current->data)
				current=current->left;
			else	
				current=current->right;
			if(current->data>0)
				sum+=current->data;
		}
	}
	else if(y==current->data){//y=root 
		if(current->data>0)
			sum+=current->data;
		while(x!=current->data){
			if(x<current->data)
				current=current->left;
			else	
				current=current->right;
			if(current->data>0)
				sum+=current->data;
		}
	}
	fprintf(fptr1,"%d\n",sum);
}
/****************/
void reset(treenode ptr){//後序刪除 
	if(ptr!=NULL){
		reset(ptr->left);
		reset(ptr->right);
		if(ptr==root)	
			root=NULL;
		else
			free(ptr);
	}
	root=NULL;
}
/****************/
int main() {
	FILE *fptr;
	fptr=fopen("input_1.txt","r");
	fptr1=fopen("output_1.txt","w");
	int m,n,num,i,num1,count=1;
	char arr[5];
	fscanf(fptr,"%d%d",&m,&n);
	while(m!=0&&n!=0){
		fprintf(fptr1,"# %d\n",count++);
		for(i=1;i<=m;i++){
			fscanf(fptr,"%d",&num);
			if(!check(num))
				create(num);
		}
		for(i=1;i<=n;i++){
			fscanf(fptr,"%s",&arr);
			if(!strcmp(arr,"I")){
				fscanf(fptr,"%d",&num);
				if(!check(num))
					create(num);
			}
			else if(!strcmp(arr,"D")){
				fscanf(fptr,"%d",&num);
				if(check(num))
					del(num);
			}
			else if(!strcmp(arr,"Q")){
				fscanf(fptr,"%d",&num);
				if(check(num))
					search(num);
			}
			else if(!strcmp(arr,"P")){
				fscanf(fptr,"%d%d",&num,&num1);
				if(check(num)&&check(num1)){
					road(num,num1);
				}
			}
		}
		reset(root);
		fscanf(fptr,"%d%d",&m,&n);
	} 
	fclose(fptr);
	fclose(fptr1);
	return 0;
}

