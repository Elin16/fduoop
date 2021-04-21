#ifndef PLAYER_H
#define PLAYER_H
#define DOWN  "z"
#define UP "w"
#define LEFT "a"
#define RIGHT "s"
#define YES "y"
#define NO "n"
#include<iostream>
#include<cstring>
using namespace std;
class player
{
private:
       char *name;
       int sores;
       char com[50];
       void myNameIs(char *playerName);
       void cheers();
       static bool continuePlay();
       
public:
       bool cheatingOther;
       bool beingCheated;
       void addSore(int sore);
       void printSores();
       void setName(); 
       bool myMove(int *dir);
       void turn();
       void getBeingCheated();
       player();
       ~player();
       player(char* playerName);
       static char cheatWords[1024];
       friend class GameBox;
};
#endif
