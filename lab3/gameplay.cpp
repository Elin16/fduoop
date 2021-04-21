#include "gameplay.h"
#include "gamebox.h"
#include "player.h"
const char TEST_MODLE[]="-t";
const char TEST_MODLE_8[]="-ttt";
const int  TEST_WIN_NUM=64;
const int  WIN_NUM=2048;
const char SINGLE[]= "s";
const char DOUBLE[]= "d";
const int BUFSIZE=50;
gameplay::gameplay(){
       playerNum=1;
       G.winNum(WIN_NUM);//default 2048
}
gameplay:: ~gameplay(){

}
inline void gameplay::winNumModel(int argc,char*args[]){
       for(int i=0;i<argc;++i){
              if(strcmp(args[i],TEST_MODLE)==0){
                     G.winNum(TEST_WIN_NUM);
                     break;
              }
              if(strcmp(args[i],TEST_MODLE_8)==0){
                     G.winNum(8);
              }
       }
}

inline void gameplay::welcome(const char*nameOfGame){
	printf("____________Welcome to %s____________",nameOfGame);
}
inline void gameplay::playerModel(){
       puts("Please choose the player modle of game:");
       puts("Single player: enter s ");
       puts("Double player: enter d ");
       printf("Make your choice:");
       char com[BUFSIZE];
       while(1){
              fgets(com,BUFSIZE,stdin);
              com[strlen(com)-1]='\0';
              if(strcmp(com,SINGLE)==0){
                     playerNum=1;
                     break;
              }
              else 
              if(strcmp(com,DOUBLE)==0){
                     playerNum=2;
                     break;
              }
              else{
                     puts("error input");
                     printf("please choose again:");
              }
       }
}
inline bool gameplay::commend(player *Jack){
       int sore=0,dir=0;bool f=0;//用户不可以有无效操作
       f=Jack->myMove(&dir);
       if(f){
              f=G.oneMove(dir,&sore);
              Jack->addSore(sore);
              Jack->printSores();//是否应该封装？？
       }
       return f; 
}

inline void gameplay::singleplayer(){
       player Jack;
       Jack.setName();
       G.firHit();//初始局面
       while(G.playing(Jack)){//  哪一种实现方式比较好？传不传Jack？
              commend(&Jack);
       }
}
inline void gameplay::doubleplayer(){
       player Jack,Mark;
       Jack.setName();
       Mark.setName();
       player *oper;
       bool playing=1,round=0;
       G.firHit();//初始局面
       while(playing){
              round=!round;
              if(round) oper=&Jack;else oper=&Mark;   
              oper->turn();
              if(commend(oper)==0){
                     round=!round;
                     continue;
              }  
              switch (G.checkState()){
		       case victory:
		       case fail:G.endOfGame(Jack,Mark);playing=0;break;
	              default:;
	       }
       }
}
inline void gameplay::playGame(){
       if(playerNum==1) singleplayer();
       else doubleplayer();
}
int main(int argc,char *args[]){
       gameplay contr;
       contr.welcome("2048");
       contr.winNumModel(argc,args);
       contr.playerModel();
       contr.playGame();
       return 0;
}