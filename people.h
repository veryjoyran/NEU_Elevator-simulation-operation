#ifndef PEOPLE_H
#define PEOPLE_H

#include "list_basic.h"
#include <string>

using std::string;

class People {
public:
    People()=default;
    People(string id, int ReachTime);
    ~People();
    string GetId();
    int GetReachTime();
    void SetId(string id);
    void SetReachTime(int ReachTime);
    void SetTargetFloor(int TargetFloor);
    int GetTargetFloor();
    void SetStartFloor(int StartFloor);
    int GetStartFloor();
    
private:
    string id;
    int ReachTime;
    int TargetFloor;
    int StartFloor;
};

#endif