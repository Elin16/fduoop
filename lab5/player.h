#ifndef PLAYER_H
#define PLAYER_H
#include<cstring>
#include<iostream>
using namespace std;
class Player{
private:
       string com,name;
       int sores,ID;
public:
       Player(){sores=0;setName();}
       void cheers();
       void setName(); 
       int getID();
       Player* addSore(int sore);
       void printSores();
       void printTurn();
       Player(int ID);
       ~Player();
       Player(char* playerName); 
       int getSores ()const;
       const char* getName()const;  
};
#endif
