#include <chrono>
#include <thread>
#include "floor.h"
#include "elevator.h"
#include "people.h"
#include "calling.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
using namespace std;
//单部电梯运行逻辑
void singleElevatorRun(Elevator &elevator,Floor floor[14],Calling &calling){
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

         //将电梯中的人员排序,为后续删除做准备
        elevator.sortedTargetFloor(elevator.GetFloor(), direction, elevator.GetTargetFloor(), elevator.GetPeopleNum());
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
            //将电梯中的人员排序,为后续删除做准备
        elevator.sortedTargetFloor(elevator.GetFloor(), direction, elevator.GetTargetFloor(), elevator.GetPeopleNum());
        }
    }
    //电梯下降
    else if(TargetFloor<CurrentFloor){
        for(int i=CurrentFloor;i>=TargetFloor;i--){
            elevator.SetFloor(i);
            cout<<"当前电梯所在楼层为"<<elevator.GetFloor()<<endl;
        }
        CurrentFloor=elevator.GetFloor();
    
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

        //将电梯中的人员排序,为后续删除做准备
        elevator.sortedTargetFloor(elevator.GetFloor(), direction, elevator.GetTargetFloor(), elevator.GetPeopleNum());
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
//单部电梯运行
int elevatorRun(Elevator &elevator, Floor floor[14], Calling &calling, int num)
{
    ofstream outfile;
    outfile.open("src/outputPeople.txt", ios::app);
    if(!outfile)
    {
        cout << "打开文件失败" << endl;
        exit(1);
    }
    
    outfile << "电梯" << num;
    int flag = 0; //判断是否有人没上来
    //检查电梯状态
    int CurrentFloor = elevator.GetFloor();
    cout << "所在楼层为:" << elevator.GetFloor() << " ";
    outfile << "所在楼层为:" << elevator.GetFloor() << " ";
    int direction = elevator.getDirection(calling, CurrentFloor);

    //将calling中的楼层按照逻辑进行排序，并找到接下来需要去掉的楼层
    calling.sortedTargetFloor(CurrentFloor, direction);
    int TargetFloor = calling.getDataTargetFloor();
    cout << "目标楼层为:" << TargetFloor << " ";
    outfile << "目标楼层为:" << TargetFloor << " ";

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
        cout << "电梯上行中" << endl;
        outfile << "电梯上行中" << endl;
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
        cout << "电梯下行中" << endl;
        outfile << "电梯下行中" << endl;
    }
    else  //电梯到达，上下乘客，更新判断
    {
        elevator.SetState(0);
        int calling_num = calling.GetTargetfloorNum();
        for(int i = 1; i <= calling_num; i++)
        {
            if(calling.CallingGetElemAtIndex(1) == TargetFloor)
            {
                calling.popTargetFloor();
            }
        }

        cout << "电梯到达，开门放人" << endl;
        outfile << "电梯到达，开门放人" << endl;
        CurrentFloor = elevator.GetFloor();
        
        //到达目标楼层后，将需要下楼的人员从电梯中删除
        int people_num = elevator.GetPeopleNum();
        for(int i = 0; i < people_num ; i++)
        {
            if(elevator.GetTargetFloor()[0].GetTargetFloor() == CurrentFloor)
            {
                cout << elevator.GetTargetFloor()[0].GetId() << "下电梯" << endl;
                outfile << elevator.GetTargetFloor()[0].GetId() << "下电梯" << endl;
                elevator.deletePeople(elevator.GetTargetFloor());
            }
        }
        //到达目标楼层后，将目标楼层的人员添加到电梯中
        while(elevator.GetPeopleNum() < MAXPEOPLE && floor[TargetFloor-1].getPeopleNum() != 0)
        {
            People temp = floor[TargetFloor-1].popPeople();
            string name = temp.GetId();
            
            cout << temp.GetId() << "上电梯" << endl;
            outfile << temp.GetId() << "上电梯" << endl;
            elevator.addPeople(temp, elevator.GetTargetFloor());
            //将刚上电梯的目标楼层添加到calling中
            calling.pushTargetFloor(temp.GetTargetFloor());
            
            
        }

        

        //在此处之前完成开关门的操作
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
            outfile << "操作已经完成" << endl;
            flag = -1;
        }
        else
        {
            cout << "还有操作未完成" << endl;
            outfile << "还有操作未完成" << endl;
            elevator.sortedTargetFloor(elevator.GetFloor(), elevator.getDirection(calling,elevator.GetFloor()), elevator.GetTargetFloor(), elevator.GetPeopleNum());
        
            cout << "当前电梯的人数为" << elevator.GetPeopleNum() << endl;
            outfile << "当前电梯的人数为" << elevator.GetPeopleNum() << endl;
            //当前电梯中的人员的目标楼层为
            for(int i = 0; i < elevator.GetPeopleNum(); i++)
            {
                cout << elevator.GetTargetFloor()[i].GetTargetFloor() << " ";
                outfile << elevator.GetTargetFloor()[i].GetTargetFloor() << " ";
            }

            if(elevator.GetPeopleNum() == MAXPEOPLE && floor[TargetFloor-1].getPeopleNum() != 0)
            {
                cout << "电梯已满" << endl;
                outfile << "电梯已满" << endl;
                for(int i = 0; i < floor[TargetFloor-1].getPeopleNum(); i++)
                {
                    People temp = floor[TargetFloor-1].popPeople();
                    cout << temp.GetId() << "等待" << endl;
                    outfile << temp.GetId() << "等待" << endl;
                    temp.SetReachTime(temp.GetReachTime()+1);
                    floor[TargetFloor-1].pushPeople(temp);
                    flag = TargetFloor;
                }
            }
            
            direction=elevator.getDirection(calling, CurrentFloor);
            cout << "电梯的方向为排队第一个人按到的位置：" << direction << endl;
            outfile << "电梯的方向为排队第一个人按到的位置：" << direction << endl;
            elevator.SetState(direction);
            //打印calling中的楼层
            //将calling中的楼层按照逻辑进行排序
            calling.sortedTargetFloor(CurrentFloor,direction);

            cout << "calling中的楼层为" << endl;
            outfile << "calling中的楼层为" << endl;
            if(calling.GetTargetfloorNum()!=0)
            {
                int i;
                for( i = 1; i<=calling.GetTargetfloorNum(); i++)
                {
                    cout << calling.CallingGetElemAtIndex(i) << " ";
                    outfile << calling.CallingGetElemAtIndex(i) << " ";
                }
                cout << endl;
            }

        } 
        

        
    }

    return flag; //返回flag，判断是否需要继续运行 0表示正常运行，正数表示电梯已满需要其他电梯来相应，-1表示所有操作已完成
}  
//从文件中读取人员
void getPeopleFromfile(const string& filename, People* people) 
{
    cout<<"正在读取文件"<<endl;

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
//从超员楼层中获取人员
void getPeopleFromfloor(People* people, int time, int floor)
{
    int i = 0;
    while(people[i].GetStartFloor() != 0)
    {
        i++;
    }
    people[i].SetId("null");
    people[i].SetReachTime(time);
    people[i].SetStartFloor(floor);
    if(floor != 6) people[i].SetTargetFloor(6);
    else people[i].SetTargetFloor(1);
}
//从输入中获取人员
void getPeopleFromInputSingal(People* people, string name, int time, int startFloor, int targetFloor)
{
    int i = 0;
    while(people[i].GetStartFloor() != 0)
    {
        i++;
    }
    people[i].SetId(name);
    people[i].SetReachTime(time);
    people[i].SetStartFloor(startFloor);
    people[i].SetTargetFloor(targetFloor);

    cout << "姓名：" << people[i].GetId() << endl;
    cout << "到达时间：" << people[i].GetReachTime() << endl;
    cout << "起始楼层：" << people[i].GetStartFloor() << endl;
    cout << "目标楼层：" << people[i].GetTargetFloor() << endl;
}

void getPeopleFromInput(People* people)
{
    cout << "请输入人员数量: " << endl;
    int num;
    cin >> num;
    for(int i = 0; i < num; i++)
    {
        string name;
        int time;
        int startFloor;
        int targetFloor;
        cout << "请输入姓名：";
        cin >> name;
        cout << "请输入到达时间：";
        cin >> time;
        cout << "请输入起始楼层：";
        cin >> startFloor;
        cout << "请输入目标楼层：";
        cin >> targetFloor;
        getPeopleFromInputSingal(people, name, time, startFloor, targetFloor);
    }
    
}
//从随机数中获取人员
void getPeopleFromRandom(People* people)
{
    srand((unsigned)time(NULL));
    int num = rand()%20;
    for(int i = 0; i < num; i++)
    {
        int time = rand()%50;
        int startFloor = rand()%14+1;
        int targetFloor = rand()%14+1;
        while(targetFloor == startFloor)
        {
            targetFloor = rand()%14+1;
        }
        string name = "random" + to_string(i);
        getPeopleFromInputSingal(people, name, time, startFloor, targetFloor);
    }
}
//电梯运行
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

    //并将数据存入people数组中
    People* people = new People[100];
    

    //从文件中读取数据
    //getPeopleFromfile("src/inputPeople.txt", people);

    //从输入中读取数据
    //getPeopleFromInput(people);

    //从随机数读取数据
    getPeopleFromRandom(people);

    //将数据记录写入文件
    std::ofstream outfile("src/outputPeople.txt");

    if (!outfile.is_open()) {
        std::cerr << "无法打开文件!" << std::endl;
        exit(1);
    }

    outfile << "电梯系统开始运行" << std::endl;
    outfile.close(); 

    outfile.open("src/outputPeople.txt", std::ios::app);

    if (!outfile.is_open()) {
        std::cerr << "无法再次打开文件!" << std::endl;
        exit(1);
    }


    //按照时间进行运行
    int currentTime;
    int spareTime[4] = {0, 0, 0, 0};
    for(currentTime = 1; currentTime < 10000; currentTime++)
    {
        int j = 0;
        int rest = 0;
        for(int i = 0; i < 100; i++)
        {
            if(people[i].GetReachTime() >= currentTime )
            {
                rest++;
            }
        }

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
                continue;
            }
            
            
        }
        //去除重复的楼层
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
                l--;
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
                else if( elevator[k].GetState() != 0 && temp[i].GetStartFloor() == elevator[k].GetFloor() )
                {
                    waitingTime[k] = abs(elevator[k].GetFloor()-ToptargetFloor) * 10;
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
                        outfile << temp[i].GetId() <<" :不会按电梯就不要按" << endl;
                        j--;
                    }
                    else
                    {
                        waitingTime[k] = abs(elevator[k].GetFloor() - temp[i].GetStartFloor())*5;
                    }
                }
            }
            //找到最短等待时间的电梯
            
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
            //设置电梯的状态state
            spareTime[answerElevator] = 0;
            int elevatorState = 0;
            if(temp[i].GetTargetFloor() - temp[i].GetStartFloor() > 0) elevatorState = 1;
            else elevatorState = -1;
            elevator[answerElevator].SetState(elevatorState);
            //缓存操作？
        }

        for(int i = 0; i < 4; i++)
        {
            if(spareTime[i] >= 10)
            {
                calling[i].pushTargetFloor(1);
                spareTime[i] = 0;
            }
        }
        cout << "当前时间为：" << currentTime << endl;
        outfile << "当前时间为：" << currentTime << endl;
        int Listeningstate[4] = {0, 0, 0, 0};
        int elevatorState[4] = {1, 1, 1, 1};
        for(int i = 0; i < 4; i++)
        {
            cout << "电梯" << i+1 << "状态： ";
            if(calling[i].GetTargetfloorNum() != 0)
            {
                
                Listeningstate[i] = elevatorRun(elevator[i], floor, calling[i], i+1);
                if(Listeningstate[i] > 0)
                {
                    cout << "电梯" << i+1 << "已满，需要其他电梯响应" << endl;
                    outfile << "电梯" << i+1 << "已满，需要其他电梯响应" << endl;
                    getPeopleFromfloor(people, currentTime+1, Listeningstate[i]);
                    
                }
                else if(Listeningstate[i] == -1)
                {
                    spareTime[i]++;
                    cout << "电梯" << i+1 << "在第" << elevator[i].GetFloor() << "层空闲" << spareTime[i] << "秒" << endl;
                    outfile << "电梯" << i+1 << "在第" << elevator[i].GetFloor() << "层空闲" << spareTime[i] << "秒" << endl;
                }
            }
            else
            {
                if(elevator[i].GetFloor() !=1 )
                {
                    spareTime[i]++;
                    cout << "电梯" << i+1 << "在第" << elevator[i].GetFloor() << "层空闲" << spareTime[i] << "秒" << endl;
                    outfile << "电梯" << i+1 << "在第" << elevator[i].GetFloor() << "层空闲" << spareTime[i] << "秒" << endl;
                }
                else
                {
                    cout << "电梯" << i+1 << "空闲" << endl;
                    outfile << "电梯" << i+1 << "空闲" << endl;
                    elevatorState[i] = 0;
                }
                
            }
            
        }
    //每1s执行一次    
    //sleep(1);
    
    int end = elevatorState[0] + elevatorState[1] + elevatorState[2] + elevatorState[3] + rest;
    if(end) continue;
    else
    {
        cout << "所有电梯空闲" << endl;
        cout << "运行时长为：" << currentTime << endl;
        int i = 0;
        while(people[i].GetStartFloor() != 0 && people[i].GetId() != "null")
        {
            i++;
        }

        cout << "运行时长为：" << currentTime << endl;
        outfile << "运行时长为：" << currentTime << endl;
        cout << "总人次数为：" << i << endl;
        outfile << "总人次数为：" << i << endl;
        break;
    }
        
    }

}

