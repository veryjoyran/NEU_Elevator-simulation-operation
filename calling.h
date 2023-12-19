#ifndef CALLING_H
#define CALLING_H
#include "list_basic.h"

class Calling : private LinkList<int> {
public:
    Calling();
    ~Calling();
    void pushTargetFloor(int Targetfloor);
    int popTargetFloor();
    void sortedTargetFloor(int currentFloor,int direction);
    void CallingTravel();
    int GetTargetfloorNum();
    int GetElemAtIndex(int index);
private:
    int TargetfloorNum;
};

#endif