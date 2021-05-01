#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include "player.h"
#include "gamebox.h"
#include "cheat.h"
const char TEST_MODLE[]="-t";
const char TABLE_MODLE[]="-s";
const int  TEST_WIN_NUM=64;
const int  WIN_NUM=2048;
const int BUFSIZE=50;
#define DOWN  "z"
#define UP "w"
#define LEFT "a"
#define RIGHT "s"
using namespace std;
class GameControl{
       public:
              GameControl();
              virtual ~GameControl();
              void beforeGame(int argc,char *args[]);
              void playGame();
       private:
              Cheat cheatBuff;
              vector<Player> playerList;
              bool command(Player* Jack);
              bool operMove(Player* Jack);
              bool playing();
              bool vicOfGame();
              bool infinitModle();
              void endOfGame();
              GameBox gbox; 
              int  playerNum,winNum,edgeSize;
              int infinitGameModel;
              void welcome(const char*nameOfGame);
              void winNumModel(int argc,char *args[]);
              bool tableSize(int argc,char *args[]);
              void playerModel();
              bool setTableSize();
};
#endif