//单部电梯测试主函数
void TestSingleElevatorRun(){
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
    singleElevatorRun(elevator,floor,calling);
}
//链表测试函数

void TestList_Basic()
{
    LinkList<int> l;
    int i;
    cout << "1.创建单链表   2.遍历单链表   3.获取单链表的长度   4.判断单链表是否为空   5.获取节点\n";
    cout << "6.在尾部插入指定元素   7.在指定位置插入指定元素   8.在头部插入指定元素\n";
    cout<<"9.在尾部删除元素   10.删除所有元素   11.删除指定元素   12.在头部删除元素  13.获取指定下标的数据  14. 设置指定下标的数据 0.退出" << endl;
    do
    {
        cout << "请输入要执行的操作: ";
        cin >> i;
        switch (i)
        {
        case 1:
            int n;
            cout << "请输入单链表的长度: ";
            cin >> n;
            l.CreateLinkList(n);
            break;
        case 2:
            l.TravalLinkList();
            break;
        case 3:
            cout << "该单链表的长度为" << l.GetLength() << endl;
            break;
        case 4:
            if (l.IsEmpty() == 1)
                cout << "该单链表是空表" << endl;
            else
            {
                cout << "该单链表不是空表" << endl;
            }
            break;
        case 5:
            int data;
            cout << "请输入要获取节点: ";
            cin >> data;
            cout << "该节点的位置为" << l.FindNodePosition(data) << endl;
            break;
        case 6:
            int endData;
            cout << "请输入要在尾部插入的值: ";
            cin >> endData;
            l.InsertElemAtEnd(endData);
            break;
        case 7:
            int pointData;
            int index;
            cout << "请输入要插入的数据: ";
            cin >> pointData;
            cout << "请输入要插入数据的位置: ";
            cin >> index;
            l.InsertElemAtIndex(pointData, index);
            break;
        case 8:
            int headData;
            cout << "请输入要在头部插入的值: ";
            cin >> headData;
            l.InsertElemAtHead(headData);
            break;
        case 9:
            l.DeleteElemAtEnd();
            break;
        case 10:
            l.DeleteAll();
            break;
        case 11:
            int pointDeleteData;
            cout << "请输入要删除的数据: ";
            cin >> pointDeleteData;
            l.DeleteElemAtPoint(pointDeleteData);
            break;
        case 12:
            l.DeleteElemAtHead();
            break;
        case 13:
            int indexData;
            cout << "请输入要获取的下标: ";
            cin >> indexData;
            cout << "该下标的数据为" << l.GetElemAtIndex(indexData) << endl;
            break;
        case 14:
            int indexSetData;
            int setData;
            cout << "请输入要设置的下标: ";
            cin >> indexSetData;
            cout << "请输入要设置的数据: ";
            cin >> setData;
            l.SetElemAtIndex(indexSetData,setData);
            break;
        default:
            break;
        }
    }while (i != 0);
 
    system("pause");
}

