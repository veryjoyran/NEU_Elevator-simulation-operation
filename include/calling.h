#ifndef CALLING_H
#define CALLING_H
#include "list_basic.h"

class Calling : private LinkList<int> {
public:
    Calling();
    ~Calling();
    void pushTargetFloor(int Targetfloor);
    int popTargetFloor();
    int getDataTargetFloor();
    void sortedTargetFloor(int currentFloor,int direction);
    void CallingTravel();
    int GetTargetfloorNum();
    int CallingGetElemAtIndex(int index);
    int GetMaxTargetFloor();
    int GetMinTargetFloor();
private:
    int TargetfloorNum;
};

#endif