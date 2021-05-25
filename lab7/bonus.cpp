#include "bonus.h"
Bonus::Bonus(){
        bonusModel=0;
        lastTime.tv_sec=lastTime.tv_usec=0;
        copylot.tv_sec=copylot.tv_usec=0;
}
Bonus::~Bonus(){}
void Bonus::openBonusModel(bool open){
        bonusModel=open;
        //std::cout<<"bonusModel on\n";
}
bonus_info Bonus::checkBonus(struct timeval now){
        lastTime=copylot;copylot=now;
        if(bonusModel==false||lastTime.tv_usec==0||now.tv_sec>lastTime.tv_sec+1) return bonus_info(0,0,0);
        long secs=now.tv_usec-lastTime.tv_usec+(now.tv_sec-lastTime.tv_sec)*1000000;
        std::cout<<(secs<1000000)<<" "<<(float)(secs)/1e6<<" "<<"\n";
        return bonus_info(secs<1000000,(float)(secs)/1e6,1);
}