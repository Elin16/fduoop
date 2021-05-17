#include "gamecontrol.h"
#define debug(x) cout<<#x"="<<x<<endl;
bool GameControl::operMove(Player* Jack){
       int sore=0,dir=0;bool validDirCommand=0;
       validDirCommand=input.usrCommandOfDir(&dir);              //获得Player的方向命令，
       if(validDirCommand){                             //有方向命令
              validDirCommand=gbox.oneMove(dir,&sore);     //按照dir方向移动，获得sore分;若可移动，f为true；方向命令有效//无效要不要打印分数？？？
              Jack->addSore(sore)->printSores();        //Player加分
       }else
       if(dir==-1)//validDir=0 dir=-1，cheat命令
              cheatBuff.setCheat(input.getCheatWords(),Jack->getID());   //true:成功设置
       return validDirCommand;//执行了一次有效的移动命令
}

bool GameControl::command(Player* Jack){
       int sore=0,dir=0;bool validDirCommand=0;//用户不可以有无效操作
       if(cheatBuff.canCheat(gbox.onlyDir(&dir),Jack->getID())){
              do{ cheatBuff.playCheat(dir);validDirCommand=operMove(Jack);
              }while(!validDirCommand);
       }
       if(!validDirCommand) validDirCommand=operMove(Jack);//无cheat
       return validDirCommand;
}
inline void GameControl::welcome(const char*nameOfGame){
	printf("____________Welcome to %s____________\n",nameOfGame);
}
void GameControl::beforeGame(int argc,char *args[]){
       welcome("2048");
       gbox.initial(input.getTableSize(argc,args),input.getWinNum(argc,args));
       if(playerNum>1) cheatBuff.validateCheatBuff();
       cout<<playerNum<<"in base class\n";
       for(int id=0;id<playerNum;++id){
              playerList.push_back(Player(id));
       }
}
       SinglePlayerGameControl::SinglePlayerGameControl(int playerNum){
              this->playerNum = playerNum;
       }
       SinglePlayerGameControl::~SinglePlayerGameControl(){}
       void SinglePlayerGameControl::playGame(){
              gbox.firstHit();
              Player Jack;
              while(playing()) command(&Jack);          
       }
       bool SinglePlayerGameControl::playing(){
              switch (gbox.checkState()){
		       case victory:return infinitModle();
                     case fail:return 0;
	              default:return 1;
	       }        
       }
       bool SinglePlayerGameControl::infinitModle(){
              puts("~~~~~Congratulations!You get a Victory~~~~~");	
       	if(input.continuePlay()) return gbox.infinitGame();
       	else return 0;
       }
       void SinglePlayerGameControl::endOfGame(){
              puts("___________	Game Over!	___________");
              switch(gbox.checkState()){
                     case victory :if(gbox.infinitGameModel()) puts("~~~~~That's the end.Claps for you.~~~~~~");
                                   puts("~~~~~Congratulations to you!~~~~~");break;
                     case fail:    puts("-----Sorry about that,you are failed-----");break;
                     default:break;
              } 
       }
       
       MultiPlayerGameControl::MultiPlayerGameControl(int playerNum){
              this->playerNum=playerNum;
       }
       MultiPlayerGameControl::~MultiPlayerGameControl(){
       }
       void MultiPlayerGameControl::playGame(){
              gbox.firstHit();//初始局面
              vector<Player>::iterator operatorNow=playerList.begin();
              while(playing()){
                     operatorNow->printTurn();
                     if(command(&(*operatorNow))==0) continue;
                     operatorNow++;
                     if(operatorNow==playerList.end()) operatorNow=playerList.begin();
              }
       }
       bool MultiPlayerGameControl::playing(){
             return gbox.checkState()==play;
       }
       void MultiPlayerGameControl::endOfGame(){
                     int hightestSore=playerList[0].getSores(),winnerID=0;
                     for(int i=1;i<playerList.capacity();++i)
                     if(playerList[i].getSores()>hightestSore){
                            hightestSore=playerList[i].getSores();winnerID=i;
                     }
                     if(winnerID!=0||hightestSore>playerList[winnerID].getSores()) printf("%s wins the game!",playerList[winnerID].getName());
                     else puts("-----This is an even game.-----");
       }
       FileInOutGameControl::FileInOutGameControl(){
       }
       FileInOutGameControl::~FileInOutGameControl(){
       }