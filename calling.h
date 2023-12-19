#ifndef CALLING_H
#define CALLING_H
#include "list_basic.h"

class Calling : public LinkList<int> {
public:
    Calling();
    ~Calling();
    void pushTargetFloor(int Targetfloor);
    int popTargetFloor();
    void sortedTargetFloor(int currentFloor,int direction);
private:
    int TargetfloorNum;
};

#endif