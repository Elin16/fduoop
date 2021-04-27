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
class Player{
private:
       string com;
       bool cheatingOthers;
       string name;
       int sores;
       Direction_int_string Direction_map;
public:
       void cheers();
       void setName(); 
       static bool continuePlay();
       void setCheatingOthers(bool cheatingOthers);
       bool getCheatingOthers();
       Player* addSore(int sore);
       void printSores();
       bool dirCommand(int *dir);
       void printTurn();
       Player();
       ~Player();
       Player(char* playerName);
       static string cheatWords;
       static void winner(const Player &p1,const Player &p2);
       int getSores ()const;
       const char* getName()const;   
};
#endif
