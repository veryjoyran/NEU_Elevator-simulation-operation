#include "floor.h"

Floor::Floor() {
    peopleNum = 0;
}

Floor::~Floor() {}

void Floor::SetFloorNum(int floorNum) {
    this->floorNum = floorNum;
}

int Floor::GetFloorNum() {
    return floorNum;
}

int Floor::getPeopleNum() {
    return peopleNum;
}

void Floor::pushPeople(People people) {
    this->InsertElemAtEnd(people);
    peopleNum++;
}

People Floor::popPeople() {
    People temp=GetElemAtIndex(1);
    this->DeleteElemAtHead();
    peopleNum--;
    return temp;
}



