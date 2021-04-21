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
       fgets(com,BUFSIZE,stdin);
       com[strlen(com)-1]='\0';
       *dir=0;
       if(strcmp(com,UP)==0){
              *dir=2;
       }else if(strcmp(com,DOWN)==0){
              *dir=4;
	}else if(strcmp(com,LEFT)==0){
              *dir=1;
	}else if(strcmp(com,RIGHT)==0) {
              *dir=3;
	}else if(com[0]=='c'){//cheatcommend
              int k=1;
              while(k<strlen(com)&&(com[k]==' '||com[k]=='\t')) k++;
              for(int i=k;i<strlen(com);++i) 
                     cheatWords[i-1]=com[i];
              cheatWords[strlen(cheatWords)]='\0';
              *dir=-1;
              return 0;//本次操作没有执行移动
       }else{
              puts("error input");
              return 0;
       }
       return 1;//本次操作执行了移动
}
void player::setName(){
       printf("please enter the name of player:");
       fgets(com,BUFSIZE,stdin);
       com[strlen(com)-1]='\0';
       myNameIs(com);
}
player::player(){
       name=NULL;
       sores=0; 
}
player::player(char* playerName){
       sores=0;
       cheatingOther=0;
       beingCheated=0;
       name=new char[strlen(playerName)];
       for(int i=0;i<strlen(playerName);++i) name[i]=playerName[i]; 
       setName();
}

player::~player(){
       delete [] name;
       name=NULL;
}
void player::myNameIs(char *playerName){
       delete [] name;
       name=new char[strlen(playerName)];
       for(int i=0;i<strlen(playerName);++i) name[i]=playerName[i]; 
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
       char com[BUFSIZE];
       while(1){
              fgets(com,BUFSIZE,stdin);
              com[strlen(com)-1]='\0';
              if(strcmp(com,YES)==0){
                    return 1;
              }else
              if(strcmp(com,NO)==0){
                     return 0;
              }else{
                     puts("Error input,please try agian.");
              }
       }
       return 1;
}
void player::getBeingCheated(){
       beingCheated=1;
}