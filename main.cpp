#include <chrono>
#include <thread>
#include "elevator.h"
#include "floor.h"
#include "people.h"
#include "calling.h"
#include <iostream>
using namespace std;

void elevatorRun(Elevator &elevator,Floor floor[14],Calling &calling){
    bool allDelivered = false; // 用于检查所有乘客是否送达
    cout<<"方向为"<<elevator.getDirection()<<endl;
    while(1){
        
        //检查电梯状
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

    
    
    //将calling中的楼层按照逻辑进行排序，并找到接下来需要去掉的楼层
    calling.sortedTargetFloor(CurrentFloor,direction);
    cout<<"当前电梯的目标楼层为"<<calling.popTargetFloor()<<endl;
    int TargetFloor=calling.popTargetFloor();

    //电梯上升
    if(TargetFloor>CurrentFloor){
        for(int i=CurrentFloor;i<=TargetFloor;i++){
            elevator.SetFloor(i);
            cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
        }
        //到达目标楼层后，将目标楼层的人员添加到电梯中
        elevator.addPeople(floor[TargetFloor-1].popPeople(),elevator.GetTargetFloor());
        cout<<"当前电梯的人数为"<<elevator.GetPeopleNum()<<endl;
        //将电梯中的人员的目标楼层添加到calling中
        for(int i=0;i<elevator.GetPeopleNum();i++){
            calling.pushTargetFloor(elevator.GetTargetFloor()[i].GetTargetFloor());
        }
        //将calling中的楼层按照逻辑进行排序，并准备进入下一次循环
        calling.sortedTargetFloor(CurrentFloor,direction);
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

    }

    // 检查是否所有乘客都到达目的地
        allDelivered = true; // 假设所有乘客都送达
        for (int i = 0; i < 14; i++) {
            if (floor[i].getPeopleNum()!=0) { // 假设 Floor 类有一个检查是否为空的方法
                allDelivered = false; // 如果任何楼层仍有乘客，继续循环
                break;
            }
        }
    std::this_thread::sleep_for(std::chrono::seconds(5));
}  


}

int main(){
    Elevator elevator;
    Floor floor[14];
    Calling calling;

    for(int i=0;i<14;i++){
        floor[i].SetFloorNum(i+1);
    }
    //初始化人员
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
    //初始化楼层
    for(int i=0;i<5;i++){
        floor[people[i].GetStartFloor()-1].pushPeople(people[i]);
    }

    //将需要响应的楼层传给calling
    for(int i=0;i<14;i++){
        if(floor[i].getPeopleNum()!=0){
            calling.pushTargetFloor(i+1);
        }
    }
    elevator.setDirection(100);
    cout<<"方向为"<<elevator.getDirection()<<endl;
    //电梯运行逻辑
    elevatorRun(elevator,floor,calling);

    return 0;
}

/*
        //将需要响应的楼层传给calling
        for(int i=0;i<14;i++){
        bool flag=true;
        if(floor[i].getPeopleNum()!=0){
            for(int j=0;j<calling.GetTargetfloorNum();j++){
                if(calling.GetElemAtIndex(j)==i+1){
                    flag=false;
                }
            }
            if(flag==true){
                calling.pushTargetFloor(i);
            }
            
        }
    }
*/