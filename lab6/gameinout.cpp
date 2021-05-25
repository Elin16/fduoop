#include "gameinout.h"
GameInOut::GameInOut(){
                DirectionMap.insert(PairIntString (1,LEFT));
                DirectionMap.insert(PairIntString (2,UP));
                DirectionMap.insert(PairIntString (3,RIGHT));
                DirectionMap.insert(PairIntString (4,DOWN));
        }
        int GameInOut::getPlayerNum(){
                puts("Please choose the Player modle of game:\nSingle Player: enter 1\nDouble Player: enter 2\n");
                printf("Make your choice:");
                int com,validCom=0,playerNum,validInput; 
                do{     validInput=scanf("%d",&com);fflush(stdin);
                        if(validInput&&0<com&&com<3) playerNum=com,validCom=1;
                        else  printf("error input\nplease choose again:");
                }while(!validCom);
                return playerNum;
        }
        int  GameInOut::getWinNum(int argc,char*args[]){
                int winNum=WIN_NUM;
                for(int i=0;i<argc;++i)
                if(strcmp(args[i],TEST_MODLE)==0){
                     winNum=TEST_WIN_NUM;break;//64
                }
                return winNum;
        }
        int GameInOut::getTableSize(int argc,char *args[]){
                int edgeSize;
                for(int i=0;i<argc;++i)
                if(strcmp(args[i],TABLE_MODLE)==0&&i+1<argc){
                     edgeSize=atoi(args[i+1]);
                     if(1<edgeSize&&edgeSize<6) return edgeSize;
                }
                while(true){
                        puts("The table size is illegaled.\nplease set the table size(choose among 2*2,3*3,4*4,5*5)");
                        printf("enter the length of the table edge(2/3/4/5):");
                        validInput=scanf("%d",&edgeSize);fflush(stdin);
                        if(validInput&&1<edgeSize&&edgeSize<6) return edgeSize;
                }
        }
        int GameInOut::getTableSize(){
                int edgeSize;
                validInput=scanf("%d",&edgeSize);fflush(stdin);
                if(validInput&&1<edgeSize&&edgeSize<6) return edgeSize;return 4;
        }
        bool GameInOut::usrCommandOfDir(int*dir){
                cin>>com;
                if(com=="c"){
                        cin>>cheatWords;
                        *dir=-1;
                        cout<<"cheat sentence is "<<cheatWords<<endl;
                        return 0;
                }
                for(DirIterator it=DirectionMap.begin();it!=DirectionMap.end();++it)
                if(it->second==com){
                        *dir=it->first;return 1;//本次操作执行了移动
                }
                puts("error input");
                return 0;//本次操作没有执行移动  
        }
        bool GameInOut::continuePlay(){
                puts("You have succeeded get a victiory\nDo you want to continue the game?");
                puts("enter y for continuing\nenter n for endding the game:");
                while(1){
                        cin>>com;fflush(stdin);
                        if(com==YES) return 1;else if(com==NO) return 0;
                        else puts("Error input,please try agian.");
                }      
        }
        char* GameInOut::getFileName(int argc,char*args[],const char *command){
                char *FileName=NULL;
                for(int i=0;i<argc;++i)
                if(strcmp(args[i],command)==0){
                        FileName=args[i+1];
                }
                return FileName;
        }
        
        string GameInOut::getCheatWords(){return cheatWords;}