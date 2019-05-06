# 五子棋实验报告

##### PB16060674-归舒睿

[TOC]

## 运行方法

根目录下：  
1：  
`./run.sh`  

2：  
```shell
make
./bin/fiveInARow
```

## 评分函数


### 得分单元

根据五子棋术语：活五，活/半/死 四，活/半/死 三，活/半/死 二，单，来作为加分单元。  
其分值根据重要性程度，人为设计。  
```C++
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
```

### 棋盘得分

根据遍历整个棋盘，行列正斜反斜中的得分单元进行计分，得分考虑到双三，双四等高度威胁，因此采用多个相同得分单元，会以个数n，单元得分*($n^m$)来计分（m是某参数，通常设为2）。  
然后正负得分进行加权和：goal = maxGoal * 1.2 - minGoal;  从加权可以看出AI偏向与进攻（1.2的偏高权重）  

## 剪枝策略

剪枝的作用是加快AI的响应速度，剪去不需要考虑的情况

### 剪枝优化

剪枝的效果取决于排序的好坏，于是尽量迅速的找到a和b的最好边界值可大幅度的剪枝。  
因此我的剪枝排序采取一种**威胁优先**的方式剪枝：  
* 每一步棋盘都会有个棋盘大小的dangeRate，其中每个坐标表明这那个点的**威胁**
* **威胁**来自于五子棋术语“威胁”的拓展：此处的威胁是得分单元连线上的两个端点，如：三个子的头尾两个端点。
* **威胁**的值也直接与产生威胁的得分单元的得分相关
* 于是，拓展节点的优先顺序便和威胁值相关，威胁值为0的位置是不考虑的，若想强行多考虑一圈，也可以调整`wideLevel`


