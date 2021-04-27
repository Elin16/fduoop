## hyl2048
#### Elin Eason
### 两级客户程序员
#### main方法和GameControl方法都可以视为客户程序员
- hyl2048中，共有三个类：gamebox，player，GameControl。gamebox的实例**G**为游戏中的2048地图,关键成员变量是table[]，储存当前游戏进度，关键成员函数是moveDir()、checkState()。player的实例为游戏玩家，有name、sore两个成员变量，关键成员函数是dirCommand()。GameControl的实例为contr，相当于游戏中的“庄家”，关联起gamebox和player两个类。关键成员函数是command(player&Jack)。
    
- 在本程序中，GameControl可视为gamebox和player两个类的客户程序员。
  00）contr调用gamebox中的checkstate函数，得到游戏状态：playing/victory/fail
  + 游戏进行中playing：
  0）contr调用player类的成员函数获得**玩家指令**：
    1. 方向指令dir
    2. cheat指令
  1）contr将**方向指令dir**传递给G。方向指令作为参数调用gamebox的dirCommand()，得到此方向指令dir是否有效**vaildCommand**（对map产生了修改为有效），和此方向指令操作**得分sore**。
  2）contr将**得分sore**传递给player实例，并让player打印当前分数。
  3）若此方向指令有效，则contr调用另一位玩家获得玩家指令（回到0）；若方向指令无效，则指定当前玩家再次给出玩家指令（回到0）
  对cheat 命令：
    4）contr判断cheat命令是否生效，并进行相应标记。
    5）contr指定当前玩家再次给出玩家指令（回到0）
  + victory/fail：
    启动相应的游戏结束模式
    *若是单人模式，玩家获胜后可选择无限游戏模式*

### disadvantage
- 变量名、函数名、参数列表命名 过于**简略**，对程序可读性造成一定的影响
- GameBox 构造函数没有提供默认值，若客户程序员不调用initial函数，将导致**不可预料的后果**。
  根据对类的设计的清晰性要求，用户应当可以以不同组合、不同顺序、各种环境中综合使用多个类。所以设计类时，不应该限制用户如何以及何时使用该类；**设计属性和方法也应该使得功能的实现与它们出现的顺序无关。**
- table的实现：使用数组而非动态分配内存，缺乏灵活性

### advantage
#### 设计优点
- 封装性：主程序中仅仅使用到GameControl类的对象，其他类的内部成员和方法对用户实现了隐藏。若要修改方法实现，也不影响客户程序员的使用。这使类更加易于维护。
```c++
int main(int argc,char *args[]){
       GameControl contr;
       contr.beforeGame(argc,args);
       contr.playGame();
       return 0;
}
```
- 内聚性：每一个类仅描述一个单一的实体，如gamebox负责游戏的地图内容及其更新；player负责操作和计分。不把本应分属于不同对象的功能杂糅在一个笼统的状态类中，仅通过GameControl类在它们之间传递消息。接口简单明了，使代码易于理解、重用。（此处应有示意图）

- 一致性：变量和方法的命名采用了一致的风格，主要使用驼峰命名法。用完整有意义的英语单词表示了程序中的变量和函数，使得它们的作用看上去容易明白，代码清晰易读。

```c++
class GameControl{
       public:
              cheatstate cheatBuff;
              GameControl();
              virtual ~GameControl();
              void beforeGame(int argc,char *args[]);
              void playGame();
       private:
              bool  commend(player *Jack);
              inline void singleplayer();
              inline void doubleplayer();
              void playCheat(const int&dir);
              bool operMove(player *Jack);
              bool setCheat();
              bool playing();
              bool vicOfGame();
              bool infinitModle();
              bool endOfGame();
              void endOfGame(const player &p1,const player &p2);
              GameBox G; 
              int  playerNum,winNum,edgeSize;
              Direction_int_string Direction_map;
              int infinitGameModel;
              player* playerList;
              void welcome(const char*nameOfGame);
              void winNumModel(int argc,char *args[]);
              bool tableSize(int argc,char *args[]);
              void playerModel();
              bool setTableSize();
};
```
#### 使用优点
- 良好的用户交互:在游戏过程中给予玩家充足的操作提示。不仅改善了玩家体验，还减少了非法输入导致程序出错的可能。
- 实现了单人玩家无限游戏的模式：当gamebox中出现第一个2048时，游戏会提示玩家选择是否继续游戏。若继续，则进入无限游戏模式，游戏将会进行到没有合法的着法为止。



参考资料： Y.Daniel.Liaing
## 好的面向对象程序设计
### 类的设计原则
- 内聚性 描述一个单一的实体
- 一致性 标准设计风格和命名习惯
- 封装性 private
- 清晰性 清晰的合约，易于解释和理解。用户可以以不同组合、不同顺序、各种环境中综合使用多个类。设计类时，不应该限制用户如何以及何时使用该类；设计属性；**设计方法应该使得功能的实现与它们出现的顺序无关。**
### notes
- “这些方法是读取和修改半径的唯一途径，生产程序员完全控制了如何访问radius属性”
  “若要修改方法实现，也不影响客户程序员的使用。这使类更加易于维护”
*所有数据域都应该被声明为私有的，防止数据篡改并使类更加易于维护*
*构造方法和方法应该声明为公共的*
- 使用this引用数据域：使代码易于阅读，并且可以避免创建不必要的名字
- 类的合约、开发、使用
 ## 面向对象思考
### 类的抽象和封装 ：Abstract Data Type ADT
面向过程式编程是动作驱动的，数据和动作是分离的。面向对象编程的范式重点在于对象，动作和数据一起定义在对象中。
### 面向对象的思想
面向过程的范式重点是设计方法。面向对象的范式的重点在对象和对象上的操作。数据和方法耦合构成了对象。
### 类的关系
- 关联：有API接口
- 聚合：has-a，一个类中包含若干个其他的类的对象
- 组合：聚合形式的加强，被聚合的对象依赖聚合对象。name 之于 student 是组合；address 之于 student 是聚集。
  *组合和聚合的实现方法并无二致*
- 继承
