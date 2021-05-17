#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include<vector>
#include "player.h"
#include "gamebox.h"
#include "cheat.h"
#include "gameinout.h"
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
              int getPlayerNum(){return playerNum;}//bug
       protected:
              GameInOut input;
              int playerNum;
              GameBox gbox; 
              vector<Player> playerList;
              bool command(Player* Jack);
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
       void beforeGame(int argc,char *args[]){
              freopen(input.getFileName(argc,args,"-i"),"r",stdin);
              freopen(input.getFileName(argc,args,"-o"),"w",stdout);
              //cout<<"beforgame in file inout \n";
              int edgeSize=input.getTableSize(),*table;
              int totalBlocks=edgeSize*edgeSize;
              table=new int[totalBlocks];
              for(int i=0;i<totalBlocks;++i) cin>>table[i];
              gbox.setGameBox(edgeSize,table);
              delete []table;
       }
       void playGame(){
              string result=gbox.validDirection();
              cout<<result.length();
              if(result[0]=='a'&&result[1]=='w') swap(result[0],result[1]);
              for(int i=0;i<result.length();++i) cout<<" "<<result[i];
              cout<<endl;

              int dir;
              input.usrCommandOfDir(&dir);
              gbox.moveAndPrintResult(dir);
       }
       void endOfGame(){
              fclose(stdin);
              fclose(stdout);
       }
};
#endif