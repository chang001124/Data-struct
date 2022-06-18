#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	char name[20],name1[20];
	FILE *fptr=NULL,*fptr1=NULL;
	/*fptr=fopen("123.txt","r");	
	fptr1=fopen("456.txt","r");*/
	while(!fptr){
		printf("please enter your file name: ");
		scanf("%s",&name);
		strcat(name,".txt"); 
		fptr=fopen(name,"r");
	}
	while(!fptr1){
		printf("please enter your check file name: ");
		scanf("%s",&name1);
		strcat(name1,".txt"); 
		fptr1=fopen(name1,"r");
	}
	int check=1;
	int c='\n',d;
	while(1){
		c = fgetc(fptr);
		d = fgetc(fptr1);
		if(feof(fptr)||feof(fptr1)){
			check=1;
			break;
		}
			
		if(c==d){
			continue;
		}
		else{
			check=0;
			break;
		}
	}
	
	//以下檢查空白 
	while(!feof(fptr)){
		c = fgetc(fptr);
		if(c=='\n'||c==-1||c==' '){
			check=1;
		}
		else{
			check=0;
			break;
		}
			
	}
	while(!feof(fptr1)&&check!=0){
		c = fgetc(fptr1);
		if(c=='\n'||c==-1||c==' '){
			check=1;
		}
		else{
			check=0;
			break;
		}
	}
	if(check){
		printf("True\n");
	}
	else{
		printf("False\n");
	}
	fclose(fptr);
	fclose(fptr1);
	system("PAUSE");
	return 0;
}

