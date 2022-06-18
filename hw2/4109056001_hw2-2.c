#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int total=0,time=0,count;
typedef struct orders *order;
typedef struct orders {	
	int order_id,arrival,deadline,money,punishment;
	char name[100];
	order link;
}orders;
order order_head=NULL; 
typedef struct ingredients *ingredient;
typedef struct ingredients{
	char name[20];
	ingredient link;
}ingredients; 

typedef struct recipe{
	int s_time;
	char name[20];
	ingredient stove;
	ingredient cutting;
	ingredient other;
}recipe;

void push_stove(char name[],int i,recipe *food){
	if(!strcmp(name,"x")){
		return;
	} 
	ingredient new_one=(ingredient)malloc(sizeof(ingredients));
	strcpy(new_one->name,name);
	new_one->link=NULL;
	if(food[i].stove==NULL){
		food[i].stove=new_one;
		return;
	}
	ingredient last=food[i].stove;
	while(last->link!=NULL){
		last=last->link;
	}
	last->link=new_one;
}

void push_cutting(char name[],int i,recipe *food){
	if(!strcmp(name,"x")){
		return;
	} 
	ingredient new_one=(ingredient)malloc(sizeof(ingredients));
	strcpy(new_one->name,name);
	new_one->link=NULL;
	if(food[i].cutting==NULL){
		food[i].cutting=new_one;
		return;
	}
	ingredient last=food[i].cutting;
	while(last->link!=NULL){
		last=last->link;
	}
	last->link=new_one;
}

void push_other(char name[],int i,recipe *food){
	if(!strcmp(name,"x")){
		return;
	} 
	ingredient new_one=(ingredient)malloc(sizeof(ingredients));
	strcpy(new_one->name,name);
	new_one->link=NULL;
	if(food[i].other==NULL){
		food[i].other=new_one;
		return;
	}
	ingredient last=food[i].other;
	while(last->link!=NULL){
		last=last->link;
	}
	last->link=new_one;
}
void push_order(int order_id,char name[],int arrival,int deadline,int money,int punishment){
	order new_one=(order)malloc(sizeof(orders));
	new_one->order_id=order_id;
	strcpy(new_one->name,name);
	new_one->arrival=arrival;
	new_one->deadline=deadline;
	new_one->money=money;
	new_one->punishment=punishment;
	new_one->link=NULL;//
	if(order_head==NULL){
		order_head=new_one;
		return;
	}
	order last=order_head;
	while(last->link!=NULL){
		last=last->link;
	}
	last->link=new_one;
}
void show(int num){
	order last=order_head;
	while(last!=NULL){
		printf("%d %s %d %d %d %d\n",last->order_id,last->name,last->arrival,last->deadline,last->money,last->punishment);
		last=last->link;
	}
}
void show_r(int num,recipe *food){
	int i;
	for(i=0;i<num;i++){
		ingredient last=food[i].other;
		while(last->link!=NULL){
			printf("%s ",last->name);
			last=last->link;
		}
		printf("%s\n",last->name);
	}
 } 
 void del(order last){
 	last->money=-1;
 }
