#include "player.h"
Player::Player(){sores=0;setName();}
void Player::printTurn(){cout<<"This is "<<name<<"'s turn:";}
void Player::cheers(){cout<<"Oh "<<name<<",you are successed!";}
void Player::setName(){
       printf("please enter the name of Player:");
       cin>>name;
}
Player::Player(int ID){
       name="Hansen";sores=0; this->ID=ID;
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
int Player::getID(){
       return ID;
}
int Player::getSores()const{
       return sores;
}
const char* Player::getName()const{
       return name.c_str();
}
