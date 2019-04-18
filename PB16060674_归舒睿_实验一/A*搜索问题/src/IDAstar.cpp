#include"IDAstar.h"
#include<time.h>
#include<unistd.h>

namespace IDAstar{

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

int f(int x, int y, int pathLen){
    // 搜索函数，曼哈顿距离作为启发函数
    return pathLen + (16 - x) + (24 - y);
}


void IDAstarSearch(int pathLen, string path, int x, int y){
    if(x == 16 && y == 24){
        finished = true;
        lastPath = path;
    }
    if(finished){
        return;
    }
    if(A[x][y] == 1){
        return;
    }
    if(f(x, y, pathLen) > fmax){
        return;
    }
    IDAstarSearch(pathLen+1, path+"U", x-1, y);
    IDAstarSearch(pathLen+1, path+"D", x+1, y);
    IDAstarSearch(pathLen+1, path+"L", x, y-1);
    IDAstarSearch(pathLen+1, path+"R", x, y+1);
}

}

int main(int argc, char **argv)
{
    IDAstar::inputInit();
    clock_t startTime = clock();
    IDAstar::fmax = 0;
    while(!IDAstar::finished){
        IDAstar::IDAstarSearch(0, "", 1, 0);
        IDAstar::fmax += 1;
    }
    // int x1=1, y1=0;
    // for(char c : IDAstar::lastPath){
    //     if(c == 'U')
    //         x1 -= 1;
    //     if(c == 'D')
    //         x1 += 1;
    //     if(c == 'L')
    //         y1 -= 1;
    //     if(c == 'R')
    //         y1 += 1;
    //     IDAstar::mazeOutput(x1, y1);
    //     sleep(1);
    // }
    clock_t endTime = clock();
    FILE *fp;
    if((fp = fopen("../data/output_IDA.txt", "w")) == NULL) cout<<"Cannot open output file!"<<endl;
    fprintf(fp, "%d\n%s\n%f", (int)IDAstar::lastPath.size(), IDAstar::lastPath.c_str(), (double)(endTime - startTime) / CLOCKS_PER_SEC);


    return 0;
}