#include "player.h"
string Player::cheatWords="";
void Player::printTurn(){
       cout<<"This is "<<name<<"'s turn:";
}
void Player::cheers(){
       cout<<"Oh "<<name<<",you are successed!";
}
bool Player::dirCommand(int *dir){
       //turn（）不应该放在这里。只有double Player 才需要提示
       cin>>com;
       if(com=="c"){
              cin>>cheatWords;
              *dir=-1;
              cout<<"cheat sentence is "<<cheatWords<<endl;
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
void Player::setName(){
       printf("please enter the name of Player:");
       cin>>name;
}
Player::Player(int ID){
       name="Hansen";
       sores=0; 
       this->ID=ID;
       Direction_map.insert(Pair_int_string (1,LEFT));
       Direction_map.insert(Pair_int_string (2,UP));
       Direction_map.insert(Pair_int_string (3,RIGHT));
       Direction_map.insert(Pair_int_string (4,DOWN));
       setName();
}

Player::~Player(){
}

void Player::printSores(){
     cout<<name<<"'s sores now is "<<sores<<"\n\n";
}
Player* Player::addSore(int sore){
       sores+=sore;
       return this;
}
bool Player::continuePlay(){
       puts("You have succeeded get a victiory.");
       puts("Do you want to continue the game?");
       puts("enter y for continuing");
       puts("enter n for endding the game");
       string com;
       while(1){
              cin>>com;fflush(stdin);
              if(com==YES) return 1;
              else if(com==NO) return 0;
              else puts("Error input,please try agian.");
       }
       return 1;
}

int Player::getID(){
       return ID;
}
int Player::getSores()const{
       return sores;
}
const char* Player::getName()const{
       return name.c_str();
}
