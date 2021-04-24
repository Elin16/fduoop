#include "gameplay.h"
int main(int argc,char *args[]){
       gameplay contr;
       contr.beforeGame(argc,args);
       contr.playGame();
       return 0;
}