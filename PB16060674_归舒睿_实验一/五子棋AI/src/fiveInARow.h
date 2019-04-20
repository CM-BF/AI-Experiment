#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_map>
#include<queue>
#include<string>
#include<math.h>
using namespace std;

// Debug model
//#define DEBUG
#ifdef DEBUG
#define print(format, args...) printf(format, ##args)
#else
#define print(format, args...) 
#endif

namespace fiveInARow
{
#define MAX_GOAL 100000

#define TYPE_FIVE 0
#define TYPE_ALIVE_FOUR 1
#define TYPE_SEMI_FOUR 2
#define TYPE_DEAD_FOUR 3
#define TYPE_ALIVE_THREE 4
#define TYPE_SEMI_THREE 5
#define TYPE_DEAD_THREE 6
#define TYPE_ALIVE_TWO 7
#define TYPE_SEMI_TWO 8
#define TYPE_DEAD_TWO 9
#define TYPE_SINGLE 10

#define GOAL_FIVE MAX_GOAL
#define GOAL_ALIVE_FOUR 6000
#define GOAL_SEMI_FOUR 1000
#define GOAL_DEAD_FOUR 50
#define GOAL_ALIVE_THREE 500
#define GOAL_SEMI_THREE 100
#define GOAL_DEAD_THREE 35
#define GOAL_ALIVE_TWO 30
#define GOAL_SEMI_TWO 10
#define GOAL_DEAD_TWO 5
#define GOAL_SINGLE 0

#define MAX_CHESS 1
#define MIN_CHESS 2
#define NO_CHESS 0


class Chess
{
private:
    int table[17][17];
    int maxTypeNum[11];
    float maxTypeGoal[11];
    int minTypeNum[11];
    float minTypeGoal[11];
    float goal; 
    int dangerRate[17][17];
    unordered_map<int, int> type2goal;
public:
    Chess(/* args */);
    void flush();
    void scan();
    void judge(int, int, int, int, int, string);
    void evaluate();
    float value();
    void show(int, int);
    int getTable(int, int);
    void setTable(int, int, int);
    int getDangerRate(int, int);
    ~Chess();
};


Chess::Chess(/* args */)
{
    for(int i=0; i<17; i++)
        for(int j=0; j<17; j++)
            if(i == 0 || j == 0 || i == 16 || j == 16){
                table[i][j] = 8;
            }else{
                table[i][j] = 0;
            }
                
    for(int i=0; i<11; i++){
        maxTypeNum[i] = 0;
        maxTypeGoal[i] = 0;
        minTypeNum[i] = 0;
        minTypeGoal[i] = 0;
    }

    for(int i=0; i<17; i++){
        for(int j=0; j<17; j++){
            dangerRate[i][j] = 0;
        }
    }

    type2goal.insert({TYPE_SINGLE, GOAL_SINGLE});
    type2goal.insert({TYPE_DEAD_TWO, GOAL_DEAD_TWO});
    type2goal.insert({TYPE_SEMI_TWO, GOAL_SEMI_TWO});
    type2goal.insert({TYPE_ALIVE_TWO, GOAL_ALIVE_TWO});
    type2goal.insert({TYPE_DEAD_THREE, GOAL_DEAD_THREE});
    type2goal.insert({TYPE_SEMI_THREE, GOAL_SEMI_THREE});
    type2goal.insert({TYPE_ALIVE_THREE, GOAL_ALIVE_THREE});
    type2goal.insert({TYPE_DEAD_FOUR, GOAL_DEAD_FOUR});
    type2goal.insert({TYPE_SEMI_FOUR, GOAL_SEMI_FOUR});
    type2goal.insert({TYPE_ALIVE_FOUR, GOAL_ALIVE_FOUR});
    type2goal.insert({TYPE_FIVE, GOAL_FIVE});
    
        
    goal = 0;
}

void Chess::flush()
{
    for(int i=0; i<11; i++){
        maxTypeNum[i] = 0;
        maxTypeGoal[i] = 0;
        minTypeNum[i] = 0;
        minTypeGoal[i] = 0;
    }
    for(int i=0; i<17; i++){
        for(int j=0; j<17; j++){
            dangerRate[i][j] = 0;
        }
    }
    goal = 0;
}

int Chess::getDangerRate(int x, int y)
{
    return dangerRate[x][y];
}


inline void Chess::judge(int bx, int by, int ex, int ey, int type, string who)
{
    if(!who.compare("Max")){
        if(table[bx][by] != 0 && table[ex][ey] != 0){
            maxTypeNum[type]++;
            dangerRate[bx][by] = type2goal.at(type);
            dangerRate[ex][ey] = type2goal.at(type);
        }else{
            if(table[bx][by] != 0 || table[ex][ey] != 0){
                maxTypeNum[type - 1]++;
                dangerRate[bx][by] = type2goal.at(type - 1);
                dangerRate[ex][ey] = type2goal.at(type - 1);
            }else{
                maxTypeNum[type - 2]++;
                dangerRate[bx][by] = type2goal.at(type - 2);
                dangerRate[ex][ey] = type2goal.at(type - 2);
            }
        }
    }
    if(!who.compare("Min")){
        if(table[bx][by] != 0 && table[ex][ey] != 0){
            minTypeNum[type]++;
            dangerRate[bx][by] = type2goal.at(type);
            dangerRate[ex][ey] = type2goal.at(type);
        }else{
            if(table[bx][by] != 0 || table[ex][ey] != 0){
                minTypeNum[type - 1]++;
                dangerRate[bx][by] = type2goal.at(type - 1);
                dangerRate[ex][ey] = type2goal.at(type - 1);
            }else{
                minTypeNum[type - 2]++;
                dangerRate[bx][by] = type2goal.at(type - 2);
                dangerRate[ex][ey] = type2goal.at(type - 2);
            }
        }
    }
}

void Chess::scan()
{
    /****************************************************************************************/
    /********************************************遍历行***************************************/
    /****************************************************************************************/
    for(int i=0; i<17; i++){
        int count = 0, b = -1, e = -1;
        for(int j=0; j<17; j++){
            // deal with Max 
            if(count == 0 && table[i][j] == 1){
                b = j;
                count++;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 1){
                    count++;
                }else{
                    e = j - 1;
                    switch (count)
                    {
                        case 1:
                            maxTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(i, b-1, i, e+1, TYPE_DEAD_TWO, "Max");
                            break;
                        case 3:
                            judge(i, b-1, i, e+1, TYPE_DEAD_THREE, "Max");
                            break;
                        case 4:
                            judge(i, b-1, i, e+1, TYPE_DEAD_FOUR, "Max");
                            break;
                        case 5:
                            maxTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
        }
        count = 0;
        b = -1;
        e = -1;
        for(int j=0; j<17; j++){
            // deal with Min
            if(count == 0 && table[i][j] == 2){
                b = j;
                count++;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 2){
                    count++;
                }else{
                    e = j - 1;
                    switch (count)
                    {
                        case 1:
                            minTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(i, b-1, i, e+1, TYPE_DEAD_TWO, "Min");
                            break;
                        case 3:
                            judge(i, b-1, i, e+1, TYPE_DEAD_THREE, "Min");
                            break;
                        case 4:
                            judge(i, b-1, i, e+1, TYPE_DEAD_FOUR, "Min");
                            break;
                        case 5:
                            minTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
        }
    }
    /****************************************************************************************/
    /********************************************遍历列***************************************/
    /****************************************************************************************/
    for(int j=0; j<17; j++){
        int count = 0, b = -1, e = -1;
        for(int i=0; i<17; i++){
            // deal with Max 
            if(count == 0 && table[i][j] == 1){
                b = i;
                count++;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 1){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            maxTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, j, e+1, j, TYPE_DEAD_TWO, "Max");
                            break;
                        case 3:
                            judge(b-1, j, e+1, j, TYPE_DEAD_THREE, "Max");
                            break;
                        case 4:
                            judge(b-1, j, e+1, j, TYPE_DEAD_FOUR, "Max");
                            break;
                        case 5:
                            maxTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
        }
        count = 0;
        b = -1;
        e = -1;
        for(int i=0; i<17; i++){
            // deal with Min
            if(count == 0 && table[i][j] == 2){
                b = i;
                count++;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 2){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            minTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, j, e+1, j, TYPE_DEAD_TWO, "Min");
                            break;
                        case 3:
                            judge(b-1, j, e+1, j, TYPE_DEAD_THREE, "Min");
                            break;
                        case 4:
                            judge(b-1, j, e+1, j, TYPE_DEAD_FOUR, "Min");
                            break;
                        case 5:
                            minTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
        }
    }

    /****************************************************************************************/
    /******************************************遍历顺对角线************************************/
    /****************************************************************************************/
    for(int k=15; k>=1; k--){
        int i=k, j=1;
        int count=0, b=-1, e=-1;
        while(i != 17){
            // 处理Max
            if(count == 0 && table[i][j] == 1){
                b = i;
                count++;
                i++;
                j++;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 1){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            maxTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_TWO, "Max");
                            break;
                        case 3:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_THREE, "Max");
                            break;
                        case 4:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_FOUR, "Max");
                            break;
                        case 5:
                            maxTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
            i++;
            j++;
        }
        i=k; 
        j=1;
        count=0;
        b=-1;
        e=-1;
        while(i != 17){
            // 处理Min
            if(count == 0 && table[i][j] == 2){
                b = i;
                count++;
                i++;
                j++;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 2){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            minTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_TWO, "Min");
                            break;
                        case 3:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_THREE, "Min");
                            break;
                        case 4:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_FOUR, "Min");
                            break;
                        case 5:
                            minTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
            i++;
            j++;
        }
    }



    /****************************************************************************************/
    /******************************************遍历顺对角线2***********************************/
    /****************************************************************************************/
    for(int k=2; k<=15; k++){
        int i=1, j=k;
        int count=0, b=-1, e=-1;
        while(j != 17){
            // 处理Max
            if(count == 0 && table[i][j] == 1){
                b = i;
                count++;
                i++;
                j++;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 1){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            maxTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_TWO, "Max");
                            break;
                        case 3:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_THREE, "Max");
                            break;
                        case 4:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_FOUR, "Max");
                            break;
                        case 5:
                            maxTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
            i++;
            j++;
        }
        i=1; 
        j=k;
        count=0;
        b=-1;
        e=-1;
        while(j != 17){
            // 处理Min
            if(count == 0 && table[i][j] == 2){
                b = i;
                count++;
                i++;
                j++;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 2){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            minTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_TWO, "Min");
                            break;
                        case 3:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_THREE, "Min");
                            break;
                        case 4:
                            judge(b-1, b-1-i+j, e+1, e+1-i+j, TYPE_DEAD_FOUR, "Min");
                            break;
                        case 5:
                            minTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
            i++;
            j++;
        }
    }








    /****************************************************************************************/
    /******************************************遍历逆对角线************************************/
    /****************************************************************************************/
    for(int k=1; k<=15; k++){
        int i=1, j=k;
        int count=0, b=-1, e=-1;
        while(j != -1){
            // 处理Max
            if(count == 0 && table[i][j] == 1){
                b = i;
                count++;
                i++;
                j--;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 1){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            maxTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_TWO, "Max");
                            break;
                        case 3:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_THREE, "Max");
                            break;
                        case 4:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_FOUR, "Max");
                            break;
                        case 5:
                            maxTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
            i++;
            j--;
        }
        i=1; 
        j=k;
        count=0;
        b=-1;
        e=-1;
        while(j != -1){
            // 处理Min
            if(count == 0 && table[i][j] == 2){
                b = i;
                count++;
                i++;
                j--;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 2){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            minTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_TWO, "Min");
                            break;
                        case 3:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_THREE, "Min");
                            break;
                        case 4:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_FOUR, "Min");
                            break;
                        case 5:
                            minTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
            i++;
            j--;
        }
    }



    /****************************************************************************************/
    /******************************************遍历逆对角线2***********************************/
    /****************************************************************************************/
    for(int k=2; k<=15; k++){
        int i=k, j=15;
        int count=0, b=-1, e=-1;
        while(i != 17){
            // 处理Max
            if(count == 0 && table[i][j] == 1){
                b = i;
                count++;
                i++;
                j--;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 1){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            maxTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_TWO, "Max");
                            break;
                        case 3:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_THREE, "Max");
                            break;
                        case 4:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_FOUR, "Max");
                            break;
                        case 5:
                            maxTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
            i++;
            j--;
        }
        i=k; 
        j=15;
        count=0;
        b=-1;
        e=-1;
        while(i != 17){
            // 处理Min
            if(count == 0 && table[i][j] == 2){
                b = i;
                count++;
                i++;
                j--;
                continue;
            }
            if(count != 0){
                if(table[i][j] == 2){
                    count++;
                }else{
                    e = i - 1;
                    switch (count)
                    {
                        case 1:
                            minTypeNum[TYPE_SINGLE]++;
                            break;
                        case 2:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_TWO, "Min");
                            break;
                        case 3:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_THREE, "Min");
                            break;
                        case 4:
                            judge(b-1, i+j-(b-1), e+1, i+j-(e+1), TYPE_DEAD_FOUR, "Min");
                            break;
                        case 5:
                            minTypeNum[TYPE_FIVE]++;
                            break;
                        default:
                            break;
                    }
                    count = 0;
                    b = -1;
                    e = -1;
                }
            }
            i++;
            j--;
        }
    }
}

