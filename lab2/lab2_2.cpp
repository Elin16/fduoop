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

int nextValue(int pos,int dir){
	int np;
	switch (dir){
		case 1:np=pos+1;//left
			while(np%WIDTH!=0&&table[np]==0) np++;
			if(np%WIDTH==0) return 0;
			break;
		case 2:np=pos+WIDTH;//up
			while(np<TOTAL&&table[np]==0) np+=WIDTH;
			if(np>=TOTAL) return 0;
			break;
		case 3:np=pos-1;//right
			while(np>=0&&np%WIDTH!=(WIDTH-1)&&table[np]==0) np--;
			if(np<0||np%WIDTH==(WIDTH-1)) return 0;
			break;
		case 4:np=pos-WIDTH;//down
			while(np>=0&&table[np]==0) np-=WIDTH;
			if(np<0) return 0;
			break;
	}
	int v=table[np];
	table[np]=0;
	return v;
}
int allDir(int dir){
	int f=0;
	if(dir==1||dir==2){
		for(int i=0;i<TOTAL;++i)
		if(table[i]==0){
			table[i]=nextValue(i,dir);
			if(table[i]) f=1;
		}
	}else{
		for(int i=TOTAL-1;i>=0;--i)
		if(table[i]==0){
			table[i]=nextValue(i,dir);
			if(table[i]) f=1;
		}
	}
	return f;
}
int nextPos(int pos,int dir){
	int np;
	switch (dir){
		case 1:np=pos+1;//left
			if(np%WIDTH==0) np=-1;
			break;
		case 2:np=pos+WIDTH;//up
			if(np>=TOTAL) np=-1;
			break;
		case 3:np=pos-1;//right
			if(np%WIDTH==WIDTH-1) np=-1;
			break;
		case 4:np=pos-WIDTH;//down
			if(np<0) np=-1;
			break;
	}
	return np;
}
int colliationDir(int dir){
	int f=0;
	if(dir==1||dir==2){
		for(int i=0;i<TOTAL;++i)
		if(table[i]){
			int p=nextPos(i,dir);
			if(p>=0&&table[i]==table[p]){
				table[i]=table[i]<<1;
				table[p]=0;
				sum--;//zhe ju hua lou diao le !!!! haihao shi bu chong ban ben 
				f=1;
			}
		}
	}else{
		for(int i=TOTAL-1;i>=0;--i)
		if(table[i]){
			int p=nextPos(i,dir);
			if(p>=0&&table[i]==table[p]){
				table[i]=table[i]<<1;
				table[p]=0;
				sum--;//zhe ju hua lou diao le !!!! haihao shi bu chong ban ben
				f=1;
			}
		}
	}
	return f;
}
int moveDir(int dir){
	int f[3];
	f[0]=allDir(dir);
	f[1]=colliationDir(dir);
	f[2]=allDir(dir);
	return (f[0]|f[1]|f[2]);
}
int commend(){
	if(strcmp(com,TEST_MODLE)==0) {
		changeWinningNumber(); return 2;	
	}
	else if(strcmp(com,UP)==0){
		return moveDir(2);
	} 
	else if(strcmp(com,DOWN)==0){
		return moveDir(4); 
	} 
	else if(strcmp(com,LEFT)==0){
		return moveDir(1); 
	} 
	else if(strcmp(com,RIGHT)==0) {
		return moveDir(3); 
	}
	else return -1;
}
void generateNumber(){
	if(sum<TOTAL) addNumber();
}
int main(){
    initial();
    int playing=1,flag;
    while(playing){
        fgets(com,50,stdin);
        com[strlen(com)-1]='\0';
        flag=commend();
        switch (flag){
			case -1:puts("error input");break;
			case 1:addNumber();
			case 0:/*system("clear");*/printTable();break;
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
