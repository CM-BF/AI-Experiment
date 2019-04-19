#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_map>
#include<queue>
#include<string>
#include<math.h>
using namespace std;

// Debug model
#define DEBUG
#ifdef DEBUG
#define print(format, args...) printf(format, ##args)
#else
#define print(format, args...) 
#endif

namespace fiveInARow
{
#define MAX_GOAL 10000

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
#define GOAL_ALIVE_FOUR 500
#define GOAL_SEMI_FOUR 200
#define GOAL_DEAD_FOUR 40
#define GOAL_ALIVE_THREE 100
#define GOAL_SEMI_THREE 50
#define GOAL_DEAD_THREE 35
#define GOAL_ALIVE_TWO 30
#define GOAL_SEMI_TWO 10
#define GOAL_DEAD_TWO 5
#define GOAL_SINGLE 1

typedef struct {
    int x, y;
} pos;

typedef pos positions[5];

class Chess
{
private:
    int table[17][17];
    int maxTypeNum[11];
    int maxTypeGoal[11];
    int minTypeNum[11];
    int minTypeGoal[11];
    int goal; 
public:
    Chess(/* args */);
    void flush();
    void scan();
    void judge(int, int, int, int, int, string);
    void evaluate();
    void value();
    ~Chess();
};

void posClean(positions &p)
{
    for(int i=0; i<5; i++){
        p[i].x = -1;
        p[i].y = -1;
    }
}

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
    goal = 0;
}

inline void Chess::judge(int bx, int by, int ex, int ey, int type, string who)
{
    if(!who.compare("Max")){
        if(table[bx][by] != 0 && table[ex][ey] != 0)
            maxTypeNum[type]++;
        else{
            if(table[bx][by] != 0 || table[ex][ey] != 0)
                maxTypeNum[type + 1]++;
            else
                maxTypeNum[type + 2]++;
        }
    }
    if(!who.compare("Min")){
        if(table[bx][by] != 0 && table[ex][ey] != 0)
            minTypeNum[type]++;
        else{
            if(table[bx][by] != 0 || table[ex][ey] != 0)
                minTypeNum[type + 1]++;
            else
                minTypeNum[type + 2]++;
        }
    }
    
}

void Chess::scan()
{
    /****************************************************************************************/
    /********************************************遍历行***************************************/
    /****************************************************************************************/
    for(int i=1; i<16; i++){
        int count = 0, b = -1, e = -1;
        for(int j=1; j<16; j++){
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
        for(int j=1; j<16; j++){
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
    for(int j=1; j<16; j++){
        int count = 0, b = -1, e = -1;
        for(int i=1; i<16; i++){
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
        for(int i=1; i<16; i++){
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
                continue;
            }
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
                continue;
            }
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
                continue;
            }
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
    for(int k=1; k<=15; k++){
        int i=k, j=15;
        int count=0, b=-1, e=-1;
        while(i != 17){
            // 处理Max
            if(count == 0 && table[i][j] == 1){
                b = i;
                count++;
                continue;
            }
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

Chess::~Chess()
{
}







} // fiveInARow
