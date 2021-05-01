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
              void setCheat(Player *Jack){
                     if(stateOfCheatBuff==cancheat){
                            stateOfCheatBuff=cheating;
                            cheatWords=Jack->getCheatWords();
                            cheaterID=Jack->getID();
                     }else{
                            puts("No avalible cheatBuff!");
                     }
                }
              void playCheat(const int&dir){
                     cout<<cheatWords<<" 同意请按 "<<direction[dir]<<" ";
              }
              int operMove(GameBox *gbox,Player *Jack){
                     int sore=0,dir=0;bool validDirCommand=0;
                     validDirCommand=Jack->dirCommand(&dir);              //获得Player的方向命令，
                     if(validDirCommand){                             //有方向命令
                            validDirCommand=gbox->oneMove(dir,&sore);     //按照dir方向移动，获得sore分;若可移动，f为true；方向命令有效//无效要不要打印分数？？？
                            Jack->addSore(sore)->printSores();        //Player加分
                     }
                     return validDirCommand;
              }
              bool checkAndCheat(GameBox *gbox,Player*Jack){
                     if(stateOfCheatBuff!=cheating||Jack->getID()==cheaterID) return 0;
                     int dir=0;
                     if(gbox->onlyDir(&dir)){
                            do{playCheat(dir);}while(operMove(gbox,Jack)==0);//Jack 进行的操作有效//无效会给出useless operation 提示
                            stateOfCheatBuff=cheated;//成功cheat
                            return 1;
                     }
                     return 0;
              }
};
#endif
