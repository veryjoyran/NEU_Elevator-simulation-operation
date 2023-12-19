#include "elevator.h"
#include "floor.h"
#include "people.h"
#include "calling.h"
#include <iostream>
using namespace std;

void elevatorRun(Elevator elevator,Floor floor[14],Calling calling){
    
    while(1){
        int CurrentFloor=elevator.GetFloor();
        cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
        int direction=elevator.getDirection();
        if(direction==1){
            cout<<"当前电梯的方向为上"<<endl;
        }
        else if(direction==2){
            cout<<"当前电梯的方向为下"<<endl;
        }
        else{
            cout<<"当前电梯的为静止"<<endl;
        }
        
        for(int i=1;i<=14;i++){
        if(floor[i].getPeopleNum()!=0){
            calling.pushTargetFloor(i);
        }
    }
    calling.sortedTargetFloor(CurrentFloor,direction);
    cout<<"当前电梯的目标楼层为"<<calling.popTargetFloor()<<endl;
    calling.CallingTravel();
    int TargetFloor=calling.popTargetFloor();

    //电梯上升
    if(TargetFloor>CurrentFloor){
        for(int i=CurrentFloor;i<=TargetFloor;i++){
            elevator.SetFloor(i);
            cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
        }
        elevator.addPeople(floor[TargetFloor-1].popPeople(),elevator.GetTargetFloor());
        cout<<"当前电梯的人数为"<<elevator.GetPeopleNum()<<endl;
        for(int i=0;i<elevator.GetPeopleNum();i++){
            calling.pushTargetFloor(elevator.GetTargetFloor()[i].GetTargetFloor());
        }
        calling.sortedTargetFloor(CurrentFloor,direction);
        cout<<"当前电梯的目标楼层为"<<calling.popTargetFloor()<<endl;
        calling.CallingTravel();
    }
    //电梯下降
    else if(TargetFloor<CurrentFloor){
        for(int i=CurrentFloor;i>=TargetFloor;i--){
            elevator.SetFloor(i);
            cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
        }
        elevator.addPeople(floor[TargetFloor-1].popPeople(),elevator.GetTargetFloor());
        cout<<"当前电梯的人数为"<<elevator.GetPeopleNum()<<endl;
        for(int i=0;i<elevator.GetPeopleNum();i++){
            calling.pushTargetFloor(elevator.GetTargetFloor()[i].GetTargetFloor());
        }
        calling.sortedTargetFloor(CurrentFloor,direction);
        cout<<"当前电梯的目标楼层为"<<calling.popTargetFloor()<<endl;
        calling.CallingTravel();
    }
}  


}

int main(){
    Elevator elevator;
    Floor floor[14];
    Calling calling;

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
    
    elevatorRun(elevator,floor,calling);

    return 0;
}