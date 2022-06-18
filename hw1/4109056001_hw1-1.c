#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int compare(char op){
	switch(op){
		case '+':
		case '-':
			return 12;
		case '*':
		case '/':
		case '%':
			return 13;
		case '>':
		case '<':
			return 10;
		case '&':
			return 8;
		case '^':
			return 7;
		case '|':
			return 6;
		default:
			return 0;	
	}
}
void perfix(char arr[]){
	FILE *fptr1;
 	fptr1=fopen("output_1.txt","a+");//a+ 接續寫入 
	int top=-1,i,count=0,check=1;
	char stack[strlen(arr)],arr1[strlen(arr)*2];
	for(i=strlen(arr)-1;i>=0;i--){
		char op=arr[i-1];//前一個字元
		switch(arr[i]){
			case '+':
			case '*':
			case '/':
			case '%':
			case '>':
			case '<':
			case '&':
			case '|':
			case '^':
				while(compare(arr[i])<compare(stack[top])){
					arr1[count++]=' ';
					arr1[count++]=stack[top--];
				}
				top++;
				arr1[count++]=' ';//空格 
				stack[top]=arr[i];
				continue;
			case '-':
				if(op=='+'||op=='-'||op=='*'||op=='/'||op=='%'||op=='>'||op=='<'||op=='&'||op=='|'||op=='^'||op=='('||i==0){
					
					if(i==0){
						//arr1[count++]=' ';//空格			
						check=0;
					}
					arr1[count++]=arr[i];
					if(check==0)
						i=-1;
				}
				else{
					while(compare(arr[i])<compare(stack[top])){
					arr1[count++]=' ';
					arr1[count++]=stack[top--];
					}
					top++;
					arr1[count++]=' ';//空格 
					stack[top]=arr[i];
				}
				continue;
			case '(':
				while(stack[top]!=')'){
					arr1[count++]=' ';//空格 
					arr1[count++]=stack[top--];
				}
				top--;
				continue;
			case ')':
				top++;
				stack[top]=arr[i];
				continue;
			default: 		
				arr1[count++]=arr[i];
				continue;
		}
	}
	while(top!=-1){//剩餘的stack 
		arr1[count++]=' ';//空格 
		arr1[count++]=stack[top--];
	}
	for(i=count-1;i>=0;i--){
		//printf("%c",arr1[i]);
		fprintf(fptr1,"%c",arr1[i]);
	}
	fprintf(fptr1,"%c",'\n');
	fclose(fptr1);
}

int main(){
	char arr[101];
	FILE *fptr,*fptr1;
	fptr1=fopen("output_1.txt","w");
	fclose(fptr1);
 	fptr=fopen("input_1.txt","r");
 	while(fscanf(fptr,"%s",&arr)!=EOF){
 		perfix(arr);
 		//printf("\n");
 		}
 	fclose(fptr);
	return 0;
}
