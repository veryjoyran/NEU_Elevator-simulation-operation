#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
// 人的数据
typedef struct People {
	int aim;
	int startfloor;
};
// 电梯外呼叫的 队列
typedef struct Callingnode {
	People data;
	Callingnode* next;
};
typedef struct Calling {
	Callingnode* front;
	Callingnode* rear;
};

// 创建队列
Calling* initCalling();
// 入队
void EnCalling(int aim, int start, Calling* calls);
// 出队
void OutCalling(Calling* calls);
// 打印队内全部
void PrintCalling(Calling* calls);
// 获得呼叫数据 直到输入-1 -1 -1
void getInput();



// 电梯还没写好
typedef struct Elevator {
	int nowfloor;
	int* aimfloor;
	People* passengers;
	int state;//0,1,2
	int num;
};
Elevator initElevator();
void formElevator(Elevator* p, Calling* calls);




