#include "player.h"
#include<iostream>
#include<cstring>
const int BUFSIZE=50;
using namespace std;
char player::cheatWords[]="";
void player::turn(){
       cout<<"This is "<<name<<"'s turn:";
}
void player::cheers(){
       cout<<"Oh "<<name<<",you are successed!";
}
bool player::myMove(int *dir){
       //turn（）不应该放在这里。只有double player 才需要提示
       cin>>com;
       if(com=="c"){
              cin>>cheatWords;
              *dir=-1;
              return 0;
       }
       Dir_iterator it;
       for(it=Direction_map.begin();it!=Direction_map.end();++it)
       if(it->second==com){
              *dir=it->first;return 1;//本次操作执行了移动
       }
       puts("error input");
       return 0;//本次操作没有执行移动
       
}
void player::setName(){
       printf("please enter the name of player:");
       cin>>com;
       delete [] name;
       name=new char[com.length()];
       for(int i=0;i<com.length();++i) name[i]=com[i]; 
}
player::player(){
       name=NULL;
       sores=0; 
       cheatingOther=0;
       beingCheated=0;
       Direction_map.insert(Pair_int_string (1,LEFT));
       Direction_map.insert(Pair_int_string (2,UP));
       Direction_map.insert(Pair_int_string (3,RIGHT));
       Direction_map.insert(Pair_int_string (4,DOWN));
       setName();
}

player::~player(){
       delete [] name;
       name=NULL;
}

void player::printSores(){
     cout<<name<<"'s sores now is "<<sores<<"\n\n";
}
void player::addSore(int sore){
       sores+=sore;
}
bool player::continuePlay(){
       puts("You have succeeded get a victiory.");
       puts("Do you want to continue the game?");
       puts("enter y for continuing");
       puts("enter n for endding the game");
       string com;
       while(1){
              cin>>com;fflush(stdin);
              if(com==YES) return 1;
              else if(com=="NO") return 0;
              else puts("Error input,please try agian.");
       }
       return 1;
}
void player::getBeingCheated(){
       beingCheated=1;
}