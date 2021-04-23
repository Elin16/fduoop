#include "gameplay.h"
#define debug(x) cout<<#x"="<<x<<endl;
gameplay::gameplay(){
       playerNum=1;
       winNum=WIN_NUM;//2048
       edgeSize=4;
       cheatBuff=nocheat;
       Direction_map.insert(Pair_int_string (1,LEFT));
       Direction_map.insert(Pair_int_string (2,UP));
       Direction_map.insert(Pair_int_string (3,RIGHT));
       Direction_map.insert(Pair_int_string (4,DOWN));
}
gameplay:: ~gameplay(){

}
inline void gameplay::winNumModel(int argc,char*args[]){
       for(int i=0;i<argc;++i){
              if(strcmp(args[i],TEST_MODLE)==0){
                     winNum=TEST_WIN_NUM;break;//64
              }
              if(strcmp(args[i],TEST_MODLE_8)==0){
                     winNum=8;break;
              }
       }
}
inline bool gameplay::tableSize(int argc,char *args[]){
       for(int i=0;i<argc;++i){
              if(strcmp(args[i],TABLE_MODLE)==0&&i+1<argc){
                     edgeSize=atoi(args[i+1]);
                     if(1<edgeSize&&edgeSize<6) return 1;
              }
       }
       return 0;
}

inline void gameplay::welcome(const char*nameOfGame){
	printf("____________Welcome to %s____________\n",nameOfGame);
}
inline void gameplay::playerModel(){
       puts("Please choose the player modle of game:");
       puts("Single player: enter s ");
       puts("Double player: enter d ");
       printf("Make your choice:");
       string com;
       while(1){
              cin>>com;
              if(com==SINGLE){
                     playerNum=1;return ;
              }else if(com==DOUBLE){
                     playerNum=2;return ;
              }else{
                     puts("error input");
                     printf("please choose again:");
              }
       }
}
inline void gameplay::playGame(){
       G.initial(edgeSize,winNum);
       if(playerNum==1) singleplayer();
       else doubleplayer();
}
bool gameplay::setTableSize(){
       puts("The table size is illegaled.");
       puts("please set the table size(choose among 2*2,3*3,4*4,5*5)");
       puts("enter the length of the table edge(2/3/4/5):");
       scanf("%d",&edgeSize);fflush(stdin);
       if(1<edgeSize&&edgeSize<6){
              return 1;
       }else return 0;
}

int main(int argc,char *args[]){
       gameplay contr;
       contr.welcome("2048");
       contr.winNumModel(argc,args);
       if(!contr.tableSize(argc,args)){// 一定需要用户设定吗
              while(!contr.setTableSize()){}     
       }
       contr.playerModel();
       contr.playGame();
       return 0;
}

inline void gameplay::doubleplayer(){
       player Jack,Mark;//Jack.setName();Mark.setName();
       player *oper[2]={&Jack,&Mark};// shuzu
       bool round=0;
       G.firHit();//初始局面
       while(playing()){
              round=!round;
              if(oper[round]->cheatingOther)oper[!round]->getBeingCheated();
              oper[round]->turn();
              if(commend(oper[round])==0){
                     round=!round;
                     continue;
              }  
       }
       endOfGame(*oper[0],*oper[1]);
}

inline void gameplay::singleplayer(){
       player Jack;
       G.firHit();//初始局面
       while(playing()) commend(&Jack);
       endOfGame();
}

bool gameplay::operMove(player *Jack){
       int sore=0,dir=0;bool f=0;
       f=Jack->myMove(&dir);              //获得player的方向命令，
       if(f){                             //有方向命令
              f=G.oneMove(dir,&sore);     //按照dir方向移动，获得sore分;若可移动，f为true；方向命令有效//无效要不要打印分数？？？
              Jack->addSore(sore)->printSores();        //player加分
       }else
       if(dir==-1){//f=0；// dir=-1，cheat命令
              Jack->cheatingOther=setCheat();   //true:成功设置
       }
       return f;//执行了一次有效的移动命令
}

void gameplay::playCheat(const int &dir){
       Dir_iterator it=Direction_map.find(dir);
       cout<<player::cheatWords<< "同意请按"<<it->second<<endl;
}

inline bool gameplay::commend(player *Jack){
       int sore=0,dir=0;bool f=0;//用户不可以有无效操作
       if(cheatBuff==cheating&&Jack->beingCheated){//进入 cheat 命令
              if(G.onlyDir(&dir)){//如果符合cheat条件
                     do{
                            playCheat(dir);
                     }while(operMove(Jack)==0);//Jack 进行的操作有效//无效会给出useless operation 提示
                     cheatBuff=cheated;//成功cheat
                     return 1;
              }
       }
       return operMove(Jack);//无cheat
}
bool gameplay::setCheat(){
       switch (cheatBuff){
       case nocheat:
              if(playerNum==2){
                      cheatBuff=cheating;//cheat 命令启动//Jack->cheatingOther=1;
                     puts("Cheat commend is working now~");
                     return 1;
              }//playerNum==1 自然下落
       default:puts("no cheat commend");//cheat被抢用 或 单人模式无cheat
       } 
       return 0;                   
}
bool gameplay::endOfGame(){
    puts("___________		Game Over!		___________");
    switch(G.checkState()){
      	case victory :if(infinitGameModel) puts("~~~~~That's the end.Claps for you.~~~~~~");
                     puts("~~~~~Congratulations to you!~~~~~");break;
       case fail:    puts("-----Sorry about that,you are failed-----");break;
       default:break;
       }
       return 0;
}

void gameplay:: endOfGame(const player &p1,const player &p2){
	puts("___________		Game Over!		___________");
       player::winner(p1,p2);
}

bool gameplay::infinitModle(){
       puts("~~~~~Congratulations!You get a Victory~~~~~");	
	infinitGameModel=player::continuePlay();
	if(infinitGameModel) return  G.infinitGame();//return 1
	else return 0;
}

bool gameplay::playing(){
       if(playerNum==2){
              switch (G.checkState()){
                     fail:return 0;
                     default:return 1;
              }
       }//single player
	switch (G.checkState()){
		case victory:return infinitModle();// single player can choose infinity game in this step;and this will change the stopping
		//非无限模式自然下落到end of game
              case fail:return 0;
	       default:return 1;
	}
}