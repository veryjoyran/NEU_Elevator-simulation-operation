#include <chrono>
#include <thread>
#include "elevator.h"
#include "floor.h"
#include "people.h"
#include "calling.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int elevatorRun(Elevator &elevator, Floor floor[14], Calling &calling)
{
    
    int flag = 0; //判断是否有人没上来
    //检查电梯状态
    int CurrentFloor = elevator.GetFloor();
    cout << "所在楼层为:" << elevator.GetFloor() << " ";
    int direction = elevator.getDirection(calling, CurrentFloor);

    //将calling中的楼层按照逻辑进行排序，并找到接下来需要去掉的楼层
    calling.sortedTargetFloor(CurrentFloor, direction);
    int TargetFloor = calling.getDataTargetFloor();
    cout << "目标楼层为:" << TargetFloor << " ";

    //电梯运行
    if(TargetFloor > CurrentFloor)
    {
        int state = elevator.GetState();
        elevator.SetState(state+1);
        state = elevator.GetState();
        if(state == 6)
        {
            elevator.SetState(state - 5);
            elevator.SetFloor(CurrentFloor+1);
        }
        else cout << "电梯上行中" << endl;
    }
    else if(TargetFloor < CurrentFloor)
    {
        int state = elevator.GetState();
        elevator.SetState(state-1);
        state = elevator.GetState();
        if(state == -6)
        {
            elevator.SetState(state + 5);
            elevator.SetFloor(CurrentFloor-1);
        }
        else cout << "电梯下行中" << endl;
    }
    else  //电梯到达，上下乘客，更新判断
    {
        calling.popTargetFloor();
        cout << "电梯到达，开门放人" << endl;
        CurrentFloor = elevator.GetFloor();
        //将电梯中的人员排序,为后续删除做准备
        elevator.sortedTargetFloor(CurrentFloor, direction, elevator.GetTargetFloor());
        //到达目标楼层后，将需要下楼的人员从电梯中删除
        for(int i = 0; i<elevator.GetPeopleNum(); i++)
        {
            if(elevator.GetTargetFloor()[i].GetTargetFloor() == CurrentFloor)
            {
                cout << elevator.GetTargetFloor()[i].GetId() << "下电梯" << endl;
                elevator.deletePeople(elevator.GetTargetFloor());
            }
        }
        //到达目标楼层后，将目标楼层的人员添加到电梯中
        while(elevator.GetPeopleNum() < MAXPEOPLE && floor[TargetFloor-1].getPeopleNum() != 0)
        {
            People temp = floor[TargetFloor-1].popPeople();
            string name = temp.GetId();
            
            cout << temp.GetId() << "上电梯" << endl;
            elevator.addPeople(temp, elevator.GetTargetFloor());
            //将刚上电梯的目标楼层添加到calling中
            calling.pushTargetFloor(temp.GetTargetFloor());
            
            
        }

        
        cout << "当前电梯的人数为" << elevator.GetPeopleNum() << endl;
        if(elevator.GetPeopleNum() == MAXPEOPLE && floor[TargetFloor-1].getPeopleNum() != 0)
        {
            cout << "电梯已满" << endl;
            flag = CurrentFloor;
        }
        
        direction=elevator.getDirection(calling, CurrentFloor);
        cout << "电梯的方向为排队第一个人按到的位置：" << direction << endl;
        //打印calling中的楼层
        //将calling中的楼层按照逻辑进行排序
        calling.sortedTargetFloor(CurrentFloor,direction);

        cout << "calling中的楼层为" << endl;
        if(calling.GetTargetfloorNum()!=0)
        {
            int i;
            for( i = 1; i<=calling.GetTargetfloorNum(); i++)
            {
                cout << calling.CallingGetElemAtIndex(i) << " ";
            }
            cout << endl;
        }

        //判断是否完成运行，防止引发数组越界以及空指针异常
        //检查是否所有人员都已经送达
        bool allDelivered=true;
        for(int i=0;i<14;i++)
        {
            if(calling.GetTargetfloorNum()!=0||elevator.GetPeopleNum()!=0) allDelivered=false;
        }
        if(allDelivered==true) 
        {
            cout << "操作已经完成" << endl;
            flag = -1;
        }
        else cout << "还有操作未完成" << endl;
    }

    return flag; //返回flag，判断是否需要继续运行 0表示正常运行，正数表示电梯已满需要其他电梯来相应，-1表示所有操作已完成
}  

void getPeopleFromfile(const string& filename, People* people) {
    
    ifstream file(filename);
    string line;
    int index = 0;

    if (!file.is_open()) {
        cout << "无法打开文件: " << filename << endl;
    }

    while (getline(file, line)) {
        if (index >= 100) {
            cout << "警告: 数据超出最大处理量 只处理前100条数据" << endl;
            break;
        }

        stringstream ss(line);
        string id, reachTime, targetFloor, startFloor;

        if (!(getline(ss, id, ' ') && 
              getline(ss, reachTime, ' ') &&
              getline(ss, targetFloor, ' ') && 
              getline(ss, startFloor)
              )
            ) 
        {
            cout << "数据格式错误: " << line << endl;
            continue; // 跳过这条数据，继续处理下一行
        }

        try {
            people[index].SetId(id);
            people[index].SetReachTime(stoi(reachTime));
            people[index].SetTargetFloor(stoi(targetFloor));
            people[index].SetStartFloor(stoi(startFloor));
        } catch (const exception& e) 
        {
            cout << "解析错误: " << line << " (" << e.what() << ")" << std::endl;
            continue; // 跳过这条数据，继续处理下一行
        }

        index++;
    }
    cout<<"读取文件成功"<<endl;
}

