#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE *fptr1;
/******************/
struct wall{
	char color;
}walls[100001];
/******************/
void prepare(){
	int i;
	for(i=0;i<100001;i++){
		walls[i].color='_';
	}
}
/******************/
void pp(int num1,int num2,char color){
	int i;
	for(i=num1;i<=num2;i++){
		walls[i].color=color;
	}
}
/******************/
void qq(int num1,int num2){
	int i,b=0;
	char d='\0';
	for(i=num1;i<=num2;i++){
		if(d==walls[i].color)
			continue;
		d=walls[i].color;
		if(b)
			fprintf(fptr1," ");
		fprintf(fptr1,"%c",walls[i].color);
		b=1;
	}
	fprintf(fptr1,"\n");
}
/******************/
int main() {
	FILE *fptr;
	fptr=fopen("input_3.txt","r");
	fptr1=fopen("output_3.txt","w");
	int m,n,i,num1,num2;
	char ch,color;
	fscanf(fptr,"%d %d ",&m,&n);
	prepare();
	for(i=1;i<=n;i++){
		fscanf(fptr,"%c",&ch);
		if(ch=='P'){
			fscanf(fptr,"%d %d %c ",&num1,&num2,&color);
			pp(num1,num2,color);
		}
		else{//ch=='Q'
			fscanf(fptr,"%d %d ",&num1,&num2);
			qq(num1,num2);
		}
	}
	fclose(fptr);
	fclose(fptr1);
	return 0;
}