void Chess::evaluate()
{
    flush();
    scan();
    // print("max:\n");
    // for(int i=0; i<11; i++){
    //     print("%d\n", maxTypeNum[i]);
    // }
    // print("min:\n");
    // for(int i=0; i<11; i++){
    //     print("%d\n", minTypeNum[i]);
    // }

    maxTypeGoal[TYPE_SINGLE] = pow(maxTypeNum[TYPE_SINGLE], 2) * GOAL_SINGLE;
    maxTypeGoal[TYPE_DEAD_TWO] = pow(maxTypeNum[TYPE_DEAD_TWO], 2) * GOAL_DEAD_TWO;
    maxTypeGoal[TYPE_SEMI_TWO] = pow(maxTypeNum[TYPE_SEMI_TWO], 2) * GOAL_SEMI_TWO; 
    maxTypeGoal[TYPE_ALIVE_TWO] = pow(maxTypeNum[TYPE_ALIVE_TWO], 2) * GOAL_ALIVE_TWO;
    maxTypeGoal[TYPE_DEAD_THREE] = pow(maxTypeNum[TYPE_DEAD_THREE], 2) * GOAL_DEAD_THREE;
    maxTypeGoal[TYPE_SEMI_THREE] = pow(maxTypeNum[TYPE_SEMI_THREE], 2) * GOAL_SEMI_THREE;
    maxTypeGoal[TYPE_ALIVE_THREE] = pow(maxTypeNum[TYPE_ALIVE_THREE], 2) * GOAL_ALIVE_THREE;
    maxTypeGoal[TYPE_DEAD_FOUR] = pow(maxTypeNum[TYPE_DEAD_FOUR], 2) * GOAL_DEAD_FOUR;
    maxTypeGoal[TYPE_SEMI_FOUR] = pow(maxTypeNum[TYPE_SEMI_FOUR], 2) * GOAL_SEMI_FOUR;
    maxTypeGoal[TYPE_ALIVE_FOUR] = pow(maxTypeNum[TYPE_ALIVE_FOUR], 2) * GOAL_ALIVE_FOUR;
    maxTypeGoal[TYPE_FIVE] = pow(maxTypeNum[TYPE_FIVE], 2) * GOAL_FIVE;

    minTypeGoal[TYPE_SINGLE] = pow(minTypeNum[TYPE_SINGLE], 2) * GOAL_SINGLE;
    minTypeGoal[TYPE_DEAD_TWO] = pow(minTypeNum[TYPE_DEAD_TWO], 2) * GOAL_DEAD_TWO;
    minTypeGoal[TYPE_SEMI_TWO] = pow(minTypeNum[TYPE_SEMI_TWO], 2) * GOAL_SEMI_TWO; 
    minTypeGoal[TYPE_ALIVE_TWO] = pow(minTypeNum[TYPE_ALIVE_TWO], 2) * GOAL_ALIVE_TWO;
    minTypeGoal[TYPE_DEAD_THREE] = pow(minTypeNum[TYPE_DEAD_THREE], 2) * GOAL_DEAD_THREE;
    minTypeGoal[TYPE_SEMI_THREE] = pow(minTypeNum[TYPE_SEMI_THREE], 2) * GOAL_SEMI_THREE;
    minTypeGoal[TYPE_ALIVE_THREE] = pow(minTypeNum[TYPE_ALIVE_THREE], 2) * GOAL_ALIVE_THREE;
    minTypeGoal[TYPE_DEAD_FOUR] = pow(minTypeNum[TYPE_DEAD_FOUR], 2) * GOAL_DEAD_FOUR;
    minTypeGoal[TYPE_SEMI_FOUR] = pow(minTypeNum[TYPE_SEMI_FOUR], 2) * GOAL_SEMI_FOUR;
    minTypeGoal[TYPE_ALIVE_FOUR] = pow(minTypeNum[TYPE_ALIVE_FOUR], 2) * GOAL_ALIVE_FOUR;
    minTypeGoal[TYPE_FIVE] = pow(minTypeNum[TYPE_FIVE], 2) * GOAL_FIVE;

    float maxGoal=0, minGoal=0;
    for(auto goal : maxTypeGoal){
        maxGoal += goal;
    }
    for(auto goal : minTypeGoal){
        minGoal += goal;
    }
    //计算出goal的值
    goal = maxGoal * 1.2 - minGoal;
}

float Chess::value(){
    return goal;
}

void Chess::show(int x=0, int y=0){
    for(int i=-1; i<17; i++){
        if(i > 0){
            printf("\033[31m%2d \033[0m", i);
        }else{
            printf("   ");
        }
    }
    printf("\n");
    for(int i=0; i<17; i++){
        if(i > 0){
            printf("\033[31m%2d \033[0m", i);
        }else{
            printf("   ");
        }
        for(int j=0; j<17; j++){
            if(i == x && j == y){
                printf("\033[31m%2d \033[0m", table[i][j]);
            }else
            {
                if(table[i][j] == MAX_CHESS){
                    printf("\033[32m%2d \033[0m", table[i][j]);
                }else if (table[i][j] == MIN_CHESS){
                    printf("\033[33m%2d \033[0m", table[i][j]);
                }else{
                    printf("%2d ", table[i][j]);
                }
            }     
        }
        printf("\n");
    }
}

inline int Chess::getTable(int x, int y)
{
    return table[x][y];
}

inline void Chess::setTable(int x, int y, int value)
{
    table[x][y] = value;
}

Chess::~Chess()
{
}







} // fiveInARow
