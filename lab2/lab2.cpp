#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define WIDTH 4
#define LENGTH 4
#define TOTAL 16
#define BUFF "n"
#define N 50
#define DOWN  "z"
#define UP "w"
#define LEFT "a"
#define RIGHT "s"
#define TEST_MODLE "-t" 
#define MERGE 2
int sum,numberOfWinning,table[TOTAL]={0};
typedef enum {
 	victory,fail,play
}statement; 
char com[N];
void drawTheLine(){
    for(int i=0;i<WIDTH;++i)printf("+-----");
    printf("+\n");
}
void printTable(){
    drawTheLine();
    for(int i=0;i<TOTAL;++i){
        if(table[i]){
			if(table[i]<16)printf("|  %d  ",table[i]);
			else if(table[i]<128) printf("|  %d ",table[i]);
			else if(table[i]<1024) printf("| %d ",table[i]);
			else printf("| %d",table[i]);
		}
        else printf("|     ");
        if((i+1)%WIDTH==0){
            printf("|\n");
            drawTheLine();
        } 
    }
}
int addNumber(){
   int t=rand()%TOTAL;
    while(table[t]) t=rand()%TOTAL;
    table[t]=2;
    sum++;
    return (sum!=TOTAL);
}

void initial(){
      sum=0;
      numberOfWinning=2048;
      srand((unsigned)time(NULL));
      addNumber();
      puts("Welcome to 2048 !\n\n  enter \'-t\' then you can win this game by generating the number  64\n");
      printTable();
}
void gameOver(){
    puts("game over");
}
void winGame(){
	puts("~~~~~Congratulations!You get a Victory~~~~~");
} 
void loseGame(){
	puts("-----Sorry about that,you are failed-----");
}
statement checkState(){
	for(int i=0;i<TOTAL;++i) if(table[i]==numberOfWinning) return victory;
	if(sum<TOTAL) return play;
	int nearNum;
	for(int i=0;i<TOTAL;++i){
		nearNum=i+1;
		if((nearNum%WIDTH)&&(table[nearNum]==table[i])) return play;
		nearNum=i+WIDTH; 
		if(nearNum<TOTAL&&table[nearNum]==table[i]) return play;
	}
	return fail;
}
void changeWinningNumber(){
	numberOfWinning=64;
	puts("Now you can win this game when number 64 appears");
}
int allDown(){
	int x,y,f=0;
	for(int i=TOTAL-WIDTH;i<TOTAL;++i){
		x=i;
		while(x>=0){
			if(table[x]==0){
				y=x-WIDTH;
				while(y>=0&&table[y]==0) y-=WIDTH;
				if(y>=0&&table[y]) table[x]=table[y],table[y]=0,f=1;
			}
			x-=WIDTH;
		}
	}
	return f;
} 
int colliationDown(){
	int f=0;
	for(int i=TOTAL;i-WIDTH>=0;i--)
	if(table[i]&&table[i]==table[i-WIDTH]){
		table[i]=table[i]<<1;
		table[i-WIDTH]=0;
		sum--;
		f=1;
	}
	return f;
}
int moveDown(){
	int f[3];
	f[0]=allDown();
	f[1]=colliationDown();
	f[2]=allDown();
	return(f[0]|f[1]|f[2]);
}
int allUp(){
	int x,y,f=0;
	for(int i=0;i<WIDTH;++i){
		x=i;
		while(x<TOTAL){
			if(table[x]==0){
				y=x+WIDTH;
				while(y<TOTAL&&table[y]==0) y+=WIDTH;
				if(y<TOTAL&&table[y]) table[x]=table[y],table[y]=0,f=1;
			}
			x+=WIDTH;
		}
	}
	return f;
} 
int colliationUp(){
	int f=0;
	for(int i=0;i+WIDTH<TOTAL;i++)
	if(table[i]&&table[i]==table[i+WIDTH]){
		table[i]=table[i]<<1;
		table[i+WIDTH]=0;
		sum--;
		f=1;
	}
	return f;
}
int moveUp(){
	int f[3];
	f[1]=allUp();
	f[2]=colliationUp();
	f[0]=allUp();
	return(f[0]|f[1]|f[2]);
}
int allLeft(){
	int x,y,f=0;
	for(int i=0;i<LENGTH;++i){
		x=i*WIDTH;
		while(x<(i+1)*WIDTH){
			if(table[x]==0){
				y=x+1;
				while((y%WIDTH)&&table[y]==0) y++;
				if((y%WIDTH)&&table[y]) table[x]=table[y],table[y]=0,f=1;
			}
			x++;
		}
	}
	return f;
} 
int colliationLeft(){
	int f=0;
	for(int i=0;i<TOTAL;i++)
	if(table[i]&&(i+1)%WIDTH&&table[i]==table[i+1]){
		table[i]=table[i]<<1;
		table[i+1]=0;
		sum--;
		f=1;
	}
	return f;
}
int moveLeft(){
	int f[3];
	f[0] =	allLeft();
	f[1]=colliationLeft();
	f[2]=allLeft();
	return(f[0]|f[1]|f[2]);
}
int allRight(){
	int x,y,f=0;
	for(int i=0;i<LENGTH;++i){
		x=i*WIDTH+WIDTH-1;
		while(x>i*WIDTH){
			if(table[x]==0){
				y=x-1;
				while((y>=i*WIDTH)&&table[y]==0) y--;
				if((y>=i*WIDTH)&&table[y]) table[x]=table[y],table[y]=0,f=1;
			}
			x--;
		}
	}
	return f;
} 
int colliationRight(){
	int f=0;
	for(int i=TOTAL-1;i>=0;i--)
	if(table[i]&&i%WIDTH&&table[i]==table[i-1]){
		table[i]=table[i]<<1;
		table[i-1]=0;
		sum--;
		f=1;
	}
	return f;
}
int moveRight(){
	int f[3];	
	f[0]=allRight();
	f[1]=colliationRight();
	f[2]=allRight();
	return(f[0]|f[1]|f[2]);
}
int commend(){
	if(strcmp(com,TEST_MODLE)==0) {
		changeWinningNumber(); return 2;	
	}
	else if(strcmp(com,UP)==0){
		return moveUp();
	} 
	else if(strcmp(com,DOWN)==0){
		return moveDown(); 
	} 
	else if(strcmp(com,LEFT)==0){
		return moveLeft(); 
	} 
	else if(strcmp(com,RIGHT)==0) {
		return moveRight(); 
	}
	else return -1;
}
void generateNumber(){
	if(sum<TOTAL) addNumber();
}
int main( ){
    initial();
    int playing=1,flag;
    while(playing){
        fgets(com,50,stdin);
        com[strlen(com)-1]='\0';
        flag=commend();
        switch (flag){
			case -1:puts("error input");break;
			case 1:addNumber();
			case 0:system("clear");printTable();break;
			case 2:break;
		}
        switch (checkState()){
			case victory:winGame();playing=0;break;
			case fail:loseGame();playing=0;break;
			default:continue;
		}
    }
    return 0;
}
