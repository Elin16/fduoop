#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include<iostream>
#include<cstdio>
#include<cstring>
#include "player.h"
#include "gamebox.h"
using namespace std;
typedef enum {
       nocheat,cheating,cheated
}cheatstate;
class gameplay{
       public:
              cheatstate cheatBuff;
              gameplay();
              virtual ~gameplay();
              void welcome(const char*nameOfGame);
              void winNumModel(int argc,char *args[]);
              bool tableSize(int argc,char *args[]);
              void playerModel();
              bool setTableSize();
              void playGame();
       private:
              bool  commend(player *Jack);
              inline void singleplayer();
              inline void doubleplayer();
              bool playCheat(const int&dir);
              bool operMove(player *Jack);
              bool setCheat();
              GameBox G; 
              int  playerNum,winNum,edgeSize;
};
#endif