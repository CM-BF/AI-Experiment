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
#define DEBUG
#ifdef DEBUG
#define print(format, args...) printf(format, ##args)
#else
#define print(format, args...) 
#endif

namespace IDAstar{

int A[18][25] = {0};
int fmax;
bool finished = false;
string lastPath;

void inputInit(void);
void mazeOutput(int , int);
void IDAstarSearch(int, string, int, int);
int f(int, int);




}