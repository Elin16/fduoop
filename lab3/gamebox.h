#ifndef GAME_H_
#define GAME_H_
#include "player.h"
typedef enum {
 	victory,fail,play
}statement; 
class GameBox{
public:
       GameBox();
       virtual ~GameBox();
       void firHit();
       statement checkState();
       void endOfGame();
       void endOfGame(const player& p1,const player& p2);
       bool oneMove(const int& dir,int *sor);
       void winNum(const int& num);
       bool playing(const player&p1);
       bool vicOfGame(const player& p1);
private:
       const int WIDTH;
       const int LENGTH;
       const int TOTAL;
       int totalFulled;
       int numOfWinning;
       int table[100];
       bool infintGame;
       void addNumber();
       void allDir(const int& dir,bool *f);
       int nextPos(const int& pos,const int& dir);
       int colliationDir(const int& dir,bool *f);
       int nextValue(const int& pos,const int& dir);
       bool moveDir(const int& dir,int *sor);
       void drawTheLine();
       void printTable();

};

#endif /* GAME_H_ */