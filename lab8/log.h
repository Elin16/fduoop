#ifndef LOGFUNC_H
#define LOGFUNC_H
#include<cstring>
#include<time.h>
#include<iostream>
#include<cstdio>
#include<fstream>
#include<iomanip>
using namespace std;
class Log{
public:
        Log();
        ~Log();
        void log(time_t now,int dir,int score,const char*playerName="默认玩家");
        void log(time_t now,float timeSpent,int score,const char*playerName="默认玩家");
        void openLog(bool open);
private:
        tm *ltm;
        FILE *flog;
        bool logging;
        char timbuf[256];
        static const char *directionChinese[];
};
#endif