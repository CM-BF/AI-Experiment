/**************************************************************************/
/* 环境: Ubuntu 18.04 编译器: g++ 7.3.0 编译工具: Make 4.1  ******************/
/* 作者: Shurui(Citrine) Gui              时间: 2019.04   ******************/
/**************************************************************************/

#include"Astar.h"
#include<time.h>
#include<unistd.h>

namespace Astar{

void mazeOutput(int x, int y)
{
    for(int i=0; i<18; i++){
        for(int j=0; j<25; j++){
            if(i == x && j == y){
                printf("\033[31m%d \033[0m", A[i][j]);
            }else{
                printf("%d ", A[i][j]);
            }
        }
        printf("\n");
    }
}

void inputInit()
{
    FILE *fp;
    if ((fp = fopen("../data/input.txt", "r")) == NULL) cout << "Cannot open the file!" << endl;
    for (int i=0; i<18; i++){
        for(int j=0; j<25; j++){
            if(j != 24){
                fscanf(fp, "%d ", &A[i][j]);
            }else{
                fscanf(fp, "%d", &A[i][j]);
            }  
        }
        if(i != 17){
            fscanf(fp, "\n");
        }
    }
}

int f(structNode node){
    // 搜索函数，曼哈顿距离作为启发函数
    return node.pathLen + (16 - node.x) + (24 - node.y);
}

inline void extend(structNode topNode){
    if(A[topNode.x-1][topNode.y] == 0){
            structNode newNode={parent:(int)scannedNode.size(), x:topNode.x-1, y:topNode.y, direction: 'U', pathLen: topNode.pathLen+1, fvalue:0};
            newNode.fvalue = f(newNode);
            nodeQueue.push(newNode);
        }
        if(A[topNode.x+1][topNode.y] == 0){
            structNode newNode={parent:(int)scannedNode.size(), x:topNode.x+1, y:topNode.y, direction: 'D', pathLen: topNode.pathLen+1, fvalue:0};
            newNode.fvalue = f(newNode);
            nodeQueue.push(newNode);
        }
        if(A[topNode.x][topNode.y-1] == 0){
            structNode newNode={parent:(int)scannedNode.size(), x:topNode.x, y:topNode.y-1, direction: 'L', pathLen: topNode.pathLen+1, fvalue:0};
            newNode.fvalue = f(newNode);
            nodeQueue.push(newNode);
        }
        if(A[topNode.x][topNode.y+1] == 0){
            structNode newNode={parent:(int)scannedNode.size(), x:topNode.x, y:topNode.y+1, direction: 'R', pathLen: topNode.pathLen+1, fvalue:0};
            newNode.fvalue = f(newNode);
            nodeQueue.push(newNode);
        }
}

void AstarSearch(){
    clock_t startTime = clock();
    structNode begin={parent:-1, x:1, y:0, direction: ' ', pathLen:0, fvalue:0};
    begin.fvalue = f(begin);
    nodeQueue.push(begin);

    while(1){
        structNode topNode = nodeQueue.top();
        if(topNode.fvalue == topNode.pathLen){
            scannedNode.push_back(topNode);
            nodeQueue.pop();
            break;
        }
        extend(topNode);
        scannedNode.push_back(topNode);
        nodeQueue.pop();
    }
    clock_t endTime = clock();

    string path="";
    structNode backNode = scannedNode.back();
    print("%d\n", backNode.pathLen);
    while(backNode.pathLen != 0){
        path = backNode.direction + path;
        // mazeOutput(backNode.x, backNode.y);
        // sleep(1);
        backNode = scannedNode[backNode.parent];
    }
    FILE *fp;
    if((fp = fopen("../data/output_A.txt", "w")) == NULL) cout<<"Cannot open output file!"<<endl;
    fprintf(fp, "%d\n%s\n%f", (int)path.size(), path.c_str(), (double)(endTime - startTime) / CLOCKS_PER_SEC);

    print("finished!\n");
    

}

}

int main(int argc, char **argv)
{
    Astar::inputInit();
    Astar::AstarSearch();

    


    return 0;
}