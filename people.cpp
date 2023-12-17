#include "people.h"
using namespace std;

People::People(string id, int ReachTime) : id(id), ReachTime(ReachTime) {}

People::~People() {}

string People::GetId() {
    return id;
}

int People::GetReachTime() {
    return ReachTime;
}

void People::SetId(string id) {
    this->id = id;
}

void People::SetReachTime(int ReachTime) {
    this->ReachTime = ReachTime;
}

void People::SetTargetFloor(int TargetFloor) {
    this->TargetFloor = TargetFloor;
}

int People::GetTargetFloor() {
    return TargetFloor;
}

void People::SetStartFloor(int StartFloor) {
    this->StartFloor = StartFloor;
}

int People::GetStartFloor() {
    return StartFloor;
}


