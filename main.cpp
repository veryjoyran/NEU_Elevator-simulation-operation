#include "elevator.h"
#include "floor.h"
#include "people.h"
#include <iostream>
using namespace std;

void elevatorRun(Elevator elevator,Floor floor[14]){


}  

int main(){
    Elevator elevator;
    Floor floor[14];

    for(int i=0;i<14;i++){
        floor[i].SetFloorNum(i+1);
    }
    
    People people[5];
    people[0].SetTargetFloor(5);
    people[1].SetTargetFloor(3);
    people[2].SetTargetFloor(7);
    people[3].SetTargetFloor(9);
    people[4].SetTargetFloor(11);

    people[0].SetStartFloor(4);
    people[1].SetStartFloor(4);
    people[2].SetStartFloor(4);
    people[3].SetStartFloor(4);
    people[4].SetStartFloor(2);

    for(int i=0;i<5;i++){
        floor[people[i].GetStartFloor()-1].pushPeople(people[i]);
    }
     
    
    
    cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
    cout<<"当前电梯的状态为"<<elevator.GetState()<<endl;
    cout<<"当前电梯的人数为"<<elevator.GetPeopleNum()<<endl;
    cout<<"当前电梯的方向为"<<elevator.getDirection()<<endl;
    cout<<"当前电梯的目标楼层为"<<elevator.GetTargetFloor()[0].GetTargetFloor()<<endl;

    
    

    return 0;
}