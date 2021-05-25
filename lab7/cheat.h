#ifndef CHEAT_H
#define CHEAT_H
#include<cstring>
#include<iostream>
#include<cstdio>
using namespace std;
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
              Cheat();
              ~Cheat();
              void validateCheatBuff();
              void invalidateCheatBuff();
              void setCheat(string cheatWodrds,int cheaterID);
              void playCheat(const int&dir);
              bool canCheat(bool onlyDir,int playerID);
};
#endif

