#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
using namespace std;
#define DOWN  "z"
#define UP "w"
#define LEFT "a"
#define RIGHT "s"
typedef std::map<int,string> Direction_int_string;
typedef std::pair<int,string> Pair_int_string;
typedef  Direction_int_string ::iterator Dir_iterator;
int main(){
        Direction_int_string Direction_map;
        Direction_map.insert(Pair_int_string (1,LEFT));
        Direction_map.insert(Pair_int_string (2,UP));
        Direction_map.insert(Pair_int_string (3,RIGHT));
        Direction_map.insert(Pair_int_string (4,DOWN));
        Direction_int_string ::iterator it;
        it=Direction_map.find(1);
        string com="w";
        for(Dir_iterator it=Direction_map.begin();it!=Direction_map.end();++it)
                if(it->second==com)
                {
                        cout<<"find!";
        cout<<it->first<<" "<<it->second<<endl;

                } 
        
        cout<<it->first<<" "<<it->second<<endl;


        return 0;
}