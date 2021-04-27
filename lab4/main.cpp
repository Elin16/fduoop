#include "gameplay.h"
int main(int argc,char *args[]){
       GameControl contr;
       contr.beforeGame(argc,args);
       contr.playGame();
       return 0;
}