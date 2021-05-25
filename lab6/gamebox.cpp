#include "gamebox.h"
#define debug(x) cout<<#x"="<<x<<endl;
using namespace std; 
GameBox:: GameBox(){ //winning =2048 default why can not be working ?
	totalFulled=0;
	infinit=0;
	srand((unsigned)time(NULL));
	this->numOfWinning=2048;
	WIDTH=LENGTH=4;
	TOTAL=WIDTH*LENGTH;
	for(int i=0;i<TOTAL;++i) table[i]=0;
}
GameBox::~GameBox(){
}
void GameBox::initial(int edgeSize,int numOfWinning){ //winning =2048 default why can not be working ?
	this->numOfWinning=numOfWinning;
	WIDTH=LENGTH=edgeSize;
	TOTAL=WIDTH*LENGTH;
	for(int i=0;i<TOTAL;++i) table[i]=0;
}
void GameBox:: setNumOfWinning(const int& numOfWinning){
	this->numOfWinning=numOfWinning;
	printf("The winning num is %d\n ",numOfWinning);
}
void GameBox::firstHit(){
    addNumber();
    puts("___________		Game Start!		___________");
    printTable();
}
int GameBox::translate(Position p){
	cout<<"emptyp:"<<p.x<<" "<<p.y<<"\n";
	return p.y+p.x*WIDTH;
}
Position GameBox::translate (int p){
	return Position(p/WIDTH,p%WIDTH);
}
inline void GameBox:: addNumber(){
	table[pickOneSpareBlock()]=2;
	totalFulled++;
	return ;
}
 
Statement GameBox::checkState(){
	if(!infinit){
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
void GameBox::printTable(){
    	for(int i=0;i<WIDTH;++i)printf("+-----");
    	printf("+\n");
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
            		for(int i=0;i<WIDTH;++i)printf("+-----");
    	    		printf("+\n");
       		 } 
    }
}

int GameBox:: nextValue(const int& pos,const int& dir,int*table){
	int np=pos+delta[dir][ROW]+delta[dir][COL]*WIDTH;
	while(0<=np&&np<TOTAL){
		if(delta[dir][ROW]&&(np/WIDTH!=pos/WIDTH)) return 0;
		if(table[np]==0) np=np+delta[dir][ROW]+delta[dir][COL]*WIDTH;
		else break;
	}
	if(np<0||np>=TOTAL) return 0;
	int v=table[np];
	table[np]=0;
	return v;
}
void GameBox::allDir(const int & dir,bool*f,int*table){
	int fdir,i;
	if(dir==1||dir==2) fdir=1,i=0;else fdir=-1,i=TOTAL-1;
	for(i=i;0<=i&&i<TOTAL;i+=fdir){
		if(table[i]==0){
			table[i]=nextValue(i,dir,table);
			if(table[i]) *f=1;
		}
	}
} 
int GameBox::nextPos(const int& pos,const int& dir,int*table){
	int np=pos+delta[dir][ROW]+delta[dir][COL]*WIDTH;
	if(np<0||np>=TOTAL) return -1;
	if(delta[dir][ROW]&&np/WIDTH!=pos/WIDTH) return -1;
	return np;
}
int GameBox:: colliationDir(const int& dir,bool *f,int*table){
	int sor=0,i,fdir;
	if(dir==1||dir==2) fdir=1,i=0;else fdir=-1,i=TOTAL-1;
	for(i=i;0<=i&&i<TOTAL;i+=fdir){
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
	}
	return sor;
}
void GameBox:: tryColliationDir(const int& dir,bool *f,int*table){
	int i,fdir;
	if(dir==1||dir==2) fdir=1,i=0;else fdir=-1,i=TOTAL-1;
	for(i=i;0<=i&&i<TOTAL;i+=fdir)
		if(table[i]){
			int p=nextPos(i,dir,table);
			if(p>=0&&table[i]==table[p]){
				*f=1;return ;
			}
		}
	
}

bool GameBox:: moveDir(const int& dir,int *sor,int*table){
	bool f[3];
	allDir(dir,&f[0],table);
	*sor=colliationDir(dir,&f[1],table);
	allDir(dir,&f[2],table);
	return (f[0]|f[1]|f[2]);
}
bool GameBox::tryMoveThisDirection(const int& dir){
	copy(begin(table),end(table),begin(cotable));
	bool f=false;
	allDir(dir,&f,cotable);
	if(f) return 1;
	tryColliationDir(dir,&f,cotable);
	return f;
}

bool GameBox::onlyDir(int *dir){
	bool possibleMove=0,canMove=0;
	for(int i=1;i<=4;++i){
		possibleMove=tryMoveThisDirection(i);
		if(possibleMove){
			if(canMove) return 0;
			else canMove=1,*dir=i;
		}
	}
	return canMove;
}
bool GameBox:: oneMove(const int& dir,int *sor){
	bool f=moveDir(dir,sor,table);
	if(f) addNumber();
	else puts("Uesless operation");
	printTable();
	return f;
}

bool GameBox:: infinitGame(){
	infinit=1;
	puts("Game continue!");
	printTable();
	return 1;
}
void GameBox::setGameBox(int edgeSize,int*table){
              WIDTH=LENGTH=edgeSize;
              TOTAL=WIDTH*LENGTH;
              totalFulled=0;
              for(int i=0;i<TOTAL;++i){
                     this->table[i]=table[i];
                     if(table[i]) totalFulled++;
              }
}
int GameBox::pickOneSpareBlock (){
	vector<int> emptyBlocks;
	for(int i=0;i<TOTAL;++i) 
	if(!table[i]) emptyBlocks.push_back(i);
	int t=rand()%emptyBlocks.size();
	return emptyBlocks[t];
	//Position p(emptyBlocks[t]/WIDTH,emptyBlocks[t]%WIDTH);
	//return p;
}
void GameBox::printBareTable (){
	for(int i=0;i<TOTAL;++i){
		cout<<table[i];
		(i+1)%WIDTH==0?cout<<"\n":cout<<" ";
	} 
}
void GameBox::moveAndPrintResult(int dir){
	//cout<<"moveAndPrintResult\n"<<dir<<"\n";
        int score;
        moveDir(dir,&score,table);
        printBareTable();
        Position p=translate(pickOneSpareBlock());
        cout<<2<<"\n"<<p.x<<" "<<p.y<<"\n";
        cout<<score<<endl;
}
string GameBox::validDirection(){
              string result="";
              for(int i=1;i<=4;++i) 
              if(tryMoveThisDirection(i)){
                     result+=COM[i];
              }
              return result;
       }
       