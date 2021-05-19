#ifndef GAMEINOUT_H
#define GAMEINOUT_H
#include<iostream>
#include<cstdio>
#include<map>
const char TEST_MODLE[]="-t";
const char TABLE_MODLE[]="-s";
const int  TEST_WIN_NUM=64;
const int  WIN_NUM=2048;
#define DOWN  "z"
#define UP "w"
#define LEFT "a"
#define RIGHT "s"
#define YES "y"
#define NO "n"
using namespace std;
typedef std::map<int,string> DirectionIntString;
typedef std::pair<int,string> PairIntString;
typedef DirectionIntString ::iterator DirIterator;
class GameInOut{
public:
        GameInOut();
        static int getPlayerNum();
        int  getWinNum(int argc,char*args[]);
        int getTableSize(int argc,char *args[]);
        int getTableSize();
        bool usrCommandOfDir(int*dir);
        bool continuePlay();
        char* getFileName(int argc,char*args[],const char *command);
        string getCheatWords();
private:
        DirectionIntString DirectionMap;
        string com,cheatWords;
        bool validInput;
};
#endif