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
       string com;
       void cheers();
       void setName(); 
public:
       static bool continuePlay();
       char *name;
       int sores;
       bool cheatingOther;
       bool beingCheated;
       player* addSore(int sore);
       void printSores();
       bool myMove(int *dir);
       void turn();
       void getBeingCheated();
       player();
       ~player();
       player(char* playerName);
       static string cheatWords;
       static void winner(const player &p1,const player &p2);
       friend class gameplay;
       Direction_int_string Direction_map;
};
#endif
