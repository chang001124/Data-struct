#include <stdio.h>
#include <stdlib.h>
#define n 70
#define max 1000000
struct node{
	int sum;
	int leaf;
}node;
struct node str[n];

void reset(){
	int i;
	for(i=0;i<n;i++){
		if(str[i].leaf!=0){
			printf("%d",str[i].sum);
			str[i].leaf=0;
			str[i].sum=0;
		}
	}
}

int main() {
	FILE *fptr;
	fptr=fopen("input_8-1.txt","r");
	int line,i,count,j,num1,num2,min1,min2,temp;
	char w;
	reset();
	while(1){
		count=0;
		fscanf(fptr,"%d ",&line);
		//printf("%d",line);
		if(line==0)
			break;
		while(count<line){
			fscanf(fptr,"%c",&w);
			//printf("%c",w);
			if(w>='0'&&w<='9'){
				j=w-'0';
			} 
			else if(w>='a'&&w<='z'){
				j=w-'a'+10;
			}
			else if(w>='A'&&w<='Z'){
				j=w-'A'+36;
			}
			else if(w==' '){
				j=62;
			}
			else if(w=='!'){
				j=63;
			}
			else if(w==','){
				j=64;
			}
			else if(w=='-'){
				j=65;
			}
			else if(w=='.'){
				j=66;
			}
			else if(w==':'){
				j=67;
			}
			else if(w==';'){
				j=68;
			}
			else if(w=='?'){
				j=69;
			}
			if(w=='\n')
				count++;
			else{
				str[j].leaf++;
			}
		}
		
		while(1){
			count=0;
			min1=max;
			min2=max;
			num1=71;
			num2=71;
			for(i=0;i<n;i++){
				if(str[i].leaf!=0){
					count++;
					if(str[i].leaf<min1){
						min1=str[i].leaf;
						num1=i;
					}
					if(min1<min2){
						temp=min1;
						min1=min2;
						min2=temp;
						temp=num1;
						num1=num2;
						num2=temp;
					}
				}
			}
			if(count<=1)
				break;
			str[num2].leaf += str[num1].leaf;
            str[num2].sum +=  str[num1].sum + str[num2].leaf;
            str[num1].leaf = 0;
            str[num1].sum = 0;
		} 
		reset();
        printf("\n\n");
	}
	fclose(fptr);
	return 0;
}

