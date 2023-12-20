#include "calling.h"


Calling::Calling() {
    TargetfloorNum = 0;
}

Calling::~Calling() {}

void Calling::pushTargetFloor(int Targetfloor) {
    this->InsertElemAtEnd(Targetfloor);
    TargetfloorNum++;
}

int Calling::getDataTargetFloor()
{
    return GetElemAtIndex(1);
}

int Calling::popTargetFloor() {
    int temp=GetElemAtIndex(1);
    this->DeleteElemAtHead();
    TargetfloorNum--;
    return temp;
}

void Calling::sortedTargetFloor(int currentFloor,int direction) {
    int temp;

    //在电梯上升的情况下，先将比当前楼层大的楼层按从小到大放在前面，再将比当前楼层小的楼层按从大到小放在后面
    if(direction==1){
        for(int i=1;i<TargetfloorNum;i++){
            for(int j=1;j<TargetfloorNum-i+1;j++){
                if(GetElemAtIndex(j)<GetElemAtIndex(j+1)){
                    temp=GetElemAtIndex(j);
                    this->SetElemAtIndex(j,GetElemAtIndex(j+1));
                    this->SetElemAtIndex(j+1,temp);
                }
            }
        }

        for(int i=1;i<TargetfloorNum;i++){
            for(int j=1;j<TargetfloorNum-i+1;j++){
                if(GetElemAtIndex(j)>currentFloor&&GetElemAtIndex(j+1)>currentFloor){
                    if(GetElemAtIndex(j)>GetElemAtIndex(j+1)){
                        temp=GetElemAtIndex(j);
                        this->SetElemAtIndex(j,GetElemAtIndex(j+1));
                        this->SetElemAtIndex(j+1,temp);
                    }
                }
            }
        }
    }

    //在电梯下降的情况下，先将比当前楼层小的楼层按从大到小放在前面，再将比当前楼层大的楼层按从小到大放在后面
    else if(direction==2){
        for(int i=1;i<TargetfloorNum;i++){
            for(int j=1;j<TargetfloorNum-i+1;j++){
                if(GetElemAtIndex(j)>GetElemAtIndex(j+1)){
                    temp=GetElemAtIndex(j);
                    this->SetElemAtIndex(j,GetElemAtIndex(j+1));
                    this->SetElemAtIndex(j+1,temp);
                }
            }
        }

        for(int i=1;i<TargetfloorNum;i++){
            for(int j=1;j<TargetfloorNum-i+1;j++){
                if(GetElemAtIndex(j)<currentFloor&&GetElemAtIndex(j+1)<currentFloor){
                    if(GetElemAtIndex(j)<GetElemAtIndex(j+1)){
                        temp=GetElemAtIndex(j);
                        this->SetElemAtIndex(j,GetElemAtIndex(j+1));
                        this->SetElemAtIndex(j+1,temp);
                    }
                }
            }
        }

    }
}

void Calling::CallingTravel() {
    this->TravalLinkList();
}

int Calling::GetTargetfloorNum() {
    return TargetfloorNum;
}

int Calling::CallingGetElemAtIndex(int index) {
    return this->GetElemAtIndex(index);
}

int Calling::GetMaxTargetFloor()
{
    int max=0;
    for(int i = 1; i <= TargetfloorNum; i++)
    {
        if(GetElemAtIndex(i)>max)
        {
            max=GetElemAtIndex(i);
        }
    }
    return max;

}

int Calling::GetMinTargetFloor()
{
    int min=14;
    for(int i = 1; i <= TargetfloorNum; i++)
    {
        if(GetElemAtIndex(i)<min)
        {
            min=GetElemAtIndex(i);
        }
    }
    return min;

}

/*
int main(){

    Calling calling;
    calling.pushTargetFloor(1);
    calling.pushTargetFloor(8);
    calling.pushTargetFloor(4);
    calling.pushTargetFloor(2);
    calling.pushTargetFloor(10);
    calling.CallingTravel();
    calling.sortedTargetFloor(5,2);
    calling.CallingTravel();



    return 0;
}
*/