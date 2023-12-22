#ifndef ELEVAOTR_H
#define ELEVAOTR_H

#define MAXPEOPLE 12
#define MaxFloor 14
#include "list_basic.h"
#include "people.h"
#include "floor.h"
#include "calling.h"
class Elevator {
public:
    Elevator();
    ~Elevator();
    void SetFloor(int floor);
    int GetFloor();
    void SetState(int state);
    int GetState();
    void SetPeopleNum(int peopleNum);
    int GetPeopleNum();
    int getDirection(Calling &calling,int currentFloor);
    void setDirection(int direction);
    People* GetTargetFloor();


    void addPeople(People people,People* TargetFloor); //添加乘客
    void deletePeople(People* TargetFloor); //删除乘客
    void sortedTargetFloor(int currentFloor,int direction,People* TargetFloor,int peopleNum); //对目标楼层进行排序




private:
    int currentFloor;
    int state;     //0表示电梯静止，1表示电梯上升，-1表示电梯下降，小于10正数和负数表示正在运行
    int peopleNum;
    int direction; //1表示电梯上升，2表示电梯下降
    People TargetFloor[MAXPEOPLE];

};

#endif