#include "gamecontrol.h"
int main(int argc,char *args[]){
       bool fileInOut=0;
       for(int i=0;i<argc;++i) 
       if(strcmp(args[i],"-i")==0) fileInOut=1;
       else if(strcmp(args[i],"-o")==0) fileInOut=1;

       int playerNum=-1;
       if(fileInOut)  playerNum=0;
       else playerNum=GameInOut::getPlayerNum();

       GameControl *p;
       FileInOutGameControl F;
       SinglePlayerGameControl S(playerNum);
       MultiPlayerGameControl D(playerNum);
       switch (playerNum){
              case 0:p=&F;;break;
              case 1:p=&S;break;
              default:p=&D;break;
       }
       p->beforeGame(argc,args);
       p->playGame();
       p->endOfGame();
       return 0;
}