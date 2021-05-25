#include "player.h"
Player::Player(){scores=0;setName();}
void Player::printTurn(){cout<<"This is "<<name<<"'s turn:";}
void Player::cheers(){cout<<"Oh "<<name<<",you are successed!";}
void Player::setName(){
       printf("please enter the name of Player:");
       cin>>name;
}
Player::Player(int ID){
       name="Hansen";scores=0; this->ID=ID;
       setName();
}
Player::~Player(){
}

void Player::printScores(){
     cout<<name<<"'s scores now is "<<scores<<"\n\n";
}
Player* Player::addScore(int score){
       scores+=score;
       return this;
}
int Player::getID(){
       return ID;
}
int Player::getScores()const{
       return scores;
}
const char* Player::getName()const{
       return name.c_str();
}
