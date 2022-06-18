#include <stdio.h>
#include <stdlib.h>
/**********************/
typedef struct tree *treenode;
typedef struct tree{
	int data;
	treenode right;
	treenode left;
}tree;
treenode root=NULL;
/**********************/
void insert(int num){
	treenode newnode=(treenode)malloc(sizeof(tree));
	newnode->data=num;
	newnode->left=NULL;
	newnode->right=NULL;
	if(root==NULL){
		root=newnode;
		return;
	}
	treenode current=root,back;
	while(current!=NULL){
		back=current;
		if(num>current->data)
			current=current->right;
		else
			current=current->left;
	}
	if(num>back->data)
		back->right=newnode;
	else
		back->left=newnode;
}
/**********************/
void del(int num){
	int check=1;
	treenode back=root,current=root,temp;
	while(current->data!=num){
		back=current;
		if(num>current->data)
			current=current->right;
		else
			current=current->left;
	}
	//printf("%d %d\n",current->data,back->data);
	if(current->left==NULL&&current->right==NULL){//處理業節點 
		temp=current;
		if(back->left!=NULL){
			if(back->left->data==current->data)
				back->left=NULL;
			else
				back->right=NULL;
		}
		else
			back->right=NULL;
		free(temp);
	}
	else if(current->left!=NULL){
		back=current->left;
		while(back->right!=NULL){
			check=0;
			temp=back;
			back=back->right;
		}
		current->data=back->data;
		if(check==1)
			current->left=back->left;
		else
			temp->right=back->left;
		free(back);
	}
	else if(current->left==NULL&&current->right!=NULL){
		back=current->right;
		while(back->left!=NULL){
			temp=back;
			check=0;
			back=back->left;
		}
		current->data=back->data;
		if(check==1)
			current->right=back->right;
		else
			temp->left=back->right;
		free(back);
	}
	return;
}
/**********************/
void road(int num1,int num2){
	int sum=0;
	treenode ptr=root,current;
	if(num1<ptr->data&&num2<ptr->data||num1>ptr->data&&num2>ptr->data){
		while(1){
			if(ptr->data>=num1&&ptr->data<=num2||ptr->data>=num2&&ptr->data<=num1)
				break;
			if(ptr->data>=num1&&ptr->data>=num2)
				ptr=ptr->left;
			else
				ptr=ptr->right;
		}
	}
	//printf("\n%d \n",ptr->data);
	if(num1==root->data){
		ptr=root;
		if(ptr->data>0)
			sum+=ptr->data;
		while(num2!=ptr->data){
			if(num2<ptr->data)
				ptr=ptr->left;
			else
				ptr=ptr->right;
			if(ptr->data>0)
				sum+=ptr->data;
		}
	}
	else if(num2==root->data){
		ptr=root;
		if(ptr->data>0)
			sum+=ptr->data;
		while(num1!=ptr->data){
			if(num1<ptr->data)
				ptr=ptr->left;
			else
				ptr=ptr->right;
			if(ptr->data>0)
				sum+=ptr->data;
		}
	}
	else{
		current=ptr;
		if(ptr->data>0)
			sum+=ptr->data;
		while(num2!=ptr->data){
			if(num2<ptr->data)
				ptr=ptr->left;
			else
				ptr=ptr->right;
			if(ptr->data>0)
				sum+=ptr->data;
		}
		ptr=current;
		while(num1!=ptr->data){
			if(num1<ptr->data)
				ptr=ptr->left;
			else
				ptr=ptr->right;
			if(ptr->data>0)
				sum+=ptr->data;
		}
	}
	printf("%d\n",sum);
}
/**********************/
int check(int num){
	treenode ptr=root;
	while(ptr!=NULL){
		if(ptr->data==num){
			return 1;
		}
		if(ptr->data>num)
			ptr=ptr->left;
		else
			ptr=ptr->right;
	}
	return 0;
}
/**********************/
void show(treenode ptr){
	if(ptr!=NULL){
		show(ptr->left);
		show(ptr->right);
		printf("%d ",ptr->data);
	}
}
/**********************/
int main() {
	FILE *fptr;
	fptr=fopen("input_1.txt","r");
	int a,b,num,i;
	char arr[5];
	fscanf(fptr,"%d%d",&a,&b);
	for(i=1;i<=a;i++){
		fscanf(fptr,"%d",&num);
		if(!check(num))
			insert(num);
	}
	show(root);
	printf("\n");
	for(i=1;i<=b;i++){
		fscanf(fptr,"%s",arr);
		if(!strcmp(arr,"I")){
			fscanf(fptr,"%d",&num);
			if(!check(num))
				insert(num);
		}
		else if(!strcmp(arr,"D")){
			fscanf(fptr,"%d",&num);
			if(check(num))
				del(num);
		}
		else if(!strcmp(arr,"P")){
			fscanf(fptr,"%d%d",&num,&a);
			if(check(num)&&check(a))
				road(num,a);
		}
	}
	
	fclose(fptr);
	return 0;
}

