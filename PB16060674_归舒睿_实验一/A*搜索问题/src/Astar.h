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