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

void Floor::pushPeople(People people) {
    this->InsertElemAtEnd(people);
    peopleNum++;
}

void Floor::popPeople() {
    this->DeleteElemAtEnd();
    peopleNum--;
}
