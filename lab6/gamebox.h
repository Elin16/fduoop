#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;
typedef enum {
 	victory,fail,play
}Statement; 
const int delta[5][2]={
       0,0,1,0,0,1,-1,0,0,-1
};//a w s z 
typedef struct{int sore;bool moved;
}result;
typedef struct P{
       P(int x,int y){this->x=x;this->y=y;}
       int x,y;
}Position;
const int ROW=0;
const int COL=1;
const char COM[5]={'q','a','w','s','z'};//left 和 up 与老师的顺序不同
class GameBox{
public:
       GameBox();
       virtual ~GameBox();
       void firstHit();
       Statement checkState();
       bool oneMove(const int& dir,int *sor);
       void setNumOfWinning(const int& numOfWinning);
       void initial(int edgeSize,int numOfWinning);
       bool infinitGameModel(){return infinit;}
       string validDirection();
       bool onlyDir(int *dir);
       bool infinitGame();
       void setGameBox(int edgeSize,int*table);
       void moveAndPrintResult(int dir);
private:
       int WIDTH,LENGTH,TOTAL;
       int totalFulled;
       int numOfWinning;
       bool infinit;
       int table[50],cotable[50];
       int pickOneSpareBlock();
       void printBareTable();
       void addNumber();
       bool tryMoveThisDirection(const int&dir);
       void allDir(const int& dir,bool *f,int*table);
       int colliationDir(const int& dir,bool *f,int*table);
       int nextPos(const int& pos,const int& dir,int*table);
       int nextValue(const int& pos,const int& dir,int*table);
       bool moveDir(const int& dir,int *sor,int*table);
       void tryColliationDir(const int& dir,bool *f,int*table);
       void printTable();
       int translate(Position p);
       Position translate(int p);
};
#endif /* GAME_H_ */