void getPeopleFromfloor(People* people, int time, int floor)
{
    int i = 0;
    while(people[i].GetId() != "\0")
    {
        i++;
    }
    people[i].SetId("null");
    people[i].SetReachTime(time);
    people[i].SetStartFloor(floor);
    if(floor != 6) people[i].SetTargetFloor(6);
    else people[i].SetTargetFloor(1);
}

void runComputing()
{
    //初始化电梯，楼层和calling
    Elevator elevator[4];
    Floor floor[14];
    Calling calling[4];

    for(int i=0;i<14;i++)
    {
        floor[i].SetFloorNum(i+1);
    }

    //读取文件,并将数据存入people数组中
    People* people = new People[100];
    cout<<"正在读取文件"<<endl;
    getPeopleFromfile("src/inputPeople.txt", people);
    cout<<"读取文件成功"<<endl;

    //按照时间进行运行
    int currentTime;
    int spareTime[4] = {0};
    for(currentTime = 0; currentTime < 10000; currentTime++)
    {
        int j = 0;
        People* temp = new People[100]; 
        for(int i=0; i<100; i++)
        {
            //将当前时间到达的人员添加到楼层中
            if(people[i].GetReachTime() == currentTime && people[i].GetStartFloor() != 0)
            {
                if(people[i].GetId() == "null")
                {
                    int peopleNum = floor[people[i].GetStartFloor()-1].getPeopleNum();
                    for(int i = 0; i < peopleNum; i++)
                    {
                        People tempPeople = floor[people[i].GetStartFloor()-1].popPeople();
                        temp[j] = tempPeople;
                        j++;
                        floor[people[i].GetStartFloor()-1].pushPeople(tempPeople);
                    }

                }
                else
                {
                    floor[people[i].GetStartFloor()-1].pushPeople(people[i]);
                    temp[j] = people[i];
                    j++;
                }
                
            }
            else
            {
                break;
            }
            
            
        }
        int aim[14] = {0};
        for(int l = 0; l < j; l++)
        {
            if( aim[temp[l].GetStartFloor()-1] == 0)
            {
                aim[temp[l].GetStartFloor()-1]++;
            }
            else
            {
                for(int i = l; i < j-1; i++)
                {
                    temp[i]=temp[i+1];
                }
                j--;
            }
        }
        int totalPeople = j;
        
        //将需要的响应传给calling
        for(int i = 0; i < totalPeople; i++)
        {
            //得到每个时间进行比较
            int waitingTime[4] = {280};
            for(int k = 0; k < 4; k++)
            {
                int flag = temp[i].GetTargetFloor() - temp[i].GetStartFloor();
                int ToptargetFloor = 0;
                int Edgefloor = 0;
                if( elevator[k].GetState() > 0)
                {
                    ToptargetFloor = calling[k].GetMaxTargetFloor();
                    Edgefloor = 1;
                }
                else
                {
                    ToptargetFloor = calling[k].GetMinTargetFloor();
                    Edgefloor = 14;
                }

                if( flag * elevator[k].GetState() > 0 && temp[i].GetStartFloor() > elevator[k].GetFloor())
                {
                    waitingTime[k] = 10 + abs(elevator[k].GetFloor()-temp[i].GetStartFloor()) * 5;
                }
                else if( flag * elevator[k].GetState() > 0 && temp[i].GetStartFloor() < elevator[k].GetFloor() )
                {
                    waitingTime[k] = 10 + (abs(elevator[k].GetFloor()-ToptargetFloor) + abs(ToptargetFloor-Edgefloor) + abs(Edgefloor - temp[i].GetStartFloor())) * 5;
                }
                else if( flag * elevator[k].GetState() < 0 )
                { 
                    waitingTime[k] = 10 + (abs(elevator[k].GetFloor()-ToptargetFloor) + abs(ToptargetFloor-temp[i].GetStartFloor())) * 5;
                }
                else if(flag * elevator[k].GetState() == 0)
                {
                    if(flag == 0)
                    {
                        cout << temp[i].GetId() <<" :不会按电梯就不要按" << endl;
                        j--;
                    }
                    else
                    {
                        waitingTime[k] = abs(elevator[k].GetFloor() - temp[i].GetStartFloor())*5;
                    }
                }
            }
            //找到最短等待时间的电梯
            //设置电梯的状态state
            int lesstime = 280;
            int answerElevator = 0;
            for(int i = 3; i >= 0 ; i--)
            {
                if(lesstime > waitingTime[i])
                {
                    lesstime = waitingTime[i];
                    answerElevator = i;
                }
            }
            calling[answerElevator].pushTargetFloor(temp[i].GetStartFloor());
            spareTime[answerElevator] = 0;
            //缓存操作？
        }

        for(int i = 0; i < 4; i++)
        {
            if(spareTime[i] >= 10)
            {
                calling[i].pushTargetFloor(1);
            }
        }
        
        int Listeningstate[4] = {0};
        for(int i = 0; i < 4; i++)
        {
            if(calling[i].GetTargetfloorNum() != 0)
            {
                Listeningstate[i] = elevatorRun(elevator[i], floor, calling[i]);
                if(Listeningstate[i] > 0 )
                {
                    getPeopleFromfloor(people, currentTime+1, Listeningstate[i]);
                    }
                else if(Listeningstate[i] == -1)
                {
                    spareTime[i]++;
                }
            }
        }
        
        
    
    }

}


int main(){
    runComputing();
    /*
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
    */

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