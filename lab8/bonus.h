#ifndef BONUS_H
#define BONUS_H
#include<time.h>
#include<sys/time.h>
#include<iostream>
typedef struct b{
        bool getbonus;
        float delta;
        int score;
        b(bool get,float x=0,int y=0){
                getbonus=get;delta=x;score=y;
        }
        void print(){
                std::cout<<getbonus<<" "<<delta<<" "<<score<<"\n";
        }
}bonus_info;

class Bonus{
public:
        Bonus();
        ~Bonus();
        void openBonusModel(bool open);
        bonus_info checkBonus(struct timeval now);
private:
        struct timeval lastTime,copylot;
        bool bonusModel;
};
#endif