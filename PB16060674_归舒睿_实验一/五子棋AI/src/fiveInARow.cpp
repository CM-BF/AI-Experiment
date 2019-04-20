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


int maxDepth = 5;
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
            for(int i1=-1; i1<=1; i1++){
                for(int j1=-1; j1<=1; j1++){
                    int val = funcChess.getTable(i+i1, j+j1);
                    if(val == MAX_CHESS || val == MIN_CHESS)
                        point.nearNum++;
                }
            }
            if(point.nearNum != 0)
                siteQueue.push(point);
        }
    }
    return siteQueue;
}


float Maximum_value(int depth, float a, float b)
{
    //print("Max:%d\n", depth);
    funcChess.evaluate();
    if(abs(funcChess.value()) > MAX_GOAL/2)
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
    if(abs(funcChess.value()) > MAX_GOAL/2)
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
    funcChess.setTable(nextStep.x, nextStep.y, MAX_CHESS);
    funcChess.show(nextStep.x, nextStep.y);
}

int main(int argc, char ** argv)
{
    funcChess.setTable(8, 8, MAX_CHESS);
    // funcChess.setTable(9, 9, MIN_CHESS);
    // funcChess.setTable(9, 7, MAX_CHESS);
    // funcChess.evaluate();
    // print("%f\n", funcChess.value());
    funcChess.show(8, 8);

    int userx, usery;
    while(1){
        scanf("%d %d", &userx, &usery);
        funcChess.setTable(userx, usery, MIN_CHESS);
        funcChess.show(userx, usery);
        funcChess.evaluate();
        print("%f\n", funcChess.value());
        if(abs(funcChess.value()) > MAX_GOAL/2)
            break;
        AI_where2choose();
        funcChess.evaluate();
        print("%f\n", funcChess.value());
        if(abs(funcChess.value()) > MAX_GOAL/2)
            break;
    }
    return 0;
}

