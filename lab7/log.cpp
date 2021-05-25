#include "log.h"
const char * Log::directionChinese[]={"/","左","上","右","下"};
Log::Log(){
        logging=0;
}
Log::~Log(){
}
void Log::openLog(bool open){
        logging=open;
}
void Log::log(time_t now,int dir,int score,const char*playerName){
        if(!logging) return ;
        //flog=freopen("log.txt","a",stdout);
        ofstream flog("log.txt",ios::app);
        if(flog.is_open()) cout<<"OK\n";
        ltm=localtime(&now);
        strftime(timbuf,128," %Y\\%m\\%d %T",ltm);
        flog<<playerName<<" "<<timbuf<<" "<<directionChinese[dir]<<" "<<score<<"\n";
        flog.close();
}
void Log::log(time_t now,float timeSpent,int score,const char*playerName){
        if(!logging) return ;
        ofstream flog("log.txt",ios::app);
        ltm=localtime(&now);
        strftime(timbuf,128," %Y\\%m\\%d %T",ltm);
        flog<<playerName<<" "<<timbuf<<" "<<setprecision(1)<<timeSpent<<" "<<score<<"\n";
        flog.close();
}
