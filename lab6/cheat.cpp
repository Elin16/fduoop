#include "cheat.h"
        Cheat::Cheat(){
                cheaterID=-1;
                stateOfCheatBuff=nocheat;
              }
        Cheat::~Cheat(){
                
        }
              void Cheat::validateCheatBuff(){
                     stateOfCheatBuff=cancheat;
              }
              void Cheat::invalidateCheatBuff(){
                     stateOfCheatBuff=cheated;
              }
              void Cheat::setCheat(string cheatWodrds,int cheaterID){
                     if(stateOfCheatBuff==cancheat){
                            stateOfCheatBuff=cheating;
                            this->cheatWords=cheatWodrds;
                            this->cheaterID=cheaterID;
                     }else{
                            puts("No avalible cheatBuff!");
                     }
                }
              void Cheat::playCheat(const int&dir){
                     cout<<cheatWords<<" 同意请按 "<<direction[dir]<<" ";
              }
              bool Cheat::canCheat(bool onlyDir,int playerID){
                     return (onlyDir==true&&stateOfCheatBuff==cheating&&playerID!=cheaterID);  
              }