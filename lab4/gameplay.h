#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include "player.h"
#include "gamebox.h"
const char TEST_MODLE[]="-t";
const char TEST_MODLE_8[]="-ttt";
const char TABLE_MODLE[]="-s";
const int  TEST_WIN_NUM=64;
const int  WIN_NUM=2048;
const char SINGLE[]= "s";
const char DOUBLE[]= "d";
const int BUFSIZE=50;
#define DOWN  "z"
#define UP "w"
#define LEFT "a"
#define RIGHT "s"
#define YES "y"
using namespace std;
typedef enum {
       nocheat,cheating,cheated
}cheatstate;
typedef std::map<int,string> Direction_int_string;
typedef std::pair<int,string> Pair_int_string;
typedef  Direction_int_string ::iterator Dir_iterator;
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
              void playCheat(const int&dir);
              bool operMove(player *Jack);
              bool setCheat();
              bool playing();
              bool vicOfGame();
              bool infinitModle();
              bool endOfGame();
              void endOfGame(const player &p1,const player &p2);
              GameBox G; 
              int  playerNum,winNum,edgeSize;
              Direction_int_string Direction_map;
              int infinitGameModel;

};
#endif