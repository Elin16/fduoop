#ifndef CHEAT_H
#define CHEAT_H
#include "player.h"
#include "gamebox.h"
#include<cstring>
typedef enum {
       nocheat,cancheat,cheating,cheated,
}cheatstate;
const char direction[5]={'x','a','w','s','z'};
class Cheat{
        private:
              int cheaterID;
              string cheatWords;
        public:
              cheatstate stateOfCheatBuff;
              Cheat(){
                cheaterID=-1;
                stateOfCheatBuff=nocheat;
              }
              virtual ~Cheat(){};
              void validateCheatBuff(){
                     stateOfCheatBuff=cancheat;
              }
              void invalidateCheatBuff(){
                     stateOfCheatBuff=cheated;
              }
              void setCheat(string cheatWodrds,int cheaterID){
                     if(stateOfCheatBuff==cancheat){
                            stateOfCheatBuff=cheating;
                            this->cheatWords=cheatWodrds;
                            this->cheaterID=cheaterID;
                     }else{
                            puts("No avalible cheatBuff!");
                     }
                }
              void playCheat(const int&dir){
                     cout<<cheatWords<<" 同意请按 "<<direction[dir]<<" ";
              }
              bool canCheat(bool onlyDir,int playerID){
                     return (onlyDir==true&&stateOfCheatBuff==cheating&&playerID!=cheaterID);  
              }
};
#endif

