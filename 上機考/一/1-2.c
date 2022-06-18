#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int compare(char op){
	switch(op){
		case '*':
		case '/':
		case '%':
			return 13;
		case '+':
		case '-':
			return 12;
		case '<':
		case '>':
			return 10;
		case '&':
			//return 7;
		case '^':
			//return 9;
		case '|':
			return 8;
		default:
			return 0;
	}
}
void prefix(char arr[]){
	//printf("\n");
	int i,top=-1,count=0;
	char stack[strlen(arr)],arr1[strlen(arr)];
	for(i=strlen(arr)-1;i>=0;i--){
		int check=1;
		char op=arr[i-1];
		switch(arr[i]){
			case '*':
			case '/':
			case '%':
			case '+':
			case '<':
			case '>':
			case '&':
			case '^':
			case '|':
			case '-':
				while(compare(stack[top])>compare(arr[i])){
					arr1[count++]=stack[top--];
				}
				top++;
				stack[top]=arr[i];
				continue;
			case ')':
				top++;
				stack[top]=arr[i];
				continue;
			case '(':
				while(stack[top]!=')'){
					arr1[count++]=stack[top--]; 
				}
				top--;
				continue;
			default:
				arr1[count++]=arr[i];
				continue;
		}
	}
	while(top!=-1){
		arr1[count++]=stack[top--];
	}
	for(i=count-1;i>=0;i--){
		printf("%c",arr1[i]);
	}
	printf("\n");
}
int main(){
	FILE *fptr;
	fptr=fopen("input_2-2.txt","r");
	int n,i;
	char a[201];
	fscanf(fptr,"%d",&n);
	for(i=1;i<=n;i++){
		fscanf(fptr,"%s",&a);
		prefix(a);
	}
	fclose(fptr);
	return 0;
}
