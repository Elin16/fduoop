#include "gamebox.h"
#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#define debug(x) cout<<#x"="<<x<<endl;
using namespace std; 
void GameBox::set_table(){
	table[0]=2;
	table[1]=4;
	table[2]=0;
	table[3]=0;	
}
GameBox:: GameBox(){ //winning =2048 default why can not be working ?
       totalFulled=0;
	infintGame=0;
       numOfWinning=2048;//?????
       srand((unsigned)time(NULL));
}
GameBox::~GameBox(){
 
}
void GameBox::initial(int edgeSize,int winNum){ //winning =2048 default why can not be working ?
      numOfWinning=winNum;
	WIDTH=LENGTH=edgeSize;
	TOTAL=WIDTH*LENGTH;
      for(int i=0;i<TOTAL;++i) table[i]=0;
}
void GameBox:: winNum(const int& num){
	numOfWinning=num;
	printf("The winning num is %d\n ",numOfWinning);
}
void GameBox::firHit(){
    addNumber();
    puts("___________		Game Start!		___________");
    printTable();
}

void GameBox:: addNumber(){
      int t=rand()%TOTAL;
      while(table[t]) t=rand()%TOTAL;
	table[t]=2;
      totalFulled++;
      return ;
}
 

statement GameBox::checkState(){
	if(!infintGame){
		for(int i=0;i<TOTAL;++i) if(table[i]==numOfWinning) return victory;
	} 
	if(totalFulled<TOTAL) return play;
	int nearNum;
	for(int i=0;i<TOTAL;++i){
		nearNum=i+1;
		if(nearNum<TOTAL&&(nearNum%WIDTH)&&(table[nearNum]==table[i])) return play;
		nearNum=i+WIDTH; 
		if(nearNum<TOTAL&&table[nearNum]==table[i]) return play;
	}
	return fail;
}

void GameBox::drawTheLine(){
    for(int i=0;i<WIDTH;++i)printf("+-----");
    printf("+\n");
}
void GameBox::printTable(){
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

int GameBox:: nextValue(const int& pos,const int& dir,int*table){
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
void GameBox::allDir(const int & dir,bool*f,int*table){
	int fdir,i;
	if(dir==1||dir==2) fdir=1,i=0;else fdir=-1,i=TOTAL-1;
	while(0<=i&&i<TOTAL){
		if(table[i]==0){
			table[i]=nextValue(i,dir,table);
			if(table[i]) *f=1;
		}
		i+=fdir;
	}
} 
int GameBox::nextPos(const int& pos,const int& dir,int*table){
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
int GameBox:: colliationDir(const int& dir,bool *f,int*table){
	int sor=0,i,fdir;
	if(dir==1||dir==2) fdir=1,i=0;else fdir=-1,i=TOTAL-1;
	while(0<=i&&i<TOTAL){
		if(table[i]){
			int p=nextPos(i,dir,table);
			if(p>=0&&table[i]==table[p]){
				table[i]<<=1;
				sor+=table[i];
				table[p]=0;
				totalFulled--;
				*f=1;
			}
		}
		i+=fdir;
	}
	return sor;
}
void GameBox:: tryColliationDir(const int& dir,bool *f,int*table){
	bool fdir;int i;
	if(dir==1||dir==2) fdir=1,i=0;else fdir=-1,i=TOTAL-1;
	while(0<=i&&i<TOTAL){
		if(table[i]){
			int p=nextPos(i,dir,table);
			if(p>=0&&table[i]==table[p]){
				*f=1;
				return ;
			}
		}
		i+=fdir;
	}
	return ;
}

bool GameBox:: moveDir(const int& dir,int *sor,int*table){
	bool f[3];
	allDir(dir,&f[0],table);
	*sor=colliationDir(dir,&f[1],table);
	allDir(dir,&f[2],table);
	return (f[0]|f[1]|f[2]);
}
bool GameBox::tryMove(const int& dir){
	copy(begin(table),end(table),begin(cotable));
	bool f;
	allDir(dir,&f,cotable);
	if(f) return 1;
	tryColliationDir(dir,&f,cotable);
	return f;
}

bool GameBox::onlyDir(int *dir){
	bool possibleMove=0,canMove=0;
	for(int i=1;i<=4;++i){
		possibleMove=tryMove(i);
		if(possibleMove){
			if(canMove) return 0;
			else{
				canMove=1;
				*dir=i;
			}
		}
	}
	return canMove;
}
bool GameBox:: oneMove(const int& dir,int *sor){
	bool f=moveDir(dir,sor,table);
	if(f)addNumber();
	else puts("Uesless operation");
	printTable();
	return f;
}
void GameBox::endOfGame(){
    puts("___________		Game Over!		___________");
    switch(checkState()){
      	case victory : puts("~~~~~Congratulations to you!~~~~~");break;
       case fail: 
		if(!infintGame)puts("-----Sorry about that,you are failed-----");
		else puts("~~~~~That's the end.Claps for you.~~~~~~");
		break;
        	default:break;
   	}
}

void GameBox:: endOfGame(const player &p1,const player &p2){
	puts("___________		Game Over!		___________");
	switch(checkState()){
        	case victory :
        	case fail:
		  	if(p1.sores>p2.sores) printf("%s wins!",p1.name);
			else
			if(p1.sores<p2.sores) printf("%s wins!",p2.name);
			else
			puts("-----This is an even game.-----");
	 		break;
       		default:break;
    	}	
}


bool GameBox::vicOfGame(const player& p1){
	puts("~~~~~Congratulations!You get a Victory~~~~~");	
	infintGame=player::continuePlay();
	if(infintGame){ //youwenti
		puts("Game continue!");
		printTable();
		return 1;
	}else{
		endOfGame();
		return 0;
	} 
}

bool GameBox::playing(const player &p1){
	switch (checkState()){
		case victory:
                     return vicOfGame(p1);
                     // single player can choose infinity game in this step;and this will change the stopping
		case fail:
                     endOfGame();
              	return 0;
	       default:return 1;
	}
}
