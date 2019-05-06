/**************************************************************************/
/* 环境: Ubuntu 18.04 编译器: g++ 7.3.0 编译工具: Make 4.1  ******************/
/* 作者: Shurui(Citrine) Gui              时间: 2019.04   ******************/
/**************************************************************************/

#include"fiveInARow.h"

using namespace fiveInARow;

typedef struct {
    int x, y;
} pos;

typedef struct site{
    int x, y;
    int nearNum;
    friend bool operator <(const site &a, const site &b){
        return a.nearNum < b.nearNum;
    }
} structSite;

/************************************困难度调节参数*************************************/
/***********************************最高: 7,2 ****************************************/
int maxDepth = 7;
int wideLevel = 2;

Chess mainChess;
Chess funcChess;
pos nextStep, currentStep;
int maxValue=-10000;

float Maximum_value(int, float, float);
float Minimum_value(int, float, float);
priority_queue<structSite> Action();

priority_queue<structSite> Action()
{
    priority_queue<structSite> siteQueue;
    for(int i=1; i<=15; i++){
        for(int j=1; j<=15; j++){
            if(funcChess.getTable(i, j) != NO_CHESS)
                continue;

            // 为空才执行
            //print("Action:%d, %d\n", i, j);
            structSite point = {x:i, y:j, nearNum:0};
            for(int i1=-wideLevel; i1<=wideLevel; i1++){
                for(int j1=-wideLevel; j1<=wideLevel; j1++){
                    if(i + i1 < 1 || i + i1 > 15 || j + j1 < 1 || j + j1 > 15)
                        continue;
                    int val = funcChess.getTable(i+i1, j+j1);
                    if(val == MAX_CHESS || val == MIN_CHESS)
                        point.nearNum++;
                }
            }
            if(point.nearNum != 0){
                point.nearNum += funcChess.getDangerRate(i, j);
                siteQueue.push(point);
            }
        }
    }
    return siteQueue;
}


float Maximum_value(int depth, float a, float b)
{
    //print("Max:%d\n", depth);
    funcChess.evaluate();
    if(fabs(funcChess.value()) > MAX_GOAL/2)
        return funcChess.value();
    if (depth >= maxDepth){
        return funcChess.value();
    }
    float val = -2*MAX_GOAL;
    priority_queue<structSite> siteQueue = Action();
    int size = (int)siteQueue.size();
    for(int i=0; i<size; i++){
        structSite point = siteQueue.top();
        siteQueue.pop();

        
        funcChess.setTable(point.x, point.y, MAX_CHESS);
        // funcChess.evaluate();
        // funcChess.show();
        // print("a:%f  b:%f  goal:%f\n", a, b, funcChess.value());
        float newVal = Minimum_value(depth + 1, a, b);
        funcChess.setTable(point.x, point.y, NO_CHESS);

        if(newVal > val){
            val = newVal;
        }
        if(val > b){
            return val;
        }
        if(val > a){
            a = val;
            if(depth == 1){
                nextStep.x = point.x;
                nextStep.y = point.y;
            }
        }
    }
    return val;
}

float Minimum_value(int depth, float a, float b)
{
    //print("Min:%d\n", depth);
    funcChess.evaluate();
    if(fabs(funcChess.value()) > MAX_GOAL/2)
        return funcChess.value();
    if (depth >= maxDepth){
        return funcChess.value();
    }
    
    float val = 2*MAX_GOAL;
    priority_queue<structSite> siteQueue = Action();
    int size = (int)siteQueue.size();
    for(int i=0; i<size; i++){
        print("%d", (int)siteQueue.size());
        structSite point = siteQueue.top();
        
        siteQueue.pop();

        funcChess.setTable(point.x, point.y, MIN_CHESS);
        // funcChess.evaluate();
        // funcChess.show();
        // print("a:%f  b:%f  goal:%f\n", a, b, funcChess.value());
        float newVal = Maximum_value(depth + 1, a, b);
        funcChess.setTable(point.x, point.y, NO_CHESS);

        if(newVal < val){
            val = newVal;
        }
        if(val < a){
            print("cut!!!!!!!!!\n");
            return val;
        }
        if(val < b){
            b = val;
        }
    }
    return val;
}

pos AI_where2choose()
{
    Maximum_value(1, -2*MAX_GOAL, 2*MAX_GOAL);
    
}

int main(int argc, char ** argv)
{
    int useFile = 0;
    funcChess.setTable(8, 8, MAX_CHESS);
    FILE *fp, *fop;
    //if((fp = fopen("data/input.txt", "r")) == NULL) cout << "Cannot open input file!" << endl;
    if((fop = fopen("data/output.txt", "w")) == NULL) cout << "Cannot open input file!" << endl;
    fprintf(fop, "        AI        ME\n");
    fprintf(fop, "   [%2d,%2d]", 8, 8);
    
        
    // funcChess.setTable(9, 9, MIN_CHESS);
    // funcChess.setTable(9, 7, MAX_CHESS);
    // funcChess.evaluate();
    // print("%f\n", funcChess.value());
    funcChess.show(8, 8);

    int userx, usery;
    
    while(1){
        scanf("%d %d", &userx, &usery);
        if(userx < 0 || userx > 16 || usery < 0 || usery > 16){
            cout << "Invalid!" << endl;
            char ch;
            while ((ch = getchar()) != EOF && ch != '\n');
            continue;
        }
        if (funcChess.getTable(userx, usery) != NO_CHESS){
            cout<< "You cannot set here!"<<endl;
            char ch;
            while ((ch = getchar()) != EOF && ch != '\n');
            continue;
        }
        funcChess.setTable(userx, usery, MIN_CHESS);
        fprintf(fop, "   [%2d,%2d]\n", userx, usery);
        funcChess.show(userx, usery);
        
        funcChess.evaluate();
        print("%f\n", funcChess.value());
        if(fabs(funcChess.value()) > MAX_GOAL/2){
            fprintf(fop, "\n\nUser win!");
            cout<< "Congratulation!"<<endl;    
            break;
        }
        AI_where2choose();
        funcChess.setTable(nextStep.x, nextStep.y, MAX_CHESS);
        fprintf(fop, "   [%2d,%2d]", nextStep.x, nextStep.y);
        funcChess.show(nextStep.x, nextStep.y);
        funcChess.evaluate();
        print("%f\n", funcChess.value());
        if(fabs(funcChess.value()) > MAX_GOAL/2){
            fprintf(fop, "\n\nAI win!");
            cout<< "Sorry, you loss..."<<endl;
            break;
        }
    }
    fclose(fp);
    fclose(fop);
    return 0;
}

