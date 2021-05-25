#include "log.h"
#include "bonus.h"
#include<iostream>
using namespace std;
int main(){
        Log console;
        console.openLog(1);
        console.log(time(0),1,999,"kh");
        Bonus bos;
        bos.openBonusModel(1);
        struct timeval now;
        gettimeofday(&now,NULL);
        bonus_info p=bos.checkBonus(&now);
        gettimeofday(&now,NULL);
        p=bos.checkBonus(&now);
        ///freopen("w","a.out",stdin);
        ///cout<<p.delta<<" "<<p.score<<"\n";
        ///fclose(stdin);
        return 0;
}
