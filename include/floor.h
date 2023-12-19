#ifndef FLOOR_H
#define FLOOR_H

#include "list_basic.h"
#include "people.h"

// Floor class is a queue of people
class Floor : private LinkList<People> {
public:
    Floor();
    ~Floor();
    void SetFloorNum(int floorNum);
    int GetFloorNum();
    int getPeopleNum();
    void pushPeople(People people);
    People popPeople();

private:
    int floorNum;
    int peopleNum;

};


#endif // !FLOOR_H