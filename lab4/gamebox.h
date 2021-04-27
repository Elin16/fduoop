#ifndef GAME_H_
#define GAME_H_
#include "player.h"
#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
typedef enum {
 	victory,fail,play
}Statement; 

class GameBox{
public:
       GameBox();
       virtual ~GameBox();
       void firstHit();
       Statement checkState();
       bool oneMove(const int& dir,int *sor);
       void setNumOfWinning(const int& numOfWinning);
       void initial(int edgeSize,int numOfWinning);
       bool onlyDir(int *dir);
       bool infinitGame();
private:
       int WIDTH;
       int LENGTH;
       int TOTAL;
       int totalFulled;
       int numOfWinning;
       bool infinit;
       int table[50];
       int cotable[50];
       void addNumber();
       bool tryMove(const int&dir);
       void allDir(const int& dir,bool *f,int*table);
       int colliationDir(const int& dir,bool *f,int*table);
       int nextPos(const int& pos,const int& dir,int*table);
       int nextValue(const int& pos,const int& dir,int*table);
       bool moveDir(const int& dir,int *sor,int*table);
       void tryColliationDir(const int& dir,bool *f,int*table);
       void drawTheLine();
       void printTable();
};

#endif /* GAME_H_ */
