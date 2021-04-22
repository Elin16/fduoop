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
#include<map>
using namespace std;
typedef std::map<int,string> Direction_int_string;
typedef std::pair<int,string> Pair_int_string;
typedef  Direction_int_string ::iterator Dir_iterator;
class player
{
private:
       char *name;
       int sores;
       string com;
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
       static string cheatWords;
       friend class GameBox;
       Direction_int_string Direction_map;
};
#endif
