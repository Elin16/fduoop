#ifndef GAME_H_
#define GAME_H_
#include "player.h"
#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
typedef enum {
 	victory,fail,play
}statement; 

class GameBox{
public:
       GameBox();
       virtual ~GameBox();
       void firHit();
       statement checkState();
       bool oneMove(const int& dir,int *sor);
       void winNum(const int& num);
       void initial(int edgeSize,int winNum);
       bool onlyDir(int *dir);
       bool tryMove(const int&dir);
       bool infinit;
       bool infinitGame();
private:
       int WIDTH;
       int LENGTH;
       int TOTAL;
       int totalFulled;
       int numOfWinning;
       int table[50];
       int cotable[50];
       void addNumber();
       void allDir(const int& dir,bool *f,int*table);
       int nextPos(const int& pos,const int& dir,int*table);
       int colliationDir(const int& dir,bool *f,int*table);
       int nextValue(const int& pos,const int& dir,int*table);
       bool moveDir(const int& dir,int *sor,int*table);
       void drawTheLine();
       void printTable();
       void tryColliationDir(const int& dir,bool *f,int*table);

};

#endif /* GAME_H_ */
