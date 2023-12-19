#ifndef ELEVAOTR_H
#define ELEVAOTR_H
#define MAXPEOPLE 12
#define MaxFloor 14
#include "list_basic.h"
#include "people.h"
#include "floor.h"
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
    int getDirection();
    People* GetTargetFloor();


    void addPeople(People people,People* TargetFloor); //添加乘客
    void deletePeople(People* TargetFloor); //删除乘客
    void sortedTargetFloor(int currentFloor,int direction,People* TargetFloor);




private:
    int currentFloor;
    int state;     //0表示电梯静止，1表示电梯上升，2表示电梯下降
    int peopleNum;
    int direction; //1表示电梯上升，2表示电梯下降
    People TargetFloor[MAXPEOPLE];

};

#endif