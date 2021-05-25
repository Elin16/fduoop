#ifndef PLAYER_H
#define PLAYER_H
#include<cstring>
#include<iostream>
using namespace std;
class Player{
private:
       string com,name;
       int scores,ID;
public:
       Player();
       void cheers();
       void setName(); 
       int getID();
       Player* addScore(int score);
       void printScores();
       void printTurn();
       Player(int ID);
       ~Player();
       Player(char* playerName); 
       int getScores ()const;
       const char* getName()const;  
};
#endif
