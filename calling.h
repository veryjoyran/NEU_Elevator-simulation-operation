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
private:
    int TargetfloorNum;
};

#endif