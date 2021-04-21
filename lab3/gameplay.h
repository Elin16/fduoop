#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include<iostream>
#include<cstdio>
#include<cstring>
#include "player.h"
#include "gamebox.h"
using namespace std;
class gameplay{
       public:
              gameplay();
              virtual ~gameplay();
              void welcome(const char*nameOfGame);
              void winNumModel(int argc,char *args[]);
              void playerModel();
              void playGame();
       private:
              bool  commend(player *Jack);
              inline void singleplayer();
              inline void doubleplayer();
              GameBox G; 
              int  playerNum;
};
#endif