#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include<vector>
#include "player.h"
#include "gamebox.h"
#include "cheat.h"
#include "gameinout.h"
#include "log.h"
#include "bonus.h"
const int BUFSIZE=50;
using namespace std;
class GameControl{
       public:
              GameControl(){};
              virtual ~GameControl(){};
              virtual void beforeGame(int argc,char *args[]);
              virtual void playGame(){};
              virtual void endOfGame(){};
              virtual bool playing(){return 0;};
       protected:
              GameInOut input;
              int playerNum;
              GameBox gbox; 
              vector<Player> playerList;
              bool command(Player* Jack);
              Log console;
              Bonus bonuscon;
       private:
              Cheat cheatBuff;
              bool operMove(Player* Jack);
              bool vicOfGame();
              void welcome(const char*nameOfGame);
       friend class Cheat;
};
class SinglePlayerGameControl:public GameControl{
public:
       SinglePlayerGameControl(int playerNum);
       ~SinglePlayerGameControl();
       void playGame();
       bool playing();
       bool infinitModle();
       void endOfGame();
       
};
class MultiPlayerGameControl:public GameControl{
public:
       MultiPlayerGameControl(int playerNum);
       ~MultiPlayerGameControl();
       void playGame();
       bool playing();
       void endOfGame();
};
class FileInOutGameControl:public GameControl{
public:
       FileInOutGameControl();
       ~FileInOutGameControl();
       void beforeGame(int argc,char *args[]);
       void playGame();
       void endOfGame();
};
#endif