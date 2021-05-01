#include "gameplay.h"
#define debug(x) cout<<#x"="<<x<<endl;
GameControl::GameControl(){
       playerNum=1;
       winNum=WIN_NUM;//2048
       edgeSize=4;
}
GameControl:: ~GameControl(){
}
bool GameControl::operMove(Player* Jack){
       int sore=0,dir=0;bool validDirCommand=0;
       validDirCommand=Jack->dirCommand(&dir);              //获得Player的方向命令，
       if(validDirCommand){                             //有方向命令
              validDirCommand=gbox.oneMove(dir,&sore);     //按照dir方向移动，获得sore分;若可移动，f为true；方向命令有效//无效要不要打印分数？？？
              Jack->addSore(sore)->printSores();        //Player加分
       }else
       if(dir==-1){//validDir=0 dir=-1，cheat命令
              cheatBuff.setCheat(Jack);   //true:成功设置
       }
       return validDirCommand;//执行了一次有效的移动命令
}

inline bool GameControl::command(Player* Jack){
       int sore=0,dir=0;bool validDirCommand=0;//用户不可以有无效操作
       validDirCommand=cheatBuff.checkAndCheat(&gbox,Jack);
       if(!validDirCommand) validDirCommand=operMove(Jack);//无cheat
       return validDirCommand;
}
void GameControl::endOfGame(){
    puts("___________	Game Over!	___________");
    if(playerNum==1){
       switch(gbox.checkState()){
      	       case victory :if(infinitGameModel) puts("~~~~~That's the end.Claps for you.~~~~~~");
                            puts("~~~~~Congratulations to you!~~~~~");break;
              case fail:    puts("-----Sorry about that,you are failed-----");break;
              default:break;
       }  
    }else{
           int hightestSore=playerList[0].getSores(),winnerID=0;
           for(int i=1;i<playerList.capacity();++i)
           if(playerList[i].getSores()>hightestSore){
                  hightestSore=playerList[i].getSores();winnerID=i;
           }
           if(winnerID!=0||hightestSore>playerList[winnerID].getSores()) printf("%s wins the game!",playerList[winnerID].getName());
           else puts("-----This is an even game.-----");
    }
}

bool GameControl::infinitModle(){
       puts("~~~~~Congratulations!You get a Victory~~~~~");	
	infinitGameModel=Player::continuePlay();
	if(infinitGameModel) return  gbox.infinitGame();//return 1
	else return 0;
}

bool GameControl::playing(){
       switch (gbox.checkState()){
		case victory:if(playerNum==1) return infinitModle();else return 0;//非无限模式自然下落到end of game// single Player can choose infinity game in this step;and this will change the stopping          
              case fail:return 0;
	       default:return 1;
	}        
}

void GameControl::playGame(){
       gbox.firstHit();//初始局面
       vector<Player>::iterator operatorNow=playerList.begin();
       while(playing()){
              operatorNow->printTurn();
              if(command(&(*operatorNow))==0) continue;
              operatorNow++;
              if(operatorNow==playerList.end()) operatorNow=playerList.begin();
       }
       endOfGame();  
}

inline void GameControl::winNumModel(int argc,char*args[]){
       for(int i=0;i<argc;++i)
              if(strcmp(args[i],TEST_MODLE)==0){
                     winNum=TEST_WIN_NUM;break;//64
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
       puts("Please choose the Player modle of game:\nSingle Player: enter 1\nDouble Player: enter 2\n");
       printf("Make your choice:");
       int com,validCom=0;
       do{    cin>>com;
              if(0<com&&com<3) playerNum=com,validCom=1;
              else  printf("error input\n please choose again:");
       }while(!validCom);
}

bool GameControl::setTableSize(){
       puts("The table size is illegaled.\nplease set the table size(choose among 2*2,3*3,4*4,5*5)");
       printf("enter the length of the table edge(2/3/4/5):");
       scanf("%d",&edgeSize);fflush(stdin);
       if(1<edgeSize&&edgeSize<6) return 1;else return 0;
}
void GameControl::beforeGame(int argc,char *args[]){
       welcome("2048");
       winNumModel(argc,args);
       if(!tableSize(argc,args)){// 一定需要用户设定吗
              while(!setTableSize()){}     
       }
       gbox.initial(edgeSize,winNum);
       playerModel();
       if(playerNum>1) cheatBuff.validateCheatBuff();
       for(int id=0;id<playerNum;++id){
              playerList.push_back(Player(id));
       }
}
