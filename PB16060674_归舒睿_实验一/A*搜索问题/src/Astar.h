/**************************************************************************/
/* 环境: Ubuntu 18.04 编译器: g++ 7.3.0 编译工具: Make 4.1  ******************/
/* 作者: Shurui(Citrine) Gui              时间: 2019.04   ******************/
/**************************************************************************/

#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<math.h>
#include<string>
using namespace std;

// Debug model
// #define DEBUG
#ifdef DEBUG
#define print(format, args...) printf(format, ##args)
#else
#define print(format, args...) 
#endif

namespace Astar{

int A[18][25] = {0};
typedef struct node{
    int parent;
    int x, y;
    char direction;
    int pathLen;
    int fvalue;
    friend bool operator <(const node &a, const node &b){
        return a.fvalue > b.fvalue;
    }
} structNode;
vector<structNode> scannedNode;
priority_queue<structNode> nodeQueue;

void inputInit(void);
void mazeOutput(int , int);
void AstarSearch();
int f(structNode);
inline void extend(structNode);




}