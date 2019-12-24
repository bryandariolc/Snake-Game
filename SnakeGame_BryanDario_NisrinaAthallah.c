#include <stdio.h>
#include <conio.h>
#include <stdlib.h> 
#include <time.h> 

	extern int cnv_row=15, cnv_col=30, snk_max_len=100, plr_scr=0;
	int flag=0, size=1, key=3, food_x, food_y, top=62, body_icon=176, food=46, num, scores;
	void display(char game[cnv_row][cnv_col]);
	void food_pos(char game[cnv_row][cnv_col]);
	int key_pressed(int);
	void delay(int);
	void check(int *, int *, char[cnv_row][cnv_col]);
	void direction(int, int *, int *, char[cnv_row][cnv_col], int [snk_max_len][2]);
	void body_update(int *, int *, int [snk_max_len][2], char[cnv_row][cnv_col]);

int main(){
	int x, y, row, column;
	char canvas[cnv_row][cnv_col];
	int body[snk_max_len][2];
	for(x=0;x<cnv_row;x++){
		for(y=0;y<cnv_col;y++){
			canvas[x][y]=' ';
		}
	}
	printf("\n\n\n\n\tPress any key to start ");
	getch();
	system("cls");
	food_pos(canvas);
	while(1){	
		key=key_pressed(key);
		direction(key, &row, &column, canvas, body);
		check(&row, &column, canvas);
		if(flag==2){
			break;
		}
		display(canvas);
	}
	system("cls");
	printf("\n\n\n\n\tGAME OVER. YOUR SCORE: ",plr_scr);
	enqueue(plr_scr);
	disp();

}

void food_pos(char game[cnv_row][cnv_col]){
	srand(time(0));
	food_x=(rand()%(cnv_col));
	srand(time(0));
	food_y=(rand()%(cnv_row));
	while(game[food_y][food_x]!=' '){
		srand(time(0));
		food_x=(rand()%(cnv_col));
		srand(time(0));
		food_y=(rand()%(cnv_row));
	}
	game[food_y][food_x]=food;
}

void display(char game[cnv_row][cnv_col]){
	int i,j;
	system("cls");
	for(num=0;num<cnv_col-70;num++){
		printf(" ");
	}
	printf("Score: %d\n", plr_scr);
	printf("%c", 201);
	for(num=0;num<cnv_col;num++){
		printf("%c",205);
	}
	printf("%c\n", 187);
	for(i=0;i<cnv_row;i++){
		printf("%c",186);
		for(j=0;j<cnv_col;j++){
			printf("%c",game[i][j]);
		}
		printf("%c\n",186);
	}
	printf("%c",200);
	for(num=0;num<cnv_col;num++){
		printf("%c",205);
	}
	printf("%c\n", 188);
}

int key_pressed(int key){
	if(kbhit()){
		char ch;
		ch = getch();
		if(ch==119){
			if(key==0||key==2){
			}
			else{
				top=94;
				return 0;
			}
		}
		if(ch==97){
			if(key==1||key==3){
			}
			else{
				top=60;
				return 1;
			}
		}
		if(ch==115){
			if(key==0||key==2){
			}
			else{
				top=118;
				return 2;
			}
		}
		if(ch==100)
		{
			if(key==1||key==3){
			}
			else{
				top=62;
				return 3;
			}
		}
		if(ch==113){
			flag=1;
		}
	}
	return key;
}

void direction(int key, int *row, int *column, char canvas[cnv_row][cnv_col], int body[snk_max_len][2]){
	int row2=*row, column2=*column;
	int i;
	if(key==0){
		if(*row==0){
			flag=2;
		}
		else{
			if((canvas[*row-1][*column]!=' ')&&(canvas[*row-1][*column]!=food)){
				flag=2;
			}
			body_update(&row2, &column2, body, canvas);
			*row=*row-1;
			canvas[*row][*column]=top;		
		}
	}
	if(key==2){
		if(*row==cnv_row-1){
			flag=2;
		}
		else{
			if((canvas[*row+1][*column]!=' ')&&(canvas[*row+1][*column]!=food)){
				flag=2;
			}
			body_update(&row2, &column2, body, canvas);
			*row=*row+1;
			canvas[*row][*column]=top;		
		}
	}
	if(key==1){
		if(*column==0){
			flag=2;
		}
		else{
			if((canvas[*row][*column-1]!=' ')&&(canvas[*row][*column-1]!=food)){
				flag=2;
			}
			body_update(&row2, &column2, body, canvas);
			*column=*column-1;
			canvas[*row][*column]=top;	
		}
	}
	if(key==3){
		if(*column==cnv_col-1){
			flag=2;
		}
		else
		{
			if((canvas[*row][*column+1]!=' ')&&(canvas[*row][*column+1]!=food)){
				flag=2;
			}
			body_update(&row2, &column2, body, canvas);
			*column=*column+1;
			canvas[*row][*column]=top;		
		}
	}
	delay(100-(2*plr_scr));
}

void body_update(int *row, int *column, int body[snk_max_len][2], char canvas[cnv_row][cnv_col]){
	int i;
	if(flag==1){
        if(size==1){
        }
        else{
            canvas[(body[size-2][0])][(body[size-2][1])]=' ';
        }
        for(i=size-2;i>0;i--){
		    body[i][0]=body[i-1][0];
            body[i][1]=body[i-1][1];
        }
        body[0][0]=*row;
        body[0][1]=*column;
        size++;
        plr_scr++;
        for(i=size-2;i>0;i--){
            body[i][0]=body[i-1][0];
            body[i][1]=body[i-1][1];
        }
        body[0][0]=*row;
        body[0][1]=*column;
        for(i=0;i<=size-2;i++)
        {
            canvas[(body[i][0])][(body[i][1])]=body_icon;
        }
    }
    else if(flag==0){
        if(size!=1){
            canvas[(body[size-2][0])][(body[size-2][1])]=' ';
            for(i=size-2;i>0;i--){
                body[i][0]=body[i-1][0];
                body[i][1]=body[i-1][1];
            }
            body[i][0]=*row;
            body[i][1]=*column;
            for(i=0;i<=size-2;i++){
                canvas[(body[i][0])][(body[i][1])]=body_icon;
            }
        }
        else{
            canvas[*row][*column]=' ';
        }
    }
}

void check(int *row, int *column, char game[cnv_row][cnv_col]){
	if(flag==2){
		
	}
	else if((food_y==*row)&&(food_x==*column)){
		flag=1;
		food_pos(game);
	}
	else{
		flag=0;
	}
}

void delay(int milli_seconds) {  
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds); 
} 

struct node {
   int data;
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

void disp() {
   struct node *ptr = head;

   while(ptr != NULL) {
      printf(" %d ",ptr->data);
      ptr = ptr->next;
   }

}

void enqueue(int value)
{
   struct node *newNode =(struct node*) malloc(sizeof(struct node));
   struct node *temp = head;
   
   newNode->data = value;
   newNode->next = NULL;
   
   if(head == NULL){
      head = newNode;
      return;
   }

   while(temp->next != NULL){
   	temp = temp->next;
   }
   temp->next = newNode;
}

