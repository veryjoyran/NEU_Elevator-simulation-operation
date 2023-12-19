#include "elevator.h"
using namespace std;

Elevator::Elevator() {
    TargetFloor[14];
    peopleNum = 0;
    state = 0;
    currentFloor=1;
    direction=1;
}

Elevator::~Elevator() {}

void Elevator::SetFloor(int floor) {
    this->currentFloor = floor;
}

int Elevator::GetFloor() {
    return currentFloor;
}

void Elevator::SetState(int state) {
    this->state = state;
}

int Elevator::GetState() {
    return state;
}

void Elevator::SetPeopleNum(int peopleNum) {
    this->peopleNum = peopleNum;
}

int Elevator::GetPeopleNum() {
    return peopleNum;
}

People *Elevator::GetTargetFloor() {
    return TargetFloor;
}

void Elevator::addPeople(People people,People* TargetFloor) {
    TargetFloor[peopleNum]=people;
    peopleNum++;
}

void Elevator::deletePeople(People* TargetFloor) {
    for(int i=0;i<peopleNum-1;i++){
        TargetFloor[i]=TargetFloor[i+1];
    }
    peopleNum--;
}

int Elevator::getDirection() {
    if(currentFloor>TargetFloor[0].GetTargetFloor()){
        return 2;
    }
    else if(currentFloor<TargetFloor[0].GetTargetFloor()){
        return 1;
    }
    else{
        return 0;
    }
}

void Elevator::setDirection(int direction) {
    this->direction=100;
}

void Elevator::sortedTargetFloor(int currentFloor,int direction,People* TargetFloor) {
    People temp;

    //在电梯上升的情况下，先将比当前楼层大的楼层按从小到大放在前面，再将比当前楼层小的楼层按从大到小放在后面
    if(direction==1){
        for(int i=0;i<peopleNum-1;i++){
            for(int j=0;j<peopleNum-1-i;j++){
                if(TargetFloor[j].GetTargetFloor()<TargetFloor[j+1].GetTargetFloor()){
                    temp=TargetFloor[j];
                    TargetFloor[j]=TargetFloor[j+1];
                    TargetFloor[j+1]=temp;
                }
            }
        }
        for(int i=0;i<peopleNum-1;i++){
            for(int j=0;j<peopleNum-1-i;j++){
                if(TargetFloor[j].GetTargetFloor()>currentFloor){
                    if(TargetFloor[j].GetTargetFloor()>TargetFloor[j+1].GetTargetFloor()){
                        temp=TargetFloor[j];
                        TargetFloor[j]=TargetFloor[j+1];
                        TargetFloor[j+1]=temp;
                    }
                }
            }
        }
    }

    //在电梯下降的情况下，先将比当前楼层小的楼层按从大到小放在前面，再将比当前楼层大的楼层按从小到大放在后面
    else if(direction==2){
        for(int i=0;i<peopleNum-1;i++){
            for(int j=0;j<peopleNum-1-i;j++){
                if(TargetFloor[j].GetTargetFloor()>TargetFloor[j+1].GetTargetFloor()){
                    temp=TargetFloor[j];
                    TargetFloor[j]=TargetFloor[j+1];
                    TargetFloor[j+1]=temp;
                }
            }
        }
        for(int i=0;i<peopleNum-1;i++){
            for(int j=0;j<peopleNum-1-i;j++){
                if(TargetFloor[j].GetTargetFloor()<currentFloor){
                    if(TargetFloor[j].GetTargetFloor()<TargetFloor[j+1].GetTargetFloor()){
                        temp=TargetFloor[j];
                        TargetFloor[j]=TargetFloor[j+1];
                        TargetFloor[j+1]=temp;
                    }
                }
            }
        }
    }

}

