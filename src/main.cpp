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
    while(1){
        
        //检查电梯状态
        int CurrentFloor=elevator.GetFloor();
        cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
        int direction=elevator.getDirection(calling,CurrentFloor);
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
    int TargetFloor=calling.popTargetFloor();
    cout<<"当前电梯的目标楼层为"<<TargetFloor<<endl;


    //电梯上升
    if(TargetFloor>CurrentFloor){
        for(int i=CurrentFloor;i<=TargetFloor;i++){
            elevator.SetFloor(i);
            cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
        }
        CurrentFloor=elevator.GetFloor();
        //将电梯中的人员排序,为后续删除做准备
        elevator.sortedTargetFloor(CurrentFloor,direction,elevator.GetTargetFloor());
        //到达目标楼层后，将需要下楼的人员从电梯中删除
        for(int i=0;i<elevator.GetPeopleNum();i++){
            if(elevator.GetTargetFloor()[i].GetTargetFloor()==CurrentFloor){
                elevator.deletePeople(elevator.GetTargetFloor());
            }
        }
        //到达目标楼层后，将目标楼层的人员添加到电梯中
        while(elevator.GetPeopleNum()<MAXPEOPLE&&floor[TargetFloor-1].getPeopleNum()!=0){
            elevator.addPeople(floor[TargetFloor-1].popPeople(),elevator.GetTargetFloor());
        }

        cout<<"当前电梯的人数为"<<elevator.GetPeopleNum()<<endl;

        //判断是否完成运行，防止引发数组越界以及空指针异常
        //检查是否所有人员都已经送达
    allDelivered=true;
    for(int i=0;i<14;i++){
        if(floor[i].getPeopleNum()!=0||elevator.GetPeopleNum()!=0){
            allDelivered=false;
        }
    }
    if(allDelivered==true){
        break;
    }


        if(elevator.GetPeopleNum()!=0){
            //将电梯中的人员的目标楼层添加到calling中
            for(int i=0;i<elevator.GetPeopleNum();i++){
                bool flag=true;
                for(int j=1;j<=calling.GetTargetfloorNum();j++){
                    if(calling.CallingGetElemAtIndex(j)==elevator.GetTargetFloor()[i].GetTargetFloor()){
                        flag=false;
                    }
                }
                if(flag==true){
                    calling.pushTargetFloor(elevator.GetTargetFloor()[i].GetTargetFloor());
                }
            }
        }
        //焯当前的方向
        direction=elevator.getDirection(calling,CurrentFloor);
        cout<<"chao当前电梯的方向为"<<direction<<endl;
        //打印calling中的楼层
        //将calling中的楼层按照逻辑进行排序，并准备进入下一次循环
        calling.sortedTargetFloor(CurrentFloor,direction);
        
     
        cout<<"calling中的楼层为"<<endl;
        if(calling.GetTargetfloorNum()!=0){
            for(int i=1;i<=calling.GetTargetfloorNum();i++){
                cout<<calling.CallingGetElemAtIndex(i)<<endl;
            }
        }
    }
    //电梯下降
    else if(TargetFloor<CurrentFloor){
        for(int i=CurrentFloor;i>=TargetFloor;i--){
            elevator.SetFloor(i);
            cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
        }
        CurrentFloor=elevator.GetFloor();
        //将电梯中的人员排序,为后续删除做准备
        elevator.sortedTargetFloor(CurrentFloor,direction,elevator.GetTargetFloor());
        //到达目标楼层后，将需要下楼的人员从电梯中删除
        for(int i=0;i<elevator.GetPeopleNum();i++){
            if(elevator.GetTargetFloor()[i].GetTargetFloor()==CurrentFloor){
                elevator.deletePeople(elevator.GetTargetFloor());
            }
        }
        //到达目标楼层后，将目标楼层的人员添加到电梯中
        while(elevator.GetPeopleNum()<MAXPEOPLE&&floor[TargetFloor-1].getPeopleNum()!=0){
            elevator.addPeople(floor[TargetFloor-1].popPeople(),elevator.GetTargetFloor());
        }

        cout<<"当前电梯的人数为"<<elevator.GetPeopleNum()<<endl;
        
        //判断是否完成运行，防止引发数组越界以及空指针异常
        //检查是否所有人员都已经送达
    allDelivered=true;
    for(int i=0;i<14;i++){
        if(floor[i].getPeopleNum()!=0||elevator.GetPeopleNum()!=0){
            allDelivered=false;
        }
    }
    if(allDelivered==true){
        break;
    }



        //将电梯中的人员的目标楼层添加到calling中
        if(elevator.GetPeopleNum()!=0){
            for(int i=0;i<elevator.GetPeopleNum();i++){
                bool flag=true;
                for(int j=1;j<=calling.GetTargetfloorNum();j++){
                    if(calling.CallingGetElemAtIndex(j)==elevator.GetTargetFloor()[i].GetTargetFloor()){
                        flag=false;
                    }
                }
                if(flag==true){
                    calling.pushTargetFloor(elevator.GetTargetFloor()[i].GetTargetFloor());
                }
            }
        }
        
        //焯当前的方向
        direction=elevator.getDirection(calling,CurrentFloor);
        cout<<"chao当前电梯的方向为"<<direction<<endl;
        //打印calling中的楼层
        //将calling中的楼层按照逻辑进行排序，并准备进入下一次循环
        calling.sortedTargetFloor(CurrentFloor,direction);
        
     
        cout<<"calling中的楼层为"<< endl;
        if(calling.GetTargetfloorNum()!=0){
            for(int i=1;i<=calling.GetTargetfloorNum();i++){
                cout<<calling.CallingGetElemAtIndex(i)<<endl;
            }
        }
    }
   
    
    }
    cout<<"所有人员已经送达"<<endl;
     //std::this_thread::sleep_for(std::chrono::seconds(5));
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
    int CurrentFloor=elevator.GetFloor();
    cout<<"方向为"<<elevator.getDirection(calling,CurrentFloor)<<endl;
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