int main() {
	FILE *fptr,*fptr1,*fptr2;
	fptr=fopen("orders.txt","r");
	fptr1=fopen("recipes.txt","r");
	fptr2=fopen("temp.txt","w");
	int order_id,arrival,deadline,money,punishment,i,j,num,order_num;
	char name[200];
	fscanf(fptr,"%d",&order_num);//讀order數量 
	for(i=1;i<=order_num;i++){//讀取order 
		fscanf(fptr,"%d%s%d%d%d%d",&order_id,&name,&arrival,&deadline,&money,&punishment);
		//printf("%d %s %d %d %d %d\n",order_id,name,arrival,deadline,money,punishment);
		push_order(order_id,name,arrival,deadline,money,punishment);
	}
	fscanf(fptr1,"%d",&num);//讀recipes數量
	struct recipe food[num];
	char *token;
	int s_cnt,c_cnt,o_cnt;
	for(i=0;i<num;i++){
		s_cnt=0;
		c_cnt=0;
		o_cnt=1; 
		food[i].stove=NULL;
		food[i].cutting=NULL;
		food[i].other=NULL;
		for(j=1;j<=4;j++){
			fscanf(fptr1,"%s",&name);
			token=strtok(name,",");//字串分割 
			while(token!=NULL){
				switch(j){
					case 1:
						strcpy(food[i].name,token);
						break;
					case 2:
						push_stove(token,i,food);
						if(strcmp(token,"x"))
							s_cnt+=5;
						break;
					case 3:
						push_cutting(token,i,food);
						if(strcmp(token,"x"))
							c_cnt+=3;
						break;
					case 4:
						push_other(token,i,food);
						if(strcmp(token,"x"))
							o_cnt+=1;
						o_cnt+=1;
						break;
					default:
						break;
				}
				if(s_cnt>=c_cnt)
					food[i].s_time=s_cnt+o_cnt;
				else
					food[i].s_time=c_cnt+o_cnt;
				token=strtok(NULL,",");
			}
		}
	}
	int p1=1,p2=1,stove_table=1,cutting_table=1,p1check=0,p2check=0,k=0,check=1;//1 free 1 stove 2 0 free
	order last=order_head;
	order temp;
	int cost=0,stove_sum=0,cutting_sum=0,min,mtime;
	while(k!=order_num){
		if(last->arrival<=time&&last->money!=-1){
			min=last->deadline-last->arrival;
			temp=last;
			last=last->link;
			while(last){
				if(last->arrival<=time&&last->money!=-1){
					if(min>=last->deadline-last->arrival){
						min=last->deadline-last->arrival;
						temp=last;
					}
				}
				last=last->link;
			}
			last=temp;
			for(i=0;i<num;i++){
				if(!strcmp(food[i].name,last->name)){
					break;
				}
			}
			if((food[i].s_time+time)>last->deadline){
				total+=last->punishment;
				del(last);
				last=order_head;
				k++;
				continue;
			}
			for(i=0;i<num;i++){
				ingredient last_stove=food[i].stove;
				ingredient last_cutting=food[i].cutting;
				ingredient last_other=food[i].other;
				if(!strcmp(last->name,food[i].name)){
					while(last_stove!=NULL||last_cutting!=NULL){
						while(last_stove){
							if(p1==1&&stove_table==1&&p1check==0){
								stove_table=0;
								//printf("1 %d %d s %s\n",time,last->order_id,last_stove->name);
								fprintf(fptr2,"1 %d %d s %s\n",time,last->order_id,last_stove->name);
								count++;
								p1=0;
								p1check=1;
							}
							else if(p1==0&&p1check==1){
								if(p1check==1)
									stove_sum++;
								if(stove_sum%5==0){
									p1check=0;
									check=0;
									p1=1;
									stove_sum=1;
									stove_table=1;
									last_stove=last_stove->link;
								}
							}
							break;
						}
					if(check==1){
						while(last_stove){
							if(p2==1&&stove_table==1&&p2check==0){
								stove_table=0;
								p2=0;
								//printf("2 %d %d s %s\n",time,last->order_id,last_stove->name);
								fprintf(fptr2,"2 %d %d s %s\n",time,last->order_id,last_stove->name);
								count++;
								p2check=1;
							}
							else if(p2==0&&p2check==1){
								if(p2check==1)
									stove_sum++;
								if(stove_sum%5==0){
									p2check=0;
									p2=1;
									stove_sum=1;
									stove_table;
									last_stove=last_stove->link;
								}
							}
							break;
						}
					}
						while(last_cutting){
							if(p1==1&&cutting_table==1&&p1check==0){
								cutting_table=0;
								p1=0;
								//printf("1 %d %d c %s\n",time,last->order_id,last_cutting->name);
								fprintf(fptr2,"1 %d %d c %s\n",time,last->order_id,last_cutting->name);
								count++;
								p1check=2;
							}
							else if(p1==0&&p1check==2){
								if(p1check==2)
									cutting_sum++;
								if(cutting_sum%3==0){
									p1check=0;
									p1=1;
									check=0;
									cutting_sum=1;
									cutting_table=1;
									last_cutting=last_cutting->link;
								}
							}
							break;
						}
					if(check==1){
						while(last_cutting){
							if(p2==1&&cutting_table==1&&p2check==0){
								cutting_table=0;
								p2=0;
								//printf("2 %d %d c %s\n",time,last->order_id,last_cutting->name);
								fprintf(fptr2,"2 %d %d c %s\n",time,last->order_id,last_cutting->name);
								count++;
								p2check=2;
							}
							else if(p2==0&&p2check==2){
								if(p2check==2)
									cutting_sum++;
								if(cutting_sum%3==0){
									p2check=0;
									p2=1;
									cutting_sum=1;
									cutting_table=1;
									last_cutting=last_cutting->link;
								}
							}
							break;
						}
					}
						check=1;
						time++;
					}
					//printf("1 %d %d f\n",time,last->order_id);
					fprintf(fptr2,"1 %d %d f\n",time,last->order_id);
					count++;
					while(last_other!=NULL){
						time+=1;
						last_other=last_other->link;
					}
					time++;
					total+=last->money;
					del(last);
					k++;
					p1=1,p2=1,stove_table=1,cutting_table=1,p1check=0,p2check=0;	
				}
			}
		}
		last=last->link;
		if(last==NULL){
			last=order_head;
			time++;
		}
	}
	last=order_head;
	while(last){
		if(last->money!=-1)
			total+=last->punishment;
		//printf("\n%d\n",last->punishment);
		last=last->link;
	}
	char ch[1024];
	fclose(fptr2);
	FILE *fptr3;
	fptr3=fopen("players.txt","w");
	fptr2=fopen("temp.txt","r");
	fprintf(fptr3,"%d\n",count);
	while (1) 
   	{ 
          fgets(ch,1024,fptr2);  //讀取一行
          if(feof(fptr2))
          	break;
          fprintf(fptr3,"%s",ch);
          //printf("%s", ch); //輸出
    } 
	fclose(fptr2);
	fclose(fptr);
	fclose(fptr1);
	remove("temp.txt");
	return 0;
}

