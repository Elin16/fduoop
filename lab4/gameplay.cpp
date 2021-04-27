#include "gameplay.h"
#define debug(x) cout<<#x"="<<x<<endl;
GameControl::GameControl(){
       playerNum=1;
       winNum=WIN_NUM;//2048
       edgeSize=4;
       cheatBuff=nocheat;
       Direction_map.insert(Pair_int_string (1,LEFT));
       Direction_map.insert(Pair_int_string (2,UP));
       Direction_map.insert(Pair_int_string (3,RIGHT));
       Direction_map.insert(Pair_int_string (4,DOWN));
}
GameControl:: ~GameControl(){

}
bool GameControl::operMove(Player *Jack){
       int sore=0,dir=0;bool validDirCommand=0;
       validDirCommand=Jack->dirCommand(&dir);              //获得Player的方向命令，
       if(validDirCommand){                             //有方向命令
              validDirCommand=gbox.oneMove(dir,&sore);     //按照dir方向移动，获得sore分;若可移动，f为true；方向命令有效//无效要不要打印分数？？？
              Jack->addSore(sore)->printSores();        //Player加分
       }else
       if(dir==-1){//f=0；// dir=-1，cheat命令
              Jack->setCheatingOthers(setCheat());   //true:成功设置
       }
       return validDirCommand;//执行了一次有效的移动命令
}

void GameControl::playCheat(const int &dir){
       Dir_iterator it=Direction_map.find(dir);
       cout<<Player::cheatWords<< "同意请按"<<it->second<<endl;
}

inline bool GameControl::commend(Player *Jack){
       int sore=0,dir=0;bool f=0;//用户不可以有无效操作
       if(cheatBuff==cheating&&!Jack->getCheatingOthers()){//进入 cheat 命令
              if(gbox.onlyDir(&dir)){//如果符合cheat条件
                     do{
                            playCheat(dir);
                     }while(operMove(Jack)==0);//Jack 进行的操作有效//无效会给出useless operation 提示
                     cheatBuff=cheated;//成功cheat
                     return 1;
              }
       }
       return operMove(Jack);//无cheat
}
bool GameControl::setCheat(){
       switch (cheatBuff){
       case nocheat:
              if(playerNum==2){
                      cheatBuff=cheating;//cheat 命令启动//Jack->cheatingOther=1;
                     puts("Cheat commend is working now~");
                     return 1;
              }//PlayerNum==1 自然下落
       default:puts("no cheat commend");//cheat被抢用 或 单人模式无cheat
       } 
       return 0;                
}
bool GameControl::endOfGame(){
    puts("___________		Game Over!		___________");
    switch(gbox.checkState()){
      	case victory :if(infinitGameModel) puts("~~~~~That's the end.Claps for you.~~~~~~");
                     puts("~~~~~Congratulations to you!~~~~~");break;
       case fail:    puts("-----Sorry about that,you are failed-----");break;
       default:break;
       }
       return 0;
}

void GameControl:: endOfGame(const Player &p1,const Player &p2){
	puts("___________		Game Over!		___________");
       Player::winner(p1,p2);
}

bool GameControl::infinitModle(){
       puts("~~~~~Congratulations!You get a Victory~~~~~");	
	infinitGameModel=Player::continuePlay();
	if(infinitGameModel) return  gbox.infinitGame();//return 1
	else return 0;
}

bool GameControl::playing(){
       if(playerNum==2){
              switch (gbox.checkState()){
                     fail:return 0;
                     default:return 1;
              }
       }//single Player
	switch (gbox.checkState()){
		case victory:return infinitModle();// single Player can choose infinity game in this step;and this will change the stopping
		//非无限模式自然下落到end of game
              case fail:return 0;
	       default:return 1;
	}
}
inline void GameControl::winNumModel(int argc,char*args[]){
       for(int i=0;i<argc;++i){
              if(strcmp(args[i],TEST_MODLE)==0){
                     winNum=TEST_WIN_NUM;break;//64
              }
              if(strcmp(args[i],TEST_MODLE_8)==0){
                     winNum=8;break;
              }
       }
}
inline bool GameControl::tableSize(int argc,char *args[]){
       for(int i=0;i<argc;++i){
              if(strcmp(args[i],TABLE_MODLE)==0&&i+1<argc){
                     edgeSize=atoi(args[i+1]);
                     if(1<edgeSize&&edgeSize<6) return 1;
              }
       }
       return 0;
}

inline void GameControl::welcome(const char*nameOfGame){
	printf("____________Welcome to %s____________\n",nameOfGame);
}
inline void GameControl::playerModel(){
       puts("Please choose the Player modle of game:");
       puts("Single Player: enter s ");
       puts("Double Player: enter d ");
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

inline void GameControl::doublePlayer(){
       Player Jack,Mark;//Jack.setName();Mark.setName();
       Player *oper[2]={&Jack,&Mark};// shuzu
       bool round=0;
       gbox.firstHit();//初始局面
       while(playing()){
              round=!round;
              oper[round]->printTurn();
              if(commend(oper[round])==0){
                     round=!round;
                     continue;
              }  
       }
       endOfGame(*oper[0],*oper[1]);
}

inline void GameControl::singlePlayer(){
       Player Jack;
       gbox.firstHit();//初始局面
       while(playing()) commend(&Jack);
       endOfGame();
}

inline void GameControl::playGame(){
       gbox.initial(edgeSize,winNum);
       if(playerNum==1) singlePlayer();
       else doublePlayer();
}
bool GameControl::setTableSize(){
       puts("The table size is illegaled.");
       puts("please set the table size(choose among 2*2,3*3,4*4,5*5)");
       puts("enter the length of the table edge(2/3/4/5):");
       scanf("%d",&edgeSize);fflush(stdin);
       if(1<edgeSize&&edgeSize<6){
              return 1;
       }else return 0;
}
void GameControl::beforeGame(int argc,char *args[]){
       welcome("2048");
       winNumModel(argc,args);
       if(!tableSize(argc,args)){// 一定需要用户设定吗
              while(!setTableSize()){}     
       }
       playerModel();
}