//calling测试函数
void TestCalling(){

    Calling calling;
    calling.pushTargetFloor(1);
    calling.pushTargetFloor(8);
    calling.pushTargetFloor(4);
    calling.pushTargetFloor(2);
    calling.pushTargetFloor(10);
    cout<<"calling中的楼层为"<<endl;
    calling.CallingTravel();
    cout<<"排序后的calling中的楼层为"<<endl;
    calling.sortedTargetFloor(5,2);
    calling.CallingTravel();
    cout<<"删除第一个数据后calling中的楼层为"<<endl;
    calling.popTargetFloor();
    calling.CallingTravel();
}


//主程序
int main(){
    cout<<"欢迎使用电梯系统"<<endl;
    cout<<"请选择测试内容"<<endl;
    cout<<"1.电梯运行测试"<<endl;
    cout<<"2.单电梯运行测试"<<endl;
    cout<<"3.链表测试"<<endl;
    cout<<"4.Calling测试"<<endl;
    cout<<""<<endl;
    int i;
    cin>>i;
    switch(i){
        case 1:
            runComputing();
            break;
        case 2:
            TestSingleElevatorRun();
            break;
        case 3:
            TestList_Basic();
            break;
        case 4:
            TestCalling();
            break;
        default:
            break;
    }

    return 0;
}
