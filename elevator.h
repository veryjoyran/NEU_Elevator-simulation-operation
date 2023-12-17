#ifndef ELEVAOTR_H
#define ELEVAOTR_H
#define MAXPEOPLE 12
#include "list_basic.h"

class Elevator : public LinkList{
public:
    Elevator();
    ~Elevator();
    void SetFloor(int floor);
    int GetFloor();
    void SetDirection(int direction);
    int GetDirection();
    void SetState(int state);
    int GetState();
    void SetPeopleNum(int peopleNum);
    int GetPeopleNum();


private:
    int floor;
    int direction;
    int state;
    int peopleNum;
    int TargetFloor[14];


};

#endif